//
// Created by danya on 9/30/26.
//

#include "WorldService.h"

#include "api/ApiController.h"
#include "files/CacheHandler.h"
#include "files/FileHelpers.h"
#include "zip/ZipUtils.h"

std::vector<World> WorldService::scoutDirectory(const fs::path &savesDir) {
    if (!fs::exists(savesDir) || !fs::is_directory(savesDir))
        throw std::invalid_argument("Invalid saves directory.");

    std::vector<fs::path> directories = FileHelpers::getSubdirectories(savesDir);
    FileHelpers::filterToJustWorlds(directories);

    return FileHelpers::getWorldsFromDirectories(directories);
};

bool WorldService::uploadWorld(const World& world) { // NOLINT(readability-make-member-function-const)
    CacheHandler::cacheWorldToZip(world);
    fs::path zip = CacheHandler::getLatestCachedSaveZip();

    cpr::Response res = ApiController::uploadSave(client, cpr::File(zip));
    return (res.status_code == 200);
}

bool WorldService::syncWorld(const World &world) { // NOLINT(readability-make-member-function-const)
    const fs::path zipPath = CacheHandler::getAppCacheDir() / "sync.tmp.zip";
    cpr::Response res = ApiController::getSave(client, world, zipPath);
    if (res.status_code != 200) return false;

    std::error_code ec;
    const bool removed = fs::remove_all(world.rootPath, ec);
    if (ec || !removed) return false;

    return ZipUtils::extractZip(zipPath, world.rootPath);
}
