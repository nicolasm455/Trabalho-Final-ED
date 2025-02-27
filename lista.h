/**
 * @file lista.h
 * @author Nicolas Marques, Nícolas Pratis, Pedro Benetton, Vinicius.
 * @brief Arquivo de cabeçalho com as funções relativas a manipulação de listas.
 * @version 1.0
 * @date 2025-02-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Fila fila;
/**
 * @brief Struct Produto
 * 
 */
typedef struct Produto {
    int id;
    char nome[50];
    int quantidade;
} Produto;
/**
 * @brief Struct do Nó do Produto
 * 
 */
typedef struct No {
    Produto produto;
    struct No* proximo;
    struct No* anterior;
} No;

typedef struct Lista {
    No* sentinela; // Nó sentinela
} Lista;

Lista* lista_criar();
void lista_inserir_fim(Lista* l, Produto p);
Produto lista_remover_no(Lista* l, No* no);
No* lista_buscar(Lista* l, int id);
void adicionar_produto(Lista* estoque, Lista* reposicao);
void listar_vendas(Lista* vendas);
void lista_listar(Lista* l);
void listar_reposicao(Lista* l);
void realizar_venda(Lista* estoque, Lista* reposicao, Lista* vendas, fila* historicoVendas);
void lista_liberar(Lista* l);

#endif