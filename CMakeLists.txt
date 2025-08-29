cmake_minimum_required(VERSION 3.22)

project(C_Compiler LANGUAGES CXX)

# Global settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(CMAKE_EXPORT_COMPILE_COMMANDS "Export compile_commands.json" ON)
option(BUILD_TESTING "Enable building tests" ON)

# Output directories
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()

# Top-level include directory for public headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add subdirectories (these CMakeLists use INTERFACE targets/placeholders for now)
add_subdirectory(src)

include(CTest)
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

message(STATUS "Configured ${PROJECT_NAME} with C++${CMAKE_CXX_STANDARD}")

