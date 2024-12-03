#include "tripulacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_BUFFER 256  // Buffer temporário para entrada de strings

// Função para verificar se o código da tripulação já existe no arquivo
int verificarCodigoTripulacaoExistente(int codigo) {
    FILE *arquivo = fopen("tripulacao.dat", "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de tripulacao em verificarCodigoTripulacaoExistente");
        return 0;  // Arquivo não existe ou está vazio, código é válido
    }

    tripulacao t;
    while (fread(&t, sizeof(tripulacao), 1, arquivo)) {
        if (t.codigo == codigo) {
            fclose(arquivo);
            return 1;  // Código duplicado
        }
    }

    fclose(arquivo);
    return 0;  // Código não duplicado
}

// Função para criar um novo membro da tripulação
tripulacao* criarTripulacao(int codigo, const char *nome, const char *telefone, const int cargo) {
    tripulacao *t = (tripulacao*)malloc(sizeof(tripulacao));
    if (!t) {
        perror("Erro ao alocar memória para tripulação");
        exit(EXIT_FAILURE);  // Caso a alocação falhe, sai do programa
    }

    t->codigo = codigo;

    // Usa strncpy para copiar as strings, garantindo que o buffer não seja ultrapassado
    strncpy(t->nome, nome, sizeof(t->nome) - 1);
    t->nome[sizeof(t->nome) - 1] = '\0';  // Garante a terminação da string

    strncpy(t->telefone, telefone, sizeof(t->telefone) - 1);
    t->telefone[sizeof(t->telefone) - 1] = '\0';  // Garante a terminação da string

    t->cargo = cargo;

    return t;  // Retorna o ponteiro para o membro da tripulação criado
}

tripulacao** carregarTripulacao(int *quantidade) {
    FILE *arquivo = fopen("tripulacao.dat", "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de tripulação em carregarTripulacao");
        *quantidade = 0;
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    *quantidade = tamanhoArquivo / sizeof(tripulacao);
    if (*quantidade == 0) {
        fclose(arquivo);
        return NULL;
    }

    tripulacao **tripulantes = malloc(*quantidade * sizeof(tripulacao*));
    if (!tripulantes) {
        perror("Erro ao alocar memória para tripulação");
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < *quantidade; i++) {
        tripulantes[i] = malloc(sizeof(tripulacao));
        if (!tripulantes[i]) {
            perror("Erro ao alocar memória para tripulante");
            fclose(arquivo);
            return NULL;
        }
        size_t bytesLidos = fread(tripulantes[i], sizeof(tripulacao), 1, arquivo);
        if (bytesLidos != 1) {
            printf("Erro ao ler tripulante %d do arquivo\n", i + 1);
            free(tripulantes[i]);
            tripulantes[i] = NULL;
        }
    }

    fclose(arquivo);
    return tripulantes;
}

void salvarNoArquivoTripulacao(tripulacao *t) {
    FILE *arquivo = fopen("tripulacao.dat", "ab+");  // Abre o arquivo para leitura/escrita, cria se não existir
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de tripulação em salvarNoArquivoTripulacao");
    }

    fwrite(t, sizeof(tripulacao), 1, arquivo);  // Grava a estrutura tripulacao no arquivo
    printf("\nMembro da tripulação salvo no arquivo\n");

    fclose(arquivo);
}

// Função para liberar memória alocada para a tripulação
void liberarTripulacao(tripulacao *t) {
    if (t) {
        free(t);
    }
}

// Função para exibir informações de um membro da tripulação
void exibirTripulacao(const tripulacao *t) {
    if (t) {
        printf("\n--- Informações da Tripulação ---\n");
        printf("Código: %d\n", t->codigo);
        printf("Nome: %s\n", t->nome);
        printf("Telefone: %s\n", t->telefone);
        printf("Cargo: ");
        switch (t->cargo) {
            case 1: printf("Piloto\n"); break;
            case 2: printf("Copiloto\n"); break;
            case 3: printf("Comissário\n"); break;
            default: printf("Desconhecido\n"); break;
        }
        printf("------------------------------\n");
    }
}

// Função para cadastrar um novo membro da tripulação
tripulacao* cadastrarTripulacao() {
    int codigo, cargo;
    char buffer[TAM_BUFFER];  // Buffer temporário para leitura das strings

    // Captura os dados do usuário
    printf("Código do membro da tripulação: ");
    while (1) {
        fgets(buffer, TAM_BUFFER, stdin);
        if (isdigit((unsigned char)buffer[0])) {
            codigo = atoi(buffer);
            // Verifica se o código já existe
            if (verificarCodigoTripulacaoExistente(codigo)) {
                printf("Código já existente. Digite outro código: ");
            } else {
                break;
            }
        }
        printf("Código inválido. Digite um número válido: ");
    }

    printf("Nome do membro da tripulação: ");
    fgets(buffer, TAM_BUFFER, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';  // Remove o caractere de nova linha
    char nome[40];  // Array fixo de tamanho 40
    strncpy(nome, buffer, sizeof(nome) - 1);
    nome[sizeof(nome) - 1] = '\0';  // Garante que a string seja terminada

    printf("Telefone do membro da tripulação: ");
    fgets(buffer, TAM_BUFFER, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    char telefone[40];  // Array fixo de tamanho 40
    strncpy(telefone, buffer, sizeof(telefone) - 1);
    telefone[sizeof(telefone) - 1] = '\0';  // Garante que a string seja terminada

    printf("Cargo (1 - Piloto, 2 - Copiloto, 3 - Comissário): ");
    while (1) {
        scanf("%d", &cargo);
        if (cargo >= 1 && cargo <= 3) {
            break;
        }
        printf("Valor inválido. Digite 1 para Piloto, 2 para Copiloto ou 3 para Comissário: ");
    }

    // Cria um novo membro da tripulação usando os dados fornecidos
    tripulacao *novaTripulacao = criarTripulacao(codigo, nome, telefone, cargo);

    salvarNoArquivoTripulacao(novaTripulacao);

    return novaTripulacao;
}


void pesquisarTripulante(int quantidadeTripulacao, tripulacao **tripulantes) {
    char entrada[50];
    printf("Escreva o codigo ou o nome do Tripulante: ");
    scanf("%s", entrada);

    int encontrado = 0;
    for (int i = 0; i < quantidadeTripulacao; i++) {
        // Verifica se o código (como número) ou o nome (como string) corresponde
        if (atoi(entrada) == tripulantes[i]->codigo || strcmp(entrada, tripulantes[i]->nome) == 0) {
            exibirTripulacao(tripulantes[i]); // Exibe os detalhes do Tripulante
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Tripulante não encontrado.\n");
    }
}