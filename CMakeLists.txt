cmake_minimum_required(VERSION 3.19)
project(ConvolutionalLibrary)
set(CMAKE_CXX_STANDARD 11)

add_library(ConvolutionalLibrary 2DLib.cpp)
include(FindPkgConfig)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_EXE_LINKER_FLAGS "-Xlinker -v -v")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMAKE")
#set(SOURCE_FILES    src/main.c)
Message("")
Message( STATUS "SOURCE entry point : " ${SOURCE_FILES} )
Message("")
add_executable(2DConvolutionalLibrary main.cpp 2DLib.cpp output.h shared.cpp shared.h convAbs.cpp convAbs.h single.cpp single.h multi.cpp multi.h thread_data.h)

# ------- End Set Vars --- #

# ------- Executable ----- #

#ADD_EXECUTABLE(SDL2_Basic_Setup ${SOURCE_FILES})

# ------- End Executable - #

# ------- Finds ---------- #

FIND_PACKAGE(SDL2 REQUIRED)
Message("")
Message( STATUS "FINDING SDL2" )
IF (${SDL2_FOUND})
    Message( STATUS "SDL2_FOUND: " ${SDL2_FOUND})
    Message( STATUS "SDL2_INCLUDE_DIR:" ${SDL2_INCLUDE_DIR})
    Message( STATUS "SDL2_LIBRARY: " ${SDL2_LIBRARY})
ELSE()
    Message( STATUS "SDL2_FOUND: " ${SDL2_FOUND})
    Message( FATAL_ERROR "SDL2 NOT FOUND" )
ENDIF()

FIND_PACKAGE(SDL2_IMAGE)
Message("")
Message( STATUS "FINDING SDL2_IMAGE" )
Message( STATUS "SDL2_IMAGE_FOUND: " ${SDL2_IMAGE_FOUND})
IF (${SDL2_IMAGE_FOUND})
    Message( STATUS "SDL2_IMAGE_INCLUDE_DIR: " ${SDL2_IMAGE_INCLUDE_DIR})
    Message( STATUS "SDL2_IMAGE_LIBRARY: " ${SDL2_IMAGE_LIBRARY})
ELSE()
    Message( FATAL_ERROR "SDL2_IMAGE NOT FOUND" )
ENDIF()

FIND_PACKAGE(SDL2TTF)
Message("")
Message( STATUS "FINDING SDL2TTF" )
Message( STATUS "SDL2TTF_FOUND: " ${SDL2TTF_FOUND} )
IF (${SDL2TTF_FOUND})
    Message( STATUS "SDL2TTF_INCLUDE_DIR: " ${SDL2TTF_INCLUDE_DIR})
    Message( STATUS "SDL2TTF_LIBRARY: " ${SDL2TTF_LIBRARY})
ELSE()
    Message( FATAL_ERROR "SDL2TTF NOT FOUND" )
ENDIF()
Message("")

FIND_PACKAGE(SDL2Mixer)

Message( STATUS "FINDING SDL2Mixer" )
Message( STATUS "SDL2Mixer_FOUND: " ${SDL2Mixer_FOUND} )

Message("")

file(COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# ------- End Finds ------ #

# ------- Inc & Link ---- #

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2Mixer_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(2DConvolutionalLibrary ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2Mixer_LIBRARY} ${OpenCV_LIBS})
#INCLUDE(FindPkgConfig)
##target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
#PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
#PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
#INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
##find_library(SDL2_LIBRARY SDL2 "/opt/homebrew/lib/libSDL2.dylib")
#find_library(SDL2_App ${SDL2_LIBRARY})
#target_link_libraries(2DConvolutionalLibrary ${OpenCV_LIBS} ${SDL2_LIBRARIES})

#find_library(SDL2_LIBRARY SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})
#
#FIND_PACKAGE(SDL2 REQUIRED)
#Message("")
#Message( STATUS "FINDING SDL2" )
#IF (${SDL2_FOUND})
#    Message( STATUS "SDL2_FOUND: " ${SDL2_FOUND})
#    Message( STATUS "SDL2_INCLUDE_DIR:" ${SDL2_INCLUDE_DIR})
#    Message( STATUS "SDL2_LIBRARY: " ${SDL2_LIBRARY})
#ELSE()
#    Message( STATUS "SDL2_FOUND: " ${SDL2_FOUND})
#    Message( FATAL_ERROR "SDL2 NOT FOUND" )
#ENDIF()
#
#FIND_PACKAGE(SDL2_IMAGE)
#Message("")
#Message( STATUS "FINDING SDL2_IMAGE" )
#Message( STATUS "SDL2_IMAGE_FOUND: " ${SDL2_IMAGE_FOUND})
#IF (${SDL2_IMAGE_FOUND})
#    Message( STATUS "SDL2_IMAGE_INCLUDE_DIR: " ${SDL2_IMAGE_INCLUDE_DIR})
#    Message( STATUS "SDL2_IMAGE_LIBRARY: " ${SDL2_IMAGE_LIBRARY})
#ELSE()
#    Message( FATAL_ERROR "SDL2_IMAGE NOT FOUND" )
#ENDIF()
#
#FIND_PACKAGE(SDL2TTF)
#Message("")
#Message( STATUS "FINDING SDL2TTF" )
#Message( STATUS "SDL2TTF_FOUND: " ${SDL2TTF_FOUND} )
#IF (${SDL2TTF_FOUND})
#    Message( STATUS "SDL2TTF_INCLUDE_DIR: " ${SDL2TTF_INCLUDE_DIR})
#    Message( STATUS "SDL2TTF_LIBRARY: " ${SDL2TTF_LIBRARY})
#ELSE()
#    Message( FATAL_ERROR "SDL2TTF NOT FOUND" )
#ENDIF()
#Message("")
#
#FIND_PACKAGE(SDL2Mixer)
#
#Message( STATUS "FINDING SDL2Mixer" )
#Message( STATUS "SDL2Mixer_FOUND: " ${SDL2Mixer_FOUND} )
#
#Message("")
#
#file(COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#
## ------- End Finds ------ #
#
## ------- Inc & Link ---- #
#
#INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2Mixer_INCLUDE_DIR})
#TARGET_LINK_LIBRARIES(2DConvolutionalLibrary ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2Mixer_LIBRARY} )
#

