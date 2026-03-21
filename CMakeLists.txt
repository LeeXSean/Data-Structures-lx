cmake_minimum_required(VERSION 3.10)
project(DataStructuresAlgorithms CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(CMAKE_VS_PLATFORM_NAME)
    set(PLATFORM_DIR "${CMAKE_VS_PLATFORM_NAME}")
else()
    set(PLATFORM_DIR "${CMAKE_SYSTEM_PROCESSOR}")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${PLATFORM_DIR}")

file(GLOB ALL_ITEMS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

foreach(ITEM ${ALL_ITEMS})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/${ITEM}")
        
        file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/${ITEM}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/${ITEM}/*.h")
        
        if(SOURCES)
            add_executable("${ITEM}" ${SOURCES})
            set_target_properties("${ITEM}" PROPERTIES FOLDER "All_DataStructures")
        endif()
    endif()
endforeach()