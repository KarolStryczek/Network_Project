// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karol on 2018-12-31.
//

#ifndef PROJECT_NETSIM_IPACKAGERECEIVER_HPP
#define PROJECT_NETSIM_IPACKAGERECEIVER_HPP

#include "Storage/Package.hpp"
#include "Storage/IPackageStockpile.hpp"
#include "DataTypes.hpp"

enum class ReceiverType{
    Worker, Storehouse
};

class IPackageReceiver {
public:
    virtual void collectPackage(Package&&) = 0;
    virtual ReceiverType getReceiverType() const = 0;
    virtual ElementID getID() const = 0;

    virtual constIterator begin() const = 0;
    virtual constIterator end() const = 0;
    virtual constIterator cbegin() const = 0;
    virtual constIterator cend() const = 0;
};


#endif //PROJECT_NETSIM_IPACKAGERECEIVER_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)