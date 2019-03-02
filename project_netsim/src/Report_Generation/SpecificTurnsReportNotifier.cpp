// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karolina on 16.01.2019.
//

#include "Report_Generation/SpecificTurnsReportNotifier.hpp"

bool SpecificTurnsReportNotifier::shouldGenerateReport(Time time) const {
    if (_turnsSet.find(time) != _turnsSet.cend()) {
        return true;
    }
    return false;
}















// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)