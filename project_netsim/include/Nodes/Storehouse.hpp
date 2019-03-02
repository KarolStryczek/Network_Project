// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karol on 2018-12-31.
//

#ifndef PROJECT_NETSIM_STOREHOUSE_HPP
#define PROJECT_NETSIM_STOREHOUSE_HPP

#include <memory>
#include "IPackageReceiver.hpp"
#include "Storage/IPackageStockpile.hpp"

class Storehouse: public IPackageReceiver {
private:
    ElementID _storehouseID;
    std::unique_ptr<IPackageStockpile> _packageStockpile;
public:
    explicit Storehouse(ElementID storehouseID, std::unique_ptr<IPackageStockpile> packageStockpile):
        _storehouseID(storehouseID), _packageStockpile(std::move(packageStockpile)){};
    void collectPackage(Package&&) override;
    ReceiverType getReceiverType() const override { return ReceiverType::Worker; }
    ElementID getID() const override { return _storehouseID; }

    constIterator begin() const override { return _packageStockpile->cbegin(); }
    constIterator end() const override { return _packageStockpile->cend(); }
    constIterator cbegin() const override { return _packageStockpile->cbegin(); }
    constIterator cend() const override { return _packageStockpile->cend(); }
};


#endif //PROJECT_NETSIM_STOREHOUSE_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)