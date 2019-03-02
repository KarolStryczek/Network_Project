// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karol on 2018-12-31.
//

#ifndef PROJECT_NETSIM_IPACKAGESTOCKPILE_HPP
#define PROJECT_NETSIM_IPACKAGESTOCKPILE_HPP

#include <deque>
#include "Package.hpp"

// Constant iterator type.
using constIterator = std::deque<Package>::const_iterator;

/**
 * Interface type for stockpiles. Allows to push element and iterate through elements.
 */
class IPackageStockpile {
public:
    // Push object into container.
    virtual void push(Package&&) = 0;
    // Iterators.
    virtual constIterator begin() const = 0;
    virtual constIterator end() const = 0;
    virtual constIterator cbegin() const = 0;
    virtual constIterator cend() const = 0;
};

#endif //PROJECT_NETSIM_IPACKAGESTOCKPILE_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)