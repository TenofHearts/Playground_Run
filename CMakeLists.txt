cmake_minimum_required(VERSION 3.26)

project(playground_run C)

set(CMAKE_C_STANDARD 23)

include_directories(${PROJECT_NAME} PRIVATE include)

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME}
    mingw32
    SDL2main
    SDL2
    SDL2_image
    SDL2_mixer
    SDL2_ttf
)