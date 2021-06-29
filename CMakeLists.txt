cmake_minimum_required(VERSION 3.12)

project(Tieto LANGUAGES C)

file(GLOB PROJECT_SOURCE_FILES CONFIGURE_DEPENDS src/*.c)

string( TOLOWER "${CMAKE_C_COMPILER_ID}" COMPILER_ID )
if (COMPILER_ID STREQUAL "clang")
    add_compile_options(-Weverything -Wno-vla -Wno-unused-parameter -Wno-padded -Wno-atomic-implicit-seq-cst)
elseif(COMPILER_ID STREQUAL "gcc")
    add_compile_options(-Wall -Wextra -Wno-vla -Wno-unused-parameter -Wno-padded -Wno-atomic-implicit-seq-cst)
endif() 

add_executable(main ${PROJECT_SOURCE_FILES})
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(main pthread)