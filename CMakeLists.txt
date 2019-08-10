cmake_minimum_required(VERSION 3.10)

project(cpp11)


list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

find_package(Boost 1.60.0 COMPONENTS thread)

include_directories(${Boost_INCLUDE_DIRS})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
################################################################################
################################################################################
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

FUNCTION(ADDTARGETS TOP_FOLDER SECOND_FOLDER)
	set (curdir "${CMAKE_SOURCE_DIR}/${TOP_FOLDER}/${SECOND_FOLDER}")
	
	file(GLOB CPP_SOURCES "${curdir}/*.cpp")

	FOREACH(MAIN_FILE ${CPP_SOURCES})
		get_filename_component(NAME_XXX ${MAIN_FILE} NAME_WE)
		set (NAME_XXX "${SECOND_FOLDER}_${NAME_XXX}")

		add_executable(${NAME_XXX} ${MAIN_FILE})
		target_link_libraries(${NAME_XXX} ${SFML_LIBRARIES})
		set_property(TARGET ${NAME_XXX} PROPERTY FOLDER "${TOP_FOLDER}/${SECOND_FOLDER}")

		#set_property(TARGET ${NAME_XXX} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}")
		#set_property(TARGET ${NAME_XXX} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
		#set_property(TARGET ${NAME_XXX} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/code")
	ENDFOREACH(MAIN_FILE)

ENDFUNCTION()

MACRO(HANDLETOPDIR TOP_FOLDER)
	SUBDIRLIST(SUBDIRS "${CMAKE_SOURCE_DIR}/${TOP_FOLDER}")

	FOREACH(SUBDIR ${SUBDIRS})
		#message(${SUBDIR})
		ADDTARGETS("${TOP_FOLDER}" "${SUBDIR}")
	ENDFOREACH(SUBDIR)
ENDMACRO()

FOREACH(TOP_FOLDER "DiveIntoC++11" "DiveIntoC++14")
	HANDLETOPDIR("${TOP_FOLDER}")
ENDFOREACH(TOP_FOLDER)


