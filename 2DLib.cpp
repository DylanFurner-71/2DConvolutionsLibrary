//
// Created by Dylan Furner on 11/1/21.
//
#include "2DLib.h"
using namespace cv;
using namespace std;
//const string windowMessage = " - Esc to Exit - b for Blur, s for Sharpen, e for Emboss, g for Gaussian Blur, l for LofG, w for Sobel\"";
//
////works for rgb images. Basically anything except for grayscale inputs.
//Mat performConvolution(cv::Mat src, float GKernel[5][5], double bias = 0) {
//    Mat my_conv;
//    // Adding the countour of nulls around the original image, to avoid border problems during convolution
//    cv::Mat img_conv = Mat(src.rows + 5 - 1, src.cols + 5 - 1, CV_64FC3, CV_RGB(0, 0, 0));
//    for (int x = 0; x < src.rows; x++) {
//        for (int y = 0; y < src.cols; y++) {
//            img_conv.at<Vec3d>(x + 1, y + 1)[0] = src.at<Vec3d>(x, y)[0];
//            img_conv.at<Vec3d>(x + 1, y + 1)[1] = src.at<Vec3d>(x, y)[1];
//            img_conv.at<Vec3d>(x + 1, y + 1)[2] = src.at<Vec3d>(x, y)[2];
//        }
//    }
//    //Performing the convolution
//    my_conv = Mat(src.rows, src.cols, CV_64FC3, CV_RGB(0, 0, 0));
//    for (int x = (5 - 1) / 2; x < img_conv.rows - ((5 - 1) / 2); x++) {
//        for (int y = (5 - 1) / 2; y < img_conv.cols - ((5 - 1) / 2); y++) {
//            double comp_1 = 0;
//            double comp_2 = 0;
//            double comp_3 = 0;
//            for (int u = -(5 - 1) / 2; u <= (5 - 1) / 2; u++) {
//                for (int v = -(5 - 1) / 2; v <= (5 - 1) / 2; v++) {
//                    comp_1 = comp_1 + (img_conv.at<Vec3d>(x + u, y + v)[0] * GKernel[u + 2][v + 2]);
//                    comp_2 = comp_2 + (img_conv.at<Vec3d>(x + u, y + v)[1] * GKernel[u + 2][v + 2]);
//                    comp_3 = comp_3 + (img_conv.at<Vec3d>(x + u, y + v)[2] * GKernel[u + 2][v + 2]);
//                }
//            }
//            my_conv.at<Vec3d>(x - 2, y - 2)[0] = comp_1 + bias;
//            my_conv.at<Vec3d>(x - 2, y - 2)[1] = comp_2 + bias;
//            my_conv.at<Vec3d>(x - 2, y - 2)[2] = comp_3 + bias;
//        }
//    }
//    my_conv.convertTo(my_conv, CV_8UC3);
//    return my_conv;
//}
//
//Mat Blur(cv::Mat src1) {
//    //blur
//    Mat src = src1.clone();
//    src.convertTo(src, CV_64FC3);
//    float Gkernel[5][5] = {
//            {0,          0,          1.0 / 13.0, 0,          0},
//            {0,          1.0 / 13.0, 1.0 / 13.0, 1.0 / 13.0, 0},
//            {1.0 / 13.0, 1.0 / 13.0, 1.0 / 13.0, 1.0 / 13.0, 1.0 / 13.0,},
//            {0,          1.0 / 13.0, 1.0 / 13.0, 1.0 / 13.0, 0},
//            {0,          0,          1.0 / 13.0, 0,          0},
//    };
//    return performConvolution(src, Gkernel);
//}
//
//Mat GaussianBlur(cv::Mat src1) {
//    Mat src = src1.clone();
//    src.convertTo(src, CV_64FC3);
//    float GkernelGaus[5][5] = {
//            {1.0 / 273.0, 4.0 / 273.0,  7.0 / 273.0,  4.0 / 273.0,  1.0 / 273.0},
//            {4.0 / 273.0, 16.0 / 273.0, 26.0 / 273.0, 16.0 / 273.0, 4.0 / 273.0},
//            {6.0 / 273.0, 24.0 / 273.0, 41.0 / 273.0, 24.0 / 273.0, 6.0 / 273.0},
//            {4.0 / 273.0, 16.0 / 273.0, 26.0 / 273.0, 16.0 / 273.0, 4.0 / 273.0},
//            {1.0 / 273.0, 4.0 / 273.0,  7.0 / 273.0,  4.0 / 273.0,  1.0 / 273.0},
//    };
//    return performConvolution(src, GkernelGaus);
//
//}
//
//Mat Sharpen(cv::Mat src1) {
//    Mat src = src1.clone();
//    src.convertTo(src, CV_64FC3);
//    float Gkernel[5][5] = {
//            {-1, -1, -1, -1, -1},
//            {-1, -1, -1, -1, -1},
//            {-1, -1, 25, -1, -1},
//            {-1, -1, -1, -1, -1},
//            {-1, -1, -1, -1, -1},
//    };
//    return performConvolution(src, Gkernel);
//}
//
//Mat Emboss(cv::Mat src1) {
//    Mat src = src1.clone();
//    src.convertTo(src, CV_64FC3);
//    float Gkernel[5][5] = {
//            {-1, -1, -1, -1, 0},
//            {-1, -1, -1, 0,  1},
//            {-1, -1, 0,  1,  1},
//            {-1, 0,  1,  1,  1},
//            {0,  1,  1,  1,  1},
//    };
//    double bias = 128;
//    return performConvolution(src, Gkernel, bias);
//}
//
//Mat LofG(cv::Mat src1) {
//    Mat src = src1.clone();
//    src.convertTo(src, CV_64FC3);
//    float GkernelGaus[5][5] = {
//            {1.0 / 256.0, 4.0 / 256.0,  6.0 / 256.0,  4.0 / 256.0,  1.0 / 256.0},
//            {4.0 / 256.0, 16.0 / 256.0, 24.0 / 256.0, 16.0 / 256.0, 4.0 / 256.0},
//            {6.0 / 256.0, 24.0 / 256.0, 36.0 / 256.0, 24.0 / 256.0, 6.0 / 256.0},
//            {4.0 / 256.0, 16.0 / 256.0, 24.0 / 256.0, 16.0 / 256.0, 4.0 / 256.0},
//            {1.0 / 256.0, 4.0 / 256.0,  6.0 / 256.0,  4.0 / 256.0,  1.0 / 256.0},
//    };
////laplacian
//    float Gkernel[5][5] = {
//            {0, 0, 1,   0, 0},
//            {0, 1, 2,   1, 0},
//            {1, 2, -16, 2, 1},
//            {0, 1, 2,   1, 0},
//            {0, 0, 1,   0, 0},
//    };
////        Mat temp2 = src.clone();
////        Mat grey1;
////        cvtColor(temp2, grey1, COLOR_BGR2GRAY);
//    Mat temp = src.clone();
//    temp.convertTo(temp, CV_8UC3);
//    Mat Grey, newGray;
//    cvtColor(temp, Grey, COLOR_BGR2GRAY);
//    cvtColor(Grey, newGray, COLOR_GRAY2BGR);
////        Mat temp1 = performConvolution(src, GkernelGaus);
//    Mat temp1 = performConvolution(newGray, GkernelGaus);
//
//    newGray.convertTo(newGray, CV_64FC3);
//    return performConvolution(newGray, Gkernel);
//}
//
//Mat Sobel(cv::Mat src1) {
//    Mat src = src1.clone();
//    src.convertTo(src, CV_64FC3);
//    return src;
////////SOBEL_horizontal
////    float GkernelH[5][5] = {
////            {-2, -1, 0, 1, 2},
////            {-2, -1, 0, 1, 2},
////            {-2, -1, 0, 1, 2},
////            {-2, -1, 0, 1, 2},
////            {-2, -1, 0, 1, 2},
////    };
//////        dest = performConvolution(resized_down, Gkernel);
////    //sobel vert
////    float Gkernel[5][5] = {
////            {-2, -2, -2, -2, -2},
////            {-1, -1, -1, -1, -1},
////            {0, 0, 0, 0, 0},
////            {1, 1, 1, 1, 1},
////            {2, 2, 2, 2, 2},
////    };
////        Mat Grey, newGray, NG1;
////        resized_down.convertTo(resized_down, CV_8UC3);
////    cvtColor(resized_down, Grey, COLOR_RGB2GRAY);
////    cvtColor(Grey, Grey, COLOR_GRAY2RGB);
////    Grey.convertTo(Grey, CV_64FC3);
////    NG1 = performConvolution(Grey, GkernelH);
////    NG1.convertTo(NG1, CV_64FC3);
////    dest = performConvolution(NG1, Gkernel);
//}


//cv::Mat image_input(uint8_t *offset, size_t size, int width, int height) {
//    Mat cv_image = cv::Mat(width, height, CV_8UC4);
//    cv_image.data = offset;
//    cv::Mat newImage;
//    cv::cvtColor(cv_image, newImage, cv::COLOR_RGBA2BGR);
//    return newImage;
//}
single *s;
multi *m;
namespace libr {
    void init(){
        s = new single();
        m = new multi();
    }
}
namespace singleThread {
    void gaussianblur(uint8_t* offset, int size, int width, int height){
        s->gaussianblur(offset, size, width, height);
    }

    void blur(uint8_t* offset, int size, int width, int height){
        s->blur(offset, size, width, height);
    }

    void sharpen(uint8_t* offset, int size, int width, int height){
        s->sharpen(offset, size, width, height);
    }

    void emboss(uint8_t* offset, int size, int width, int height){
        s->emboss(offset, size, width, height);
    }

    void lofg(uint8_t* offset, int size, int width, int height){
        s->lofg(offset, size, width, height);
    }

    void sobel(uint8_t* offset, int size, int width, int height){
        s->sobel(offset, size, width, height);
    }
    int liveFromCamera(){
        s->liveFromCamera();
    }
}
namespace multiThread {
    void gaussianblurM(uint8_t* offset, int size, int width, int height){
        m->gaussianblur(offset, size, width, height);
    }

    void blurM(uint8_t* offset, int size, int width, int height){
        m->blur(offset, size, width, height);
    }

    void sharpenM(uint8_t* offset, int size, int width, int height){
        m->sharpen(offset, size, width, height);
    }

    void embossM(uint8_t* offset, int size, int width, int height){
        m->emboss(offset, size, width, height);
    }

    void lofgM(uint8_t* offset, int size, int width, int height){
        m->lofg(offset, size, width, height);
    }

    void sobelM(uint8_t* offset, int size, int width, int height){
        m->sobel(offset, size, width, height);
    }
    int liveFromCameraM(){
        m->liveFromCamera();
    }
    void times(){
        m->times();
    }
};