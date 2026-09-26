#pragma once
#include <string>
#include "zip.h"

namespace ZipUtils {
    bool extractZip(const std::string& zipPath, const std::string& outputDir);
    bool zipDirectory(const std::string& sourceDir, const std::string& outputZip);
};