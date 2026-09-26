#include "ZipUtils.h"
#include "zip.h"
#include <filesystem>

namespace fs = std::filesystem;

bool ZipUtils::extractZip(const std::string& zipPath, const std::string& outputDir) {
    int result = zip_extract(zipPath.c_str(), outputDir.c_str(), nullptr, nullptr);
    return result == 0;
}

bool ZipUtils::zipDirectory(const std::string& sourceDir, const std::string& outputZip) {
    fs::path baseDir(sourceDir);

    if (!fs::exists(baseDir) || !fs::is_directory(baseDir)) { return false; }

    struct zip_t* zip = zip_open(outputZip.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    if (!zip) { return false; }

    for (const auto& entry : fs::recursive_directory_iterator(baseDir)) {
        fs::path relativePath = fs::relative(entry.path(), baseDir);
        std::string zipEntryName = relativePath.generic_string();

        if (entry.is_directory()) {
            zipEntryName += '/';
            zip_entry_open(zip, zipEntryName.c_str());
            zip_entry_close(zip);
        } else if (entry.is_regular_file()) {
            zip_entry_open(zip, zipEntryName.c_str());
            zip_entry_fwrite(zip, entry.path().string().c_str());
            zip_entry_close(zip);
        }
    }

    zip_close(zip);
    return true;
}
