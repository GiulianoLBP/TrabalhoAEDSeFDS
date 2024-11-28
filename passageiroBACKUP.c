#include "passageiro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_BUFFER 256  // Buffer temporário para entrada de strings

// Função para criar um passageiro
passageiro* criarPassageiro(int codigo, const char *nome, const char *endereco, const char *telefone, int fidelidade, int pontosFidelidade) {
    passageiro *p = (passageiro*)malloc(sizeof(passageiro));  // Aloca a memória para o struct passageiro
    if (!p) {
        perror("Erro ao alocar memória para passageiro");
        exit(EXIT_FAILURE);  // Caso a alocação falhe, sai do programa
    }

    p->codigo = codigo;
    
    // Usa strncpy para copiar as strings, garantindo que o buffer não seja ultrapassado
    strncpy(p->nome, nome, sizeof(p->nome) - 1);
    p->nome[sizeof(p->nome) - 1] = '\0';  // Garante a terminação da string

    strncpy(p->endereco, endereco, sizeof(p->endereco) - 1);
    p->endereco[sizeof(p->endereco) - 1] = '\0';  // Garante a terminação da string

    strncpy(p->telefone, telefone, sizeof(p->telefone) - 1);
    p->telefone[sizeof(p->telefone) - 1] = '\0';  // Garante a terminação da string

    p->fidelidade = fidelidade;
    p->pontosFidelidade = pontosFidelidade;

    return p;  // Retorna o ponteiro para o passageiro criado
}

void listarPassageiros(FILE *arquivo) {
    passageiro p;
    rewind(arquivo);
    printf("\n--- Lista de Passageiros ---\n");
    while (fread(&p, sizeof(passageiro), 1, arquivo)) {
        printf("Código: %d\n", p.codigo);
        printf("Nome: %s\n", p.nome);
        printf("Endereço: %s\n", p.endereco);
        printf("Telefone: %s\n", p.telefone);
        printf("Fidelidade: %s\n", p.fidelidade ? "Sim" : "Não");
        printf("Pontos de Fidelidade: %d\n", p.pontosFidelidade);
        printf("----------------------------\n");
    }
}

// Função para carregar passageiros do arquivo
passageiro** carregarPassageiros(int *quantidade) {
    FILE *arquivo = fopen("passageiro.dat", "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo: passageiro.dat em carregarPassageiro");
        *quantidade = 0;
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    *quantidade = tamanhoArquivo / sizeof(passageiro);
    if (*quantidade == 0) {
        fclose(arquivo);
        return NULL;
    }

    passageiro **passageiros = malloc(*quantidade * sizeof(passageiro*));
    if (!passageiros) {
        perror("Erro ao alocar memória para passageiros");
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < *quantidade; i++) {
        passageiros[i] = malloc(sizeof(passageiro));
        if (!passageiros[i]) {
            perror("Erro ao alocar memória para passageiro");
            fclose(arquivo);
            return NULL;
        }
        size_t bytesLidos = fread(passageiros[i], sizeof(passageiro), 1, arquivo);
        if (bytesLidos != 1) {
            printf("Erro ao ler passageiro %d do arquivo\n", i + 1);
            free(passageiros[i]);
            passageiros[i] = NULL;
        }
    }

    fclose(arquivo);
    return passageiros;
}

void salvarNoArquivo(passageiro *p){
    // passageiro p;
    FILE *arquivo = fopen("passageiro.dat", "ab+");  // Abre o arquivo para leitura/escrita, cria se não existir
    if (!arquivo) {
        perror("Erro ao abrir o arquivo: passageiro.dat em f salvaNoArquivo");
    }
     fwrite(p, sizeof(passageiro), 1, arquivo);
     printf("\nPESSOA SALVA NO ARQUIVO\n");
}

// Função para cadastrar um passageiro
passageiro* cadastrarPassageiro() {
    int codigo, fidelidade, pontosFidelidade;
    char buffer[TAM_BUFFER]; // Buffer temporário para leitura das strings

    // Captura os dados do usuário
    printf("Código do passageiro: ");
    scanf("%d", &codigo);
    getchar(); // Limpa o buffer do `scanf`

    printf("Nome do passageiro: ");
    fgets(buffer, TAM_BUFFER, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove o caractere de nova linha
    char nome[40]; // Array fixo de tamanho 40
    strncpy(nome, buffer, sizeof(nome) - 1);
    nome[sizeof(nome) - 1] = '\0'; // Garante que a string seja terminada

    printf("Endereço do passageiro: ");
    fgets(buffer, TAM_BUFFER, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    char endereco[40]; // Array fixo de tamanho 40
    strncpy(endereco, buffer, sizeof(endereco) - 1);
    endereco[sizeof(endereco) - 1] = '\0'; // Garante que a string seja terminada

    printf("Telefone do passageiro: ");
    fgets(buffer, TAM_BUFFER, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    char telefone[40]; // Array fixo de tamanho 40
    strncpy(telefone, buffer, sizeof(telefone) - 1);
    telefone[sizeof(telefone) - 1] = '\0'; // Garante que a string seja terminada

    printf("Fidelidade (1 para Sim, 0 para Não): ");
    scanf("%d", &fidelidade);

    printf("Pontos de fidelidade: ");
    scanf("%d", &pontosFidelidade);

    // Cria um novo passageiro usando as strings alocadas dinamicamente
    passageiro *novoPassageiro = criarPassageiro(codigo, nome, endereco, telefone, fidelidade, pontosFidelidade);
    salvarNoArquivo(novoPassageiro);

    return novoPassageiro;
}

// Função para exibir informações do passageiro
void exibirPassageiro(const passageiro *p) {
    printf("\n--- Lista de Passageiros ---\n");
    if (p) {
        printf("Código: %d\n", p->codigo);
        printf("Nome: %s\n", p->nome);
        printf("Endereço: %s\n", p->endereco);
        printf("Telefone: %s\n", p->telefone);
        printf("Fidelidade: %s\n", p->fidelidade ? "Sim" : "Não");
        printf("Pontos de Fidelidade: %d\n", p->pontosFidelidade);
    }
}