

project(Casament_Emulator LANGUAGES C CXX)

add_executable(${PROJECT_NAME}
    main.cpp
    ../Source/snake.c
)

target_compile_definitions(${PROJECT_NAME} PRIVATE MIXU_EMULATOR=1)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.26.3
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(SDL2)



target_link_libraries(${PROJECT_NAME} SDL2::SDL2main SDL2::SDL2-static)