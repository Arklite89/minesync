#pragma once

#include "cpr/filesystem.h"

namespace fs = std::filesystem;

namespace ZipUtils {
    bool extractZip(const fs::path& zipPath, const fs::path& outputDir);
    bool zipDirectory(const fs::path& sourceDir, const fs::path& outputZip);
};