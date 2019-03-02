// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karol on 2018-12-31.
//

#ifndef PROJECT_NETSIM_PACKAGE_HPP
#define PROJECT_NETSIM_PACKAGE_HPP

#include "DataTypes.hpp"

class Package {
private:
    static ElementID _lastAssignedID;
    ElementID _packageID;
public:
    Package(): _packageID( ++_lastAssignedID ){}
    ElementID getPackageID() const { return _packageID; }
};


#endif //PROJECT_NETSIM_PACKAGE_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)