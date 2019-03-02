// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karol on 2019-01-11.
//

#include <memory>
#include "gtest/gtest.h"

#include "Nodes/Worker.hpp"
#include "Storage/PackageQueue.hpp"

/**
 * Test if fields are initialized properly.
 */
TEST(WorkerTest, CreateWorker) {
    ElementID id = 20;
    int processInterval = 2;
    Worker worker = Worker(id, processInterval, std::make_unique<PackageQueue>(QueueType::FIFO));
    EXPECT_EQ(id, worker.getID());
    EXPECT_EQ(ReceiverType::Worker, worker.getReceiverType());
    EXPECT_EQ(QueueType::FIFO, worker.getQueueType());
    EXPECT_EQ(processInterval, worker.getProcessInterval());
}

/**
 * Test if collecting package pushes it at the end of queue.
 */
TEST(WorkerTest, CollectPackage) {
    Package package1;
    Package package2;
    Package package3;
    // Last ID assigned here.
    int i = package3.getPackageID();
    ElementID id = 21;
    int processInterval = 2;
    Worker worker = Worker(id, processInterval, std::make_unique<PackageQueue>(QueueType::FIFO));
    // Packages collected backwards.
    worker.collectPackage(std::move(package3));
    worker.collectPackage(std::move(package2));
    worker.collectPackage(std::move(package1));
    for(const auto& package: worker) {
        EXPECT_EQ(i--, package.getPackageID());
    }
}

/**
 * Test if:
 * - processing package takes appropriate package(determined by queue type)
 * - package is processed for correct time.
 */
TEST(WorkerTest, ProcessPackage) {
    // Packages used in tests.
    Package package1;
    Package package2;
    Package package3;
    Package package4;
    // Packages' IDs to track packages.
    //int package1ID = package1.getPackageID();
    int package2ID = package2.getPackageID();
    int package3ID = package3.getPackageID();
    //int package4ID = package4.getPackageID();
    // Two different types of workers
    ElementID id1 = 22;
    ElementID id2 = 23;
    Worker workerFIFO = Worker(id1, 2, std::make_unique<PackageQueue>(PackageQueue(QueueType::FIFO)));
    Worker workerLIFO = Worker(id2, 1, std::make_unique<PackageQueue>(PackageQueue(QueueType::LIFO)));
    // What if there is no package in worker's queue?
    // Buffer should be empty before processing, and after processing(WorkerFIFO processes for 2 turns).
    EXPECT_EQ(0, workerFIFO.getBuffer().second);
    workerFIFO.process();
    EXPECT_EQ(0, workerFIFO.getBuffer().second);
    // Passing packages to workers.
    workerFIFO.collectPackage(std::move(package1));
    workerFIFO.collectPackage(std::move(package2));
    workerLIFO.collectPackage(std::move(package3));
    workerLIFO.collectPackage(std::move(package4));
    // One turn of processing. FIFO takes first, LIFO takes last Package.
    workerFIFO.process();
    workerLIFO.process();
    // Both have 1 package in queue ( +1 in buffer)
    ASSERT_EQ(1, workerFIFO.cend() - workerFIFO.cbegin());
    for(const auto & package: workerFIFO){
        EXPECT_EQ(package2ID, package.getPackageID());
    }
    ASSERT_EQ(1, workerLIFO.cend() - workerLIFO.cbegin());
    for(const auto & package: workerLIFO){
        EXPECT_EQ(package3ID, package.getPackageID());
    }
    // One more turn processing turn.
    workerFIFO.process();
    workerLIFO.process();
    // Worker with 1 turn processing interval have no packages in queue.
    ASSERT_EQ(1, workerFIFO.cend() - workerFIFO.cbegin());
    ASSERT_EQ(0, workerLIFO.cend() - workerLIFO.cbegin());
}
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)