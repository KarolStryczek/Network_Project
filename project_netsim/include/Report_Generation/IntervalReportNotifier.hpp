// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karolina on 05.01.2019.
//

#ifndef PROJECT_NETSIM_INTERVALREPORTNOTIFIER_HPP
#define PROJECT_NETSIM_INTERVALREPORTNOTIFIER_HPP

#include "IReportNotifier.hpp"
#include "DataTypes.hpp"

class IntervalReportNotifier: public IReportNotifier {
private:
    TimeOffset _intervalBetweenTurns;
public:
    explicit IntervalReportNotifier(TimeOffset intervalBetweenTurns): _intervalBetweenTurns(intervalBetweenTurns) {};
    bool shouldGenerateReport(Time time) const override;
    TimeOffset getIntervalBetweenTurns() const { return _intervalBetweenTurns; };
};

#endif //PROJECT_NETSIM_INTERVALREPORTNOTIFIER_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)