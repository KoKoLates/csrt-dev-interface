#include <iostream>
#include "PatternTracker.h"

class TrackerCallback {
public:
    struct TrackerObject {
        cv::Mat &frame;
        Tracker::cPatternTracker &tracker;
    };

    static void
    mouseCallback(int event, int x, int y, int flags, void *param) {
        TrackerObject *object = static_cast<TrackerObject*>(param);
        cv::Mat &frame = object->frame;
        Tracker::cPatternTracker &tracker = object->tracker;
        if (event == cv::EVENT_LBUTTONDOWN && !frame.empty()) {
            tracker.setTracker(frame, cv::Point(x, y));
        }
    }
};

int 
main(int argc, char **argv) {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "[error] video capture failed to load." << std::endl;
        exit(-1);
    }

    cv::Mat frame;
    Tracker::cPatternTracker tracker = Tracker::cPatternTracker(40);
    TrackerCallback::TrackerObject object{frame, tracker};

    cv::namedWindow("tracker");
    cv::setMouseCallback("tracker", TrackerCallback::mouseCallback, &object);

    while (cap.read(frame)) {
        if (tracker.isTracked(frame)) {
            cv::Point target;
            tracker.getPoint(target);
            printf("[info] x: %04d | y: %04d\n", target.x, target.y);
        }

        cv::imshow("tracker", frame);
        int key = cv::waitKey(1) & 0xff;
        if (key == 'q') {
            break;
        } else if (key == 'c' || key == 'C') {
            tracker.release();
        }
    }
    cap.release();
    cv::destroyAllWindows();
    return 0;
}