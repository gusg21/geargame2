cmake_minimum_required(VERSION 3.21)
set (CMAKE_CXX_STANDARD 20)

# Project declaration
project(
    geargame2
    VERSION 0.1
    LANGUAGES CXX
)

set(gg2_INCLUDE "${CMAKE_SOURCE_DIR}/include/")
message("GG2 Headers: " ${gg2_HEADERS_GLOB})

option(COMPILE_EXAMPLES "Include the examples/ subdirectory in this build" ON)

add_subdirectory(vendor/SDL)
add_subdirectory(vendor/SDL_image)
add_subdirectory(vendor/spdlog)

add_subdirectory(src) # gg2_SRC
add_subdirectory(include/gg2) # gg2_HEADERS

# Add the library
add_library(gg2 STATIC ${gg2_SRC})
target_include_directories(gg2 PRIVATE ${gg2_INCLUDE})

if (TARGET SDL3::SDL3main)
    message("Including SDL3main")
    target_link_libraries(mygame PRIVATE SDL3::SDL3main)
endif()

target_include_directories(gg2 PUBLIC vendor/SDL/include)
target_link_libraries(gg2 PRIVATE SDL3::SDL3)

target_link_libraries(gg2 PRIVATE spdlog)

if (DEBUG)
    target_compile_definitions(gg2 PRIVATE DEBUG)
endif()

# Build an example
if (COMPILE_EXAMPLES)
    add_subdirectory(examples)
endif()