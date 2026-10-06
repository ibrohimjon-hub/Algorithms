add_executable(Lab3 lab3.cpp)
target_include_directories(Lab3 PUBLIC ../LibraryCPP)
target_link_libraries(Lab3 LibraryCPP)

foreach(test_number RANGE 1 3)
    add_test(NAME TestLab3_${test_number} COMMAND ${CMAKE_COMMAND}
        "-DPROGRAM=$<TARGET_FILE:Lab3>"
        "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/input${test_number}.txt"
        "-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/valid${test_number}.txt"
        -P ${CMAKE_CURRENT_SOURCE_DIR}/check_output.cmake)
endforeach()
