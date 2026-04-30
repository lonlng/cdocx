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

    engine["报告编号"]       = "YJBH-ZX2B-TJ6B-12-1#PD-033";
    engine["探测公司"]       = "长江地球物理探测（武汉）有限公司";
    engine["预报时间"]       = "2025.12.15";
    engine["地质预报服务项目部"] = "引江补汉工程专项超前地质预报服务项目 2 标项目部";
    engine["报告日期"]       = "2025.12.15";
    engine["预报方法"]       = "地震波法、地质雷达法";
    engine["预报标段"]       = "土建 6 标";
    engine["预报段落"]       = "L1+025.7～L1+145.7";
    engine["预报隧洞"]       = "12-1#平洞（钻爆）";
    engine["隧洞名称"]       = "12-1#平洞（钻爆）";
    engine["掌子面桩号"]     = "L1+025.7";

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
