macro(header_directories return_list)
    file(GLOB_RECURSE new_list "*.h")
    set(dir_list "")
    foreach(file_path ${new_list})
        get_filename_component(dir_path ${file_path} PATH)
        set(dir_list ${dir_list} ${dir_path})
    endforeach()
    list(REMOVE_DUPLICATES dir_list)
    set(${return_list} ${dir_list})
endmacro()

cmake_minimum_required(VERSION 3.12)
project(Saxion_Y2Q1_Rendering)

set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
header_directories(INCLUDES)

include_directories(${INCLUDES})
add_executable(Saxion_Y2Q1_Rendering ${SOURCES} ${INCLUDES})

## If you want to link SFML statically
#set(SFML_STATIC_LIBRARIES TRUE)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
if(APPLE)
    find_library(OpenGL_LIBRARY OpenGL)
endif()

find_package(GLEW REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

target_link_libraries(Saxion_Y2Q1_Rendering ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} sfml-graphics sfml-audio)
