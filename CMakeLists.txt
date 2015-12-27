cmake_minimum_required(VERSION 3.3)
project(b2sync)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp B2Client.cpp B2Client.h B2AuthorizeAccountResponse.h B2APIMessage.h B2Bucket.cpp B2Bucket.h B2ListBucketsResponse.h)
add_executable(b2sync ${SOURCE_FILES})

# Add config file
file(COPY b2config.info DESTINATION "${b2sync_BINARY_DIR}")

# Include cpr
# Use the system installed cURL library to also get system defined CA cert stores, the bundled CPR does not seem to include
# CA certificates or does not know how to find them and as I have a system libcURL working I'd rather use that right now
set(USE_SYSTEM_CURL ON)
add_subdirectory(cpr)
include_directories(${CPR_INCLUDE_DIRS})
target_link_libraries(b2sync ${CPR_LIBRARIES})

# Include Boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS system propertytree)

include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(b2sync ${Boost_LIBRARIES})