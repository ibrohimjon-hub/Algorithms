execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output)

if(NOT "${result}" STREQUAL "${EXPECTED_RESULT}")
    message(FATAL_ERROR "Lab3 returned ${result}, expected ${EXPECTED_RESULT}")
endif()

file(READ "${EXPECTED}" expected)
if(NOT output STREQUAL expected)
    message(FATAL_ERROR "Lab3 output does not match valid.txt")
endif()
