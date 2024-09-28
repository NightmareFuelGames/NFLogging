MESSAGE(STATUS "---------------------------------------------------------------------------------------")
MESSAGE(STATUS "--NFLogging -> Source")
MESSAGE(STATUS "---------------------------------------------------------------------------------------")

include(${CMAKE_SOURCE_DIR}/cmake/defaults-cpp.cmake)
################# TARGET #################
set(NFLoggingSource ${CMAKE_CURRENT_SOURCE_DIR}/)

set(NFLoggingPublIncDir ${NFLoggingSource}Public/)
set(NFLoggingPrivIncDir ${NFLoggingSource}Private/)

set(NFLoggingTarget NFLogging)

##
#target
add_library(${NFLoggingTarget} SHARED
        Public/NFLoggingCommon.h

        Private/NFLogging.cpp
        Private/NFLoggingCore.cpp

        Private/LogCategory.cpp
        Private/NFLogCategoryManager.cpp
        Public/NFLogMacros.h
)

###
#spdlog
#[[
if (NOT TARGET spdlog::spdlog)
    MESSAGE(STATUS "NFLogging: spdlog target not found, Searching for spdlog package on the system")
    find_package(spdlog REQUIRED)
endif ()
]]
#[[target_link_libraries(${NFLoggingTarget} PRIVATE spdlog::spdlog)]]
#[[target_include_directories(${NFLoggingTarget} PRIVATE ${spdlog_INCLUDE_DIRS})]]

target_precompile_headers(${NFLoggingTarget} PUBLIC

)

target_compile_definitions(${NFLoggingTarget}
        PRIVATE
        NFLOG_EXPORTS
)

MESSAGE(STATUS "NFLogging target created")

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


#target_link_libraries(${NFLoggingTarget} PRIVATE spdlog)

#copy all public headers to include directory
#[[
file(GLOB NFLoggingPublicHeaders ${NFLoggingPublIncDir}*.h)
SET(HeaderDestinationDir ${BASE_OUTPUT_DIR}/include/NFLogging)
]]
#[[
MESSAGE(STATUS "NFLoggingPubIncFiles: ${NFLoggingPublicHeaders} TO ${HeaderDestinationDir}")
]]
#[[
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
]]
