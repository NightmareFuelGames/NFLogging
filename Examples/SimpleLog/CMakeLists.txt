MESSAGE(STATUS "---------------------------------------------------------------------------------------")
MESSAGE(STATUS "--NFLogging -> Examples -> example01: ${COMPANY_NAME} Log")
MESSAGE(STATUS "---------------------------------------------------------------------------------------")

if (NOT TARGET NFLogging)
    MESSAGE(FATAL_ERROR "NFLogging target not found")
endif ()

print_info()
add_executable(NFLoggingExample
        main.cpp
        testclass.cpp
        testclass.h
)

target_link_libraries(NFLoggingExample PUBLIC NFLogging)
