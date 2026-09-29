#include "ZipUtils.h"
#include "zip.h"
#include <filesystem>

namespace fs = std::filesystem;

bool ZipUtils::extractZip(const fs::path& zipPath, const fs::path& outputDir) {
    std::error_code ec;
    fs::create_directories(outputDir, ec);
    if (ec) {
        return false;
    }

    // backwards compatibility with windows vv
    std::string zipStr = zipPath.string();
    std::string outStr = outputDir.string();

int result = zip_extract(zipStr.c_str(), outStr.c_str(), nullptr, nullptr);
    return result == 0;
}

bool ZipUtils::zipDirectory(const fs::path& sourceDir, const fs::path& outputZip) {
    if (!fs::exists(sourceDir) || !fs::is_directory(sourceDir)) { return false; }

    struct zip_t* zip = zip_open(outputZip.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    if (!zip) { return false; }

    for (const auto& entry : fs::recursive_directory_iterator(sourceDir)) {
        fs::path relativePath = fs::relative(entry.path(), sourceDir);
        std::string zipEntryName = relativePath.generic_string();

        if (entry.is_directory()) {
            zipEntryName += '/';

            if (zip_entry_open(zip, zipEntryName.c_str()) != 0) {
                zip_close(zip);
                return false;
            }

            zip_entry_close(zip);
        } else if (entry.is_regular_file()) {
            if (zip_entry_open(zip, zipEntryName.c_str()) != 0) {
                zip_close(zip);
                return false;
            }

            if (zip_entry_fwrite(zip, entry.path().string().c_str()) != 0) {
                zip_entry_close(zip);
                zip_close(zip);
                return false;
            }

            zip_entry_close(zip);
        }
    }

    zip_close(zip);
    return true;
}
