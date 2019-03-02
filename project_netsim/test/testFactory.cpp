// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by gosia on 2019-01-13.
//

#include "Factory_Package/Factory.hpp"
#include "Nodes/Ramp.hpp"
#include "Nodes/Worker.hpp"
#include "Nodes/Storehouse.hpp"
#include "gtest/gtest.h"
#include <Storage/PackageQueue.hpp>


TEST(FactoryTest, verifyCohesion) {
    Factory factory;
    factory.addRamp(1, 1);
    factory.addRamp(2, 1);
    factory.addWorker(1, 1, QueueType::FIFO);
    factory.addWorker(2, 1, QueueType::FIFO);
    factory.addStorehouse(1);
    factory.addLink(ElementsOfNetwork::Ramp, 1, ElementsOfNetwork::Worker, 1);
    factory.addLink(ElementsOfNetwork::Ramp, 2, ElementsOfNetwork::Worker, 1);
    factory.addLink(ElementsOfNetwork::Ramp, 2, ElementsOfNetwork::Worker, 2);
    factory.addLink(ElementsOfNetwork::Worker, 1, ElementsOfNetwork::Worker, 1);
    factory.addLink(ElementsOfNetwork::Worker, 1, ElementsOfNetwork::Worker, 2);
    factory.addLink(ElementsOfNetwork::Worker, 2, ElementsOfNetwork::Storehouse, 1);
    EXPECT_TRUE(factory.verifyCohesion());
}

TEST(FactoryTest, removeWorker) {
    Factory factory;
    factory.addRamp(1, 1);
    factory.addWorker(1, 1, QueueType::FIFO);
    factory.addWorker(2, 1, QueueType::FIFO);
    factory.addLink(ElementsOfNetwork::Ramp, 1, ElementsOfNetwork::Worker, 1);
    factory.addLink(ElementsOfNetwork::Ramp, 1, ElementsOfNetwork::Worker, 2);
    factory.removeWorkerByID(1);
    NodeCollection<Ramp>::iterator ramp_ptr = factory.findRampByID(1);
    for (const auto ramp_pref : ramp_ptr->getPreferences()) {
        auto worker_ptr = ramp_pref.first;
        EXPECT_FALSE(worker_ptr->getID() == 1);
    }
}


TEST(FactoryTest, removeStorehouse) {
        Factory factory;
        factory.addWorker(1, 1, QueueType::FIFO);
        factory.addStorehouse(1);
        factory.addStorehouse(2);
        factory.addLink(ElementsOfNetwork::Worker, 1, ElementsOfNetwork::Storehouse, 1);
        factory.addLink(ElementsOfNetwork::Worker, 1, ElementsOfNetwork::Storehouse, 2);
        factory.removeStorehouseByID(1);
        NodeCollection<Worker>::iterator worker_ptr = factory.findWorkerByID(1);
        for (const auto worker_pref : worker_ptr -> getPreferences()) {
            auto storehouse_ptr = worker_pref.first;
            EXPECT_FALSE(storehouse_ptr -> getID() == 1);
        }
    }

// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)