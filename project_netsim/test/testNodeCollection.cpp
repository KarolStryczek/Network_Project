// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by gosia on 2019-01-13.
//

#include "Factory_Package/NodeCollection.hpp"
#include "Nodes/Ramp.hpp"
#include "Nodes/Worker.hpp"
#include "Nodes/Storehouse.hpp"
#include "DataTypes.hpp"
#include "Storage/PackageQueue.hpp"

#include "gtest/gtest.h"


TEST(NodeCollectionTest, findByID) {
    NodeCollection<Ramp> rampCollection = NodeCollection<Ramp>();
    Ramp ramp1((ElementID) 1, 1);
    rampCollection.add(ramp1);
    Ramp ramp2((ElementID) 2, 2);
    rampCollection.add(ramp2);
    Ramp ramp_test = *(rampCollection.findByID((ElementID) 1));
    EXPECT_EQ(ramp1.getID(), ramp_test.getID());
    EXPECT_EQ(ramp1.getPreferences(), ramp_test.getPreferences());


    NodeCollection<Worker> workerCollection;
    Worker worker1((ElementID) 1, 1, std::make_unique<PackageQueue>(QueueType::FIFO));
    auto worker1_ptr = std::make_shared<Worker>(std::move(worker1));
    workerCollection.add(std::move(worker1));
    Worker worker2((ElementID) 2, 1, std::make_unique<PackageQueue>(QueueType::FIFO));
    workerCollection.add(std::move(worker2));
    auto worker_test_iter = workerCollection.findByID((ElementID) 1);
    EXPECT_EQ(worker1_ptr -> getID(), worker_test_iter -> getID());
    EXPECT_EQ(worker1_ptr -> getPreferences(), worker_test_iter -> getPreferences());


    NodeCollection<Storehouse> storehouseCollection;
    Storehouse storehouse1((ElementID) 1, std::make_unique<PackageQueue>(QueueType::FIFO));
    auto storehouse_ptr = std::make_shared<Storehouse>(std::move(storehouse1));
    storehouseCollection.add(std::move(storehouse1));
    Storehouse storehouse2((ElementID) 2, std::make_unique<PackageQueue>(QueueType::FIFO));
    storehouseCollection.add(std::move(storehouse2));
    auto storehouse_iter_test = storehouseCollection.findByID((ElementID) 1);
    EXPECT_EQ(storehouse_ptr -> getID(), storehouse_iter_test -> getID());
}



TEST(NodeCollectionTest, removeByID) {
    NodeCollection<Ramp> rampCollection;
    Ramp ramp3(3, 1);
    rampCollection.add(ramp3);
    Ramp ramp4(4, 1);
    rampCollection.add(ramp4);
    rampCollection.removeByID(3);
    EXPECT_TRUE(rampCollection.findByID(3) == rampCollection.end());


    NodeCollection<Worker> workerCollection;
    Worker worker1((ElementID) 1, 1, std::make_unique<PackageQueue>(QueueType::FIFO));
    auto worker1_ptr = std::make_shared<Worker>(std::move(worker1));
    workerCollection.add(std::move(worker1));
    Worker worker2((ElementID) 2, 1, std::make_unique<PackageQueue>(QueueType::FIFO));
    workerCollection.add(std::move(worker2));
    workerCollection.removeByID(1);
    EXPECT_TRUE(workerCollection.findByID(1) == workerCollection.end());


    NodeCollection<Storehouse> storehouseCollection;
    Storehouse storehouse1((ElementID) 1, std::make_unique<PackageQueue>(QueueType::FIFO));
    auto storehouse_ptr = std::make_shared<Storehouse>(std::move(storehouse1));
    storehouseCollection.add(std::move(storehouse1));
    Storehouse storehouse2((ElementID) 2, std::make_unique<PackageQueue>(QueueType::FIFO));
    storehouseCollection.add(std::move(storehouse2));
    storehouseCollection.removeByID(1);
    EXPECT_TRUE(storehouseCollection.findByID(1) == storehouseCollection.end());
}

// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)