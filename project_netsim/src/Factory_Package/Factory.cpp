// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by gosia on 2019-01-11.
//
#include "Nodes/Ramp.hpp"
#include "Factory_Package/Factory.hpp"
#include "Nodes/Storehouse.hpp"
#include "Nodes/Worker.hpp"
#include "Factory_Package/NodeCollection.hpp"
#include "Nodes/ReceiverPreferences.hpp"
#include "Nodes/IPackageReceiver.hpp"
#include "Storage/PackageQueue.hpp"

#include <list>


NodeCollection<Ramp>::iterator Factory::findRampByID(ElementID rampID) {
    return _ramps.findByID(rampID);
}

NodeCollection<Worker>::iterator Factory::findWorkerByID(ElementID workerID) {
    return _workers.findByID(workerID);
}

NodeCollection<Storehouse>::iterator Factory::findStorehouseByID(ElementID storehouseID) {
    return _storehouses.findByID(storehouseID);
}

void Factory::addRamp(ElementID rampID, int deliveryInterval) {
    Ramp ramp(rampID, deliveryInterval);
    _ramps.add(ramp);
}

void Factory::addWorker(ElementID workerID, int processInterval, QueueType queue_qt) {
    std::unique_ptr<IPackageQueue> queue_ptr = std::make_unique<PackageQueue>(queue_qt);
    Worker worker(workerID, processInterval, std::move(queue_ptr));
    _workers.add(std::move(worker));
}

void Factory::addStorehouse(ElementID storehouseID) {
    std::unique_ptr<IPackageStockpile> packageStockpile = std::make_unique<PackageQueue>(QueueType::FIFO);
    Storehouse storehouse(storehouseID, std::move(packageStockpile));
    _storehouses.add(std::move(storehouse));
}




void Factory::removeRampByID(ElementID rampID) {
    _ramps.removeByID(rampID);
}

void Factory::removeWorkerByID(ElementID workerID) {
    for (auto it = _ramps.begin(); it != _ramps.end(); it++) {
        auto ramp_prefs = it -> getPreferences();
        for (auto it_pref =  ramp_prefs.cbegin(); it_pref != ramp_prefs.cend(); it_pref++) {
            auto worker_ptr = it_pref -> first;
            if (worker_ptr -> getID() == workerID) {
                removeLink(ElementsOfNetwork ::Ramp, it -> getID(),ElementsOfNetwork::Worker, workerID);
            }
        }
    }
    for (auto it = _workers.begin(); it != _workers.end(); it++) {
        auto worker_prefs = it -> getPreferences();
        for (auto it_pref =  worker_prefs.cbegin(); it_pref != worker_prefs.cend(); it_pref++) {
            auto worker_ptr = it_pref -> first;
            if (worker_ptr -> getID() == workerID) {
                removeLink(ElementsOfNetwork::Worker, it -> getID(),ElementsOfNetwork::Worker, workerID);
            }
        }
    }
    _workers.removeByID(workerID);
}

void Factory::removeStorehouseByID(ElementID storehouseID) {
    for (auto it = _workers.begin(); it != _workers.end(); it++) {
        auto worker_prefs = it -> getPreferences();
        for (auto it_pref =  worker_prefs.cbegin(); it_pref != worker_prefs.cend(); it_pref++) {
            auto worker_ptr = it_pref -> first;
            if (worker_ptr -> getID() == storehouseID) {
                removeLink(ElementsOfNetwork::Worker, worker_ptr -> getID(), ElementsOfNetwork::Storehouse, storehouseID);
            }
        }
    }
    return _storehouses.removeByID(storehouseID);
}

void Factory::removeLink(ElementsOfNetwork src_node_type, ElementID src_node_id,ElementsOfNetwork dest_node_type, ElementID dest_node_id) {
    if (src_node_type == ElementsOfNetwork::Ramp) {
        Ramp src_node =  *(findRampByID(src_node_id));
        if (dest_node_type == ElementsOfNetwork::Worker) {
            Worker dest_node =  *(findWorkerByID(dest_node_id));
            std::shared_ptr<IPackageReceiver> dest_node_ptr = std::make_shared<Worker>(dest_node);
            src_node.removeReceiver(dest_node_ptr);
        }
        if (dest_node_type == ElementsOfNetwork::Storehouse) {
            Storehouse dest_node =  *(findStorehouseByID(dest_node_id));
            std::shared_ptr<IPackageReceiver> dest_node_ptr = std::make_shared<Storehouse>(dest_node);
            src_node.removeReceiver(dest_node_ptr);
        }
    }
    if (src_node_type == ElementsOfNetwork::Worker) {
        Worker src_node =  *(findWorkerByID(src_node_id));
        if (dest_node_type == ElementsOfNetwork::Worker) {
            Worker dest_node =  *(findWorkerByID(dest_node_id));
            std::shared_ptr<IPackageReceiver> dest_node_ptr = std::make_shared<Worker>(dest_node);
            src_node.removeReceiver(dest_node_ptr);
        }
        if (dest_node_type == ElementsOfNetwork::Storehouse) {
            Storehouse dest_node =  *(findStorehouseByID(dest_node_id));
            std::shared_ptr<IPackageReceiver> dest_node_ptr = std::make_shared<Storehouse>(dest_node);
            src_node.removeReceiver(dest_node_ptr);
        }
    }
}



void Factory::addLink(ElementsOfNetwork src_node_type, ElementID src_node_id, ElementsOfNetwork dest_node_type, ElementID dest_node_id) {
    if (src_node_type == ElementsOfNetwork::Ramp) {
        Ramp src_node =  *(findRampByID(src_node_id));
        if (dest_node_type == ElementsOfNetwork::Worker) {
            Worker dest_node =  *(findWorkerByID(dest_node_id));
            std::shared_ptr<IPackageReceiver> dest_node_ptr = std::make_shared<Worker>(dest_node);
            src_node.addReceiver(dest_node_ptr);

        }
        if (dest_node_type == ElementsOfNetwork::Storehouse) {
            Storehouse dest_node =  *(findStorehouseByID(dest_node_id));
            std::shared_ptr<IPackageReceiver> dest_node_ptr = std::make_shared<Storehouse>(dest_node);
            src_node.addReceiver(dest_node_ptr);
        }
    }
    if (src_node_type == ElementsOfNetwork::Worker) {
        Worker src_node =  *(findWorkerByID(src_node_id));
        if (dest_node_type == ElementsOfNetwork::Worker) {
            Worker dest_node =  *(findWorkerByID(dest_node_id));
            std::shared_ptr<IPackageReceiver> dest_node_ptr = std::make_shared<Worker>(dest_node);
            src_node.addReceiver(dest_node_ptr);

        }
        if (dest_node_type == ElementsOfNetwork::Storehouse) {
            Storehouse dest_node =  *(findStorehouseByID(dest_node_id));
            std::shared_ptr<IPackageReceiver> dest_node_ptr = std::make_shared<Storehouse>(dest_node);
            src_node.addReceiver(dest_node_ptr);
        }
    }
}


bool Factory::verifyCohesion() {
    // czy wszystkie połączenia są z istniejącymi węzłami
    for (auto it = _ramps.begin(); it != _ramps.end(); it++) {
        auto ramp_prefs = it -> getPreferences();
        for (auto it_pref =  ramp_prefs.cbegin(); it_pref != ramp_prefs.cend(); it_pref++) {
            auto worker_ptr = it_pref -> first;
            ElementID worker_id= worker_ptr -> getID();
            if (Factory::findWorkerByID(worker_id) == std::nullopt) {
                throw std::runtime_error("W preferencjach rampy " + std::to_string(it -> getID()) + " jest nieistniejący pracownik!");
            }
        }
    }
    for (auto it = _workers.begin(); it != _workers.end(); it++) {
        auto worker_prefs = it -> getPreferences();
        for (auto it_pref =  worker_prefs.cbegin(); it_pref != worker_prefs.cend(); it_pref++) {
            auto dest_ptr = it_pref -> first;
            ElementID dest_id= dest_ptr -> getID();
            if (Factory::findWorkerByID(dest_id) == std::nullopt && Factory::findStorehouseByID(dest_id) == std::nullopt) {
                throw std::runtime_error( "W preferencjach pracownika " + std::to_string(it -> getID()) + " jest nieistniejący pracownik lub rampa!");
            }

        }
    }

//czy paczka trafia do magazynu
    for (auto it = _ramps.begin(); it != _ramps.end(); it++) {
        std::map<std::shared_ptr<IPackageReceiver>, double> ramp_prefs = it -> getPreferences();
        for (auto it_pref =  ramp_prefs.cbegin(); it_pref != ramp_prefs.cend(); it_pref++) {
            std::unique_ptr<Worker> worker_ptr = std::make_unique<Worker>(it_pref -> first);
            return Factory::isOkWorker(std::move(worker_ptr));
        }
    }

}

bool Factory::isOkWorker(std::unique_ptr<Worker> worker_src_ptr) {
    auto worker_src_prefs = worker_src_ptr -> getPreferences();
    //sprwdzenie, czy preferences są puste
    if (worker_src_prefs.empty()) {
        throw std::logic_error("Pracownik " + std::to_string(worker_src_ptr -> getID()) + " nie ma odbiorcy!");
    }
    for (auto it_pref =  worker_src_prefs.cbegin(); it_pref != worker_src_prefs.cend(); it_pref++) {
        auto dest_ptr = it_pref -> first;
        if (dest_ptr -> getReceiverType() == ReceiverType::Storehouse) {
            return true;
        }
        else if (dest_ptr -> getReceiverType() == ReceiverType::Worker) {
            std::unique_ptr<Worker> worker_dest_ptr = std::make_unique<Worker>(dest_ptr);
            return Factory::isOkWorker(std::move(worker_dest_ptr));
        }
        else {
            throw std::logic_error("Nieznany typ odbiorcy dla pracownika " + std::to_string(worker_src_ptr -> getID()) + "!");
        }
    }
}


// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)