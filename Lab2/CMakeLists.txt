add_executable(Lab2 lab2.cpp)
target_include_directories(Lab2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab2 LibraryCPP)

add_test(
    NAME TestLab2
    COMMAND Lab2
        ${CMAKE_CURRENT_SOURCE_DIR}/script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
)

add_test(
    NAME TestLab2Arithmetic
    COMMAND Lab2
        ${CMAKE_CURRENT_SOURCE_DIR}/arithmetic_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/arithmetic_input.txt
)

add_test(
    NAME TestLab2Repeat
    COMMAND Lab2
        ${CMAKE_CURRENT_SOURCE_DIR}/repeat_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/repeat_input.txt
)

add_test(
    NAME TestLab2Cond
    COMMAND Lab2
        ${CMAKE_CURRENT_SOURCE_DIR}/cond_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/cond_input.txt
)

add_test(
    NAME TestLab2CondFalse
    COMMAND Lab2
        ${CMAKE_CURRENT_SOURCE_DIR}/cond_false_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/cond_false_input.txt
)