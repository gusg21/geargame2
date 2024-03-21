cmake_minimum_required(VERSION 3.21)

file(GLOB gg2_SRC
     "*.h"
     "*.cc"
)

add_library(gg2 STATIC 
    ${gg2_SRC}
)