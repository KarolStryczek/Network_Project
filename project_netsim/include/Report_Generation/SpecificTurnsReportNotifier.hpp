// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karolina on 05.01.2019.
//

#ifndef PROJECT_NETSIM_SPECIFICTURNSREPORTNOTIFIER_HPP
#define PROJECT_NETSIM_SPECIFICTURNSREPORTNOTIFIER_HPP

#include "IReportNotifier.hpp"
#include <set>

class SpecificTurnsReportNotifier: public IReportNotifier {
private:
    std::set<Time> _turnsSet;
public:
    explicit SpecificTurnsReportNotifier(std::set<Time> turnsSet): _turnsSet(std::move(turnsSet)) {};
    bool shouldGenerateReport(Time time) const override;
    std::set<Time> getTurnsSet() const { return _turnsSet; };
};
#endif //PROJECT_NETSIM_SPECIFICTURNSREPORTNOTIFIER_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)