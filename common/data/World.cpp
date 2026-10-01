#include "data/World.h"

#include <utility>

World::World(std::string name, fs::path rootPath) :
name(std::move(name)), rootPath(std::move(rootPath)) {}

World::World(fs::path rootPath) : rootPath(std::move(rootPath)) {
    name = this->rootPath.filename();
}