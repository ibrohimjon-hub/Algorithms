add_executable(Lab2 lab2.cpp)

target_include_directories(Lab2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab2 LibraryCPP)

add_test(
    NAME TestLab2
    COMMAND Lab2
        ${CMAKE_CURRENT_SOURCE_DIR}/script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
)

set_tests_properties(TestLab2 PROPERTIES
    PASS_REGULAR_EXPRESSION "72 101 108 111 44 32 119 114 108 100 33 10"
)

add_test(
    NAME TestLab2Arithmetic
    COMMAND Lab2
        ${CMAKE_CURRENT_SOURCE_DIR}/arithmetic_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/arithmetic_input.txt
)

set_tests_properties(TestLab2Arithmetic PROPERTIES
    PASS_REGULAR_EXPRESSION "15 17 24 4 25 4"
)

add_test(
    NAME TestLab2Repeat
    COMMAND Lab2
        ${CMAKE_CURRENT_SOURCE_DIR}/repeat_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/repeat_input.txt
)

set_tests_properties(TestLab2Repeat PROPERTIES
    PASS_REGULAR_EXPRESSION "7 7 7 7"
)

add_test(
    NAME TestLab2Cond
    COMMAND Lab2
        ${CMAKE_CURRENT_SOURCE_DIR}/cond_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/cond_input.txt
)

set_tests_properties(TestLab2Cond PROPERTIES
    PASS_REGULAR_EXPRESSION "42"
)

add_test(
    NAME TestLab2CondFalse
    COMMAND Lab2
        ${CMAKE_CURRENT_SOURCE_DIR}/cond_false_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/cond_false_input.txt
)