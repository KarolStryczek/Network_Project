// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by gosia on 2019-01-20.
//

#include "DataTypes.hpp"
#include "Simulate.hpp"
#include "Factory_Package/Factory.hpp"
#include "Report_Generation/Reporting.hpp"
#include "Report_Generation/IReportNotifier.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;
using ::testing::AtLeast;

class MockSimulate : public Factory{
public:
    MOCK_METHOD0(verifyCohesion, bool());
    MOCK_METHOD0(deliverPackage, bool());
    MOCK_METHOD0(sendPackage, bool());
    MOCK_METHOD0(process, void());
};

TEST(SimulateTest, simulate) {
    Factory factory;
    factory.addRamp(1, 3);
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

    MockSimulate mockSimulate;
    EXPECT_CALL(mockSimulate, verifyCohesion()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(mockSimulate, deliverPackage()).Times(4)
    .WillOnce(Return(true)).WillOnce(Return(true))
    .WillOnce(Return(false)).WillOnce(Return(true));
    EXPECT_CALL(mockSimulate, sendPackage()).Times(AtLeast(4));
    EXPECT_CALL(mockSimulate, process()).Times(AtLeast(2));

}

// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)