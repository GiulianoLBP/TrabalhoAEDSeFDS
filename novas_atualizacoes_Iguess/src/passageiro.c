#include "passageiro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para inicializar um passageiro com alocação dinâmica para strings
passageiro* criarPassageiro(int codigo, const char *nome, const char *endereco, const char *telefone, int fidelidade, int pontosFidelidade) {
    passageiro *p = (passageiro*)malloc(sizeof(passageiro));
    if (!p) {
        perror("Erro ao alocar memória para passageiro");
        exit(EXIT_FAILURE);
    }

    p->codigo = codigo;
    p->nome = strdup(nome);        // Aloca e copia o nome
    p->endereco = strdup(endereco);// Aloca e copia o endereço
    p->telefone = strdup(telefone);// Aloca e copia o telefone
    p->fidelidade = fidelidade;
    p->pontosFidelidade = pontosFidelidade;

    if (!p->nome || !p->endereco || !p->telefone) {
        perror("Erro ao alocar memória para strings do passageiro");
        free(p);
        exit(EXIT_FAILURE);
    }

    return p;
}
// Função para cadastrar um passageiro
passageiro* cadastrarPassageiro() {
    int codigo, fidelidade, pontosFidelidade;
    char *nome = NULL, *endereco = NULL, *telefone = NULL;
    size_t len = 0;

    // Obtenha os dados do passageiro
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
    passageiro *novoPassageiro = criarPassageiro(codigo, nome, endereco, telefone, fidelidade, pontosFidelidade);

    // Libera as strings temporárias
    free(nome);
    free(endereco);
    free(telefone);

    return novoPassageiro;
}
// Função para liberar a memória de um passageiro
void liberarPassageiro(passageiro *p) {
    if (p) {
        free(p->nome);
        free(p->endereco);
        free(p->telefone);
        free(p);
    }
}

// Função para exibir informações do passageiro
void exibirPassageiro(const passageiro *p) {
    if (p) {
        printf("Código: %d\n", p->codigo);
        printf("Nome: %s\n", p->nome);
        printf("Endereço: %s\n", p->endereco);
        printf("Telefone: %s\n", p->telefone);
        printf("Fidelidade: %s\n", p->fidelidade ? "Sim" : "Não");
        printf("Pontos de Fidelidade: %d\n", p->pontosFidelidade);
    }
}


// Funcao para exibir informacoes de todos os passageiros
void exibirTodosPassageiros(passageiro **passageiros, int quantidade) {
    if (quantidade == 0) {
        printf("Nenhum passageiro cadastrado.\n");
        return;
    }
    
    for (int i = 0; i < quantidade; i++) {
        printf("\nPassageiro %d:\n", i + 1);
        exibirPassageiro(passageiros[i]);
    }
}
