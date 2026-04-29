// ============================================================================
// Example: 专项超前地质预报成果报告模板填充
// Auto-generated from: 专项超前地质预报成果报告模板2.docx
//
// This example uses ONLY placeholder ({{key}}) replacement.
// No bookmarks are used.
//
// Build:
//   g++ -std=c++17 main.cpp -lcdocx -o fill_template
// Run:
//   ./fill_template
// ============================================================================

#include <cdocx.h>
#include <filesystem>
#include <iostream>
#include <string>

int main() {
    // Always use the source directory's data/ regardless of working directory
    const std::filesystem::path source_dir = EXAMPLE_SOURCE_DIR;
    const std::string template_path = (source_dir / "data" / "template.docx").string();
    const std::string output_path   = (source_dir / "data" / "output.docx").string();

    // --------------------------------------------------------------
    // Open template
    // --------------------------------------------------------------
    cdocx::Document doc(template_path);
    doc.open();
    if (!doc.is_open()) {
        std::cerr << "Failed to open: " << template_path << "\n";
        return 1;
    }
    std::cout << "Template loaded: " << template_path << "\n";

    // --------------------------------------------------------------
    // Fill placeholders in document order
    // --------------------------------------------------------------
    cdocx::TemplateEngine engine(&doc);
    engine.with_target(cdocx::TemplateTarget::Placeholder);

    engine["报告编号"]       = "ZBYB-2026-0429";
    engine["探测公司"]       = "中铁隧道探测有限公司";
    engine["预报时间"]       = "2026年4月25日 ~ 2026年4月28日";
    engine["地质预报服务项目部"] = "地质超前预报服务第一项目部";
    engine["报告日期"]       = "2026年4月29日";
    engine["预报方法"]       = "地质雷达法 + 超前水平钻探";
    engine["预报标段"]       = "K12+350 ~ K12+450 标段";
    engine["预报段落"]       = "进口段左洞 DK12+350 ~ DK12+450";
    engine["预报隧洞"]       = "云雾山隧道";

    // --------------------------------------------------------------
    // Apply and save
    // --------------------------------------------------------------
    auto result = engine.apply();
    std::cout << "Replacements: " << result.success << " succeeded, "
              << result.failed << " failed, "
              << result.skipped << " skipped\n";

    doc.save(output_path);
    std::cout << "Saved: " << output_path << "\n";
    return 0;
}
