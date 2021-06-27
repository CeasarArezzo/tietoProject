cmake_minimum_required(VERSION 3.12)

project(Tieto LANGUAGES C)

file(GLOB tmp CONFIGURE_DEPENDS src/*.c)
add_executable(main ${tmp})
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_compile_options(-Wall -Wextra -Weverything -Wno-vla)

target_link_libraries(main pthread)