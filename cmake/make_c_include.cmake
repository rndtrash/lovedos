file(READ "${INPUT_FILE}" BINARY_CONTENT HEX)

get_filename_component(FILENAME "${INPUT_FILE}" NAME)
string(REGEX REPLACE "[^a-zA-Z0-9]" "_" VAR_NAME "${FILENAME}")
string(TOLOWER "${VAR_NAME}" VAR_NAME)

set(HEADER_CONTENT "static const char ${VAR_NAME}[] = {\n")
string(LENGTH "${BINARY_CONTENT}" HEX_LENGTH)

set(OFFSET 0)
while(OFFSET LESS ${HEX_LENGTH})
    string(SUBSTRING "${BINARY_CONTENT}" ${OFFSET} 2 HEX_BYTE)
    string(APPEND HEADER_CONTENT "0x${HEX_BYTE}")
    math(EXPR OFFSET "${OFFSET} + 2")
    if(OFFSET LESS ${HEX_LENGTH})
        string(APPEND HEADER_CONTENT ", ")
    endif()
endwhile()
string(APPEND HEADER_CONTENT "\n};\n")

file(WRITE "${OUTPUT_FILE}" "${HEADER_CONTENT}")