cmake_minimum_required(VERSION 3.10)

# Nome progetto
project(LibrarySystem C)

# Standard C richiesto
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Aggiungi cartella modules/ al path degli header
include_directories(modules)

# Sorgenti
set(SOURCES
    src/main.c
    src/books.c
    src/users.c
    src/utils.c
)

# Crea eseguibile
add_executable(library ${SOURCES})

