/**
 * @file example_utils.h
 * @brief Utility functions for example programs
 * 
 * This header provides helper functions for example programs to locate
 * their resource files relative to the executable location.
 */

#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include <cstdlib>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

namespace example_utils {

/**
 * @brief Get the directory of the current executable
 * @return Path to the executable's directory
 */
inline std::string get_executable_dir() {
    std::string path;
    
#ifdef _WIN32
    char buffer[MAX_PATH];
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    path = buffer;
#else
    // For Linux/Mac - read from /proc/self/exe or use argv[0]
    char buffer[1024];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        path = buffer;
    }
#endif

    // Remove the executable name to get directory
    size_t last_sep = path.find_last_of("\\/");
    if (last_sep != std::string::npos) {
        path = path.substr(0, last_sep);
    }
    
    return path;
}

/**
 * @brief Get the path to a resource file
 * 
 * Search order:
 * 1. Executable directory (where the .exe is located)
 * 2. Parent directory of executable (for build tree structure)
 * 3. Debug/Release subdirectories (for multi-config builds)
 * 4. Current working directory
 * 5. data/ subdirectory of current working directory
 * 
 * @param filename Name of the resource file (e.g., "my_test.docx")
 * @return Full path to the resource file
 */
inline std::string get_resource_path(const std::string& filename) {
    namespace fs = std::filesystem;
    
    std::string exe_dir = get_executable_dir();
    std::vector<std::string> search_paths;
    
    // Build list of search paths
    search_paths.push_back(exe_dir + "/" + filename);                          // exe dir
    search_paths.push_back(exe_dir + "/../" + filename);                       // parent of exe dir
    search_paths.push_back(exe_dir + "/Debug/" + filename);                    // Debug config
    search_paths.push_back(exe_dir + "/Release/" + filename);                  // Release config
    search_paths.push_back(exe_dir + "/data/" + filename);                     // data subdir of exe
    search_paths.push_back(exe_dir + "/../data/" + filename);                  // data in parent
    search_paths.push_back(exe_dir + "/../Debug/" + filename);                 // Debug in parent
    search_paths.push_back(exe_dir + "/../Release/" + filename);               // Release in parent
    search_paths.push_back(filename);                                          // current directory
    search_paths.push_back("data/" + filename);                                // data/ in current dir
    
    // Try each path
    for (const auto& path : search_paths) {
        try {
            if (fs::exists(path)) {
                return path;
            }
        } catch (...) {
            // Continue to next path on error
        }
    }
    
    // Last resort: return filename in current directory
    return filename;
}

/**
 * @brief Get the path for output files
 * 
 * Places output in the executable directory if writable, otherwise
 * in the current working directory.
 * 
 * @param filename Name of the output file
 * @return Full path for the output file
 */
inline std::string get_output_path(const std::string& filename) {
    namespace fs = std::filesystem;
    
    // Try executable directory
    std::string exe_dir = get_executable_dir();
    std::string exe_path = exe_dir + "/" + filename;
    
    // Check if directory is writable by testing if we can create the file
    std::ofstream test(exe_path, std::ios::app);
    if (test.is_open()) {
        test.close();
        return exe_path;
    }
    
    // Fall back to current working directory
    return filename;
}

} // namespace example_utils
