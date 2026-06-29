#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main() {
    int internalPoints = 0, borderPoints = 0;
    double polygonArea;

    Mat hsv, redMask1, redMask2, redMask, blueMask;
    Mat image = imread("img.jpg");

    vector<vector<Point>> blueContours;
    vector<vector<Point>> redContours;

    if (image.empty()) {
        cout << "error loading image" << endl;
        return -1;
    }

    cvtColor(image, hsv, COLOR_BGR2HSV);

    inRange(
        hsv,
        Scalar(0, 100, 100),
        Scalar(10, 255, 255),
        redMask1
    );

    inRange(
        hsv,
        Scalar(170, 100, 100),
        Scalar(180, 255, 255),
        redMask2
    );

    bitwise_or(redMask1, redMask2, redMask);

    inRange(
        hsv,
        Scalar(100, 100, 100),
        Scalar(140, 255, 255),
        blueMask
    );

    findContours(
        redMask,
        redContours,
        RETR_EXTERNAL,
        CHAIN_APPROX_SIMPLE
    );

    findContours(
        blueMask,
        blueContours,
        RETR_EXTERNAL,
        CHAIN_APPROX_SIMPLE
    );

    for (int i = 0; i < redContours.size(); i++) {
        vector<Point>& contour = redContours[i];
        double area = contourArea(contour);

        if (area > 20) {
            borderPoints++;
        }
    }

    for (int i = 0; i < blueContours.size(); i++) {
        vector<Point>& contour = blueContours[i];
        double area = contourArea(contour);

        if (area > 20) {
            internalPoints++;
        }
    }

    polygonArea = (internalPoints + borderPoints / 2.0) - 1;

    cout << "internal points: " << internalPoints << endl;
    cout << "border points: " << borderPoints << endl;
    cout << "polygon area: " << polygonArea << endl;

    return 0;
}