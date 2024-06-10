cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME lab_1)	 
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_definitions(-DSFML_STATIC)

include_directories("../SFML/include/")
include_directories("include/")
link_directories("../SFML/lib/")	

add_executable("${PROJECT_NAME}" include/Application.h
								 include/AnimatedText.h
								 main.cpp
								 Application.cpp
								 AnimatedText.cpp)
								 
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/Aloreta_Marthin.otf
                ${CMAKE_CURRENT_BINARY_DIR})
				
target_link_libraries("${PROJECT_NAME}" sfml-graphics-s-d
										sfml-window-s-d
										sfml-system-s-d
										opengl32
										winmm
										gdi32
										freetype)