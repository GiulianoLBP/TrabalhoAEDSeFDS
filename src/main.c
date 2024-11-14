// tudo que tiver *TROCAR* deve ser avaliado pois esta escrito de maneira informal pra facilitar o entendimento dos colegas de grupo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passageiro.h"

#define MAX_PASSAGEIROS 100

void exibirMenu();

int main() {
    PASSAGEIRO *passageiros[MAX_PASSAGEIROS];  // Array para armazenar os ponteiros dos passageiros
    int contador = 0;  // Contador de passageiros cadastrados
    int opcao;

    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpar o buffer de entrada

        switch (opcao) {
            case 1:
                cadastrarPassageiro(passageiros, &contador);
                break;
            case 2:
                verificarFidelidadeMenu(passageiros, contador);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    // Liberar memória de todos os passageiros cadastrados
    for (int i = 0; i < contador; i++) {
        liberarPassageiro(passageiros[i]);
    }

    return 0;
}

void exibirMenu() {
    printf("\n===== Menu =====\n");
    printf("1. Cadastrar Passageiro\n");
    printf("2. Verificar Fidelidade\n");
    printf("0. Sair\n");
}
