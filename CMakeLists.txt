cmake_minimum_required(VERSION 3.8)

project(seat C CXX)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)

# Add support for threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(yaml-cpp REQUIRED)
include_directories(${YAML_CPP_INCLUDE_DIR})

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
# include_directories("/usr/include/opencv4/opencv2")


# add_executable(main ransac.cpp)
# target_link_libraries(main
# ${OpenCV_LIBS}
# Threads::Threads  # Link with Threads library
# )
# target_include_directories(main PRIVATE ${OpenCV_INCLUDE_DIRS})

add_executable(main aruco2.cpp)
target_link_libraries(main
${OpenCV_LIBS}
${YAML_CPP_LIBRARIES}
# target_include_directories(aruco PRIVATE ${OpenCV_INCLUDE_DIRS})
Threads::Threads  # Link with Threads library
)

# add_executable(capture camera.cpp)
# target_link_libraries(capture
# ${OpenCV_LIBS}
# Threads::Threads  # Link with Threads library
# )


# add_executable(40detect yolov8Normal.cpp inference.cpp)
# target_link_libraries(40detect
# ${OpenCV_LIBS}
# Threads::Threads  # Link with Threads library
# )

