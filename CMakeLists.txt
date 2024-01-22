cmake_minimum_required(VERSION 3.26)

project(playground_run C)

set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/bin)

set(CMAKE_C_STANDARD 23)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
endif(WIN32)

add_definitions(-DWINDOWS_APPLICATION)

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

install(TARGETS playground_run DESTINATION bin)
install(FILES ${CMAKE_SOURCE_DIR}/bin/SDL2.dll DESTINATION bin)
install(FILES ${CMAKE_SOURCE_DIR}/bin/SDL2_mixer.dll DESTINATION bin)
install(FILES ${CMAKE_SOURCE_DIR}/bin/SDL2_image.dll DESTINATION bin)
install(FILES ${CMAKE_SOURCE_DIR}/bin/SDL2_image.dll DESTINATION bin)