macro(ccola_generate_version_header)
    set(${CMAKE_PROJECT_NAME}_VERSION_STRING "")
    set(${CMAKE_PROJECT_NAME}_VERSION_STRING_FULL "")
    set(${CMAKE_PROJECT_NAME}_VERSION_GIT_SHA)

    if (NOT ${CMAKE_PROJECT_NAME}_VERSION_MAJOR)
        set(${CMAKE_PROJECT_NAME}_VERSION_MAJOR 0)
    endif()

    if (NOT ${CMAKE_PROJECT_NAME}_VERSION_MINOR)
        set(${CMAKE_PROJECT_NAME}_VERSION_MINOR 0)
    endif()

    if (NOT ${CMAKE_PROJECT_NAME}_VERSION_PATCH)
        set(${CMAKE_PROJECT_NAME}_VERSION_PATCH 0)
    endif()

    find_package(Git QUIET)

    if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
        execute_process(COMMAND ${GIT_EXECUTABLE} -C ${PROJECT_SOURCE_DIR} rev-parse --short @{0}
            OUTPUT_VARIABLE ${CMAKE_PROJECT_NAME}_VERSION_GIT_SHA
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET)
    endif()

    set(${CMAKE_PROJECT_NAME}_VERSION_STRING ${${CMAKE_PROJECT_NAME}_VERSION_MAJOR}.${${CMAKE_PROJECT_NAME}_VERSION_MINOR}.${${CMAKE_PROJECT_NAME}_VERSION_PATCH})

    if (${CMAKE_PROJECT_NAME}_VERSION_GIT_SHA)
        set(${CMAKE_PROJECT_NAME}_VERSION_STRING_FULL
            ${${CMAKE_PROJECT_NAME}_VERSION_STRING}+${${CMAKE_PROJECT_NAME}_VERSION_GIT_SHA})
    else()
        set(${CMAKE_PROJECT_NAME}_VERSION_STRING_FULL ${CMAKE_PROJECT_NAME}_VERSION_STRING)
    endif()

    string(TIMESTAMP GENERATOR_TIMESTAMP)
    configure_file("${PROJECT_SOURCE_DIR}/ccola/Version.h.in" "${PROJECT_BINARY_DIR}/Version.h")
endmacro()