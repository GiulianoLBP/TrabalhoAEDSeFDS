// passageiro.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passageiro.h"

#define MAX_PASSAGEIROS 100

void cadastrarPassageiro(PASSAGEIRO *passageiros[], int *contador) {
    if (*contador < MAX_PASSAGEIROS) {  // Verifica se não atingiu o limite
        PASSAGEIRO *novoPassageiro = (PASSAGEIRO *)malloc(sizeof(PASSAGEIRO));
        
        if (novoPassageiro != NULL) {
            printf("Digite o nome do passageiro: ");
            fgets(novoPassageiro->nome, sizeof(novoPassageiro->nome), stdin);
            novoPassageiro->nome[strcspn(novoPassageiro->nome, "\n")] = '\0';  // Remover o '\n' da string

            printf("Digite a idade do passageiro: ");
            scanf("%d", &novoPassageiro->idade);
            getchar();  // Limpar o buffer de entrada

            novoPassageiro->fidelidade = 0;  // Inicializa com fidelidade 0

            passageiros[*contador] = novoPassageiro;
            (*contador)++;
            printf("Passageiro cadastrado com sucesso!\n");
        } else {
            printf("Erro ao alocar memória para o novo passageiro!\n");
        }
    } else {
        printf("Limite de passageiros atingido!\n");
    }
}

void verificarFidelidadeMenu(PASSAGEIRO *passageiros[], int contador) {
    for (int i = 0; i < contador; i++) {
        printf("Passageiro: %s\n", passageiros[i]->nome);
        printf("Fidelidade: %d\n", passageiros[i]->fidelidade);
    }
}

void liberarPassageiro(PASSAGEIRO *passageiro) {
    free(passageiro);
}
