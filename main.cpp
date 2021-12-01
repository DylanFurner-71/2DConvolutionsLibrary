#include "2DLib.h"
int main(int argc, char**argv) {
    libr::init();
//    singleThread::liveFromCamera();
    multiThread::liveFromCameraM();
//    multiThread::times();
}
