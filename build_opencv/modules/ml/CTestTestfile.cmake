# CMake generated Testfile for 
# Source directory: /Users/dylanfurner/Desktop/2DConvolutionsLibrary/opencv/modules/ml
# Build directory: /Users/dylanfurner/Desktop/2DConvolutionsLibrary/build_opencv/modules/ml
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_ml "/Users/dylanfurner/Desktop/2DConvolutionsLibrary/build_opencv/bin/opencv_test_ml" "--gtest_output=xml:opencv_test_ml.xml")
set_tests_properties(opencv_test_ml PROPERTIES  LABELS "Main;opencv_ml;Accuracy" WORKING_DIRECTORY "/Users/dylanfurner/Desktop/2DConvolutionsLibrary/build_opencv/test-reports/accuracy" _BACKTRACE_TRIPLES "/Users/dylanfurner/Desktop/2DConvolutionsLibrary/opencv/cmake/OpenCVUtils.cmake;1738;add_test;/Users/dylanfurner/Desktop/2DConvolutionsLibrary/opencv/cmake/OpenCVModule.cmake;1352;ocv_add_test_from_target;/Users/dylanfurner/Desktop/2DConvolutionsLibrary/opencv/cmake/OpenCVModule.cmake;1110;ocv_add_accuracy_tests;/Users/dylanfurner/Desktop/2DConvolutionsLibrary/opencv/modules/ml/CMakeLists.txt;2;ocv_define_module;/Users/dylanfurner/Desktop/2DConvolutionsLibrary/opencv/modules/ml/CMakeLists.txt;0;")
