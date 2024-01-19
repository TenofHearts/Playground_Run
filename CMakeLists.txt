cmake_minimum_required(VERSION 3.26)

project(playground_run C)

set(CMAKE_C_STANDARD 23)

# add_executable(${PROJECT_NAME}
#     src/main.c
#     src/start_menu.c
#     src/game.c
#     src/utils/print_text.c
# )

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