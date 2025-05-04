cmake_minimum_required(VERSION 3.28)
project(Boids2D LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Boids2D src/main.cpp
        src/application.cpp
        src/application.h
        src/boid.cpp
        src/boid.h
        src/quadtree.cpp
        src/quadtree.h
        src/settings.cpp
        src/settings.h
)
target_compile_features(Boids2D PRIVATE cxx_std_17)
target_link_libraries(Boids2D PRIVATE sfml-graphics sfml-system sfml-window)
