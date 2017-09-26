cmake_minimum_required(VERSION 3.6)
project(OpenCvTest)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        OpenCvTest/BinaryTest.cpp
        OpenCvTest/cvFindContoursTest2.cpp
        OpenCvTest/findContoursTest.cpp
        OpenCvTest/grayTest.cpp
        OpenCvTest/main.cpp
        OpenCvTest/RectDetect.cpp
        OpenCvTest/TemplateTest.cpp
        OpenCvTest/test.cpp)

add_executable(OpenCvTest ${SOURCE_FILES})