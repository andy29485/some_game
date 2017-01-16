# Specify the minimum version for CMake
cmake_minimum_required(VERSION 2.8.s)

# Project's name
project(game)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(${PROJECT_NAME}_EXEC_NAME game)

# Set sources/include
set(${PROJECT_NAME}_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

file(GLOB ${PROJECT_NAME}_SOURCES
  ${${PROJECT_NAME}_SOURCE_DIR}/*.cpp
  ${${PROJECT_NAME}_SOURCE_DIR}/*/*.cpp
)

include_directories("${PROJECT_SOURCE_DIR}/include")

# Set version
set (LEARN_CMAKE_VERSION_MAJOR 0)
set (LEARN_CMAKE_VERSION_MINOR 0)
set (LEARN_CMAKE_VERSION_PATCH 0)

# Compiler Condition (gcc ; g++)
if ( "${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" )
  add_definitions( -O3 )
  add_definitions( -std=gnu++14 )
else ()
  add_definitions( -std=c++14 )
endif()

#add preprocessor definitions
if (DEFINED DEBUG AND DEBUG)
 add_definitions( -DDEBUG )
 add_definitions( -g )
endif ()

if (DEFINED EDITOR AND EDITOR)
 add_definitions( -DEDITOR )
endif ()


# Check for OS
if( UNIX )
  set( LEARN_CMAKE_DEFINITIONS
    "${LEARN_CMAKE_DEFINITIONS} -Wall -Wextra -Werror
    -Wno-deprecated-declarations -Wno-unused-parameter -Wno-comment" 
  )
elseif( DEFINED SFML_PATH )
  cmake_policy(SET CMP0015 OLD)
  include_directories(${SFML_PATH}/include)
  link_directories(${SFML_PATH}/lib)
endif()

# Specify creation of executable
add_executable(${${PROJECT_NAME}_EXEC_NAME} ${${PROJECT_NAME}_SOURCES})

# Set linked libs
# Link the libraries
if( WIN32 )
  add_definitions( -DSFML_STATIC )
  set_target_properties(${${PROJECT_NAME}_EXEC_NAME}
                        PROPERTIES LINK_SEARCH_START_STATIC 1
  )
  set_target_properties(${${PROJECT_NAME}_EXEC_NAME}
                        PROPERTIES LINK_SEARCH_END_STATIC 1
  )
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  add_definitions(
    -static -static-libgcc -static-libstdc++
  )
  target_link_libraries(${${PROJECT_NAME}_EXEC_NAME}
    sfml-graphics-s sfml-window-s sfml-system-s
    opengl32 winmm gdi32 freetype jpeg libgcc_s_seh-1 pthread
  )
else()
  target_link_libraries(${${PROJECT_NAME}_EXEC_NAME}
    sfml-graphics sfml-window sfml-system
  )
endif()
