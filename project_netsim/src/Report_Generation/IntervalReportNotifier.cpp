// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karolina on 16.01.2019.
//

#include "Report_Generation/IntervalReportNotifier.hpp"

bool IntervalReportNotifier::shouldGenerateReport(Time time) const {
    if(!(time % _intervalBetweenTurns)){
        return true;
    }
    else {
        return false;
    }
}




// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)