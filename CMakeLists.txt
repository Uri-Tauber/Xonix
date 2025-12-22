cmake_minimum_required(VERSION 3.10)
project(Xonix)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML 3.
# Note: SFML 3 usually provides a Config file.
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_executable(Xonix ${SOURCES})

target_link_libraries(Xonix SFML::Graphics SFML::Window SFML::System)

# Robust asset copying
add_custom_command(TARGET Xonix POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Xonix>/resources
    COMMENT "Copying resources to build directory"
)
