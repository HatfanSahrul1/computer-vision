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


add_executable(main obstacle.cpp)
target_link_libraries(main
${OpenCV_LIBS}
Threads::Threads  # Link with Threads library
)

add_executable(capture camera.cpp)
target_link_libraries(capture
${OpenCV_LIBS}
Threads::Threads  # Link with Threads library
)


add_executable(goal1 yolov8Normal.cpp inference.cpp)
target_link_libraries(goal1
${OpenCV_LIBS}
Threads::Threads  # Link with Threads library
)

