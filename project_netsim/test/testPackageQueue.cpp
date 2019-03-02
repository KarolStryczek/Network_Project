// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karol on 2019-01-13.
//

#include <gtest/gtest.h>
#include "Storage/PackageQueue.hpp"

TEST(PackageQueueTest, Create) {
    // Create default queues and check if they are empty and have proper queue type.
    PackageQueue lifoQueue = PackageQueue(QueueType::LIFO);
    PackageQueue fifoQueue = PackageQueue(QueueType::FIFO);
    EXPECT_EQ(0, lifoQueue.cend() - lifoQueue.cbegin());
    EXPECT_EQ(0, fifoQueue.cend() - fifoQueue.cbegin());
    EXPECT_EQ(QueueType::LIFO, lifoQueue.getQueueType());
    EXPECT_EQ(QueueType::FIFO, fifoQueue.getQueueType());
}

TEST(PackageQueueTest, Push) {
    // Initialize package queues and packages, save packages' IDs.
    PackageQueue lifoQueue = PackageQueue(QueueType::LIFO);
    PackageQueue fifoQueue = PackageQueue(QueueType::FIFO);
    Package package1;
    ElementID package1ID = package1.getPackageID();
    Package package2;
    ElementID package2ID = package2.getPackageID();
    Package package3;
    ElementID package3ID = package3.getPackageID();
    Package package4;
    ElementID package4ID = package4.getPackageID();
    // Push packages to queues.
    lifoQueue.push(std::move(package1));
    lifoQueue.push(std::move(package2));
    fifoQueue.push(std::move(package3));
    fifoQueue.push(std::move(package4));
    // Check if there are 2 packages in each queue and if they are stored in order of being pushed.
    EXPECT_EQ(2, lifoQueue.cend() - lifoQueue.cbegin());
    EXPECT_EQ(2, fifoQueue.cend() - fifoQueue.cbegin());
    EXPECT_EQ(package1ID, lifoQueue.begin()->getPackageID());
    EXPECT_EQ(package2ID, (++lifoQueue.begin())->getPackageID());
    EXPECT_EQ(package3ID, fifoQueue.begin()->getPackageID());
    EXPECT_EQ(package4ID, (++fifoQueue.begin())->getPackageID());
}

TEST(PackageQueueTest, Pop) {
    // Initialize package queues and packages, save packages' IDs.
    PackageQueue lifoQueue = PackageQueue(QueueType::LIFO);
    PackageQueue fifoQueue = PackageQueue(QueueType::FIFO);
    Package package1;
    ElementID package1ID = package1.getPackageID();
    Package package2;
    ElementID package2ID = package2.getPackageID();
    Package package3;
    ElementID package3ID = package3.getPackageID();
    Package package4;
    ElementID package4ID = package4.getPackageID();
    // Push packages to queues
    lifoQueue.push(std::move(package1));
    lifoQueue.push(std::move(package2));
    fifoQueue.push(std::move(package3));
    fifoQueue.push(std::move(package4));
    // LIFO pops last pushed, FIFO pops first pushed.
    EXPECT_EQ(package2ID, lifoQueue.pop().getPackageID());
    EXPECT_EQ(package1ID, lifoQueue.pop().getPackageID());
    EXPECT_EQ(package3ID, fifoQueue.pop().getPackageID());
    EXPECT_EQ(package4ID, fifoQueue.pop().getPackageID());
}
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)