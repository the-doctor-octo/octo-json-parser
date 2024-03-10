cmake_minimum_required(VERSION 3.10)
project(OctoJsonParser VERSION 1.0)

add_executable(OctoJsonParser main.cpp json-parser.cpp file-utils.cpp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(ParserConfig.h.in ParserConfig.h)
target_include_directories(OctoJsonParser PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

# this enables the test build (Reads the cmakelists.txt in test folder)
set(BUILD_TESTING ON)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()