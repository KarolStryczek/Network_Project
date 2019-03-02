//
// Created by Karol on 2019-01-17.
//

#include <gtest/gtest.h>
#include "Storage/Package.hpp"

TEST(PackageTest, Create) {
    // Test if Packages' IDs if are assigned uniquely.
    Package previousPackage;
    for(int i = 1; i < 10; i++) {
        Package nextPackage;
        EXPECT_EQ(nextPackage.getPackageID()-1, previousPackage.getPackageID());
        previousPackage = nextPackage;
    }
}