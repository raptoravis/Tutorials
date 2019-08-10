cmake_minimum_required(VERSION 3.10)

project(cpp11)


list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

find_package(Boost 1.60.0 COMPONENTS thread)

include_directories(${Boost_INCLUDE_DIRS})

#add_executable(test "${CMAKE_SOURCE_DIR}/DiveIntoC++11/1_Arkanoid/p1.cpp")
#target_link_libraries(test ${SFML_LIBRARIES})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

FUNCTION(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist} PARENT_SCOPE)
ENDFUNCTION()

#SUBDIRLIST(SUBDIRS "${CMAKE_SOURCE_DIR}/DiveIntoC++11")
#SUBDIRLIST(SUBDIRS "${CMAKE_SOURCE_DIR}/DiveIntoC++14")

set(TARGET_FOLDER "DiveIntoC++11")

#file(GLOB CPP_SOURCES "${CMAKE_SOURCE_DIR}/DiveIntoC++11/1_Arkanoid/*.cpp")

FUNCTION(ADDTARGETS curdir)
	file(GLOB CPP_SOURCES "${curdir}/*.cpp")

	foreach(MAIN_FILE ${CPP_SOURCES})
		get_filename_component(NAME_XXX ${MAIN_FILE} NAME_WE)

		add_executable(${NAME_XXX} ${MAIN_FILE})
		target_link_libraries(${NAME_XXX} ${SFML_LIBRARIES})
		set_property(TARGET ${NAME_XXX} PROPERTY FOLDER "${TARGET_FOLDER}")

		#set_property(TARGET ${NAME_XXX} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}")
		#set_property(TARGET ${NAME_XXX} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
		#set_property(TARGET ${NAME_XXX} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/code")
	endforeach(MAIN_FILE)

ENDFUNCTION()

ADDTARGETS("${CMAKE_SOURCE_DIR}/DiveIntoC++11/1_Arkanoid")