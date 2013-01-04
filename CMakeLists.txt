project(evote-generator)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++0x")

add_library(generator SHARED generator.cpp)
target_link_libraries(generator "yaml-cpp")
target_link_libraries(generator "gmp")

add_library(pygenerator MODULE pygenerator.cpp)
target_link_libraries(pygenerator generator)
target_link_libraries(pygenerator boost_python)
set_target_properties(pygenerator PROPERTIES
	PREFIX ""
	INSTALL_RPATH "$ORIGIN"
)

find_package( Boost 1.35 REQUIRED COMPONENTS python )
include_directories(${Boost_INCLUDE_DIRS})
find_package( PythonLibs 2.7 REQUIRED )
include_directories(${PYTHON_INCLUDE_PATH})

install(TARGETS generator pygenerator DESTINATION .)
install(PROGRAMS generator.cgi DESTINATION .)
