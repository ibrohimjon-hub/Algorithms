add_executable(Lab3 lab3.cpp)
target_include_directories(Lab3 PUBLIC ../LibraryCPP)
target_link_libraries(Lab3 LibraryCPP)

add_test(NAME TestLab3 COMMAND ${CMAKE_COMMAND}
    "-DPROGRAM=$<TARGET_FILE:Lab3>"
    "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/input.txt"
    "-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/valid.txt"
    -P ${CMAKE_CURRENT_SOURCE_DIR}/check_output.cmake)
