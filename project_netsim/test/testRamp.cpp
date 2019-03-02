//
// Created by Karol on 2019-01-18.
//

#include "gtest/gtest.h"
#include "Nodes/Ramp.hpp"
#include "Nodes/Storehouse.hpp"
#include "Storage/PackageQueue.hpp"

TEST(RampTest, RampCreate) {
    extern Time turnCounter;
    turnCounter = 1;
    Ramp ramp = Ramp((ElementID) 1, 2);
    EXPECT_EQ((ElementID) 1, ramp.getID());
    EXPECT_EQ(2, ramp.getDeliveryInterval());
    EXPECT_TRUE(ramp.deliverPackage());
    EXPECT_ANY_THROW(ramp.sendPackage());
    turnCounter++;
    EXPECT_FALSE(ramp.deliverPackage());
    EXPECT_ANY_THROW(ramp.sendPackage());
}

TEST(RampTest, RampDeliver) {
    extern Time turnCounter;
    turnCounter = 1;
    Ramp ramp = Ramp((ElementID) 1, 2);
    Storehouse storehouse = Storehouse((ElementID) 3, std::make_unique<PackageQueue>(QueueType::FIFO));
    std::shared_ptr<IPackageReceiver> storehousePtr = std::make_shared<Storehouse>(std::move(storehouse));
    ramp.addReceiver(storehousePtr);
    // Storehouse is empty at the beginning
    EXPECT_EQ(0, storehousePtr->cend() - storehousePtr->cbegin());
    // First turn
    ramp.deliverPackage(); // Turn 1, package delivered
    ramp.sendPackage();
    EXPECT_EQ(1, storehousePtr->cend() - storehousePtr->cbegin());
    turnCounter++;
    ramp.deliverPackage(); // Turn 2, no package delivered
    ramp.sendPackage();
    EXPECT_EQ(1, storehousePtr->cend() - storehousePtr->cbegin());
}