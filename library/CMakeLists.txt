cmake_minimum_required(VERSION 3.0.0)
project(IStudioLang-stageI VERSION 0.1.0)

set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_compile_options(-ggdb -O3 -Wall -Wextra -Werror -Wshadow -std=c++2a -fconcepts -pedantic)

# I../includes
include_directories(include)
include_directories(source)

# puts all .cpp files inside src to the SOURCES variable
file(GLOB SOURCES source/*.cpp)

add_executable(IStudioLang source/main.cpp)

enable_testing()

#add_test(NAME Comp COMMAND IStudioLang)

# define a function to simplify adding tests
function(do_test target arg)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
endfunction(do_test)

do_test(IStudioLang -f)