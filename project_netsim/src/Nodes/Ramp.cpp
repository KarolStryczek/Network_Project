// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karol on 2018-12-31.
//

#include "Nodes/Ramp.hpp"
//#include "Simulate.hpp"

bool Ramp::deliverPackage() {
    extern Time turnCounter;
    if( (turnCounter-1)%_deliveryInterval == 0 ){
        Package newPackage;
        _toSendBuffer.first = std::move(newPackage);
        _toSendBuffer.second = true;
        return true;
    }
    else{
        return false;
    }
}

// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)