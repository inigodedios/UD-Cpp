cmake_minimum_required(VERSION 3.19)
project(UD_ProyectoProgIV)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(UD_ProyectoProgIV
        src/Api.c
        src/Api.h
        src/BaseDeDatos.c
        src/BaseDeDatos.h
        src/Estadisticas.c
        src/Estadisticas.h
        src/main.cpp
        src/main.h
        src/sqlite3.c
        src/sqlite3.h
        src/Text.c
        src/Text.h)
