//
// Created by Dylan Furner on 11/20/21.
//

#ifndef CONVOLUTIONALLIBRARY_SHARED_H
#define CONVOLUTIONALLIBRARY_SHARED_H
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
#include "output.h"

class shared {
private:


public:
    struct output *z;
    std::vector<std::vector<float>> times;
    shared();
    ~shared();
    void clearData(uint8_t *data, int length);
    void dataBack(uint8_t *buffer, int size, uint8_t *data);
    void dataBack(float *buffer, int size, float *data);
    void createData();
    void printData();
};


#endif //CONVOLUTIONALLIBRARY_SHARED_H
