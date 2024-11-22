#include "tripulacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para inicializar um passageiro com alocação dinâmica para strings
tripulacao* criarTripulacao(int codigo, const char *nome, const char *telefone, const int cargo) {
    tripulacao *t = (tripulacao*)malloc(sizeof(tripulacao));
    if (!t) {
        perror("Erro ao alocar memoria para tripulacao");
        exit(EXIT_FAILURE);
    }

    t->codigo = codigo;
    t->nome = strdup(nome);        // Aloca e copia o nome
    t->telefone = strdup(telefone);// Aloca e copia o telefone
    t->cargo = strdup(cargo);      // Aloca e copia o cargo

    if (!t->nome || !t->telefone || !t->cargo) {
        perror("Erro ao alocar memoria para strings da tripulacao");
        free(t);
        exit(EXIT_FAILURE);
    }

    return t;
}
// Função para cadastrar tripulacao
tripulacao* cadastrarTripulacao() {
    int codigo;
    char *nome = NULL, *cargo = NULL, *telefone = NULL;
    size_t len = 0;

    // Obtenha os dados do tripulante
    printf("Codigo do tripulante: ");
    scanf("%d", &codigo);
    getchar();  // Limpa o buffer de entrada

    printf("Nome do tripulante: ");
    getline(&nome, &len, stdin);
    nome[strcspn(nome, "\n")] = '\0';  // Remove o caractere de nova linha

    printf("Cargo do tripulante: ");
    len = 0;
    getline(&cargo, &len, stdin);
    cargo[strcspn(cargo, "\n")] = '\0';

    printf("Telefone do tripulante: ");
    len = 0;
    getline(&telefone, &len, stdin);
    telefone[strcspn(telefone, "\n")] = '\0';

    // Cria o novo tripulante com strings alocadas dinamicamente
    tripulacao *novaTripulacao = criarTripulacao(codigo, nome, cargo, telefone);

    // Libera as strings temporárias
    free(nome);
    free(cargo);
    free(telefone);

    return novaTripulacao;
}

// Função para liberar a memória de um tripulante
void liberarTripulacao(tripulacao *t) {
    if (t) {
        free(t->nome);
        free(t->cargo);
        free(t->telefone);
        free(t);
    }
}

// Função para exibir informações da tripulação
void exibirTripulacao(const tripulacao *t) {
    if (t) {
        printf("Codigo: %d\n", t->codigo);
        printf("Nome: %s\n", t->nome);
        printf("Cargo: %s\n", t->cargo);
        printf("Telefone: %s\n", t->telefone);
    }
}


// Funcao para exibir informacoes de todos os tripulantes
void exibirTodosTripulantes(tripulacao **tripulacao, int quantidade) {
    if (quantidade == 0) {
        printf("Nenhum tripulante cadastrado.\n");
        return;
    }
    
    for (int i = 0; i < quantidade; i++) {
        printf("\nPassageiro %d:\n", i + 1);
        exibirTripulacao(tripulacao[i]);
    }
}
