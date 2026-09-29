//
// Created by danya on 9/29/26.
//

#ifndef MINESYNC_FILEHELPERS_H
#define MINESYNC_FILEHELPERS_H
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

namespace FileHelpers {
    std::vector<fs::path> getSubdirectories(fs::path path);
}


#endif //MINESYNC_FILEHELPERS_H
