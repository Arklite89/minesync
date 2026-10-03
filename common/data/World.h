#pragma once

#include <filesystem>

namespace fs = std::filesystem;

class World {
public:
    std::string name;
    fs::path rootPath;

    explicit World(std::string name, fs::path rootPath);
    explicit World(fs::path rootPath);
};
