######## OPTIONS #

option(NF_LOG_EXAMPLE_SIMPLE "Build the ${COMPANY_NAME} Log `SimpleLog` example" ON)



if(NF_LOG_EXAMPLE_SIMPLE)
    ADD_SUBDIRECTORY(SimpleLog)
endif()