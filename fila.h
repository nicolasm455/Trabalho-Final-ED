/**
 * @file fila.h
 * @author Nicolas Marques, Nícolas Pratis, Pedro Benetton, Vinicius.
 * @brief Arquivo header com as funções relativas a manipulação de filas.
 * @version 1.0
 * @date 2025-02-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef FILA_H
#define FILA_H

#include "lista.h"

/**
 * @brief  Struct do Nó da Fila
 * 
 */
typedef struct NoFila {
    Produto produto;
    struct NoFila* proximo;
} NoFila;

/**
 * @brief Struct da Fila
 * 
 */
typedef struct Fila {
    NoFila* inicio;
    NoFila* fim;
} Fila;

Fila* fila_criar();
void fila_inserir(Fila* f, Produto p);
Produto fila_remover(Fila* f);
int fila_vazia(Fila* f);
void fila_liberar(Fila* f);
void fila_listar(Fila* f);

#endif