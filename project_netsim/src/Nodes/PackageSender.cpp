//
// Created by Karol on 2018-12-31.
//

#include "Nodes/PackageSender.hpp"

/**
 * Sends Package if there is one in toSendBuffer.
 * @return True if Package has been sent. False if there was no Package in toSendBuffer.
 */
bool PackageSender::sendPackage() {
    if( _toSendBuffer.second ) {
        std::shared_ptr<IPackageReceiver> receiver = _receiverPreferences.chooseReceiver();
        receiver->collectPackage(std::move(_toSendBuffer.first));
        _toSendBuffer.second = false;
        return true;
    }
    else {
        return false;
    }
}