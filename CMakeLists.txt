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

# Patch JoyStick hang on Unix VMs
set(SFML_JOYSTICK_FIX_FILE "${sfml_SOURCE_DIR}/src/SFML/Window/Unix/JoystickImpl.cpp")
file(READ "${SFML_JOYSTICK_FIX_FILE}" JOYSTICK_SRC)

# Only patch if not already patched
string(FIND "${JOYSTICK_SRC}" "return false; // Patched to prevent VM hang" PATCHED_ALREADY)
if(PATCHED_ALREADY EQUAL -1)
    message(STATUS "Patching SFML JoystickImpl.cpp to avoid VM hang...")

    string(REPLACE
            "int monitorFd = udev_monitor_get_fd(udevMonitor);"
            "return false; // Patched to prevent VM hang\n    int monitorFd = udev_monitor_get_fd(udevMonitor);"
            JOYSTICK_SRC "${JOYSTICK_SRC}"
    )
    file(WRITE "${SFML_JOYSTICK_FIX_FILE}" "${JOYSTICK_SRC}")
endif()

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
