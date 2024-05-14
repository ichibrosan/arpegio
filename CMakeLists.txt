cmake_minimum_required(VERSION 3.10)
project(arpegio)
set(PROJECT_NAME "arpegio")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")
set(CURL_LIBRARY "-lcurl")
set(INCLUDE_DIR "include")
# Find necessary packages
find_package(CURL REQUIRED)

# Include directories
include_directories(${CURL_INCLUDE_DIR})
include_directories(${INCLUDE_DIR})

# Specify the source files
set(SRCS src/main.cpp src/Scanner.cpp src/MacLookup.cpp
        src/HostFileGenerator.cpp src/Utilities.cpp
        src/urlencode.cpp
        include/urlencode.h
        src/cleanHostsFile.cpp
        include/cleanHostsFile.h
        src/Scanner.cpp)

# Specify the executable target
add_executable(arpegio ${SRCS})

# Link the executable with necessary libraries
target_link_libraries(arpegio ${CURL_LIBRARY})