TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        food.cpp \
        game.cpp \
        main.cpp \
        snake.cpp

LIBS += -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

HEADERS += \
    food.h \
    game.h \
    snake.h
