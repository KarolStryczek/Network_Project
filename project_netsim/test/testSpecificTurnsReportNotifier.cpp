// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karolina on 16.01.2019.
//

#include "gtest/gtest.h"
#include "Report_Generation/SpecificTurnsReportNotifier.hpp"

/**
 * Test whether the notification is in a good turn.
 */
TEST(ReportNotifierTest, SpecificTurns) {
    Time one = 1;
    Time two = 2;
    Time three = 3;
    std::set<Time> turnSet = {1,2};
    auto specific_turns_report_notifier = SpecificTurnsReportNotifier(turnSet);
    EXPECT_TRUE(specific_turns_report_notifier.shouldGenerateReport(one));
    EXPECT_TRUE(specific_turns_report_notifier.shouldGenerateReport(two));
    EXPECT_FALSE(specific_turns_report_notifier.shouldGenerateReport(three));
}


















// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)