#pragma once
#include <filesystem>
#include <string>

#include "data/World.h"

namespace fs = std::filesystem;

class CacheHandler {
private:
    CacheHandler() = default;
    ~CacheHandler() = default;

    static constexpr int N_BACKUPS = 5;

    static fs::path getUserCacheDir();
    static int get_backup_count();
public:
    CacheHandler(const CacheHandler&) = delete;
    CacheHandler& operator=(const CacheHandler&) = delete;
    CacheHandler(CacheHandler&&) = delete;
    CacheHandler& operator=(CacheHandler&&) = delete;

    static CacheHandler& getInstance() {
        static CacheHandler instance;
        return instance;
    }

    static fs::path getAppCacheDir();
    static fs::path getLatestCachedSaveZip();
    static bool cacheWorldToZip(const World& world);
};
