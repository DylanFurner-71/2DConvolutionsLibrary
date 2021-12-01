//
// Created by Dylan Furner on 11/21/21.
//

#ifndef CONVOLUTIONALLIBRARY_MULTI_H
#define CONVOLUTIONALLIBRARY_MULTI_H
#include "convAbs.h"
#include "pthread.h"
#include "thread_data.h"
class multi : public convAbs {
private:
    vector<vector<double>> splitImage(cv::Mat src);
    void singleConvV(vector<double>* src, double GKernel[5][5], int rows, int cols, double bias = 0);
    static void* singleConv(void *threadarg);
public:
    multi();
    //Mat performConvolution(cv::Mat src, float GKernel[5][5], int rows, int cols, double bias = 0);
    Mat performConvolution(cv::Mat src, double GKernel[5][5], int rows, int cols, double bias = 0);
    Mat GaussianBlur(Mat src);
    Mat Blur(Mat src);
    Mat Sharpen(Mat src);
    Mat Emboss(Mat src);
    Mat LofG(Mat src);
    Mat Sobel(Mat src);
    void times();

};


#endif //CONVOLUTIONALLIBRARY_MULTI_H
