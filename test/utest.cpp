#include <gtest/gtest.h>
#include "PatternTracker.h"

TEST(PatternTrackerCase, PatternTrackerCase) {
    Tracker::cPatternTracker tracker = Tracker::cPatternTracker();
    cv::Mat pattern = cv::imread("../assets/pattern.png");
    tracker.setTracker(pattern, cv::Point(160, 120));

    cv::Point target(-1, -1);
    cv::Mat test = cv::imread("../assets/test.png");
    if (tracker.isTracked(test)) {
        tracker.getPoint(target);
    }
    EXPECT_EQ(target.x,102);
    EXPECT_EQ(target.y, 91);
}