// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karol on 2018-12-31.
//

#ifndef PROJECT_NETSIM_RAMP_HPP
#define PROJECT_NETSIM_RAMP_HPP

#include "PackageSender.hpp"
#include "DataTypes.hpp"

class Ramp: public PackageSender{
private:
    ElementID _rampID;
    int _deliveryInterval;
public:
    Ramp(ElementID rampID, int deliveryInterval):
        PackageSender(), _rampID(rampID), _deliveryInterval(deliveryInterval) {};

    bool deliverPackage();
    
    ElementID getID() const { return _rampID; }
    int getDeliveryInterval() const {return _deliveryInterval; }
};


#endif //PROJECT_NETSIM_RAMP_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)