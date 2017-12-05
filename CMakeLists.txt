cmake_minimum_required( VERSION 2.8.12 )

project( exception_test_prj )

include( ExternalProject )

#find_package( Boost 1.59.0 REQUIRED COMPONENTS system filesystem regex unit_test_framework program_options iostreams )

#add_definitions( -DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK )

if( ${CMAKE_CXX_COMPILER_ID} STREQUAL 'MSVC' )
	add_compile_options( -D_WIN32_WINNT=0x0601 /std:c++latest )
else( )
	if( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang" )
		add_compile_options(-std=c++14 -march=native -pthread -Weverything -Wno-c++98-compat -Wno-covered-switch-default -Wno-padded -Wno-exit-time-destructors -Wno-c++98-compat-pedantic -Wno-unused-parameter -Wno-missing-noreturn -Wno-missing-prototypes -Wno-disabled-macro-expansion)
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g -O3")
	elseif( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" )
		add_compile_options(-std=c++14 -march=native -pthread -Wall -Wno-deprecated-declarations -Wduplicated-cond -Wlogical-op -Wnull-dereference -Wold-style-cast -Wshadow)
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g -O3")
	endif( )
endif( )

externalproject_add(
    header_libraries_prj
    GIT_REPOSITORY "https://github.com/beached/header_libraries.git"
    SOURCE_DIR "${CMAKE_BINARY_DIR}/dependencies/header_libraries"
    GIT_TAG "master"
    INSTALL_DIR "${CMAKE_BINARY_DIR}/install"
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/install
)

include_directories( SYSTEM "${CMAKE_BINARY_DIR}/install/include" )
link_directories( "${CMAKE_BINARY_DIR}/install/lib" )

#include_directories( SYSTEM ${Boost_INCLUDE_DIRS} )
#link_directories( ${Boost_LIBRARY_DIRS} )

set( HEADER_FOLDER "include" )
set( SOURCE_FOLDER "src" )
set( TEST_FOLDER "tests" )

include_directories( ${HEADER_FOLDER} )

set( HEADER_FILES
	${HEADER_FOLDER}/exception.h
	${HEADER_FOLDER}/non_exception.h
)

set( SOURCE_FILES
	${SOURCE_FOLDER}/exception.cpp
	${SOURCE_FOLDER}/non_exception.cpp
)

enable_testing( )

add_library ( ex_test SHARED ${HEADER_FILES} ${SOURCE_FILES} )
add_dependencies( ex_test header_libraries_prj )

add_executable( exception_test_bin ${HEADER_FILES} ${TEST_FOLDER}/exception_tests.cpp )
#target_link_libraries( exception_test_bin ex_test ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
target_link_libraries( exception_test_bin ex_test ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( exception_test_bin header_libraries_prj )
add_test( exception_test_test exception_test_bin )

