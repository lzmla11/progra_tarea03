cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(progra_tarea03)

# 1. Requisito: C++20 (mínimo)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 2. Incluir el directorio de cabeceras (.h)
# Esto permite que en los .cpp pongas #include "Entity.h" en lugar de "../include/Entity.h"
include_directories(include)

# 3. Listar los archivos de implementación (.cpp)
set(SOURCES
    src/Entity.cpp
    src/CommandCenter.cpp
    src/CommandTypes.cpp
    main.cpp
)

# 4. Crear el ejecutable
add_executable(command_center ${SOURCES})

