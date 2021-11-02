# 2DConvolutionsLibrary
C++ Static Library that performs 2D convolutions on images using predefined 5x5 kernels. 
This library was initially created for a school project. This library relies on heavily on OpenCv for accessing camera and to access the underlying matrix that represents the image. Nonetheless, I have implemented my own filter functions rather than using OpenCv's built-in filter2D function. This was a part of the requirements of the project and it was a very good exercise to practice complex matrix operations using C++ (most of my previous experience performing similar operations would have been in Python).
TBD -> multithreaded operations on already implemented filters.

Functionality:
This library contains singlethreaded and multithreaded implementations of GaussianBlur, Box-blur, Sharpen, emboss, Laplacian of Gaussian, and Sobel convolutions. 

Development and Operating Environment:
This library was developed on a Macbook Pro with Apple M1 chip running MacOs BigSur Version 11.2.3.. Although the operating system contains some modifications to standard unix, it is a unix compliant operating system. It was developed using Clion IDE. 

Instructions For Compilation: 
  Using Cmake -
  enter directory, cmake compile command, cmake build command
  
    In unix environment:
    Open Terminal
    cd into directory
    cmake .
    cmake --build .
    This should generate a file called libConvolutionalLibrary.a
  
  Example from my environment
    Open Terminal
    Cd desktop/2DConvolutionsLibrary
    cmake .
    cmake -- build .

Instructions For Use:
This is the first ever static library that I have implemented in C++. As such, I am iffy on some of the details. 

