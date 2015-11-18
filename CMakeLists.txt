cmake_minimum_required(VERSION 3.3)
project(b2sync)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp B2Client.cpp B2Client.h B2AuthenticatedClient.cpp B2AuthenticatedClient.h)
add_executable(b2sync ${SOURCE_FILES})

# Include gitcpp
add_subdirectory(curlcpp)
include_directories(${CURLCPP_SOURCE_DIR}/include)

target_link_libraries(b2sync curlcpp)