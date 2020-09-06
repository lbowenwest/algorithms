
set(
        SOURCE_FILES
        main.cpp
        visualiser.cpp
)

add_executable(percolate ${SOURCE_FILES})

target_link_libraries(percolate PRIVATE ${SFML_LIBRARIES} argh algorithms fmt)

add_custom_command(
        TARGET percolate
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:percolate> ${PROJECT_SOURCE_DIR}/bin/percolate
)
