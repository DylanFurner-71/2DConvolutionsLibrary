//
// Created by Dylan Furner on 11/21/21.
//
//
// Created by Dylan Furner on 11/21/21.
//

#include "multi.h"
void multi::times(){
    s->createData();
    s->printData();
}
multi::multi(){
//    this->td = new thread_data[3];
}
vector<vector<double>> multi::splitImage(cv::Mat in){
    vector<Mat> rgbchannel(in.channels());
    vector<vector<double>> fin(in.channels());
    split(in.clone(), rgbchannel);
    for (int i = 0; i < rgbchannel.size(); ++i){
        Mat src = rgbchannel[i];
        std::vector<double> array(src.rows*src.cols);
        if (src.isContinuous()) {
            array.assign((double*)src.data, (double*)src.data + src.total());
        } else {
            for (int i = 0; i < src.rows; ++i) {
                array.insert(array.end(), src.ptr<double>(i), src.ptr<double>(i)+src.cols*src.channels());
            }
        }
        fin[i] = array;
    }
    return fin;
}

void multi::singleConvV(vector<double>* src, double GKernel[5][5], int rows, int cols, double bias) {
    for (int x = (5 - 1) / 2; x < rows - ((5 - 1) / 2); x++) {
        for (int y = (5 - 1) / 2; y < cols - ((5 - 1) / 2); y++) {
            float comp_1 = 0;
            for (int u = -(5 - 1) / 2; u <= (5 - 1) / 2; u++) {
                for (int v = -(5 - 1) / 2; v <= (5 - 1) / 2; v++) {
                    comp_1 = comp_1 + src->at((x + u)*cols+ (y + v)) * GKernel[u + 2][v + 2];
                }
            }
            src->at((x + -2)*cols+ (y -2 ))= comp_1 + bias;
        }
    }
}
void* multi::singleConv(void *threadarg) {
    thread_data* my_data = (thread_data*) threadarg;
    int rows = my_data->rows;
    int cols = my_data->cols;
    int bias = my_data->bias;
    double GKernel[5][5];
    for (int i = 0; i < 5; i ++){
        for (int y = 0; y < 5; y++){
            GKernel[i][y] = my_data->GKernel[i][y];
        }
    }
    vector<double> *src;// = (vector<double>*) malloc(sizeof(my_data->src));
    src = my_data->src;
    Mat * m = my_data->mat;
    for (int x = (5 - 1) / 2; x < rows - ((5 - 1) / 2); x++) {
        for (int y = (5 - 1) / 2; y < cols - ((5 - 1) / 2); y++) {
            float comp_1 = 0;
            for (int u = -(5 - 1) / 2; u <= (5 - 1) / 2; u++) {
                for (int v = -(5 - 1) / 2; v <= (5 - 1) / 2; v++) {
                    comp_1 = comp_1 + src->at((x + u)*cols+ (y + v)) * GKernel[u + 2][v + 2];
                }
            }
            src->at((x + -2)*cols+ (y -2 ))= comp_1 + bias;
        }
    }
    memcpy(m->data, src->data(), src->size()*sizeof(double ));
    pthread_exit(NULL);
}
Mat multi::performConvolution(cv::Mat image, double GKernel[5][5], int rows, int cols, double bias) {
    vector<vector<double>> rgbchannel1 = splitImage(image);//red 2 green 1 blue 0
    vector<Mat> rgbchannel(image.channels());
    double ** Kernel;
    Kernel = new double*[5];
    for (int i = 0; i < 5; i++){
        Kernel[i] = new double[5];
        for (int y = 0; y < 5; y++){
            Kernel[i][y] = GKernel[i][y];
        }
    }
//    singleConvV(&rgbchannel1[0], GKernel, rows, cols, bias);
//    singleConvV(&rgbchannel1[1], GKernel, rows, cols, bias);
//    singleConvV(&rgbchannel1[2], GKernel, rows, cols, bias);
    pthread_t threads[3];
    int rc;
    struct thread_data td[3];
//    td = new thread_data[3];
    //load threads
    for ( int i = 0; i < 3; i ++) {
        td[i].thread_id = i;
        td[i].rows = rows;
        td[i].cols = cols;
        td[i].bias = bias;
        td[i].GKernel = new double*[5];
        for (int x = 0; x < 5; x++){
            td[i].GKernel[x] = new double[5];
            for (int y = 0; y < 5; y++){
                td[i].GKernel[x][y] = GKernel[x][y];
            }
        }
        rgbchannel[i] = Mat(rows, cols, CV_64FC1);
        td[i].src = &rgbchannel1[i];
        td[i].mat = &rgbchannel[i];
    }


    for ( int i = 0; i < 3; i ++){
            rc = pthread_create(&threads[i], NULL, singleConv, (void*) &td[i]);
        if (rc){
            cout<<"Error: unable to create thread #"<<rc<<endl;
            exit(-1);
        }
    }
//    for ( int i = 0; i < 3; i ++){
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);

    Mat qq;
    merge(rgbchannel, qq);
    qq.convertTo(qq, CV_8UC3);
    return qq;
}

Mat multi::Blur(cv::Mat src1) {
    //blur
    Mat src = src1.clone();
    src.convertTo(src, CV_64FC3);
    double Gkernel[5][5] = {
            {0,          0,          1.0 / 13.0, 0,          0},
            {0,          1.0 / 13.0, 1.0 / 13.0, 1.0 / 13.0, 0},
            {1.0 / 13.0, 1.0 / 13.0, 1.0 / 13.0, 1.0 / 13.0, 1.0 / 13.0,},
            {0,          1.0 / 13.0, 1.0 / 13.0, 1.0 / 13.0, 0},
            {0,          0,          1.0 / 13.0, 0,          0},
    };
    return performConvolution(src, Gkernel, src.rows, src.cols);
}

Mat multi::GaussianBlur(cv::Mat src1) {
    Mat src = src1.clone();
    src.convertTo(src, CV_64FC3);
    double GkernelGaus[5][5] = {
            {1.0 / 273.0, 4.0 / 273.0,  7.0 / 273.0,  4.0 / 273.0,  1.0 / 273.0},
            {4.0 / 273.0, 16.0 / 273.0, 26.0 / 273.0, 16.0 / 273.0, 4.0 / 273.0},
            {6.0 / 273.0, 24.0 / 273.0, 41.0 / 273.0, 24.0 / 273.0, 6.0 / 273.0},
            {4.0 / 273.0, 16.0 / 273.0, 26.0 / 273.0, 16.0 / 273.0, 4.0 / 273.0},
            {1.0 / 273.0, 4.0 / 273.0,  7.0 / 273.0,  4.0 / 273.0,  1.0 / 273.0},
    };
    return performConvolution(src, GkernelGaus, src.rows, src.cols);

}

Mat multi::Sharpen(cv::Mat src1) {
    Mat src = src1.clone();
    src.convertTo(src, CV_64FC3);
    double Gkernel[5][5] = {
            {-1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1},
            {-1, -1, 25, -1, -1},
            {-1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1},
    };
    return performConvolution(src, Gkernel, src.rows, src.cols);
}

Mat multi::Emboss(cv::Mat src1) {
    Mat src = src1.clone();
    src.convertTo(src, CV_64FC3);
    double Gkernel[5][5] = {
            {-1, -1, -1, -1, 0},
            {-1, -1, -1, 0,  1},
            {-1, -1, 0,  1,  1},
            {-1, 0,  1,  1,  1},
            {0,  1,  1,  1,  1},
    };
    double bias = 128;
    return performConvolution(src, Gkernel, src.rows, src.cols, bias);
}

Mat multi::LofG(cv::Mat src1) {
    Mat src = src1.clone();
    src.convertTo(src, CV_64FC3);
    double GkernelGaus[5][5] = {
            {1.0 / 256.0, 4.0 / 256.0,  6.0 / 256.0,  4.0 / 256.0,  1.0 / 256.0},
            {4.0 / 256.0, 16.0 / 256.0, 24.0 / 256.0, 16.0 / 256.0, 4.0 / 256.0},
            {6.0 / 256.0, 24.0 / 256.0, 36.0 / 256.0, 24.0 / 256.0, 6.0 / 256.0},
            {4.0 / 256.0, 16.0 / 256.0, 24.0 / 256.0, 16.0 / 256.0, 4.0 / 256.0},
            {1.0 / 256.0, 4.0 / 256.0,  6.0 / 256.0,  4.0 / 256.0,  1.0 / 256.0},
    };
//laplacian
    double Gkernel[5][5] = {
            {0, 0, 1,   0, 0},
            {0, 1, 2,   1, 0},
            {1, 2, -16, 2, 1},
            {0, 1, 2,   1, 0},
            {0, 0, 1,   0, 0},
    };
//        Mat temp2 = src.clone();
//        Mat grey1;
//        cvtColor(temp2, grey1, COLOR_BGR2GRAY);
    Mat temp = src.clone();
    temp.convertTo(temp, CV_8UC3);
    Mat Grey, newGray;
    cvtColor(temp, Grey, COLOR_BGR2GRAY);
    cvtColor(Grey, newGray, COLOR_GRAY2BGR);
//        Mat temp1 = performConvolution(src, GkernelGaus);
    Mat temp1 = performConvolution(newGray, GkernelGaus, src.rows, src.cols);

    newGray.convertTo(newGray, CV_64FC3);
    return performConvolution(newGray, Gkernel, src.rows, src.cols);
}

Mat multi::Sobel(cv::Mat src1) {
    Mat src = src1.clone();
    src.convertTo(src, CV_64FC3);
    return src;
//////SOBEL_horizontal
//    double GkernelH[5][5] = {
//            {-2, -1, 0, 1, 2},
//            {-2, -1, 0, 1, 2},
//            {-2, -1, 0, 1, 2},
//            {-2, -1, 0, 1, 2},
//            {-2, -1, 0, 1, 2},
//    };
////        dest = performConvolution(resized_down, Gkernel);
//    //sobel vert
//    double Gkernel[5][5] = {
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