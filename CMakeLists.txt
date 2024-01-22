cmake_minimum_required(VERSION 3.26)

project(playground_run C)

set(CMAKE_C_STANDARD 23)

include_directories(include)

add_executable(playground_run 
src/main.c
src/start_menu.c
src/stop_menu.c
src/death_menu.c
src/game.c
src/obstacle.c
src/utils/print_text.c
src/utils/character_motion.c
src/utils/score.c
src/utils/init_game.c
src/utils/time.c
)

target_link_libraries(${PROJECT_NAME}
    mingw32
    SDL2main
    SDL2
    SDL2_image
    SDL2_mixer
    SDL2_ttf
)