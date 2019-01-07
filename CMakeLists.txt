macro(header_directories return_list)
    file(GLOB_RECURSE new_list "*.h" "*.hpp")
    set(dir_list "")
    foreach(file_path ${new_list})
        get_filename_component(dir_path ${file_path} PATH)
        set(dir_list ${dir_list} ${dir_path})
    endforeach()
    list(REMOVE_DUPLICATES dir_list)
    set(${return_list} ${dir_list})
endmacro()

# vcpkg arguments for my machine. Modify if needed.
# -DCMAKE_TOOLCHAIN_FILE=C:/Users/Maks/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x86-windows

cmake_minimum_required(VERSION 3.12)
project(Saxion_Y2Q2_Rendering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

file(GLOB_RECURSE SOURCES "src/*.cpp")
header_directories(INCLUDES)

include_directories(${INCLUDES})
add_executable(Saxion_Y2Q2_Rendering ${SOURCES})

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
if(APPLE)
    find_library(OpenGL_LIBRARY OpenGL)
endif()

#if(WIN32)
#    set(SFML_ROOT C:/dev/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit/SFML-2.5.1/lib/cmake/SFML)
#endif()

find_package(lua 5.3 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)
find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)
link_directories(${SFML_LIBRARY_DIRS})

if (WIN32)
	set(LUALIB ${LUA_LIBRARIES})
else()
	set(LUALIB lua)
endif()

target_link_libraries(Saxion_Y2Q2_Rendering ${LUALIB} glm ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} sfml-graphics sfml-audio sfml-window sfml-system)