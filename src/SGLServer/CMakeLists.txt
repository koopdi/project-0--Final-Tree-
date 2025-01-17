
# SGL_Server

add_subdirectory(libSGL)

cmake_minimum_required(VERSION 3.2.0)
project (SGL_Server VERSION 05.21.2022 LANGUAGES CXX)

# use C++17 language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# tell CMake to run the QT prepocessor (moc), when necessary
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

# Link to Qt5 graphical libraries
find_package(Qt5 COMPONENTS Widgets Multimedia Network REQUIRED)

# as moc files are generated in the binary dir, tell CMake
# to always look for includes there:
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


# Configure flags for the C++ compiler
# (In general, many warnings/errors are enabled to tighten compile-time checking.
# A few overly pedantic/confusing errors are turned off to avoid confusion.)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(
	-g
	-Wall
	-Wextra
	-Werror=return-type
	-Werror=uninitialized
	-Wunused-parameter
	-Wmissing-field-initializers
	-Wno-old-style-cast
	-Wno-sign-compare
	-Wno-sign-conversion
)

# # # student writes ordinary main() function, but it must be called within a
# # # wrapper main() that handles library setup/teardown. Rename student's
# # # to distinguish between the two main() functions and avoid symbol clash
add_compile_options(
	-Dmain=studentMain
)

# source / header files specific to this project
FILE(GLOB SGL_Server_Headers
	*.cpp
)

FILE(GLOB SGL_Server_Sources
	*.h
)

FILE(GLOB SGL_Server_Library_Headers
	libSGL/
)

add_library(SGL_Server
${SGL_Server_Headers}
${SGL_Server_Sources}
${SGL_Server_Library_Headers}
)

target_include_directories(SGL_Server
	PUBLIC
	${SGL_Server_Library_Headers}
	.
)

target_link_libraries(SGL_Server
	PUBLIC
	Protocol
	WindowManager
	SGL
)

add_subdirectory(sglClient)
