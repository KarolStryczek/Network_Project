// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karolina on 16.01.2019.
//

#include "Report_Generation/Reporting.hpp"
#include "Nodes/Worker.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>

/**
 * Assistant method used in generateStructureReport() and in generateSimulationTurnReport()
 * to sort list of ramps according to their IDs.
 * @param first: ramp from list of ramps
 * @param second ramp from list of ramps
 * @return
 */
bool compare_ramp_ID (const Ramp &first, const Ramp &second) {
    if (first.getID() < second.getID()) {
        return true;
    }
}

/**
 * Assistant method used in generateStructureReport() and in generateSimulationTurnReport()
 * to sort list of workers according to their IDs.
 * @param first: worker from list of workers
 * @param second worker from list of workers
 * @return
 */
bool compare_worker_ID (const Worker &first, const Worker &second) {
    if (first.getID() < second.getID()) {
        return true;
    }
}

/**
 * Assistant method used in generateStructureReport() and in generateSimulationTurnReport()
 * to sort list of storehouses according to their IDs.
 * @param first: storehouse from list of storehouses
 * @param second storehouse from list of storehouses
 * @return
 */
bool compare_storehouse_ID (const Storehouse &first, const Storehouse &second) {
    if (first.getID() < second.getID()) {
        return true;
    }
}

/**
 * Generates network's structure report into a file or into a console.
 * @param output: std::ofstream if file or std::cout if console
 * @param factory: reference on structure's factory
 */
void generateStructureReport(std::ostream &output, const Factory &factory) {
    std::list<Ramp> ramps_list = factory.getRamps().getNodes();
    ramps_list.sort(compare_ramp_ID);

    std::list<Worker> workers_list = factory.getWorkers().getNodes();
    workers_list.sort(compare_worker_ID);

    std::list<Storehouse> storehouses_list = factory.getStorehouses().getNodes();
    storehouses_list.sort(compare_storehouse_ID);

    output << "== LOADING RAMPS ==\n";
    output << " \n";
    for (const Ramp &ramp: ramps_list) {
        output << "LOADING_RAMP #" << ramp.getID() << "\n";
        output << "  Delivery interval: " << ramp.getDeliveryInterval() << "\n";
        output << "  Receivers:" << "\n";
        //auto = std::map<std::shared_ptr<IPackageReceiver>, double>::const_iterator
        for(auto receiver_it = ramp.getPreferences().cbegin();
        receiver_it != ramp.getPreferences().cend(); ++receiver_it) {
            ReceiverType dest_type = receiver_it->first->getReceiverType();
            std::string dest_type_str;
            if (dest_type == ReceiverType::Worker) {
                dest_type_str = "worker";
            }
            else if (dest_type == ReceiverType::Storehouse) {
                dest_type_str = "storehouse";
            }
            output << "    " << dest_type_str << " #" << receiver_it->first->getID() << "\n";
        }
        output << " \n";
    }

    output << " \n";
    output << "== WORKERS ==\n";
    output << " \n";
    for (const Worker &worker: workers_list) {
        QueueType queue_t = worker.getQueueType();
        std::string queue_t_str;
        if (queue_t == QueueType::FIFO) {
            queue_t_str = "FIFO";
        }
        else if (queue_t == QueueType::LIFO) {
            queue_t_str = "LIFO";
        }
        else {
            queue_t_str = "Invalid QueueType of the worker.";
        }
        output << "WORKER #" << worker.getID() << "\n";
        output << "  Processing time: " << worker.getProcessInterval() << "\n";
        output << "  Queue type: " << queue_t_str << "\n";
        output << "  Receivers:" << "\n";
        //auto = std::map<std::shared_ptr<IPackageReceiver>, double>::const_iterator
        for(auto receiver_it1 = worker.getPreferences().cbegin();
        receiver_it1 != worker.getPreferences().cend(); ++receiver_it1) {
            ReceiverType dest_type1 = receiver_it1->first->getReceiverType();
            std::string dest_type_str1;
            if (dest_type1 == ReceiverType::Worker) {
                dest_type_str1 = "worker";
            }
            else if (dest_type1 == ReceiverType::Storehouse) {
                dest_type_str1 = "storehouse";
            }
            output << "    " << dest_type_str1 << " #" << receiver_it1->first->getID() << "\n";
        }
        output << " \n";
    }

    output << " \n";
    output << "== STOREHOUSES ==\n";
    output << " \n";
    for (const Storehouse &storehouse: storehouses_list) {
        output << "STOREHOUSE #" << storehouse.getID() << "\n";
    }

}

/**
 * Wraps the file into which we want to generate network's structure report with the requirements
 * needed to use generateStructureReport() and uses it.
 * @param filename: name of the file into which we want to generate network's structure report
 * @param factory: reference on structure's factory
 * @return true if there is no errors while opening the file
 */
bool generateStructureReportToFile(std::string filename, const Factory &factory) {
    std::ofstream file_str(filename, std::ios::out | std::ios::trunc);

    if(file_str) {
        generateStructureReport(file_str, factory);
        file_str.close();
        return true;
    }
    else {
        std::cout << "ERROR: You can't open the file." << "\n";
        return false;
    }
}

/**
 * Generates simulation's state report into a file or into a console.
 * @param turn: number of simulation's turn which we want report of
 * @param output: std::ofstream if file or std::cout if console
 * @param factory: reference on structure's factory
 */
void generateSimulationTurnReport(std::ostream &output, const Factory &factory) {
    std::list<Worker> workers_list = factory.getWorkers().getNodes();
    workers_list.sort(compare_worker_ID);

    std::list<Storehouse> storehouses_list = factory.getStorehouses().getNodes();
    storehouses_list.sort(compare_storehouse_ID);

    output << "== WORKERS ==\n";
    output << " \n";
    for (const Worker &worker: workers_list) {
        output << "WORKER #" << worker.getID() << "\n";
        output << "  Queue:";

        const std::pair<Package, int>& pair = worker.getBuffer();
        ElementID first_id = pair.first.getPackageID();
        int first_pt = worker.getProcessInterval()-pair.second;
        output << " #" << first_id << " (pt = " << first_pt << "),";
        //auto = std::deque<Package>::const_iterator
        for(auto queue_it = worker.cbegin(); queue_it != worker.cend()-1; ++queue_it) {
            output << " #" << queue_it->getPackageID() << ",";
        }
        //auto = std::deque<Package>::const_iterator
        auto queue_it_last = worker.cend();
        output << " #" << queue_it_last->getPackageID() << "\n";
        output << "\n";
    }

    output << " \n";
    output << "== STOREHOUSES ==\n";
    output << " \n";
    for (const Storehouse &storehouse: storehouses_list) {
        output << "STOREHOUSE #" << storehouse.getID() << "\n";
        output << "  Queue:";
        //auto = std::deque<Package>::const_iterator
        for(auto queue_it1 = storehouse.cbegin(); queue_it1 != storehouse.cend()-1; ++queue_it1) {
            output << " #" << queue_it1->getPackageID() << ",";
        }
        //auto = std::deque<Package>::const_iterator
        auto queue_it_last1 = storehouse.cend();
        output << " #" << queue_it_last1->getPackageID() << "\n";
        output << "\n";
    }
}

/**
 * Wraps the file into which we want to generate simulation's state report with the requirements
 * needed to use generateSimulationTurnReport() and uses it.
 * @param turn: number of simulation's turn which we want report of
 * @param filename: name of the file into which we want to generate simulation's state report
 * @param factory: reference on structure's factory
 * @return true if there is no errors while opening the file
 */
bool generateSimulationTurnReportToFile(std::string filename, const Factory &factory) {
    std::ofstream file_str(filename, std::ios::out | std::ios::trunc);

    if(file_str) {
        generateSimulationTurnReport(file_str, factory);
        file_str.close();
        return true;
    }
    else {
        std::cout << "ERROR: You can't open the file." << "\n";
        return false;
    }
}
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)