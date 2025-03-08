cmake_minimum_required(VERSION 3.25)
project(dog)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

include_directories("include/")
link_directories(
    lib/
)

# 
file(GLOB SRCS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/main.cpp"
)

#主程序
add_executable(dlmu-dog ../main.cpp ../src/misc.cpp)
target_link_libraries(dlmu-dog libUnitreeMotorSDK_M80106_Arm64.so)

# #stop 工程
# add_executable(stop ../stop.cpp)
# target_link_libraries(stop libUnitreeMotorSDK_M80106_Arm64.so)


