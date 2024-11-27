#include "assento.h"
#include "voo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para verificar se o código do voo existe no arquivo voos.dat
int verificarCodigoVoo(int codigoVoo) {
    FILE *arquivo = fopen("voos.dat", "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de voos");
        return 0; // Arquivo não encontrado ou vazio
    }

    voo v;
    while (fread(&v, sizeof(voo), 1, arquivo)) {
        if (v.codigo == codigoVoo) {
            fclose(arquivo);
            return 1; // Código do voo encontrado
        }
    }

    fclose(arquivo);
    return 0; // Código do voo não encontrado
}

// Função para contar quantos assentos já foram cadastrados para um voo
int contarAssentosPorVoo(int codigoVoo) {
    FILE *arquivo = fopen("assentos.dat", "rb");
    if (!arquivo) {
        return 0; // Arquivo não existe ou vazio
    }

    assento a;
    int contador = 0;
    while (fread(&a, sizeof(assento), 1, arquivo)) {
        if (a.codigoVoo == codigoVoo) {
            contador++;
        }
    }

    fclose(arquivo);
    return contador;
}

// Função para cadastrar um assento
assento* cadastrarAssento() {
    assento *a = (assento*)malloc(sizeof(assento));
    if (!a) {
        perror("Erro ao alocar memória para assento");
        exit(EXIT_FAILURE);
    }

    // Captura os dados do assento
    printf("Código do voo: ");
    scanf("%d", &a->codigoVoo);

    // Verifica se o código do voo é válido
    if (!verificarCodigoVoo(a->codigoVoo)) {
        printf("Erro: Código do voo inválido!\n");
        free(a);
        return NULL;
    }

    // Verifica se o limite de assentos foi atingido
    if (contarAssentosPorVoo(a->codigoVoo) >= 60) {
        printf("Erro: Limite de 60 assentos por voo atingido!\n");
        free(a);
        return NULL;
    }

    do {
        printf("Número do assento (1 a 60): ");
        scanf("%d", &a->numero);
        if (a->numero < 1 || a->numero > 60) {
            printf("Erro: O número do assento deve estar entre 1 e 60.\n");
        }
    } while (a->numero < 1 || a->numero > 60);

    // Verifica se o assento está disponível
    if (verificarAssentoDisponivel(a->codigoVoo, a->numero) == 0) {
        printf("Erro: Este assento já está ocupado!\n");
        free(a);
        return NULL;
    }

    printf("Status (1 - Ocupado, 0 - Livre): ");
    scanf("%d", &a->status);

    salvarNoArquivoAssento(a);
    return a;
}

// Função para verificar se o assento está disponível
int verificarAssentoDisponivel(int codigoVoo, int numeroAssento) {
    FILE *arquivo = fopen("assentos.dat", "rb");
    if (!arquivo) {
        return 1; // Arquivo não existe, assento está disponível
    }

    assento a;
    while (fread(&a, sizeof(assento), 1, arquivo)) {
        if (a.codigoVoo == codigoVoo && a.numero == numeroAssento) {
            fclose(arquivo);
            return 0; // Assento já ocupado
        }
    }

    fclose(arquivo);
    return 1; // Assento disponível
}

// Função para salvar o assento no arquivo
void salvarNoArquivoAssento(assento *a) {
    FILE *arquivo = fopen("assentos.dat", "ab+");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de assentos");
        return;
    }

    fwrite(a, sizeof(assento), 1, arquivo);
    fclose(arquivo);
}

// Função para exibir os dados do assento
void exibirAssento(const assento *a) {
    if (a) {
        printf("\n--- Informações do Assento ---\n");
        printf("Número: %d\n", a->numero);
        printf("Código do voo: %d\n", a->codigoVoo);
        printf("Status: %s\n", a->status == 1 ? "Ocupado" : "Livre");
    }
}

//OI BEATRIX, coloquei um numero arbitrario de no maximo 60 lugares, assentos indo de 1 ate 60
// para ter um assento precisa de um codigo de voo valido que ja esta sendo feita a checagem, de resto mais do msm