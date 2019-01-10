cmake_minimum_required(VERSION 3.0)
project(raytracer)

SET(MSVC_FLAGS "/Zi /W3")
add_definitions(${MSVC_FLAGS})
include_directories(${PROJECT_SOURCE_DIR}/3rdParty/include)
link_directories(${PROJECT_SOURCE_DIR}/3rdParty/lib)
add_executable(
	out
	src/main.cpp
)
target_link_libraries(out SDL2d SDL2maind)
