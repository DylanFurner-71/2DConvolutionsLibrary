//
// Created by Dylan Furner on 11/21/21.
//

#include "convAbs.h"

convAbs::~convAbs() {

}

convAbs::convAbs() {
    this->s = new shared();
    this->windowMessage = " - Esc to Exit - b for Blur, s for Sharpen, e for Emboss, g for Gaussian Blur, l for LofG, w for Sobel\"";
}
cv::Mat convAbs::image_input(uint8_t *offset, size_t size, int width, int height) {
        Mat cv_image = cv::Mat(width, height, CV_8UC4);
        cv_image.data = offset;
        cv::Mat newImage;
        cv::cvtColor(cv_image, newImage, cv::COLOR_RGBA2BGR);
        return newImage;
}
int convAbs::liveFromCamera() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }
    char c = ' ';
    while (1) {
        Mat frame;
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
        char d = (char) waitKey(25);
        if (d != -1) {
            c = d;
        }
//            Mat dest;
        Mat dest(resized_down.size(), CV_MAKE_TYPE(resized_down.depth(), 4));
        int from_to[] = {0,0,1,1,2,2,2,3};
        mixChannels(&resized_down, 1, &dest, 1, from_to, 4);
//            cvtColor(resized_down, dest, COLOR_BGR2RGBA);
        uint8_t *z = dest.data;
        int size = dest.rows*dest.cols*4;
        if (c == 27) {
            break;
        }
        if (c == 98) {
            blur(z, size, dest.cols, dest.rows);
        }
//        if (c == 99) {
//            c = -1;
//            waitKey();
//
//        }
        if (c == 115) {
            sharpen(z, size, dest.cols, dest.rows);
        }
        if (c == 101) {
            emboss(z, size, dest.cols, dest.rows);
        }
        if (c == 103) {
            gaussianblur(z, size, dest.cols, dest.rows);
        }
        if (c == 108) {
            lofg(z, size, dest.cols, dest.rows);
        }
        if (c == 119) {
            sobel(z, size, dest.cols, dest.rows);
        }
        dest.data = z;
        imshow("Video" + windowMessage, dest);
    }
    cap.release();
    destroyAllWindows();
}

void convAbs::gaussianblur(uint8_t *offset, int size, int width, int height) {
    std::chrono::steady_clock::time_point start = chrono::steady_clock::now();
    cvtColor(GaussianBlur(image_input(offset, size, width, height)), dest, cv::COLOR_BGR2RGBA);
    s->dataBack(offset, size, dest.data);
    std::chrono::steady_clock::time_point end = chrono::steady_clock::now();
    std::chrono::duration<float> time = chrono::duration_cast<chrono::duration<float>>(end - start);
    s->dataBack(offset, size, dest.data);
    s->times[2].push_back(time.count());
}

void convAbs::blur(uint8_t *offset, int size, int width, int height) {
    std::chrono::steady_clock::time_point start = chrono::steady_clock::now();
    cvtColor(Blur(image_input(offset, size, width, height)), dest, cv::COLOR_BGR2RGBA);
    s->dataBack(offset, size, dest.data);
    std::chrono::steady_clock::time_point end = chrono::steady_clock::now();
    std::chrono::duration<float> time = chrono::duration_cast<chrono::duration<float>>(end - start);
    s->dataBack(offset, size, dest.data);
    s->times[4].push_back(time.count());
}
void convAbs::sharpen(uint8_t *buffer, int size, int width, int height) {
    std::chrono::steady_clock::time_point start = chrono::steady_clock::now();
    cvtColor(Sharpen(image_input(buffer, size, width, height)), dest, cv::COLOR_BGR2RGBA);
    s->dataBack(buffer, size, dest.data);
    std::chrono::steady_clock::time_point end = chrono::steady_clock::now();
    std::chrono::duration<float> time = chrono::duration_cast<chrono::duration<float>>(end - start);
    s->dataBack(buffer, size, dest.data);
    s->times[3].push_back(time.count());
}

void convAbs::emboss(uint8_t *offset, int size, int width, int height) {
    std::chrono::steady_clock::time_point start = chrono::steady_clock::now();
    cvtColor(Emboss(image_input(offset, size, width, height)), dest, cv::COLOR_BGR2RGBA);
    std::chrono::steady_clock::time_point end = chrono::steady_clock::now();
    std::chrono::duration<float> time = chrono::duration_cast<chrono::duration<float>>(end - start);
    s->dataBack(offset, size, dest.data);
    s->times[0].push_back(time.count());
}
void convAbs::lofg(uint8_t *offset, int size, int width, int height) {
    std::chrono::steady_clock::time_point start = chrono::steady_clock::now();
    cvtColor(LofG(image_input(offset, size, width, height)), dest, cv::COLOR_BGR2RGBA);
    s->dataBack(offset, size, dest.data);
    std::chrono::steady_clock::time_point end = chrono::steady_clock::now();
    std::chrono::duration<float> time = chrono::duration_cast<chrono::duration<float>>(end - start);
    s->dataBack(offset, size, dest.data);
    s->times[1].push_back(time.count());
}

void convAbs::sobel(uint8_t *offset, int size, int width, int height) {
    std::chrono::steady_clock::time_point start = chrono::steady_clock::now();
    cvtColor(Sobel(image_input(offset, size, width, height)), dest, cv::COLOR_BGR2RGBA);
    std::chrono::steady_clock::time_point end = chrono::steady_clock::now();
    std::chrono::duration<float> time = chrono::duration_cast<chrono::duration<float>>(end - start);
    s->dataBack(offset, size, dest.data);
    s->times[5].push_back(time.count());
}
