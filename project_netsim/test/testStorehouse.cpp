//
// Created by Karol on 2019-01-17.
//

#include "gtest/gtest.h"
#include "Nodes/Storehouse.hpp"
#include "Storage/PackageQueue.hpp"

TEST(StorehouseTest, Create) {
    Storehouse storehouse = Storehouse((ElementID) 1, std::make_unique<PackageQueue>(QueueType::FIFO));
    EXPECT_EQ(0, storehouse.cend() - storehouse.cbegin());
}

TEST(StorehouseTest, Collect) {
    Storehouse storehouse = Storehouse((ElementID) 1, std::make_unique<PackageQueue>(QueueType::FIFO));
    Package package1;
    ElementID package1ID = package1.getPackageID();
    Package package2;
    ElementID package2ID = package2.getPackageID();
    storehouse.collectPackage(std::move(package1));
    storehouse.collectPackage(std::move(package2));
    // Check if packages are stored in proper order.
    EXPECT_EQ(package1ID, storehouse.cbegin()->getPackageID());
    EXPECT_EQ(package2ID, (storehouse.cbegin()+1)->getPackageID());
}