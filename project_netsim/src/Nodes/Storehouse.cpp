//
// Created by Karol on 2018-12-31.
//

#include "Nodes/Storehouse.hpp"

void Storehouse::collectPackage(Package &&package) {
    _packageStockpile->push(std::move(package));
}