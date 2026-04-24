#!/usr/bin/env python3
"""
Docx Template Analyzer for CDocx
================================

Analyzes a Word .docx file and extracts all template-replaceable elements:
  - {{placeholder}} text markers
  - Word bookmarks
  - MERGEFIELD fields

Generates a ready-to-use C++17 header file with constants and a
skeleton function for cdocx::TemplateEngine.

Usage:
    python analyze_template.py template.docx -o template_keys.h
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
        # Remove delimiters and sanitize
        raw = self.name.strip()
        raw = raw.replace("{{", "").replace("}}", "")
        raw = re.sub(r"[^a-zA-Z0-9_]", "_", raw)
        # Must not start with a digit
        if raw and raw[0].isdigit():
            raw = "_" + raw
        raw = raw or "unnamed"
        # Deduplicate: if the sanitized name collides with another, append a counter
        if seen is not None:
            base = raw
            counter = 2
            while raw in seen:
                raw = f"{base}_{counter}"
                counter += 1
            seen.add(raw)
        return raw

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
        # Collect all XML parts that may contain content
        content_parts = []
        for name in zf.namelist():
            if name.endswith(".xml") or name.endswith(".rels"):
                # Document body, headers, footers, endnotes, comments
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

            # ------------------------------------------------------------------
            # 1. Bookmarks (w:bookmarkStart/@w:name)
            # ------------------------------------------------------------------
            for bm_start in root.iter(qname("bookmarkStart")):
                name = bm_start.get(qname("name"))
                if name:
                    # Try to grab surrounding paragraph text as context
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

            # ------------------------------------------------------------------
            # 2. Placeholders inside w:t text nodes
            # ------------------------------------------------------------------
            # We scan at the paragraph level so merged runs are handled.
            for para in root.iter(qname("p")):
                para_text = iter_text_in_element(para)
                if not para_text:
                    continue
                for key in extract_placeholders(para_text):
                    elements.append(
                        TemplateElement("placeholder", key, part, para_text[:80])
                    )

            # ------------------------------------------------------------------
            # 3. MERGEFIELD / other fields
            # ------------------------------------------------------------------
            for instr in root.iter(qname("instrText")):
                if instr.text:
                    code = instr.text.strip()
                    # Match "MERGEFIELD Name" or "MERGEFIELD Name \* ..."
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

    # Filter out internal Word bookmarks (auto-generated navigation markers)
    internal_bookmarks = {"_goback"}
    deduped = [
        el for el in deduped
        if not (el.kind == "bookmark" and el.name.lower() in internal_bookmarks)
    ]

    return deduped


def make_cpp_comment(text: str, width: int = 76) -> str:
    """Break a string into C++ // comment lines."""
    if not text:
        return ""
    lines = []
    while text:
        chunk = text[:width]
        text = text[width:]
        lines.append("// " + chunk)
    return "\n".join(lines)


def generate_header(elements: list, docx_name: str, guard: str) -> str:
    """Generate the C++ header file content."""
    # Group by kind
    placeholders = [e for e in elements if e.kind == "placeholder"]
    bookmarks = [e for e in elements if e.kind == "bookmark"]
    mergefields = [e for e in elements if e.kind == "mergefield"]

    # Pre-compute unique C++ identifiers once per element
    seen_ids = set()
    for el in elements:
        el._cpp_name = el.cpp_name(seen_ids)

    lines = []
    lines.append("// ============================================================================")
    lines.append(f"// Auto-generated from: {os.path.basename(docx_name)}")
    lines.append("//")
    lines.append("// Usage:")
    lines.append("//   cdocx::Document doc(\"template.docx\");")
    lines.append("//   doc.open();")
    lines.append("//   cdocx::TemplateEngine engine(&doc);")
    lines.append("//   TemplateKeys::fill(engine, data);")
    lines.append("//   engine.apply();")
    lines.append("//   doc.save(\"output.docx\");")
    lines.append("//")
    lines.append("// NOTE: This file is UTF-8 encoded. On MSVC compile with /utf-8 if it")
    lines.append("//       contains non-ASCII characters in string literals.")
    lines.append("// ============================================================================")
    lines.append("")
    lines.append(f"#pragma once")
    lines.append("")
    lines.append("#include <cdocx.h>")
    lines.append("#include <map>")
    lines.append("#include <string>")
    lines.append("")
    lines.append("namespace TemplateKeys {")
    lines.append("")

    # ------------------------------------------------------------------
    # Constants
    # ------------------------------------------------------------------
    def emit_group(title, group):
        if not group:
            return
        lines.append(f"    // {title}")
        for el in group:
            ctx = el.context.replace("\"", "\\\"")
            lines.append(f"    // Source: {el.source}")
            if ctx:
                for cl in make_cpp_comment(f"Context: {ctx}").split("\n"):
                    lines.append(f"    {cl}")
            lines.append(f'    inline constexpr const char* {el._cpp_name} = "{el.name}";')
            lines.append("")

    emit_group("Placeholders ({{key}} style)", placeholders)
    emit_group("Bookmarks", bookmarks)
    emit_group("MERGEFIELDs", mergefields)

    # ------------------------------------------------------------------
    # Convenience: names() vector
    # ------------------------------------------------------------------
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

    # ------------------------------------------------------------------
    # Skeleton fill function
    # ------------------------------------------------------------------
    lines.append("    // ------------------------------------------------------------------")
    lines.append("    // Skeleton: fill all template values")
    lines.append("    // ------------------------------------------------------------------")
    lines.append("    // Uncomment and edit the body to provide real data.")
    lines.append("    /*")
    lines.append("    inline void fill(cdocx::TemplateEngine& engine,")
    lines.append("                     const std::map<std::string, std::string>& data) {")
    for el in elements:
        if el.kind == "placeholder" or el.kind == "bookmark":
            lines.append(f'        // engine[cdocx::TemplateValue::text({el._cpp_name})] = data.at("{el.name}");')
        elif el.kind == "mergefield":
            lines.append(f'        // engine[cdocx::TemplateValue::text({el._cpp_name})] = data.at("{el.name}");')
    lines.append("    }")
    lines.append("    */")
    lines.append("")

    lines.append("} // namespace TemplateKeys")
    lines.append("")

    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(
        description="Analyze a .docx file and generate a C++ header with template keys."
    )
    parser.add_argument("docx", help="Input .docx file")
    parser.add_argument(
        "-o", "--output", default="-",
        help="Output header file (default: '-' for stdout)"
    )
    parser.add_argument(
        "--guard",
        default=None,
        help="Include guard name (default: auto-derived from filename)"
    )
    args = parser.parse_args()

    elements = parse_docx(args.docx)

    if not elements:
        print("No template elements found in the document.", file=sys.stderr)
        print("Supported: {{placeholder}} text, Word bookmarks, MERGEFIELDs.", file=sys.stderr)
        sys.exit(0)

    # Sort for stable output: kind then name
    elements.sort(key=lambda e: (e.kind, e.name))

    if args.guard is None:
        base = os.path.splitext(os.path.basename(args.output))[0]
        args.guard = re.sub(r"[^A-Z0-9]", "_", base.upper()) + "_H"

    header = generate_header(elements, args.docx, args.guard)

    if args.output == "-":
        print(header)
    else:
        with open(args.output, "w", encoding="utf-8") as f:
            f.write(header)
        print(f"Generated {args.output} with {len(elements)} template element(s).")


if __name__ == "__main__":
    main()
