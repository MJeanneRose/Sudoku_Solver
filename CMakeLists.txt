#Set projet
cmake_minimum_required( VERSION 3.16 )

set(CMAKE_C_COMPILER "gcc")

project (Sudoku_Resolver LANGUAGES C VERSION 1.0)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CONFIGURATION_TYPES RELEASE)

set(CMAKE_C_FLAGS "-Wall -Wextra -std=c11 -Wundef -Wshadow -Wstrict-prototypes -Wunreachable-code")

#Configure chemin
set(CMAKE_SOURCE_DIR %{CMAKE_SOURCE_DIR}/src)

# Find dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories (${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

#Créer des variables avec les fichiers à compiler
file(GLOB SRCS *.c)

#Compile
add_executable(Sudoku_Resolver ${SRCS})
target_link_libraries(Sudoku_Resolver ${GTK3_LIBRARIES})