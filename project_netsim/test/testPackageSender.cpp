// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karol on 2019-01-12.
//

#include "Nodes/Worker.hpp"
#include "Storage/PackageQueue.hpp"
#include "gtest/gtest.h"

#include "Nodes/PackageSender.hpp"

/**
 * Test if default packageSender properly initializes its preferences field with empty map.
 * (next tests base on this assumption).
 */
TEST(PackageSenderTest, Create) {
    PackageSender packageSender;
    preferencesT emptyPreferences;
    EXPECT_EQ(emptyPreferences, packageSender.getPreferences());
}

/**
 * Test if sending package(and placing package in toSendBuffer by Worker) works properly.
 */
TEST(PackageSenderTest, SendPackage) {
    // Create some packages
    Package package1;
    ElementID package1ID = package1.getPackageID();
    Package package2;
    // Create workerSender which is packageSender extension.
    Worker workerSender((ElementID) 10, 1, std::make_unique<PackageQueue>(QueueType::FIFO));
    // Create shared pointer to worker
    Worker workerReceiver((ElementID) 11, 2, std::make_unique<PackageQueue>(QueueType::FIFO));
    std::shared_ptr<IPackageReceiver> workerReceiverPtr = std::make_shared<Worker>(std::move(workerReceiver));
    // Add worker as receiver for packageSender
    EXPECT_TRUE(workerSender.addReceiver(workerReceiverPtr, 1));
    // Give packages to workerSender
    workerSender.collectPackage(std::move(package1));
    workerSender.collectPackage(std::move(package2));
    // Nothing to send
    EXPECT_FALSE(workerSender.sendPackage());
    // Expect receiver has no packages
    EXPECT_EQ(0, workerReceiverPtr->cend() - workerReceiverPtr->cbegin());
    // Process and send
    workerSender.process();
    // Package can be sent
    EXPECT_TRUE(workerSender.sendPackage());
    // Package 1 is now owned by workerReceiver
    EXPECT_EQ(package1ID, workerReceiverPtr->cbegin()->getPackageID());
    // Can't sent another package when there is no package in buffer
    EXPECT_FALSE(workerSender.sendPackage());
}
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)