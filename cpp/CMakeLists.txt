CMAKE_MINIMUM_REQUIRED(VERSION "3.16")
project("li2016")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable("${PROJECT_NAME}_readonly" "readonly.cpp")
add_executable("${PROJECT_NAME}_mutable" "mutable.cpp")