/**
 * @file fila.c
 * @author Nicolas Marques, Nícolas Pratis, Pedro Benetton, Vinicius.
 * @brief Arquivo com as funções relativas a manipulação de filas.
 * @version 1.0
 * @date 2025-02-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "lista.h"

/**
 * @brief Função para criar uma fila dinâmica.
 * 
 * @return Fila* 
 */
Fila* fila_criar() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

/**
 * @brief Função para inserir um produto na fila.
 * 
 * @param f 
 * @param p 
 */
void fila_inserir(Fila* f, Produto p) {
    NoFila* novo = (NoFila*) malloc(sizeof(NoFila));
    novo->produto = p;
    novo->proximo = NULL;

    if (fila_vazia(f)) {
        f->inicio = novo;
    } else {
        f->fim->proximo = novo;
    }
    f->fim = novo;
}

/**
 * @brief Função para remover um produto da fila.
 * 
 * @param f 
 * @return Produto 
 */
Produto fila_remover(Fila* f) {
    if (fila_vazia(f)) {
        Produto erro;
        erro.id = -1;
        return erro;
    }

    NoFila* removido = f->inicio;
    Produto p = removido->produto;

    f->inicio = f->inicio->proximo;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(removido);
    return p;
}

/**
 * @brief Função para verificar se a fila está vazia.
 * 
 * @param f 
 * @return int 
 */
int fila_vazia(Fila* f) {
    return f->inicio == NULL;
}

/**
 * @brief Função para liberar a memória alocada pela fila.
 * 
 * @param f 
 */
void fila_liberar(Fila* f) {
    while (!fila_vazia(f)) {
        fila_remover(f);
    }
    free(f);
}

/**
 * @brief Função para listar os produtos na fila.
 * 
 * @param f 
 */
void fila_listar(Fila* f) {
    if (fila_vazia(f)) {
        printf("Nenhum historico de vendas registrado.\n");
        return;
    }
    
    printf("Historico de Vendas:\n");
    Fila* temp = fila_criar(); // Fila temporária para armazenar vendas enquanto listamos
    while (!fila_vazia(f)) {
        Produto p = fila_remover(f);
        printf("Produto ID: %d / Nome: %s / Quantidade: %d\n", p.id, p.nome, p.quantidade);
        fila_inserir(temp, p); // Reinsere na fila temporária
    }
    
    // Restaura os produtos na fila original
    while (!fila_vazia(temp)) {
        fila_inserir(f, fila_remover(temp));
    }
    fila_liberar(temp); // Libera a fila temporária
}
