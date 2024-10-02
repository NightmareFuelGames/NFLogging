MESSAGE(STATUS "---------------------------------------------------------------------------------------")
MESSAGE(STATUS "->NFLogging")
MESSAGE(STATUS "---------->NFLogging-------------------------------------------------------------------")
MESSAGE(STATUS "---------------------------------------------------------------------------------------")

include(${CMAKE_SOURCE_DIR}/cmake/defaults-cpp.cmake)
################# TARGET #################
set(NFLoggingTarget NFLogging)

set(NFLoggingSource ${CMAKE_CURRENT_SOURCE_DIR}/)

set(NFLoggingPublIncDir ${NFLoggingSource}Public/)
set(NFLoggingPrivIncDir ${NFLoggingSource}Private/)


MESSAGE(STATUS "NFLogging target created")
add_library(${NFLoggingTarget} SHARED
        Public/NFLogging.h

        Private/LogCategory.cpp
        Private/NFLogCategoryManager.cpp
        Private/NFLogging.cpp
        Private/NFLogMessage.cpp
        Private/NFLogging_Priv.h
)

target_compile_definitions(
        ${NFLoggingTarget}
        PRIVATE
        NFLOG_EXPORTS
)

target_include_directories(
        ${NFLoggingTarget}
        PRIVATE
        ${NFLoggingPrivIncDir}
)

target_include_directories(
        ${NFLoggingTarget}
        PUBLIC
        ${NFLoggingPublIncDir}
)

#include(GenerateExportHeader)
#generate_export_header(${NFLoggingTarget})


################# INSTALL #################
file(GLOB NFLoggingPublicHeaders ${NFLoggingPublIncDir}*.h)
SET(HeaderDestinationDir ${BASE_OUTPUT_DIR}/include/NFLogging)

MESSAGE(STATUS "NFLoggingPubIncFiles: ${NFLoggingPublicHeaders} TO ${HeaderDestinationDir}")

add_custom_command(
        TARGET ${NFLoggingTarget} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${HeaderDestinationDir}  # Ensure the destination exists
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${NFLoggingPublicHeaders} ${HeaderDestinationDir}
        COMMENT "Copying public headers to ${HeaderDestinationDir}"
)

# If you want to create a separate custom target just for copying the headers
add_custom_target(copy_NFLogging_headers ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${HeaderDestinationDir}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${NFLoggingPublicHeaders} ${HeaderDestinationDir}
        COMMENT "Copying public headers to ${HeaderDestinationDir}"
)


