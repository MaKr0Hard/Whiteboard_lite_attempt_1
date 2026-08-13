cmake_minimum_required(VERSION 3.16)

project(Whiteboard_lite_attempt_1 LANGUAGES CXX C)

add_executable(Whiteboard_lite_attempt_1 main.cpp mainwindow.c editor.cpp drawings.cpp Some_canvas_window.cpp drawings_utils.c)

install(TARGETS Whiteboard_lite_attempt_1 RUNTIME DESTINATION bin)

target_compile_options(Whiteboard_lite_attempt_1 PRIVATE -O2 -Wall -Wextra )

# where to search for libraries and headers
target_include_directories(Whiteboard_lite_attempt_1 PRIVATE /usr/include/iup /usr/include/cd)
target_link_directories(Whiteboard_lite_attempt_1 PRIVATE /usr/lib64)

# link -liup
target_link_libraries(Whiteboard_lite_attempt_1 PRIVATE iupcd iup cd)

