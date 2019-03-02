// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karol on 2019-01-18.
//

#include "DataTypes.hpp"
//#include "Simulate.hpp"
//#include "Factory_Package/Factory.hpp"
//#include "Report_Generation/Reporting.hpp"

Time turnCounter;
/*

void simulate(Factory & factory, std::ostream &output, const std::shared_ptr<IReportNotifier> reportNotifier_ptr) {
    factory.verifyCohesion();
    for (turnCounter = 1; turnCounter <= 2; turnCounter++) {
        //etap 1
        for (auto ramp_ptr = factory.getRamps().begin(); ramp_ptr != factory.getRamps().end(); ramp_ptr++) {
            ramp_ptr->deliverPackage();
        }
        //etap 2
        for (auto ramp_ptr = factory.getRamps().begin(); ramp_ptr != factory.getRamps().end(); ramp_ptr++) {
            ramp_ptr->sendPackage();
        }
        for (auto worker_ptr = factory.getWorkers().begin();
             worker_ptr != factory.getWorkers().end(); worker_ptr++) {
            worker_ptr->sendPackage();
        }

        //etap 3
        for (auto worker_ptr = factory.getWorkers().begin();
             worker_ptr != factory.getWorkers().end(); worker_ptr++) {
            worker_ptr->process();
        }

        //raportowanie
        if (reportNotifier_ptr -> shouldGenerateReport(turnCounter)) {
            generateSimulationTurnReport(output, factory);
        }
}


}
 */

// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)