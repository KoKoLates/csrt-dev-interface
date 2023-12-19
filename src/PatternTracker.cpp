#include "PatternTracker.h"

namespace Tracker {

cPatternTracker::cPatternTracker() {
    m_point = cv::Point(-1, -1);
    m_pattern_size = 40;
}

cPatternTracker::cPatternTracker(const int &size) {
    m_point = cv::Point(-1, -1);
    m_pattern_size = size;
}

bool
cPatternTracker::setTracker(const cv::Mat &frame, const cv::Point &point) {
    m_point = point;
    cv::Size frame_size = frame.size();
    if (!m_tracker.get()) {
        m_tracker = cv::TrackerCSRT::create();
    }

    if (m_point.x != -1 && m_point.y != -1) {
        int x1 = std::max(0, m_point.x - m_pattern_size / 2);
        int y1 = std::max(0, m_point.y - m_pattern_size / 2);
        int x2 = std::min(m_point.x + m_pattern_size / 2, frame_size.width);
        int y2 = std::min(m_point.y + m_pattern_size / 2, frame_size.height);

        m_pattern = cv::Rect(x1, y1, x2 - x1, y2 - y1);
        m_tracker->init(frame, m_pattern);
        return true;
    }
    return false;
}

bool 
cPatternTracker::isTracked(const cv::Mat &frame) {
    if (!m_pattern.empty() && !m_tracker.empty()) {
        cv::Rect results;
        m_tracker->update(frame, results);
        cv::rectangle(frame, results, cv::Scalar(0, 255, 255), 2);
        m_point.x = results.x + results.width / 2;
        m_point.y = results.y + results.height / 2;
        return m_point.x != 0 || m_point.y != 0;
    }
    return false;
}

void
cPatternTracker::getPoint(cv::Point &point) const {
    point = m_point;
}

void
cPatternTracker::release() {
    m_tracker.release();
}

}