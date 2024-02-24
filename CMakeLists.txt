cmake_minimum_required(VERSION 2.6)
project(SnakeGame)

set(EXECUTABLE_NAME "Snake")
set(PROJECT_SOURCES
       game.h
       snake.h
       food.h
       game.cpp
       food.cpp
       snake.cpp
       main.cpp)

add_executable(${EXECUTABLE_NAME} ${PROJECT_SOURCES})

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-audio)

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)



