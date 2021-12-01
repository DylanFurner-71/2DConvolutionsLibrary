//
// Created by Dylan Furner on 11/20/21.
//

#include "shared.h"
using namespace std;
shared::shared(){
    z = (struct output *) malloc(sizeof(struct output));
    for (int i = 0; i < 6; i++) {
        times.push_back(vector<float>());
    }
}
shared::~shared(){

}
void shared::clearData(uint8_t *data, int length) {

}
void shared::dataBack(uint8_t *buffer, int size, uint8_t *data) {
    for (int i = 0; i < size; i++) {
        *(buffer + i) = *(data + i);
    }
}
void shared::dataBack(float *buffer, int size, float *data) {
    for (int i = 0; i < size; i++) {
        *(buffer + i) = *(data + i);
    }
}

void shared::createData() {
    z->averages = new float[times.size()];
    z->alltimes = new float *[times.size()];
    for (int i = 0; i < times.size(); i++) {
        z->sizes[i] = times[i].size();
        z->alltimes[i] = new float[times[i].size()];
        for (int k = 0; k < z->sizes[i]; k++) {
            z->averages[i] += times[i][k];
            z->alltimes[i][k] = times[i][k];
        }
        z->averages[i] /= z->sizes[i];
    }
}
void shared::printData() {
    for (int i = 0; i < times.size(); i++) {
        cout << "Averages of filter #" << i << " " << z->averages[i] << endl;
        cout << "Size of captures " << z->sizes[i]<<endl;
        cout << "Data" << endl;
        for (int k = 0; k < z->sizes[i]; z++) {
            cout << z->alltimes[i][k] << ",";
        }
        cout << endl;
    }
}
