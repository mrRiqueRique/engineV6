cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(graphic LANGUAGES C CXX)
include(FetchContent)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

find_package(assimp CONFIG REQUIRED)

add_library(glad STATIC
    ${PROJECT_SOURCE_DIR}/external/glad/src/gl.c
)

target_include_directories(glad PUBLIC
    ${PROJECT_SOURCE_DIR}/external/glad/include
)

add_library(stb STATIC
    ${PROJECT_SOURCE_DIR}/external/stb/stb_image_impl.cpp
)

target_include_directories(stb PUBLIC
    ${PROJECT_SOURCE_DIR}/external/stb
)

add_library(engine STATIC
    src/Core/Core.cpp
)

target_include_directories(engine PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/external/glm
)

target_link_libraries(engine PUBLIC
    OpenGL::GL
    glfw
    glad
    stb
    assimp::assimp
)

add_subdirectory(src/IO)
add_subdirectory(src/Core)
add_subdirectory(src/Graphics)
add_subdirectory(src/Resources)
add_subdirectory(src/Utility)

add_executable(demo src/main.cpp)

target_link_libraries(demo PRIVATE engine)

if(WIN32)
    add_custom_command(TARGET demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:glfw>
        $<TARGET_FILE_DIR:demo>
    )
endif()