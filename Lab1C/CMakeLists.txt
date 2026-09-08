add_executable(Lab1C lab1.c)
target_include_directories(Lab1C PUBLIC ../LibraryC)
target_link_libraries(Lab1C LibraryC)

add_executable(Lab1C2 lab2.c)
target_include_directories(Lab1C2 PUBLIC ../LibraryC)
target_link_libraries(Lab1C2 LibraryC)

add_test(NAME TestLab1C COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1C PROPERTY PASS_REGULAR_EXPRESSION "1 2 3 4 5")

add_test(NAME TestLab1C_PositiveNegative COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab1C_PositiveNegative PROPERTY PASS_REGULAR_EXPRESSION "-1 -2 -3")

add_test(NAME TestLab1C_Unique COMMAND Lab1C2 ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab1C_Unique PROPERTY PASS_REGULAR_EXPRESSION "1 4 5")