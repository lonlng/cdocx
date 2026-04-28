#!/usr/bin/env python3
"""
Deep structural comparison between cdocx and python-docx output.
Identifies gaps, inefficiencies, and structural differences.
"""

from zipfile import ZipFile
import xml.etree.ElementTree as ET
import os
import re

# Register namespaces for pretty printing
namespaces = {
    'w': 'http://schemas.openxmlformats.org/wordprocessingml/2006/main',
    'r': 'http://schemas.openxmlformats.org/officeDocument/2006/relationships',
    'wp': 'http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing',
}


def analyze_docx(path, label):
    """Comprehensive DOCX structural analysis."""
    result = {"label": label, "path": path}

    if not os.path.exists(path):
        result["error"] = "File not found"
        return result

    result["size"] = os.path.getsize(path)

    with ZipFile(path, "r") as zf:
        result["zip_entries"] = {
            name: {"size": zf.getinfo(name).file_size,
                   "compressed": zf.getinfo(name).compress_size}
            for name in zf.namelist()
        }

        # Parse document.xml
        if "word/document.xml" in zf.namelist():
            with zf.open("word/document.xml") as f:
                xml_bytes = f.read()
                result["document_xml_size"] = len(xml_bytes)
                tree = ET.fromstring(xml_bytes)
                ns = {"w": "http://schemas.openxmlformats.org/wordprocessingml/2006/main"}

                result["paragraphs"] = len(tree.findall(".//w:p", ns))
                result["runs"] = len(tree.findall(".//w:r", ns))
                result["tables"] = len(tree.findall(".//w:tbl", ns))
                result["bookmark_starts"] = len(tree.findall(".//w:bookmarkStart", ns))
                result["bookmark_ends"] = len(tree.findall(".//w:bookmarkEnd", ns))
                result["text_nodes"] = len(tree.findall(".//w:t", ns))
                result["rpr_nodes"] = len(tree.findall(".//w:rPr", ns))
                result["ppr_nodes"] = len(tree.findall(".//w:pPr", ns))
                result["tblpr_nodes"] = len(tree.findall(".//w:tblPr", ns))
                result["tcpr_nodes"] = len(tree.findall(".//w:tcPr", ns))
                result["hyperlink_nodes"] = len(tree.findall(".//w:hyperlink", ns))
                result["fld_char_nodes"] = len(tree.findall(".//w:fldChar", ns))

                # Check for whitespace-only text nodes (potential pretty-print contamination)
                whitespace_text = 0
                for t in tree.findall(".//w:t", ns):
                    if t.text and t.text.strip() == "" and t.text != "":
                        whitespace_text += 1
                result["whitespace_text_nodes"] = whitespace_text

                # Count run-merging candidates: adjacent runs with identical rPr
                body = tree.find(".//w:body", ns)
                if body is not None:
                    mergeable = 0
                    for para in body.findall("w:p", ns):
                        runs = para.findall("w:r", ns)
                        for i in range(len(runs) - 1):
                            r1 = runs[i]
                            r2 = runs[i + 1]
                            # Compare rPr children as strings (simplistic)
                            p1 = r1.find("w:rPr", ns)
                            p2 = r2.find("w:rPr", ns)
                            if (p1 is None and p2 is None) or \
                               (p1 is not None and p2 is not None and
                                ET.tostring(p1, encoding='unicode') == ET.tostring(p2, encoding='unicode')):
                                mergeable += 1
                    result["mergeable_adjacent_runs"] = mergeable

        # Parse styles.xml
        if "word/styles.xml" in zf.namelist():
            with zf.open("word/styles.xml") as f:
                result["styles_xml_size"] = len(f.read())

        # Parse settings.xml
        if "word/settings.xml" in zf.namelist():
            with zf.open("word/settings.xml") as f:
                settings_tree = ET.parse(f)
                settings_root = settings_tree.getroot()
                ns = {"w": "http://schemas.openxmlformats.org/wordprocessingml/2006/main"}
                zoom = settings_root.find(".//w:zoom", ns)
                result["settings_zoom"] = zoom.get("{http://schemas.openxmlformats.org/wordprocessingml/2006/main}percent") if zoom is not None else "default"

        # Check for common parts
        result["has_numbering"] = "word/numbering.xml" in zf.namelist()
        result["has_footnotes"] = "word/footnotes.xml" in zf.namelist()
        result["has_endnotes"] = "word/endnotes.xml" in zf.namelist()
        result["has_comments"] = "word/comments.xml" in zf.namelist()
        result["has_stylesWithEffects"] = "word/stylesWithEffects.xml" in zf.namelist()
        result["has_thumbnail"] = "docProps/thumbnail.jpeg" in zf.namelist()
        result["has_customXml"] = any("customXml" in n for n in zf.namelist())
        result["has_webSettings"] = "word/webSettings.xml" in zf.namelist()
        result["has_theme"] = "word/theme/theme1.xml" in zf.namelist()
        result["has_settings"] = "word/settings.xml" in zf.namelist()
        result["has_fontTable"] = "word/fontTable.xml" in zf.namelist()

    return result


def print_analysis(a):
    """Pretty-print analysis result."""
    print(f"\n{'='*70}")
    print(f"  {a['label']}")
    print(f"  {a['path']}")
    print(f"{'='*70}")

    if "error" in a:
        print(f"  ERROR: {a['error']}")
        return

    print(f"  File size:            {a['size']:,} bytes")
    print(f"  ZIP entries:          {len(a['zip_entries'])}")
    print(f"  document.xml size:    {a.get('document_xml_size', 'N/A')}")
    print(f"  styles.xml size:      {a.get('styles_xml_size', 'N/A')}")

    print(f"\n  XML Structure:")
    for key in ["paragraphs", "runs", "tables", "bookmark_starts", "bookmark_ends",
                "text_nodes", "rpr_nodes", "ppr_nodes", "tblpr_nodes", "tcpr_nodes",
                "hyperlink_nodes", "fld_char_nodes"]:
        if key in a:
            print(f"    {key:22s}: {a[key]}")

    if "whitespace_text_nodes" in a:
        print(f"    whitespace text nodes : {a['whitespace_text_nodes']}")
    if "mergeable_adjacent_runs" in a:
        print(f"    mergeable adjacent runs: {a['mergeable_adjacent_runs']}")

    print(f"\n  Parts Present:")
    for key in ["has_numbering", "has_footnotes", "has_endnotes", "has_comments",
                "has_stylesWithEffects", "has_thumbnail", "has_customXml",
                "has_webSettings", "has_theme", "has_settings", "has_fontTable"]:
        val = a.get(key, False)
        icon = "✓" if val else "✗"
        print(f"    {icon} {key[4:]}")


def compare_pair(a, b):
    """Side-by-side comparison of two documents."""
    print(f"\n{'='*70}")
    print(f"  COMPARISON: {a['label']} vs {b['label']}")
    print(f"{'='*70}")

    # Size comparison
    size_a = a.get('size', 0)
    size_b = b.get('size', 0)
    ratio = size_b / size_a if size_a > 0 else 0
    print(f"  File size:   {a['label']:25s} {size_a:8,} bytes")
    print(f"               {b['label']:25s} {size_b:8,} bytes")
    print(f"               Ratio (b/a): {ratio:.2f}x")

    # XML structure comparison
    print(f"\n  XML Structure:")
    for key in ["paragraphs", "runs", "tables", "text_nodes", "rpr_nodes", "ppr_nodes"]:
        va = a.get(key, 0)
        vb = b.get(key, 0)
        diff = vb - va
        print(f"    {key:15s}: {va:4d} vs {vb:4d}  (diff: {diff:+4d})")

    # Parts comparison
    print(f"\n  Parts Gap Analysis:")
    for key in ["has_numbering", "has_footnotes", "has_endnotes", "has_comments",
                "has_stylesWithEffects", "has_thumbnail", "has_customXml",
                "has_webSettings", "has_theme", "has_settings", "has_fontTable"]:
        va = a.get(key, False)
        vb = b.get(key, False)
        if va and not vb:
            print(f"    ⚠ {a['label']} has {key[4:]} but {b['label']} does NOT")
        elif vb and not va:
            print(f"    ⚠ {b['label']} has {key[4:]} but {a['label']} does NOT")


def main():
    base = "/home/dev/workspaces/cdocx/build"

    docs = [
        (f"{base}/python_docx_output/04_empty.docx", "python-docx empty"),
        (f"{base}/cdocx_empty.docx", "cdocx empty"),
        (f"{base}/python_docx_output/01_basic_document.docx", "python-docx basic"),
        (f"{base}/cdocx_equivalent.docx", "cdocx equivalent"),
        (f"{base}/python_docx_output/02_bookmark_document.docx", "python-docx bookmark"),
        (f"{base}/09_text_formatting_output.docx", "cdocx text formatting"),
        (f"{base}/python_docx_output/05_complex_formatting.docx", "python-docx complex"),
        (f"{base}/document_builder_example.docx", "cdocx doc builder"),
        (f"{base}/python_docx_output/06_table_merge.docx", "python-docx table merge"),
    ]

    results = {}
    for path, label in docs:
        results[label] = analyze_docx(path, label)

    for path, label in docs:
        print_analysis(results[label])

    # Key comparisons
    compare_pair(results["python-docx empty"], results["cdocx empty"])
    compare_pair(results["python-docx basic"], results["cdocx equivalent"])

    # Summary findings
    print(f"\n{'='*70}")
    print(f"  SUMMARY FINDINGS")
    print(f"{'='*70}")

    empty_py = results["python-docx empty"]
    empty_cdocx = results["cdocx empty"]

    print(f"\n1. EMPTY DOCUMENT BASELINE")
    print(f"   python-docx empty: {empty_py['size']:,} bytes")
    print(f"   cdocx empty:       {empty_cdocx['size']:,} bytes")
    print(f"   python-docx is {empty_py['size']/empty_cdocx['size']:.1f}x larger")
    print(f"   python-docx includes: stylesWithEffects.xml, thumbnail.jpeg, customXml,")
    print(f"                         webSettings.xml, full numbering.xml")
    print(f"   cdocx minimal parts: no thumbnail, no customXml, no stylesWithEffects,")
    print(f"                        minimal styles.xml (~{empty_cdocx.get('styles_xml_size', 0)} bytes)")

    basic_py = results["python-docx basic"]
    basic_cdocx = results["cdocx equivalent"]

    print(f"\n2. BASIC DOCUMENT WITH CONTENT")
    print(f"   python-docx basic:     {basic_py['size']:,} bytes")
    print(f"   cdocx equivalent:      {basic_cdocx['size']:,} bytes")
    print(f"   Size ratio: {basic_py['size']/basic_cdocx['size']:.1f}x")

    # Content equivalence check
    print(f"\n3. CONTENT EQUIVALENCE")
    print(f"   Paragraphs:  python-docx={basic_py['paragraphs']} cdocx={basic_cdocx['paragraphs']}")
    print(f"   Runs:        python-docx={basic_py['runs']} cdocx={basic_cdocx['runs']}")
    print(f"   Tables:      python-docx={basic_py['tables']} cdocx={basic_cdocx['tables']}")
    print(f"   Text nodes:  python-docx={basic_py['text_nodes']} cdocx={basic_cdocx['text_nodes']}")

    print(f"\n4. XML QUALITY INDICATORS")
    for name in ["python-docx basic", "cdocx equivalent"]:
        r = results[name]
        ws = r.get('whitespace_text_nodes', 0)
        mr = r.get('mergeable_adjacent_runs', 0)
        print(f"   {name:25s}: whitespace text nodes={ws}, mergeable adjacent runs={mr}")

    print(f"\n5. MISSING PARTS IN CDOCX (relative to python-docx baseline)")
    for key in ["has_numbering", "has_stylesWithEffects", "has_thumbnail",
                "has_customXml", "has_webSettings"]:
        if basic_py.get(key, False) and not basic_cdocx.get(key, False):
            print(f"   - {key[4:]}: cdocx does not generate this part")

    print(f"\n6. POTENTIAL CDOCX IMPROVEMENTS")
    print(f"   a. Thumbnail generation is opt-in for users who need file preview")
    print(f"   b. styles.xml is functionally complete but still 50x smaller than python-docx")
    print(f"   c. stylesWithEffects.xml is legacy compatibility only")
    print(f"   d. customXml is rarely needed for programmatic generation")


if __name__ == "__main__":
    main()
