cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(typit VERSION 1.0 LANGUAGES CXX)

# Especificar la versión de C++ que se usará
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Añadir todos los archivos fuente automáticamente
file(GLOB SOURCES "src/*.cpp")

# Crear el ejecutable
add_executable(typit ${SOURCES})

# Incluir el directorio de cabeceras
target_include_directories(typit PRIVATE src)
