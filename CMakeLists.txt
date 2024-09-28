cmake_minimum_required(VERSION 3.22)
project(NFLogging)

include(${CMAKE_SOURCE_DIR}/cmake/defaults-cpp.cmake)
MESSAGE(STATUS "---------------------------------------------------------------------------------------")
MESSAGE(STATUS "----------------------------------NFLogging: Building----------------------------------")
MESSAGE(STATUS "---------------------------------------------------------------------------------------")
MESSAGE(STATUS "")
print_info()

################# SPDLOG ################
#[[ADD_SUBDIRECTORY(vendor/spdlog)]]

################# BASE #################
ADD_SUBDIRECTORY(Source)

################# EXAMPLES #################
option(NF_LOGGING_EXAMPLES "Build NFLogging example(s)" ON)


if (NF_LOGGING_EXAMPLES)
    ADD_SUBDIRECTORY(Examples)
endif ()