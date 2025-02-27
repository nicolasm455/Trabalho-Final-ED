/**
 * @file main.c
 * @author Nicolas Marques, Nícolas Pratis, Pedro Benetton, Vinicius.
 * @brief 
 * @version 1.0
 * @date 2025-02-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */

/*-------------------------------------\
|    Nicolas Marques - 832533          |
|    Nícolas Pratis - 828543           |
|    Pedro Benetton - 832533           |
|    Vinicius Camargo - 829996         |
|                                      |
|    Trabalho Final Estrutura de Dados |
|    Professor Mario                   |
|                                      |
|    Controle de estoque               |
\-------------------------------------*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "lista.h"

/**
 * @brief Função main para rodar o programa.
 * 
 * @return int 
 */
int main() {
    
    Fila* historicoVendas = fila_criar();
    Lista* estoque = lista_criar(); // Lista de produtos no estoque
    Lista* reposicao = lista_criar(); // Lista de reposicao necessaria
    Lista* vendas = lista_criar(); // Lista de vendas realizadas

    int opcao;
    do {
        printf("\n=== Sistema de Controle de Estoque ===\n");
        printf("1 - Adicionar Produto ao Estoque\n");
        printf("2 - Realizar Venda\n");
        printf("3 - Listar Produtos no Estoque\n");
        printf("4 - Listar Vendas Realizadas\n");
        printf("5 - Listar Reposicoes Necessarias\n");
        printf("6 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionar_produto(estoque, reposicao); // Adiciona produtos ao estoque e remove de reposicao 
                break;
            case 2:
                realizar_venda(estoque, reposicao, vendas, historicoVendas); // Passar a fila como parâmetro
                break;
            case 3:
                lista_listar(estoque);
                break;
            case 4:
                fila_listar(historicoVendas);
                break;
            case 5:
                listar_reposicao(reposicao); // Agora percorremos a lista de reposição
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 6);

    lista_liberar(estoque); // Liberando estoque
    lista_liberar(reposicao); // Liberando reposicao
    lista_liberar(vendas); // Liberando vendas
}