add_executable(testing1 main.cc)

message("GG2 Include Path: " ${gg2_INCLUDE})

target_link_libraries(testing1 gg2)
target_include_directories(testing1 PRIVATE ${gg2_INCLUDE})

add_custom_command(TARGET testing1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_LIST_DIR}/assets"
        $<TARGET_FILE_DIR:testing1>/assets)