#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passageiro.h"

#define MAX_PASSAGEIROS 100

void exibirMenu();

int main() {
    passageiro **passageiros = NULL;  // Array de ponteiros para struct passageiro
    int quantidade = 0;                      // Quantidade de passageiros carregados
    int opcao;

    // Carrega os passageiros do arquivo
    passageiros = carregarPassageiros(&quantidade);
    if (quantidade > 0) {
        printf("Passageiros carregados do arquivo.\n");
    }
    printf("\nLista de Passageiros:\n");
    for (int i = 0; i < quantidade; i++) {
        exibirPassageiro(passageiros[i]);
    }
    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer de entrada

        if (opcao == 1) {
            // Chama a função cadastrarPassageiro que lida com a coleta de dados
            passageiro *novoPassageiro = cadastrarPassageiro();

            // Redimensiona o array de passageiros e adiciona o novo passageiro
            passageiros = realloc(passageiros, (quantidade + 1) * sizeof(passageiro *));
            if (!passageiros) {
                perror("Erro ao alocar memória para passageiros");
                exit(EXIT_FAILURE);
            }
            passageiros[quantidade] = novoPassageiro;
            quantidade++;

            printf("Passageiro adicionado com sucesso!\n");

        } else if (opcao != 0) {
            printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    printf("Programa finalizado.\n");
    return 0;
}

void exibirMenu() {
    printf("\n===== Menu =====\n");
    printf("1. Cadastrar Passageiro\n");
    printf("0. Sair\n");
}
