set(log_lib NFLogging)
if(NOT TARGET ${log_lib})
    MESSAGE(FATAL_ERROR "NFLogging target not found")
endif ()

include(../../../cmake/infoprint.cmake)
add_executable(NFLoggingExample
        main.cpp
        )

target_link_libraries(NFLoggingExample PUBLIC ${log_lib})
