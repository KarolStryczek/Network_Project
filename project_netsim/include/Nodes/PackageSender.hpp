// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karol on 2018-12-31.
//

#ifndef PROJECT_NETSIM_PACKAGESENDER_HPP
#define PROJECT_NETSIM_PACKAGESENDER_HPP

#include <functional>
#include "ReceiverPreferences.hpp"

/**
 * PackageSender Class is responsible for managing Package sending process for other classes.
 */
class PackageSender {
protected:
    ReceiverPreferences _receiverPreferences;
    std::pair<Package, bool> _toSendBuffer;
public:
    /**
     * Create PackageSender object with deterministic receiver choosing procedure.
     * @param choosingFunction: Function passed to ReceiverPreferences constructor.
     */
    explicit PackageSender(std::function<double()> choosingFunction):
        _receiverPreferences(std::move(choosingFunction)), _toSendBuffer() { _toSendBuffer.second = false; };
    /**
     * Create PackageSender with default ReceiverPreferences object.
     */
    PackageSender(): _receiverPreferences(), _toSendBuffer() { _toSendBuffer.second = false; };

    // Definition in .cpp
    bool sendPackage();

    // Getters
    const preferencesT& getPreferences() const { return _receiverPreferences.getPreferences(); };

    // Delegating adding method
    bool addReceiver(std::shared_ptr<IPackageReceiver> receiver , double priority = 1)
        { return _receiverPreferences.addReceiver(std::move(receiver), priority); };
    // Delegating removing method
    bool removeReceiver(std::shared_ptr<IPackageReceiver> receiver)
        { return _receiverPreferences.removeReceiver(std::move(receiver)); };

    // Virtual destructor to assure proper destructor calling hierarchy.
    virtual ~PackageSender() = default;
};


#endif //PROJECT_NETSIM_PACKAGESENDER_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)