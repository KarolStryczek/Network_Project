// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)

#ifndef PROJEKT_FACTORY_HPP
#define PROJEKT_FACTORY_HPP


#include <IO.hpp>
#include "NodeCollection.hpp"
#include "Nodes/Ramp.hpp"
#include "Nodes/Worker.hpp"
#include "Nodes/Storehouse.hpp"
#include "IO.hpp"

class Factory {
private:
    NodeCollection<Ramp> _ramps;
    NodeCollection<Worker> _workers;
    NodeCollection<Storehouse> _storehouses;
    void removeLink(ElementsOfNetwork src_node_type, ElementID src_node_id, ElementsOfNetwork dest_node_type, ElementID dest_node_id);
    bool isOkWorker(std::unique_ptr<Worker> worker_ptr);
public:
    Factory() : _ramps(), _workers(), _storehouses() {};
    iterator<Ramp> findRampByID(ElementID rampID);
    iterator<Worker> findWorkerByID(ElementID workerID);
    iterator<Storehouse> findStorehouseByID(ElementID storehouseID);
    void removeRampByID(ElementID rampID);
    void removeWorkerByID(ElementID workerID);
    void removeStorehouseByID(ElementID storehouseID);
    void addRamp(ElementID rampID, int deliveryInterval);
    void addWorker(ElementID workerID, int processInterval,  QueueType queue_qt);
    void addStorehouse(ElementID storehouseID);
    void addLink(ElementsOfNetwork src_node_type, ElementID src_node_id, ElementsOfNetwork dest_node_type, ElementID dest_node_id);
    NodeCollection<Ramp> getRamps() const { return _ramps; }
    NodeCollection<Worker> getWorkers() const { return _workers; }
    NodeCollection<Storehouse> getStorehouses() const { return _storehouses; }

    bool verifyCohesion();
};

#endif //PROJEKT_FACTORY_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)