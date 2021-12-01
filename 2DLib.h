#ifndef INC_2DCONVOLUTIONALLIBRARY_2DLIB_H
#define INC_2DCONVOLUTIONALLIBRARY_2DLIB_H
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
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
#include "convAbs.h"
#include "single.h"
#include "multi.h"
extern "C" {

namespace libr {
    void init();
}
namespace singleThread {
    void gaussianblur(uint8_t* offset, int size, int width, int height);

    void blur(uint8_t* offset, int size, int width, int height);

    void sharpen(uint8_t* offset, int size, int width, int height);

    void emboss(uint8_t* offset, int size, int width, int height);

    void lofg(uint8_t* offset, int size, int width, int height);

    void sobel(uint8_t* offset, int size, int width, int height);
    int liveFromCamera();
}
namespace multiThread {
    void gaussianblurM(uint8_t* offset, int size, int width, int height);

    void blurM(uint8_t* offset, int size, int width, int height);

    void sharpenM(uint8_t* offset, int size, int width, int height);

    void embossM(uint8_t* offset, int size, int width, int height);

    void lofgM(uint8_t* offset, int size, int width, int height);

    void sobelM(uint8_t* offset, int size, int width, int height);
    int liveFromCameraM();
    void times();
}
}

#endif //INC_2DCONVOLUTIONALLIBRARY_2DLIB_H
