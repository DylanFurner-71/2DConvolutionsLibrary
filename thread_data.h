//
// Created by Dylan Furner on 11/30/21.
//

#ifndef CONVOLUTIONALLIBRARY_THREAD_DATA_H
#define CONVOLUTIONALLIBRARY_THREAD_DATA_H
struct thread_data {
    int thread_id;
    int rows, cols, bias;
    double ** GKernel;
    vector<double>* src;
    Mat* mat;
};
#endif //CONVOLUTIONALLIBRARY_THREAD_DATA_H
