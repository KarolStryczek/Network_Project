// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karolina on 05.01.2019.
//

#ifndef PROJECT_NETSIM_IREPORTNOTIFIER_HPP
#define PROJECT_NETSIM_IREPORTNOTIFIER_HPP

#include "DataTypes.hpp"

class IReportNotifier {
public:
    virtual bool shouldGenerateReport(Time time) const = 0;
};



#endif //PROJECT_NETSIM_IREPORTNOTIFIER_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)