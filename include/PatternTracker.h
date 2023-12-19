#ifndef PATTERN_TRACKER_H_
#define PATTERN_TRACKER_H_

#include <iostream>

#include "opencv2/opencv.hpp"
#include "opencv2/tracking/tracking.hpp"

namespace Tracker {

class cPatternTracker {
public:
    cPatternTracker();
    cPatternTracker(const int &size);

    bool setTracker(const cv::Mat &frame, const cv::Point &point);
    bool isTracked(const cv::Mat &frame);

    void getPoint(cv::Point &point) const;
    void release();

private:
    cv::Rect m_pattern;
    cv::Point m_point;
    cv::Ptr<cv::TrackerCSRT> m_tracker;

    int m_pattern_size;
};

}

#endif // PATTERN_TRACKER_H_