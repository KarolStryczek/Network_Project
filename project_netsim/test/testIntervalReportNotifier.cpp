// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karolina on 16.01.2019.
//

#include "gtest/gtest.h"
#include "Report_Generation/IntervalReportNotifier.hpp"

/**
 * Test whether the notification is in a good turn.
 */
TEST(ReportNotifierTest, Interval) {
    Time one = 1;
    Time seven = 7;
    Time two = 2;
    Time four = 4;
    Time six = 6;
    TimeOffset intervalBetweenTurns = 2;
    auto interval_report_notifier = IntervalReportNotifier(intervalBetweenTurns);
    EXPECT_TRUE(interval_report_notifier.shouldGenerateReport(two));
    EXPECT_TRUE(interval_report_notifier.shouldGenerateReport(four));
    EXPECT_TRUE(interval_report_notifier.shouldGenerateReport(six));
    EXPECT_FALSE(interval_report_notifier.shouldGenerateReport(one));
    EXPECT_FALSE(interval_report_notifier.shouldGenerateReport(seven));
}


















// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)