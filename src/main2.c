#include <stdio.h>
#include <stdlib.h>
#include "passageiro.h"

int main() {
    struct passageiro **passageiros = NULL;  // Array de ponteiros para struct passageiro
    int quantidade = 0;                      // Quantidade de passageiros criados
    int opcao;

    do {
        printf("\nMenu de Passageiros:\n");
        printf("1. Adicionar Passageiro\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer de entrada

        if (opcao == 1) {
            int codigo, fidelidade, pontosFidelidade;
            char *nome = NULL, *endereco = NULL, *telefone = NULL;
            size_t len = 0;  // Variável para getline

            // Obtenha os dados do passageiro do usuário
            printf("Código do passageiro: ");
            scanf("%d", &codigo);
            getchar();  // Limpa o buffer de entrada

            printf("Nome do passageiro: ");
            getline(&nome, &len, stdin);
            nome[strcspn(nome, "\n")] = '\0';  // Remove o caractere de nova linha

            printf("Endereço do passageiro: ");
            len = 0;
            getline(&endereco, &len, stdin);
            endereco[strcspn(endereco, "\n")] = '\0';

            printf("Telefone do passageiro: ");
            len = 0;
            getline(&telefone, &len, stdin);
            telefone[strcspn(telefone, "\n")] = '\0';

            printf("Fidelidade (1 para Sim, 0 para Não): ");
            scanf("%d", &fidelidade);

            printf("Pontos de fidelidade: ");
            scanf("%d", &pontosFidelidade);

            // Cria o novo passageiro com strings alocadas dinamicamente
            struct passageiro *novoPassageiro = criarPassageiro(codigo, nome, endereco, telefone, fidelidade, pontosFidelidade);

            // Redimensiona o array de passageiros e adiciona o novo passageiro
            passageiros = realloc(passageiros, (quantidade + 1) * sizeof(struct passageiro *));
            if (!passageiros) {
                perror("Erro ao alocar memória para passageiros");
                exit(EXIT_FAILURE);
            }
            passageiros[quantidade] = novoPassageiro;
            quantidade++;

            printf("Passageiro adicionado com sucesso!\n");

            // Libera as strings temporárias
            free(nome);
            free(endereco);
            free(telefone);

        } else if (opcao != 0) {
            printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    // Exibe todos os passageiros criados
    printf("\nLista de Passageiros:\n");
    for (int i = 0; i < quantidade; i++) {
        exibirPassageiro(passageiros[i]);
    }

    // Libera a memória dos passageiros e do array
    for (int i = 0; i < quantidade; i++) {
        liberarPassageiro(passageiros[i]);
    }
    free(passageiros);

    printf("Programa finalizado.\n");
    return 0;
}
