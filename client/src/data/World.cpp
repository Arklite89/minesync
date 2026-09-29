//
// Created by danya on 9/29/26.
//

#include "World.h"

#include <utility>

World::World(std::string name, fs::path rootPath) :
name(std::move(name)), rootPath(std::move(rootPath)) {}