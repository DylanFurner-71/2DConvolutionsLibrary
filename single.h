//
// Created by Dylan Furner on 11/21/21.
//

#ifndef CONVOLUTIONALLIBRARY_SINGLE_H
#define CONVOLUTIONALLIBRARY_SINGLE_H
#include "convAbs.h"
using namespace cv;
using namespace std;
class single : public convAbs {
public:
    Mat performConvolution(cv::Mat src, float GKernel[5][5], double bias = 0);
    Mat GaussianBlur(Mat src);

    Mat Blur(Mat src);

    Mat Sharpen(Mat src);

    Mat Emboss(Mat src);

    Mat LofG(Mat src);

    Mat Sobel(Mat src);

};


#endif //CONVOLUTIONALLIBRARY_SINGLE_H
