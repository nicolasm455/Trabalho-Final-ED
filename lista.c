/**
 * @file lista.c
 * @author Nicolas Marques, Nícolas Pratis, Pedro Benetton, Vinicius.
 * @brief Arquivo com as funções relativas a manipulação de listas.
 * @version 1.0
 * @date 2025-02-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "fila.h"



/**
 * @brief Função para criar uma lista dinâmica.
 * 
 * @return Lista* 
 */
Lista* lista_criar() { 
    Lista* l = (Lista*) malloc(sizeof(Lista));
    l->sentinela = (No*) malloc(sizeof(No));
    l->sentinela->proximo = l->sentinela;
    l->sentinela->anterior = l->sentinela;
    return l;
}

/**
 * @brief Função para inserir um produto no fim da lista.
 * 
 * @param l 
 * @param p 
 */
void lista_inserir_fim(Lista* l, Produto p) { // Funcao para inserir no fim da lista.
    No* novo = (No*) malloc(sizeof(No));
    novo->produto = p;
    novo->proximo = l->sentinela;
    novo->anterior = l->sentinela->anterior;
    l->sentinela->anterior->proximo = novo;
    l->sentinela->anterior = novo;
}
/**
 * @brief Função para adicionar um produto ao estoque.
 * 
 * @param estoque 
 * @param reposicao 
 */
void adicionar_produto(Lista* estoque, Lista* reposicao) { 
    Produto p;
    printf("ID do produto: ");
    scanf("%d", &p.id);
    printf("Nome do produto: ");
    scanf("%s", p.nome);
    printf("Quantidade: ");
    scanf("%d", &p.quantidade);

    // Verifica se o produto está na lista de reposicao
    No* no_reposicao = lista_buscar(reposicao, p.id);
    if (no_reposicao != NULL) { 
        // Se o produto estava na reposicao, ele é removido de lá
        lista_remover_no(reposicao, no_reposicao);
        printf("Produto %s removido da lista de reposicao.\n", p.nome);
    }

    lista_inserir_fim(estoque, p); // Insere no estoque
    printf("Produto adicionado ao estoque.\n");
}

/**
 * @brief Função para listar as vendas realizadas.
 * 
 * @param vendas 
 */
void listar_vendas(Lista* vendas) {
    if (vendas->sentinela == NULL || vendas->sentinela->proximo == vendas->sentinela) {
        printf("Nenhuma venda foi realizada ainda.\n");
        return;
    }

    printf("Lista de Vendas Realizadas:\n");
    int contador = 1;

    No* atual = vendas->sentinela->proximo;
    while (atual != vendas->sentinela) {
        printf("%d - %s | Quantidade: %d\n", contador++, atual->produto.nome, atual->produto.quantidade);
        atual = atual->proximo;
    }
}


/**
 * @brief Função para remover um produto da lista usando nó.
 * 
 * @param l 
 * @param no 
 * @return Produto 
 */
Produto lista_remover_no(Lista* l, No* no) { // Funcao que remove produto da lista.
    if (no == l->sentinela) {
        Produto erro;
        erro.id = -1;
        return erro;
    }
    no->anterior->proximo = no->proximo;
    no->proximo->anterior = no->anterior;
    Produto p = no->produto;
    free(no);
    return p;
}

/**
 * @brief Função para buscar um produto na lista.
 * 
 * @param l 
 * @param id 
 * @return No* 
 */
No* lista_buscar(Lista* l, int id) {
    No* atual = l->sentinela->proximo;
    while (atual != l->sentinela) {
        if (atual->produto.id == id) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

/**
 * @brief  Função para listar os produtos no estoque.
 * 
 * @param l 
 */
void lista_listar(Lista* l) {
    if (l->sentinela == NULL || l->sentinela->proximo == l->sentinela) {
        printf("Nao ha itens no estoque.\n");
        return;
    }
    
    No* atual = l->sentinela->proximo;
    while (atual != l->sentinela) {
        printf("ID: %d, Nome: %s, Quantidade: %d\n", atual->produto.id, atual->produto.nome, atual->produto.quantidade);
        atual = atual->proximo;
    }
}

/**
 * @brief Função para listar os produtos que necessitam de reposição.
 * 
 * @param l 
 */
void listar_reposicao(Lista* reposicao) {
    if (reposicao->sentinela == NULL || reposicao->sentinela->proximo == reposicao->sentinela) {
        printf("Nenhum item precisa de reposicao.\n");
        return;
    }
    
    printf("Itens que necessitam de reposicao:\n");
    int contador = 1;
    
    No* atual = reposicao->sentinela->proximo;
    while (atual != reposicao->sentinela) {
        printf("%d - %s\n", contador++, atual->produto.nome);
        atual = atual->proximo;
    }
}

/**
 * @brief Função para realizar uma venda.
 * 
 * @param estoque 
 * @param reposicao 
 * @param vendas 
 * @param historicoVendas 
 */
void realizar_venda(Lista* estoque, Lista* reposicao, Lista* vendas, fila* historicoVendas) {
    int id, quantidade;
    printf("ID do produto para venda: ");
    scanf("%d", &id);
    
    No* no = lista_buscar(estoque, id);
    if (no == NULL) {
        printf("Produto nao encontrado no estoque.\n");
        return;
    }
    
    printf("Quantidade para remover: ");
    scanf("%d", &quantidade);
    
    if (quantidade > no->produto.quantidade) {
        printf("Quantidade insuficiente no estoque.\n");
        return;
    }
    
    Produto vendido = no->produto;
    vendido.quantidade = quantidade; // Salva apenas a quantidade vendida
    
    lista_inserir_fim(vendas, vendido); // Adiciona a venda à lista de vendas
    fila_inserir(historicoVendas, vendido); // Adiciona a venda à fila de histórico

    no->produto.quantidade -= quantidade;
    
    if (no->produto.quantidade == 0) { // Se zerar o estoque, adiciona à reposição e remove do estoque
        lista_inserir_fim(reposicao, no->produto);
        lista_remover_no(estoque, no);
    }
    
    printf("%d unidades de %s enviadas para entrega e registradas como venda.\n", quantidade, vendido.nome);
}

/**
 * @brief Função para liberar a memória alocada pela lista.
 * 
 * @param l 
 */
void lista_liberar(Lista* l) {
    No* atual = l->sentinela->proximo;
    while (atual != l->sentinela) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(l->sentinela);
    free(l);
}