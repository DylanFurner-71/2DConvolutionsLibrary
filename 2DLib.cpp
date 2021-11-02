//
// Created by Dylan Furner on 11/1/21.
//
#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include <chrono>
#include <thread>
#include <vector>
#include <string>
using namespace cv;
using namespace std;
    const string windowMessage = " - Esc to Exit - b for Blur, s for Sharpen, e for Emboss, g for Gaussian Blur, l for LofG, w for Sobel\"";


//works for rgb images. Basically anything except for grayscale inputs.
    Mat performConvolution(cv::Mat src, float GKernel[5][5], double bias = 0) {
        Mat my_conv;
        // Adding the countour of nulls around the original image, to avoid border problems during convolution
        cv::Mat img_conv = Mat(src.rows + 5 - 1, src.cols + 5 - 1, CV_64FC3, CV_RGB(0, 0, 0));
        for (int x = 0; x < src.rows; x++) {
            for (int y = 0; y < src.cols; y++) {
                img_conv.at<Vec3d>(x + 1, y + 1)[0] = src.at<Vec3d>(x, y)[0];
                img_conv.at<Vec3d>(x + 1, y + 1)[1] = src.at<Vec3d>(x, y)[1];
                img_conv.at<Vec3d>(x + 1, y + 1)[2] = src.at<Vec3d>(x, y)[2];
            }
        }
        //Performing the convolution
        my_conv = Mat(src.rows, src.cols, CV_64FC3, CV_RGB(0, 0, 0));
        for (int x = (5 - 1) / 2; x < img_conv.rows - ((5 - 1) / 2); x++) {
            for (int y = (5 - 1) / 2; y < img_conv.cols - ((5 - 1) / 2); y++) {
                double comp_1 = 0;
                double comp_2 = 0;
                double comp_3 = 0;
                for (int u = -(5 - 1) / 2; u <= (5 - 1) / 2; u++) {
                    for (int v = -(5 - 1) / 2; v <= (5 - 1) / 2; v++) {
                        comp_1 = comp_1 + (img_conv.at<Vec3d>(x + u, y + v)[0] * GKernel[u + 2][v + 2]);
                        comp_2 = comp_2 + (img_conv.at<Vec3d>(x + u, y + v)[1] * GKernel[u + 2][v + 2]);
                        comp_3 = comp_3 + (img_conv.at<Vec3d>(x + u, y + v)[2] * GKernel[u + 2][v + 2]);
                    }
                }
                my_conv.at<Vec3d>(x, y)[0] = comp_1 + bias;
                my_conv.at<Vec3d>(x, y)[1] = comp_2 + bias;
                my_conv.at<Vec3d>(x, y)[2] = comp_3 + bias;
            }
        }
        my_conv.convertTo(my_conv, CV_8UC3);
        return my_conv;
    }

    Mat Blur(cv::Mat src1) {
        //blur
        Mat src = src1.clone();
        src.convertTo(src, CV_64FC3);
        float Gkernel[5][5] = {
                {0,          0,          1.0 / 13.0, 0,          0},
                {0,          1.0 / 13.0, 1.0 / 13.0, 1.0 / 13.0, 0},
                {1.0 / 13.0, 1.0 / 13.0, 1.0 / 13.0, 1.0 / 13.0, 1.0 / 13.0,},
                {0,          1.0 / 13.0, 1.0 / 13.0, 1.0 / 13.0, 0},
                {0,          0,          1.0 / 13.0, 0,          0},
        };
        return performConvolution(src, Gkernel);
    }

    Mat GaussianBlur(cv::Mat src1) {
        Mat src = src1.clone();
        src.convertTo(src, CV_64FC3);
        float GkernelGaus[5][5] = {
                {1.0 / 256.0, 4.0 / 256.0,  6.0 / 256.0,  4.0 / 256.0,  1.0 / 256.0},
                {4.0 / 256.0, 16.0 / 256.0, 24.0 / 256.0, 16.0 / 256.0, 4.0 / 256.0},
                {6.0 / 256.0, 24.0 / 256.0, 36.0 / 256.0, 24.0 / 256.0, 6.0 / 256.0},
                {4.0 / 256.0, 16.0 / 256.0, 24.0 / 256.0, 16.0 / 256.0, 4.0 / 256.0},
                {1.0 / 256.0, 4.0 / 256.0,  6.0 / 256.0,  4.0 / 256.0,  1.0 / 256.0},
        };
        return performConvolution(src, GkernelGaus);

    }

    Mat Sharpen(cv::Mat src1) {
        Mat src = src1.clone();
        src.convertTo(src, CV_64FC3);
        float Gkernel[5][5] = {
                {-1, -1, -1, -1, -1},
                {-1, -1, -1, -1, -1},
                {-1, -1, 25, -1, -1},
                {-1, -1, -1, -1, -1},
                {-1, -1, -1, -1, -1},
        };
        return performConvolution(src, Gkernel);
    }

    Mat Emboss(cv::Mat src1) {
        Mat src = src1.clone();
        src.convertTo(src, CV_64FC3);
        float Gkernel[5][5] = {
                {-1, -1, -1, -1, 0},
                {-1, -1, -1, 0,  1},
                {-1, -1, 0,  1,  1},
                {-1, 0,  1,  1,  1},
                {0,  1,  1,  1,  1},
        };
        double bias = 128;
        return performConvolution(src, Gkernel, bias);
    }

    Mat LofG(cv::Mat src1) {
        Mat src = src1.clone();
        src.convertTo(src, CV_64FC3);
        float GkernelGaus[5][5] = {
                {1.0 / 256.0, 4.0 / 256.0,  6.0 / 256.0,  4.0 / 256.0,  1.0 / 256.0},
                {4.0 / 256.0, 16.0 / 256.0, 24.0 / 256.0, 16.0 / 256.0, 4.0 / 256.0},
                {6.0 / 256.0, 24.0 / 256.0, 36.0 / 256.0, 24.0 / 256.0, 6.0 / 256.0},
                {4.0 / 256.0, 16.0 / 256.0, 24.0 / 256.0, 16.0 / 256.0, 4.0 / 256.0},
                {1.0 / 256.0, 4.0 / 256.0,  6.0 / 256.0,  4.0 / 256.0,  1.0 / 256.0},
        };
//laplacian
        float Gkernel[5][5] = {
                {0, 0, 1,   0, 0},
                {0, 1, 2,   1, 0},
                {1, 2, -16, 2, 1},
                {0, 1, 2,   1, 0},
                {0, 0, 1,   0, 0},
        };
        Mat temp = performConvolution(src, GkernelGaus);
        Mat Grey, newGray;
        cvtColor(temp, Grey, COLOR_BGR2GRAY);
        cvtColor(Grey, newGray, COLOR_GRAY2BGR);
        newGray.convertTo(newGray, CV_64FC3);
        return performConvolution(newGray, Gkernel);
    }

    Mat Sobel(cv::Mat src1) {
        Mat src = src1.clone();
        src.convertTo(src, CV_64FC3);
//////SOBEL_horizontal
//    float GkernelH[5][5] = {
//            {-2, -1, 0, 1, 2},
//            {-2, -1, 0, 1, 2},
//            {-2, -1, 0, 1, 2},
//            {-2, -1, 0, 1, 2},
//            {-2, -1, 0, 1, 2},
//    };
////        dest = performConvolution(resized_down, Gkernel);
//    //sobel vert
//    float Gkernel[5][5] = {
//            {-2, -2, -2, -2, -2},
//            {-1, -1, -1, -1, -1},
//            {0, 0, 0, 0, 0},
//            {1, 1, 1, 1, 1},
//            {2, 2, 2, 2, 2},
//    };
//        Mat Grey, newGray, NG1;
//        resized_down.convertTo(resized_down, CV_8UC3);
//    cvtColor(resized_down, Grey, COLOR_RGB2GRAY);
//    cvtColor(Grey, Grey, COLOR_GRAY2RGB);
//    Grey.convertTo(Grey, CV_64FC3);
//    NG1 = performConvolution(Grey, GkernelH);
//    NG1.convertTo(NG1, CV_64FC3);
//    dest = performConvolution(NG1, Gkernel);
    }

    Mat oneMore(cv::Mat src) {

    }
namespace singleThread{
    int takePicture() {
        cv::VideoCapture camera(0);
        if (!camera.isOpened()) {
            std::cerr << "ERROR: Could not open camera" << std::endl;
            return 1;
        }
        cv::namedWindow("Webcam", cv::WINDOW_AUTOSIZE);
        std::this_thread::sleep_for(std::chrono::nanoseconds(10000));
        cv::Mat frame, dest;
        camera >> frame;
        std::this_thread::sleep_for(std::chrono::nanoseconds(10000));
        camera >> frame;
        int down_width = 500;
        int down_height = 500;
        Mat resized_down, resized_down2;
        resize(frame, resized_down, Size(down_width, down_height), INTER_LINEAR);
//    resized_down.convertTo(resized_down, CV_64FC3);
        bool finished = false;
        while (!finished) {
            while (1) {
                cv::imshow("Original" + windowMessage, resized_down);
                char c = (char) waitKey(25);
                if (c == 27) {
                    finished = true;
                    break;
                }
                if (c == 98) {
                    dest = Blur(resized_down);
                    break;
                }
                if (c == 115) {
                    dest = Sharpen(resized_down);
                    break;
                }
                if (c == 101) {
                    dest = Emboss(resized_down);
                    break;
                }
                if (c == 103) {
                    dest = GaussianBlur(resized_down);
                    break;
                }
                if (c == 108) {
                    dest = LofG(resized_down);
                    break;
                }
                if (c == 119) {
                    dest = Sobel(resized_down);
                    break;
                }
            }
            while (1 && !finished) {
                // show the image on the window
                cv::imshow("Convoluted Image" + windowMessage, dest);
                // wait (10ms) for a key to be pressed
                char c = (char) waitKey(0);
                if (c == 27) {
                    finished = true;
                    break;
                }
                if (c == 111) {
                    dest = resized_down.clone();
                }
                if (c == 98) {
                    dest = Blur(resized_down);
                }
                if (c == 115) {
                    dest = Sharpen(resized_down);
                }
                if (c == 101) {
                    dest = Emboss(resized_down);
                }
                if (c == 103) {
                    dest = GaussianBlur(resized_down);
                }
                if (c == 108) {
                    dest = LofG(resized_down);
                }
                if (c == 119) {
                    dest = Sobel(resized_down);
                }
            }
        }
        camera.release();
    }

    int liveFromCamera() {
        VideoCapture cap(0);
        if (!cap.isOpened()) {
            std::cout << "Error opening video stream or file" << std::endl;
            return -1;
        }
        char c = ' ';
        while (1) {
            Mat frame, dest;
            cap >> frame;
            if (frame.empty())
                break;
            int down_width = 500;
            int down_height = 500;
            Mat resized_down;
            resize(frame, resized_down, Size(down_width, down_height), INTER_LINEAR);
            if (resized_down.empty()) {
                break;
            }
            dest = resized_down.clone();
            char d = (char) waitKey(25);
            if (d != -1) {
                c = d;
            }
            if (c == 27) {
                break;
            }
            if (c == 111) {
                dest = resized_down.clone();
            }
            if (c == 98) {
                dest = Blur(resized_down);
            }
            if (c == 115) {
                dest = Sharpen(resized_down);
            }
            if (c == 101) {
                dest = Emboss(resized_down);
            }
            if (c == 103) {
                dest = GaussianBlur(resized_down);
            }
            if (c == 108) {
                dest = LofG(resized_down);
            }
            if (c == 119) {
                dest = Sobel(resized_down);
            }
            imshow("Video" + windowMessage, dest);
        }
        cap.release();
        destroyAllWindows();
    }
};