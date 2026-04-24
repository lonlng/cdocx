#!/usr/bin/env python3
"""
Docx Template Analyzer for CDocx
================================

Analyzes a Word .docx file and extracts all template-replaceable elements:
  - {{placeholder}} text markers
  - Word bookmarks
  - MERGEFIELD fields

Generates a ready-to-compile C++17 source file that opens the template,
fills all detected elements using cdocx::TemplateEngine, and saves the result.

Usage:
    python analyze_template.py template.docx -o fill_template.cpp
    python analyze_template.py template.docx          # writes to stdout
"""

import argparse
import os
import re
import sys
import zipfile
from xml.etree import ElementTree as ET

# WordprocessingML namespace
NS_W = "http://schemas.openxmlformats.org/wordprocessingml/2006/main"
ET.register_namespace("w", NS_W)


def qname(tag: str) -> str:
    """Build a namespaced tag like {NS}tag."""
    return f"{{{NS_W}}}{tag}"


class TemplateElement:
    """A single detected template element."""

    def __init__(self, kind: str, name: str, source: str, context: str = ""):
        self.kind = kind          # 'placeholder' | 'bookmark' | 'mergefield'
        self.name = name
        self.source = source      # e.g. 'word/document.xml'
        self.context = context    # surrounding text for context

    def cpp_name(self, seen: set = None) -> str:
        """Return a valid C++ identifier derived from the element name."""
        raw = self.name.strip()
        raw = raw.replace("{{", "").replace("}}", "")
        raw = re.sub(r"[^a-zA-Z0-9_]", "_", raw)
        if raw and raw[0].isdigit():
            raw = "_" + raw
        raw = raw or "unnamed"
        if seen is not None:
            base = raw
            counter = 2
            while raw in seen:
                raw = f"{base}_{counter}"
                counter += 1
            seen.add(raw)
        return raw

    def cpp_value_literal(self) -> str:
        """Return a C++ string literal, escaping quotes and backslashes."""
        s = self.name.replace("\\", "\\\\").replace('"', '\\"')
        return f'"{s}"'

    def __repr__(self) -> str:
        return f"{self.kind}:{self.name}"


def iter_text_in_element(element: ET.Element) -> str:
    """Concatenate all w:t text inside an element, preserving order."""
    parts = []
    for t in element.iter(qname("t")):
        if t.text:
            parts.append(t.text)
    return "".join(parts)


def extract_placeholders(text: str, prefix: str = "{{", suffix: str = "}}") -> list:
    """Find all placeholder keys inside text."""
    pattern = re.escape(prefix) + r"(.*?)" + re.escape(suffix)
    return re.findall(pattern, text)


def parse_docx(docx_path: str) -> list:
    """Open a .docx and return a list of TemplateElement objects."""
    elements = []

    if not zipfile.is_zipfile(docx_path):
        print(f"Error: '{docx_path}' is not a valid .docx (ZIP) file.", file=sys.stderr)
        sys.exit(1)

    with zipfile.ZipFile(docx_path, "r") as zf:
        content_parts = []
        for name in zf.namelist():
            if name.endswith(".xml") or name.endswith(".rels"):
                if any(
                    name.startswith(p)
                    for p in (
                        "word/document",
                        "word/header",
                        "word/footer",
                        "word/endnotes",
                        "word/footnotes",
                        "word/comments",
                    )
                ):
                    content_parts.append(name)

        for part in content_parts:
            try:
                xml_bytes = zf.read(part)
            except KeyError:
                continue

            try:
                root = ET.fromstring(xml_bytes)
            except ET.ParseError as e:
                print(f"Warning: could not parse {part}: {e}", file=sys.stderr)
                continue

            # Bookmarks
            for bm_start in root.iter(qname("bookmarkStart")):
                name = bm_start.get(qname("name"))
                if name:
                    ctx = ""
                    parent_para = bm_start
                    while parent_para is not None:
                        if parent_para.tag == qname("p"):
                            ctx = iter_text_in_element(parent_para)[:80]
                            break
                        parent_para = parent_para.find("..")
                    elements.append(
                        TemplateElement("bookmark", name, part, ctx)
                    )

            # Placeholders inside w:t text nodes
            for para in root.iter(qname("p")):
                para_text = iter_text_in_element(para)
                if not para_text:
                    continue
                for key in extract_placeholders(para_text):
                    elements.append(
                        TemplateElement("placeholder", key, part, para_text[:80])
                    )

            # MERGEFIELD / other fields
            for instr in root.iter(qname("instrText")):
                if instr.text:
                    code = instr.text.strip()
                    m = re.match(r"MERGEFIELD\s+(\S+)", code, re.IGNORECASE)
                    if m:
                        field_name = m.group(1)
                        ctx = ""
                        parent_para = instr
                        while parent_para is not None:
                            if parent_para.tag == qname("p"):
                                ctx = iter_text_in_element(parent_para)[:80]
                                break
                            parent_para = parent_para.find("..")
                        elements.append(
                            TemplateElement("mergefield", field_name, part, ctx)
                        )

    # Deduplicate by (kind, name) keeping first source
    seen = set()
    deduped = []
    for el in elements:
        key = (el.kind, el.name)
        if key not in seen:
            seen.add(key)
            deduped.append(el)

    # Filter out internal Word bookmarks
    internal_bookmarks = {"_goback"}
    deduped = [
        el for el in deduped
        if not (el.kind == "bookmark" and el.name.lower() in internal_bookmarks)
    ]

    return deduped


def escape_cpp_string(s: str) -> str:
    """Escape a string for use as a C++ string literal."""
    return s.replace("\\", "\\\\").replace('"', '\\"')


def generate_cpp_program(elements: list, docx_path: str, output_path: str) -> str:
    """Generate a complete, compilable C++ source file."""
    # Pre-compute unique C++ identifiers
    seen_ids = set()
    for el in elements:
        el._cpp_name = el.cpp_name(seen_ids)

    abs_docx = os.path.abspath(docx_path).replace("\\", "/")
    abs_out = os.path.abspath(output_path).replace("\\", "/")

    lines = []
    lines.append("// ============================================================================")
    lines.append(f"// Auto-generated from: {os.path.basename(docx_path)}")
    lines.append("//")
    lines.append("// This is a complete, ready-to-compile C++17 program.")
    lines.append("// Steps to use:")
    lines.append("//   1. Edit the data values in main() below.")
    lines.append("//   2. Compile:  g++ -std=c++17 this_file.cpp -lcdocx -o fill_template")
    lines.append("//   3. Run:      ./fill_template")
    lines.append("//   4. Output:   output.docx (or the path you set)")
    lines.append("//")
    lines.append("// NOTE: This file is UTF-8 encoded. On MSVC compile with /utf-8 if it")
    lines.append("//       contains non-ASCII characters in string literals.")
    lines.append("// ============================================================================")
    lines.append("")
    lines.append("#include <cdocx.h>")
    lines.append("#include <iostream>")
    lines.append("#include <map>")
    lines.append("#include <string>")
    lines.append("")

    # ------------------------------------------------------------------
    # Constants
    # ------------------------------------------------------------------
    lines.append("// ------------------------------------------------------------------")
    lines.append("// Template key constants (auto-detected from the .docx file)")
    lines.append("// ------------------------------------------------------------------")
    lines.append("namespace TemplateKeys {")
    for el in elements:
        ctx = escape_cpp_string(el.context)
        lines.append(f'    // Source: {el.source}')
        if ctx:
            lines.append(f'    // Context: {ctx}')
        lines.append(f'    inline constexpr const char* {el._cpp_name} = "{escape_cpp_string(el.name)}";')
        lines.append("")
    lines.append("} // namespace TemplateKeys")
    lines.append("")

    # ------------------------------------------------------------------
    # Main program
    # ------------------------------------------------------------------
    lines.append("int main() {")
    lines.append(f'    const std::string template_path = "{escape_cpp_string(abs_docx)}";')
    lines.append(f'    const std::string output_path   = "{escape_cpp_string(abs_out)}";')
    lines.append("")
    lines.append("    // --------------------------------------------------------------")
    lines.append("    // Open the template document")
    lines.append("    // --------------------------------------------------------------")
    lines.append("    cdocx::Document doc(template_path);")
    lines.append("    if (!doc.open()) {")
    lines.append('        std::cerr << "Failed to open: " << template_path << "\\n";')
    lines.append("        return 1;")
    lines.append("    }")
    lines.append('    std::cout << "Template loaded: " << template_path << "\\n";')
    lines.append("")
    lines.append("    // --------------------------------------------------------------")
    lines.append("    // Create TemplateEngine and fill data")
    lines.append("    // --------------------------------------------------------------")
    lines.append("    cdocx::TemplateEngine engine(&doc);")
    lines.append("")
    lines.append("    // ===== EDIT THE VALUES BELOW =====")
    lines.append("")

    # Group by kind for better readability
    placeholders = [e for e in elements if e.kind == "placeholder"]
    bookmarks = [e for e in elements if e.kind == "bookmark"]
    mergefields = [e for e in elements if e.kind == "mergefield"]

    if placeholders:
        lines.append("    // --- Placeholders ({{key}} style) ---")
        for el in placeholders:
            lines.append(f'    engine[cdocx::TemplateValue::text(TemplateKeys::{el._cpp_name})] = "{escape_cpp_string(el.name)}";  // TODO: replace value')
        lines.append("")

    if bookmarks:
        lines.append("    // --- Bookmarks ---")
        for el in bookmarks:
            lines.append(f'    engine[cdocx::TemplateValue::text(TemplateKeys::{el._cpp_name})] = "{escape_cpp_string(el.name)}";  // TODO: replace value')
        lines.append("")

    if mergefields:
        lines.append("    // --- MERGEFIELDs ---")
        for el in mergefields:
            lines.append(f'    engine[cdocx::TemplateValue::text(TemplateKeys::{el._cpp_name})] = "{escape_cpp_string(el.name)}";  // TODO: replace value')
        lines.append("")

    lines.append("    // ===== END OF EDITABLE VALUES =====")
    lines.append("")

    # Optional: batch set example
    lines.append("    // Alternative: batch set from a map")
    lines.append("    // std::map<std::string, std::string> data = {")
    for el in elements:
        lines.append(f'    //     {{"{escape_cpp_string(el.name)}", "your_value_here"}},')
    lines.append("    // };")
    lines.append("    // engine.set_batch(data);")
    lines.append("")

    # Apply
    lines.append("    // --------------------------------------------------------------")
    lines.append("    // Apply replacements")
    lines.append("    // --------------------------------------------------------------")
    lines.append("    auto result = engine.apply();")
    lines.append('    std::cout << "Replacements: " << result.success << " succeeded, "')
    lines.append('              << result.failed << " failed, "')
    lines.append('              << result.skipped << " skipped\\n";')
    lines.append("")

    # Save
    lines.append("    // --------------------------------------------------------------")
    lines.append("    // Save the result")
    lines.append("    // --------------------------------------------------------------")
    lines.append("    if (!doc.save(output_path)) {")
    lines.append('        std::cerr << "Failed to save: " << output_path << "\\n";')
    lines.append("        return 1;")
    lines.append("    }")
    lines.append('    std::cout << "Saved: " << output_path << "\\n";')
    lines.append("")
    lines.append("    return 0;")
    lines.append("}")
    lines.append("")

    return "\n".join(lines)


def generate_header(elements: list, docx_name: str, guard: str) -> str:
    """Generate the C++ header file content (legacy mode)."""
    placeholders = [e for e in elements if e.kind == "placeholder"]
    bookmarks = [e for e in elements if e.kind == "bookmark"]
    mergefields = [e for e in elements if e.kind == "mergefield"]

    seen_ids = set()
    for el in elements:
        el._cpp_name = el.cpp_name(seen_ids)

    lines = []
    lines.append("// ============================================================================")
    lines.append(f"// Auto-generated from: {os.path.basename(docx_name)}")
    lines.append("//")
    lines.append("// Usage:")
    lines.append('//   cdocx::Document doc("template.docx");')
    lines.append("//   doc.open();")
    lines.append("//   cdocx::TemplateEngine engine(&doc);")
    lines.append("//   TemplateKeys::fill(engine, data);")
    lines.append("//   engine.apply();")
    lines.append('//   doc.save("output.docx");')
    lines.append("//")
    lines.append("// NOTE: This file is UTF-8 encoded. On MSVC compile with /utf-8 if it")
    lines.append("//       contains non-ASCII characters in string literals.")
    lines.append("// ============================================================================")
    lines.append("")
    lines.append("#pragma once")
    lines.append("")
    lines.append("#include <cdocx.h>")
    lines.append("#include <map>")
    lines.append("#include <string>")
    lines.append("")
    lines.append("namespace TemplateKeys {")
    lines.append("")

    def emit_group(title, group):
        if not group:
            return
        lines.append(f"    // {title}")
        for el in group:
            ctx = el.context.replace('"', '\\"')
            lines.append(f"    // Source: {el.source}")
            if ctx:
                from textwrap import wrap
                wrapped = wrap(f"Context: {ctx}", width=70)
                for w in wrapped:
                    lines.append(f"    // {w}")
            lines.append(f'    inline constexpr const char* {el._cpp_name} = "{escape_cpp_string(el.name)}";')
            lines.append("")

    emit_group("Placeholders ({{key}} style)", placeholders)
    emit_group("Bookmarks", bookmarks)
    emit_group("MERGEFIELDs", mergefields)

    lines.append("    // ------------------------------------------------------------------")
    lines.append("    // All key names (for iteration / UI generation)")
    lines.append("    // ------------------------------------------------------------------")
    lines.append("    inline std::vector<std::string> names() {")
    lines.append("        return {")
    for el in elements:
        lines.append(f'            {el._cpp_name},')
    lines.append("        };")
    lines.append("    }")
    lines.append("")

    lines.append("    // ------------------------------------------------------------------")
    lines.append("    // Skeleton: fill all template values")
    lines.append("    // ------------------------------------------------------------------")
    lines.append("    // Uncomment and edit the body to provide real data.")
    lines.append("    /*")
    lines.append("    inline void fill(cdocx::TemplateEngine& engine,")
    lines.append("                     const std::map<std::string, std::string>& data) {")
    for el in elements:
        lines.append(f'        // engine[cdocx::TemplateValue::text({el._cpp_name})] = data.at("{escape_cpp_string(el.name)}");')
    lines.append("    }")
    lines.append("    */")
    lines.append("")

    lines.append("} // namespace TemplateKeys")
    lines.append("")

    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(
        description="Analyze a .docx file and generate C++ code for template filling."
    )
    parser.add_argument("docx", help="Input .docx file")
    parser.add_argument(
        "-o", "--output", default="-",
        help="Output file (default: '-' for stdout). Extension decides mode: .h -> header, .cpp -> full program"
    )
    parser.add_argument(
        "--mode",
        choices=["program", "header", "auto"],
        default="auto",
        help="Output mode: 'program' = compilable .cpp, 'header' = .h with constants, 'auto' = decide by extension (default)"
    )
    parser.add_argument(
        "--guard",
        default=None,
        help="Include guard name for header mode (default: auto-derived from filename)"
    )
    parser.add_argument(
        "--out-docx",
        default="output.docx",
        help="Output .docx path written into the generated program (default: output.docx)"
    )
    args = parser.parse_args()

    elements = parse_docx(args.docx)

    if not elements:
        print("No template elements found in the document.", file=sys.stderr)
        print("Supported: {{placeholder}} text, Word bookmarks, MERGEFIELDs.", file=sys.stderr)
        sys.exit(0)

    elements.sort(key=lambda e: (e.kind, e.name))

    # Determine output mode
    mode = args.mode
    if mode == "auto":
        ext = os.path.splitext(args.output)[1].lower()
        if ext == ".h" or ext == ".hpp":
            mode = "header"
        else:
            mode = "program"

    if mode == "header":
        if args.guard is None:
            base = os.path.splitext(os.path.basename(args.output))[0]
            args.guard = re.sub(r"[^A-Z0-9]", "_", base.upper()) + "_H"
        content = generate_header(elements, args.docx, args.guard)
    else:
        content = generate_cpp_program(elements, args.docx, args.out_docx)

    if args.output == "-":
        print(content)
    else:
        with open(args.output, "w", encoding="utf-8") as f:
            f.write(content)
        print(f"Generated {args.output} with {len(elements)} template element(s).")


if __name__ == "__main__":
    main()
