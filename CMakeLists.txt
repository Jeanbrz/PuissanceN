cmake_minimum_required(VERSION 3.19)
project(untitled6 C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled6 main.c LOGIQUE/Logique.c LOGIQUE/Logique.h AFFICHAGE/Affichage.c AFFICHAGE/Affichage.h DONNEES/Base_Donnee.c DONNEES/Base_Donnee.h UTILS/Utils.c UTILS/Utils.h)