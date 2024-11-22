#include "assento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para criar um assento com alocação dinâmica para strings
assento* criarAssento(int codigo, int codVoo, int status) {
    assento *a = (assento*)malloc(sizeof(assento));
    if (!a) {
        perror("Erro ao alocar memoria para assento");
        exit(EXIT_FAILURE);
    }

    a->codigo = codigo;
    a->codVoo = codVoo;            
    a->status = status;
   

    if (!a->codigo || !a->codVoo || !a->status) {
        perror("Erro ao alocar memoria para assentos");
        free(a);
        exit(EXIT_FAILURE);
    }

    return a;
}
// Função para cadastrar assento
assento* cadastrarAssento() {
    int codigo, codVoo, status;
    size_t len = 0;

    // Obtenha os dados do assento
    printf("Codigo (numero) do assento: ");
    scanf("%d", &codigo);
    getchar();  // Limpa o buffer de entrada

    printf("Codigo do voo: ");
    scanf("%d", &codVoo);
    getchar();  // Limpa o buffer de entrada

    printf("Status (1 - Ocupado, 0 - Livre): ");
    scanf("%d", &status);
    getchar();  // Limpa o buffer de entrada


    // Cria novo assento com strings alocadas dinamicamente
    assento *novoAssento = criarAssento(codigo, codVoo, status);

    return novoAssento;
}

// Função para liberar a memória de um assento
void liberarAssento(assento *a) {
    if (a) {
        free(a->codigo);
        free(a->codVoo);
        free(a->status);
        free(a);
    }
}

// Função para exibir informações do assento
void exibirAssento(const assento *a) {
    if (a) {
        printf("Codigo (numero) assento: %d\n", a->codigo);
        printf("Codigo Voo: %d\n", a->codVoo);
        printf("Status (1 - Ocupado, 0 - Livre): %d\n", a->status);
    }
}


// Funcao para exibir informacoes de todos os assentos
void exibirTodosAssentos(assento **assento, int quantidade) {
    if (quantidade == 0) {
        printf("Nenhum assento cadastrado.\n");
        return;
    }
    
    for (int i = 0; i < quantidade; i++) {
        printf("\nAssento %d:\n", i + 1);
        exibirTripulacao(assento[i]);
    }
}
