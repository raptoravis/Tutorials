cmake_minimum_required(VERSION 3.10)

project(cpp11)


list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

find_package(Boost 1.60.0 COMPONENTS thread)
#message("${Boost_INCLUDE_DIRS}")

#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "$ENV{Boost_ROOT}/boost")
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "$ENV{Boost_ROOT}/lib")

include_directories(${Boost_INCLUDE_DIRS})

#add_executable(test "${CMAKE_SOURCE_DIR}/DiveIntoC++11/1_Arkanoid/p1.cpp")
#target_link_libraries(test ${SFML_LIBRARIES})


file(GLOB CPP_SOURCES "${CMAKE_SOURCE_DIR}/DiveIntoC++11/1_Arkanoid/*.cpp")

#message ("${CPP_SOURCES}")

foreach(MAIN_FILE ${CPP_SOURCES})
	get_filename_component(NAME_XXX ${MAIN_FILE} NAME_WE)

	add_executable(${NAME_XXX} ${MAIN_FILE})
	target_link_libraries(${NAME_XXX} ${SFML_LIBRARIES})

	#set_property(TARGET ${NAME_XXX} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}")
	#set_property(TARGET ${NAME_XXX} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
	#set_property(TARGET ${NAME_XXX} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/code")
endforeach(MAIN_FILE)
