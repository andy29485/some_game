# Specify the minimum version for CMake
cmake_minimum_required(VERSION 2.8.s)

# Project's name
project(game)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(${PROJECT_NAME}_EXEC_NAME game)

# Set sources/include
set(${PROJECT_NAME}_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(${PROJECT_NAME}_SOURCES
  ${${PROJECT_NAME}_SOURCE_DIR}/main.cpp
)
include_directories("${PROJECT_SOURCE_DIR}/include")

# Set version
set (LEARN_CMAKE_VERSION_MAJOR 0)
set (LEARN_CMAKE_VERSION_MINOR 0)
set (LEARN_CMAKE_VERSION_PATCH 0)

# Specify creation of executable
add_executable(${${PROJECT_NAME}_EXEC_NAME} ${${PROJECT_NAME}_SOURCES})

# Set linked libs
# Link the libraries
target_link_libraries(${${PROJECT_NAME}_EXEC_NAME}
  sfml-graphics sfml-window sfml-system
)

# Compiler Condition (gcc ; g++)
if ( "${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" )
  message( STATUS "Setting the flags for ${CMAKE_C_COMPILER_ID} compiler" )
  add_definitions( -O3 )
endif()

# Check for OS
if( UNIX )
  set( LEARN_CMAKE_DEFINITIONS
    "${LEARN_CMAKE_DEFINITIONS} -Wall -Wextra -Werror -Wno-deprecated-declarations -Wno-unused-parameter -Wno-comment" )
else if( MINGW )
  set(SFML_PATH "SFML")
  include_directories(${SFML_PATH}/include)
  include_directories(${SFML_PATH}/lib)
endif()
