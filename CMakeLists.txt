cmake_minimum_required(VERSION 3.5.1)
project(CometEngine VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)

add_executable(Comet 
	src/main.cpp 
	src/Time.cpp
	src/Shader.cpp
	external/glad/glad.c
)

target_link_libraries(Comet PRIVATE glfw)

target_include_directories(Comet PRIVATE 
	external/glfw/include
	external/glad/include
)

set_property(TARGET Comet PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

add_custom_command(
    TARGET Comet POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/shaders"
    "$<TARGET_FILE_DIR:Comet>/shaders"
)