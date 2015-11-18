cmake_minimum_required(VERSION 3.3)
project(b2sync)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp B2Client.cpp B2Client.h B2AuthToken.h B2APIMessage.h)
add_executable(b2sync ${SOURCE_FILES})

# Add config file
file(COPY b2config.info DESTINATION "${b2sync_BINARY_DIR}")

# Include gitcpp
add_subdirectory(curlcpp)
include_directories(${CURLCPP_SOURCE_DIR}/include)

target_link_libraries(b2sync curlcpp)

# Include Boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS system propertytree)

include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(b2sync ${Boost_LIBRARIES})