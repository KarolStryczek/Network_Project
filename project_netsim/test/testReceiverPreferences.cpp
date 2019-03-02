// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karol on 2019-01-12.
//


#include "gtest/gtest.h"

#include "Nodes/ReceiverPreferences.hpp"
#include "Storage/PackageQueue.hpp"
#include "Nodes/Worker.hpp"

/**
 * Test if receiverPreferences objects are initialized with empty map(next tests base on this assumption).
 */
TEST(ReceiverPreferencesTest, Create) {
    ReceiverPreferences receiverPreferences;
    std::map<std::shared_ptr<IPackageReceiver>, double> emptyMap;
    EXPECT_EQ(emptyMap, receiverPreferences.getPreferences());
}

/**
 * Test if adding and removing receiver works properly, and returns expected boolean value.
 */
TEST(ReceiverPreferencesTest, AddRemove) {
    // Default (random) ReceiverPreferences
    ReceiverPreferences receiverPreferences;

    // Create some different workers
    Worker worker1 = Worker((ElementID) 11, 1, std::make_unique<PackageQueue>(PackageQueue(QueueType::FIFO)));
    std::shared_ptr<IPackageReceiver> worker1Ptr = std::make_shared<Worker>(std::move(worker1));
    Worker worker2 = Worker((ElementID) 12, 3, std::make_unique<PackageQueue>(PackageQueue(QueueType::LIFO)));
    std::shared_ptr<IPackageReceiver> worker2Ptr= std::make_shared<Worker>(std::move(worker2));
    Worker worker3 = Worker((ElementID) 13, 2, std::make_unique<PackageQueue>(PackageQueue(QueueType::FIFO)));
    std::shared_ptr<IPackageReceiver> worker3Ptr= std::make_shared<Worker>(std::move(worker3));

    // Assert empty preferences map at the beginning.
    std::map<std::shared_ptr<IPackageReceiver>, double> emptyMap;
    ASSERT_EQ(emptyMap, receiverPreferences.getPreferences());

    // Adding receivers with the same priority
    receiverPreferences.addReceiver(worker1Ptr, 1);
    receiverPreferences.addReceiver(worker2Ptr, 1);
    receiverPreferences.addReceiver(worker3Ptr, 1);

    auto iter = receiverPreferences.begin();
    EXPECT_EQ(worker1Ptr, iter->first);
    EXPECT_EQ(worker2Ptr, (++iter)->first);
    EXPECT_EQ(worker3Ptr, (++iter)->first);

    // Checking if add/remove methods return boolean values properly
    EXPECT_FALSE(receiverPreferences.addReceiver(worker1Ptr, 1));
    EXPECT_TRUE(receiverPreferences.removeReceiver(worker1Ptr));
    EXPECT_FALSE(receiverPreferences.removeReceiver(worker1Ptr));
}

/**
 * Test if choosing works properly for mocked choosing function.
 */
TEST(ReceiverPreferencesTest, Choose) {
    int i = 1;
    // Determine choosing receiver. Lambda returns 0.2, 0.4, 0.6, 0.8, 0.2 ...
    ReceiverPreferences receiverPreferences = ReceiverPreferences([i]() mutable { return ((i++)%5)/5.0; });

    // Create some different workers
    Worker worker1 = Worker((ElementID) 11, 1, std::make_unique<PackageQueue>(PackageQueue(QueueType::FIFO)));
    std::shared_ptr<IPackageReceiver> worker1Ptr = std::make_shared<Worker>(std::move(worker1));
    Worker worker2 = Worker((ElementID) 12, 3, std::make_unique<PackageQueue>(PackageQueue(QueueType::LIFO)));
    std::shared_ptr<IPackageReceiver> worker2Ptr= std::make_shared<Worker>(std::move(worker2));
    Worker worker3 = Worker((ElementID) 13, 2, std::make_unique<PackageQueue>(PackageQueue(QueueType::FIFO)));
    std::shared_ptr<IPackageReceiver> worker3Ptr= std::make_shared<Worker>(std::move(worker3));

    // Choosing when there is no receiver
    EXPECT_THROW(receiverPreferences.chooseReceiver(), std::domain_error);

    // Adding receivers with the same priority
    receiverPreferences.addReceiver(worker1Ptr);
    receiverPreferences.addReceiver(worker2Ptr);
    receiverPreferences.addReceiver(worker3Ptr);

    // Expected values of distribute function are 0.2, 0.4, 0.6, 0.8, which stand for Workers number: 1, 2, 2, 3.
    EXPECT_EQ(worker1Ptr->getID(), receiverPreferences.chooseReceiver()->getID());
    EXPECT_EQ(worker2Ptr->getID(), receiverPreferences.chooseReceiver()->getID());
    EXPECT_EQ(worker2Ptr->getID(), receiverPreferences.chooseReceiver()->getID());
    EXPECT_EQ(worker3Ptr->getID(), receiverPreferences.chooseReceiver()->getID());
}
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)