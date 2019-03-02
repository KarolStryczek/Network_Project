// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karolina on 05.01.2019.
//

#ifndef PROJECT_NETSIM_REPORTING_HPP
#define PROJECT_NETSIM_REPORTING_HPP

#include "Factory_Package/Factory.hpp"
#include "DataTypes.hpp"

#include <memory>

void generateStructureReport(std::ostream &output, const Factory &factory);
bool generateStructureReportToFile(std::string filename, const Factory &factory);
void generateSimulationTurnReport(std::ostream &output, const Factory &factory);
bool generateSimulationTurnReportToFile(std::string filename, const Factory &factory);

#endif //PROJECT_NETSIM_REPORTING_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)