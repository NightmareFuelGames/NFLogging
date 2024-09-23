cmake_minimum_required(VERSION 3.29)
project(NFLogging)

print_info()

################# BASE #################
ADD_SUBDIRECTORY(Source)

################# EXAMPLES #################
option(NF_LOGGING_EXAMPLES "Build NFLogging example(s)" ON)


if(NF_LOGGING_EXAMPLES)
    ADD_SUBDIRECTORY(Examples)
endif()