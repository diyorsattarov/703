cmake_minimum_required(VERSION 3.2)

project(cpp-cmake-template VERSION 0.01)

# Define an option for building tests (default is ON)
option(BUILD_TESTS "Build the tests" ON)

# Add subdirectories based on the BUILD_TESTS option
if(BUILD_TESTS)
    add_subdirectory(test)
else()
    add_subdirectory(src)
endif()

add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Makefile
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/cmake_install.cmake
    COMMENT "Cleaning build files in root directory"
)

#add_dependencies(clean_all clean_test)  # Add this line to ensure clean_test is executed before clean_root
