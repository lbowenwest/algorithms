
set(
        SOURCE_FILES
        main.cpp
        board.cpp
)

add_executable(connectz ${SOURCE_FILES})

target_link_libraries(connectz PRIVATE sul::dynamic_bitset)

add_custom_command(
        TARGET connectz
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:connectz> ${PROJECT_SOURCE_DIR}/bin/connectz
)