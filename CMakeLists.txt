cmake_minimum_required(VERSION 3.8)

project(seat C CXX)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)

# Add support for threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
# include_directories("/usr/include/opencv4/opencv2")


add_executable(main ransac.cpp)
target_link_libraries(main
${OpenCV_LIBS}
Threads::Threads  # Link with Threads library
)

# add_executable(aruco aruco.cpp)
# target_link_libraries(aruco
# ${OpenCV_LIBS}
# # target_include_directories(aruco PRIVATE ${OpenCV_INCLUDE_DIRS})
# Threads::Threads  # Link with Threads library
# )

add_executable(capture camera.cpp)
target_link_libraries(capture
${OpenCV_LIBS}
Threads::Threads  # Link with Threads library
)


add_executable(et yolov8Normal.cpp inference.cpp)
target_link_libraries(et
${OpenCV_LIBS}
Threads::Threads  # Link with Threads library
)

