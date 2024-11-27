#include "reserva.h"
#include "voo.h"
#include "passageiro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para verificar se o código do passageiro é válido
int verificarCodigoPassageiro(int codigoPassageiro) {
    FILE *arquivo = fopen("passageiros.dat", "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de passageiros");
        return 0;
    }

    passageiro p;
    while (fread(&p, sizeof(passageiro), 1, arquivo)) {
        if (p.codigo == codigoPassageiro) {
            fclose(arquivo);
            return 1; // Código do passageiro encontrado
        }
    }

    fclose(arquivo);
    return 0; // Código do passageiro não encontrado
}

// Função para atualizar o status de um assento
void atualizarStatusAssento(int codigoVoo, int numeroAssento, int status) {
    FILE *arquivo = fopen("assentos.dat", "rb+");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de assentos");
        return;
    }

    assento a;
    while (fread(&a, sizeof(assento), 1, arquivo)) {
        if (a.codigoVoo == codigoVoo && a.numero == numeroAssento) {
            fseek(arquivo, -sizeof(assento), SEEK_CUR);
            a.status = status;
            fwrite(&a, sizeof(assento), 1, arquivo);
            break;
        }
    }

    fclose(arquivo);
}
// Função para cadastrar uma reserva
reserva* cadastrarReserva() {
    reserva *r = (reserva*)malloc(sizeof(reserva));
    if (!r) {
        perror("Erro ao alocar memória para reserva");
        exit(EXIT_FAILURE);
    }

    // Captura o código do voo e valida
    do {
        printf("Código do voo: ");
        scanf("%d", &r->codigoVoo);

        if (!verificarCodigoVooExistente(r->codigoVoo)) {
            printf("Erro: Código do voo inválido! Tente novamente.\n");
        }
    } while (!verificarCodigoVooExistente(r->codigoVoo));

    // Captura o número do assento e valida
    do {
        printf("Número do assento: ");
        scanf("%d", &r->numeroAssento);

        if (!verificarAssentoDisponivel(r->codigoVoo, r->numeroAssento)) {
            printf("Erro: Assento ocupado ou inválido! Escolha outro.\n");
        }
    } while (!verificarAssentoDisponivel(r->codigoVoo, r->numeroAssento));

    // Captura o código do passageiro e valida
    do {
        printf("Código do passageiro: ");
        scanf("%d", &r->codigoPassageiro);

        if (!verificarCodigoPassageiro(r->codigoPassageiro)) {
            printf("Erro: Código do passageiro inválido! Tente novamente.\n");
        }
    } while (!verificarCodigoPassageiro(r->codigoPassageiro));

    salvarNoArquivoReserva(r);
    atualizarStatusAssento(r->codigoVoo, r->numeroAssento, 1); // Marca o assento como ocupado
    return r;
}

// Função para cancelar uma reserva
void cancelarReserva(int codigoVoo, int numeroAssento) {
    FILE *arquivo = fopen("reservas.dat", "rb+");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de reservas");
        return;
    }

    reserva r;
    int encontrado = 0;

    // Procura a reserva no arquivo
    while (fread(&r, sizeof(reserva), 1, arquivo)) {
        if (r.codigoVoo == codigoVoo && r.numeroAssento == numeroAssento) {
            encontrado = 1;

            // Remove a reserva (opcional: logicamente, marcando status como inválido)
            fseek(arquivo, -sizeof(reserva), SEEK_CUR);
            memset(&r, 0, sizeof(reserva));
            fwrite(&r, sizeof(reserva), 1, arquivo);

            // Atualiza o status do assento para livre
            atualizarStatusAssento(codigoVoo, numeroAssento, 0);
            printf("Reserva cancelada com sucesso.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Erro: Reserva não encontrada.\n");
    }

    fclose(arquivo);
}

// Função para salvar a reserva no arquivo
void salvarNoArquivoReserva(reserva *r) {
    FILE *arquivo = fopen("reservas.dat", "ab+");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de reservas");
        return;
    }

    fwrite(r, sizeof(reserva), 1, arquivo);
    fclose(arquivo);
}



// Função para exibir a reserva
void exibirReserva(const reserva *r) {
    if (r) {
        printf("\n--- Informações da Reserva ---\n");
        printf("Código do voo: %d\n", r->codigoVoo);
        printf("Número do assento: %d\n", r->numeroAssento);
        printf("Código do passageiro: %d\n", r->codigoPassageiro);
    }
}
