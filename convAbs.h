//
// Created by Dylan Furner on 11/21/21.
//

#ifndef CONVOLUTIONALLIBRARY_CONVABS_H
#define CONVOLUTIONALLIBRARY_CONVABS_H
#include <iostream>
#include <vector>
#include <chrono>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include "output.h"
#include "shared.h"

using namespace std;
using namespace cv;
class convAbs {
protected:
    shared *s;
    cv::Mat dest;
    string windowMessage;
public:
    convAbs();
    ~convAbs();
    void getData(float *buff, int size, float *target) {
        s->dataBack(buff, size, target);
    }

    float *getAddressSizes() {
        s->createData();
        return s->z->sizes;
    }

    float *getAddressAverages() {
        return s->z->averages;
    }

    float *getTimesData(int row) {
        return s->z->alltimes[row];
    }
    void gaussianblur(uint8_t* offset, int size, int width, int height);
 void blur(uint8_t* offset, int size, int width, int height);
 void sharpen(uint8_t* offset, int size, int width, int height);
 void emboss(uint8_t* offset, int size, int width, int height);
 void lofg(uint8_t* offset, int size, int width, int height);
 void sobel(uint8_t* offset, int size, int width, int height);
    virtual Mat GaussianBlur(Mat src) = 0;
    virtual Mat Blur(Mat src) = 0;
    virtual Mat Sharpen(Mat src) = 0;
    virtual Mat Emboss(Mat src) = 0;
    virtual Mat LofG(Mat src) = 0;
    virtual Mat Sobel(Mat src) = 0;
int liveFromCamera();
cv::Mat image_input(uint8_t *offset, size_t size, int width, int height);
};


#endif //CONVOLUTIONALLIBRARY_CONVABS_H
