cmake_minimum_required(VERSION 3.21)

# Project declaration
project(
    geargame2
    VERSION 0.1
    LANGUAGES CXX
)

set(gg2_INCLUDES "${CMAKE_SOURCE_DIR}/include/")

add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)
add_subdirectory(src) # gg2_SRC

# Add the library
add_library(gg2 STATIC ${gg2_SRC})
target_include_directories(gg2 PRIVATE ${gg2_INCLUDES})

if(TARGET SDL3::SDL3main)
    message("Including SDL3main")
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(mygame PRIVATE SDL3::SDL3main)
endif()

target_link_libraries(gg2 PRIVATE SDL3::SDL3)

# Build an example
add_subdirectory(examples)