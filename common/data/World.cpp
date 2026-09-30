//
// Created by danya on 9/29/26.
//

#include "data/World.h"

#include <utility>

World::World(std::string name, fs::path rootPath) :
name(std::move(name)), rootPath(std::move(rootPath)) {}

World::World(fs::path rootPath) : rootPath(std::move(rootPath)) {
    name = rootPath.filename();
}