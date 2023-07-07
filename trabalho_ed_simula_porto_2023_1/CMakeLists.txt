cmake_minimum_required(VERSION 3.25)
project(trabalho_ED_simula_porto C)

set(CMAKE_C_STANDARD 11)

add_executable(trabalho_ED_simula_porto main.c fila_navios.c fila_navios.h pilha_containers.c pilha_containers.h funcoes_utilitarias.h funcoes_utilitarias.c travessas.c travessas.h)
