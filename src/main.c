#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passageiro.h"
#include "tripulacao.h"

#define MAX_PASSAGEIROS 100
#define MAX_TRIPULACAO 50

void exibirMenu();

int main() {
    passageiro **passageiros = NULL;  // Array de ponteiros para struct passageiro
    int quantidadePassageiros = 0;                      // Quantidade de passageiros carregados
    tripulacao **tripulantes = NULL;  // Array de ponteiros para struct tripulacao
    int quantidadeTripulacao = 0;                    // Quantidade de tripulantes carregados
    int opcao;

    // Carrega os passageiros e a tripulação do arquivo
    passageiros = carregarPassageiros(&quantidadePassageiros);
    tripulantes = carregarTripulacao(&quantidadeTripulacao);

    if (quantidadePassageiros > 0) {
        printf("Passageiros carregados do arquivo.\n");
    }
    if (quantidadeTripulacao > 0) {
        printf("Tripulação carregada do arquivo.\n");
    }

    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer de entrada

        if (opcao == 1) {
            // Cadastrar Passageiro
            passageiro *novoPassageiro = cadastrarPassageiro();

            // Redimensiona o array de passageiros e adiciona o novo passageiro
            passageiros = realloc(passageiros, (quantidadePassageiros + 1) * sizeof(passageiro *));
            if (!passageiros) {
                perror("Erro ao alocar memória para passageiros");
                exit(EXIT_FAILURE);
            }
            passageiros[quantidadePassageiros] = novoPassageiro;
            quantidadePassageiros++;

            printf("Passageiro adicionado com sucesso!\n");

        } else if (opcao == 2) {
            // Cadastrar Tripulante
            tripulacao *novoTripulante = cadastrarTripulacao();

            // Redimensiona o array de tripulantes e adiciona o novo tripulante
            tripulantes = realloc(tripulantes, (quantidadeTripulacao + 1) * sizeof(tripulacao *));
            if (!tripulantes) {
                perror("Erro ao alocar memória para tripulantes");
                exit(EXIT_FAILURE);
            }
            tripulantes[quantidadeTripulacao] = novoTripulante;
            quantidadeTripulacao++;

            printf("Tripulante adicionado com sucesso!\n");

        } else if (opcao == 3) {
            // Exibir Passageiros
            printf("\nLista de Passageiros:\n");
            for (int i = 0; i < quantidadePassageiros; i++) {
                exibirPassageiro(passageiros[i]);
            }

        } else if (opcao == 4) {
            // Exibir Tripulação
            printf("\nLista de Tripulantes:\n");
            for (int i = 0; i < quantidadeTripulacao; i++) {
                exibirTripulacao(tripulantes[i]);
            }

        } else if (opcao != 0) {
            printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    // Libera a memória alocada
    for (int i = 0; i < quantidadePassageiros; i++) {
        free(passageiros[i]);
    }
    free(passageiros);

    for (int i = 0; i < quantidadeTripulacao; i++) {
        free(tripulantes[i]);
    }
    free(tripulantes);

    printf("Programa finalizado.\n");
    return 0;
}

void exibirMenu() {
    printf("\n===== Menu =====\n");
    printf("1. Cadastrar Passageiro\n");
    printf("2. Cadastrar Tripulante\n");
    printf("3. Exibir Passageiros\n");
    printf("4. Exibir Tripulantes\n");
    printf("0. Sair\n");
}
