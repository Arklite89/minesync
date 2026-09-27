#include "CacheHandler.h"

#include <iostream>
#include <filesystem>
#include <cstdlib>

#include "ClientAppConfig.h"
#include "../../../common/zip/ZipUtils.h"

#if defined(_WIN32)
#include <windows.h>
#include <shlobj.h>
#endif

namespace fs = std::filesystem;

fs::path CacheHandler::getUserCacheDir() {
#if defined(_WIN32)

    PWSTR path = nullptr;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path))) {
        fs::path cache_dir(path);
        CoTaskMemFree(path);
        return cache_dir;
    }

    const char* local_app_data = std::getenv("LOCALAPPDATA");
    return local_app_data ? fs::path(local_app_data) : {};

#elif defined(__APPLE__)

const char* home = std::getenv("HOME");
    if (home) { return fs::path(home) / "Library" / "Caches"; }

    return {};

#else

const char* xdg_cache = std::getenv("XDG_CACHE_HOME");
    if (xdg_cache && xdg_cache[0] != '\0') { return fs::path(xdg_cache); }

    const char* home = std::getenv("HOME");
    if (home) { return fs::path(home) / ".cache"; }

    return {};

#endif
}

fs::path CacheHandler::getAppCacheDir() {
    fs::path base_cache = getUserCacheDir();

    if (base_cache.empty()) {
        std::cerr << "Failed to get cache directory." << std::endl;
        return {};
    }

    fs::path app_cache = base_cache / ClientAppConfig::APP_NAME;

    std::error_code ec;
    fs::create_directories(app_cache, ec);
    if (ec) {
        std::cerr << "Failed to create app cache directory: " << ec.message() << std::endl;
        return {};
    }

    return app_cache;
}

bool CacheHandler::cacheSaveToZip(const fs::path& save_path) {
    fs::path output_path = getAppCacheDir() / (std::string(ClientAppConfig::SAVE_CACHE_DIRNAME) + ".zip");

    if (fs::exists(output_path)) {
        std::error_code ec;
        fs::remove(output_path, ec);
        if (ec) {
            std::cerr << "Failed to remove existing cached save file: " << ec.message() << std::endl;
            return false;
        }
    }

    return ZipUtils::zipDirectory(save_path, output_path);
}