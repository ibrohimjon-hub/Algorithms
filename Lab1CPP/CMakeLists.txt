add_executable(Lab1CPP lab1.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_executable(Lab1CPP2 lab2.cpp)
target_include_directories(Lab1CPP2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP2 LibraryCPP)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP PROPERTY PASS_REGULAR_EXPRESSION "1 2 3 4 5")

add_test(NAME TestLab1CPP_PositiveNegative COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab1CPP_PositiveNegative PROPERTY PASS_REGULAR_EXPRESSION "-1 -2 -3")

add_test(NAME TestLab1CPP_Unique COMMAND Lab1CPP2 ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab1CPP_Unique PROPERTY PASS_REGULAR_EXPRESSION "1 4 5")