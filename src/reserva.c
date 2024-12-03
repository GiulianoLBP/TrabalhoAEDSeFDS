#include "reserva.h"
#include "voo.h"
#include "passageiro.h"
#include "assento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para verificar se o código do passageiro é válido
int verificarCodigoPassageiro(int codigoPassageiro) {
    FILE *arquivo = fopen("passageiro.dat", "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de passageiros em reservas");
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
        if (r->codigoVoo == 0) {
            printf("Operação cancelada. Você pode realizar outras ações.\n");
            free(r); // Libera a memória alocada
            return NULL; // Retorna NULL indicando que a reserva não foi realizada
        }
        if (!verificarCodigoVooExistente(r->codigoVoo)) {
            printf("Erro: Código do voo inválido! Tente novamente.\n");
        }
    } while (!verificarCodigoVooExistente(r->codigoVoo));

    // Captura o número do assento e valida
    do {
        printf("Número do assento: ");
        scanf("%d", &r->numeroAssento);
        if (r->numeroAssento == 0) {
            printf("Operação cancelada. Você pode realizar outras ações.\n");
            free(r); // Libera a memória alocada
            return NULL; // Retorna NULL indicando que a reserva não foi realizada
        }
        if (verificarAssentoDisponivel(r->codigoVoo, r->numeroAssento)) {
            printf("Erro: Assento ocupado ou inválido! Escolha outro.\n");
        }
    } while (verificarAssentoDisponivel(r->codigoVoo, r->numeroAssento));

    // Captura o código do passageiro e valida
    do {
        printf("Código do passageiro: ");
        scanf("%d", &r->codigoPassageiro);
        if (r->codigoPassageiro == 0) {
            printf("Operação cancelada. Você pode realizar outras ações.\n");
            free(r); // Libera a memória alocada
            return NULL; // Retorna NULL indicando que a reserva não foi realizada
        }
        if (!verificarCodigoPassageiro(r->codigoPassageiro)) {
            printf("Erro: Código do passageiro inválido! Tente novamente.\n");
        }
    } while (!verificarCodigoPassageiro(r->codigoPassageiro));

    salvarNoArquivoReserva(r);
    atualizarStatusAssento(r->codigoVoo, r->numeroAssento); // Marca o assento como ocupado
    return r;
}

// Funcao para carregar passageiros do arquivo
reserva** carregarReservas(int *quantidade) {
    FILE *arquivo = fopen("reservas.dat", "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo em carregarReservas em reservas");
        *quantidade = 0;
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    *quantidade = tamanhoArquivo / sizeof(reserva);
    if (*quantidade == 0) {
        fclose(arquivo);
        return NULL;
    }

    reserva **reservas = malloc(*quantidade * sizeof(reserva*));
    if (!reservas) {
        perror("Erro ao alocar memoria para reservas");
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < *quantidade; i++) {
        reservas[i] = malloc(sizeof(reserva));
        if (!reservas[i]) {
            perror("Erro ao alocar memoria para reserva");
            fclose(arquivo);
            return NULL;
        }
        size_t bytesLidos = fread(reservas[i], sizeof(reserva), 1, arquivo);
        if (bytesLidos != 1) {
            printf("Erro ao ler reserva %d do arquivo\n", i + 1);
            free(reservas[i]);
            reservas[i] = NULL;
        }
    }

    fclose(arquivo);
    return reservas;
}

void exibirTodosAssentos(assento **assentos, int quantidadeAssentos) {
    if (quantidadeAssentos == 0) {
        printf("Nenhum assento disponível para exibição.\n");
        return;
    }

    for (int i = 0; i < quantidadeAssentos; i++) {
        exibirAssento(assentos[i]);
    }
}

void reescreverArquivos(reserva **reservas, int quantidadeReservas, assento **assentos, int quantidadeAssentos) {
    // Apagar o conteúdo dos arquivos anteriores de reservas
    FILE *fileReservas = fopen("reservas.dat", "wb");
    if (!fileReservas) {
        perror("Erro ao abrir o arquivo reservas: em reescreverArquivos de reservas");
        exit(EXIT_FAILURE);
    }

    // Escrever as novas reservas no arquivo
    for (int i = 0; i < quantidadeReservas; i++) {
        fwrite(reservas[i], sizeof(reserva), 1, fileReservas);
    }

    fclose(fileReservas);
    exibirTodosAssentos(assentos, quantidadeAssentos);
    // Apagar o conteúdo dos arquivos anteriores de assentos
    FILE *fileAssentos = fopen("assentos.dat", "wb");
    if (!fileAssentos) {
        perror("Erro ao abrir o arquivo assentos:em reescreverArquivos de reservas");
        exit(EXIT_FAILURE);
    }

    // Escrever os novos assentos no arquivo
    for (int i = 0; i < quantidadeAssentos; i++) {
        fwrite(assentos[i], sizeof(assento), 1, fileAssentos);
    }
    

    fclose(fileAssentos);
}

// Função para cancelar uma reserva
void cancelarReserva(int codigoVoo, int numeroAssento, int codigoPassageiro, reserva ***reservas, int *quantidadeReservas, assento ***assentos, int *quantidadeAssentos) {
    int reservaEncontrada = 0;

    // Procurar a reserva correspondente
    for (int i = 0; i < *quantidadeReservas; i++) {
        if ((*reservas)[i]->codigoVoo == codigoVoo && (*reservas)[i]->numeroAssento == numeroAssento && (*reservas)[i]->codigoPassageiro == codigoPassageiro) {
            // Encontrou a reserva
            reservaEncontrada = 1;

            // Alterar status do assento
            for (int j = 0; j < *quantidadeAssentos; j++) {
                if ((*assentos)[j]->codigoVoo == codigoVoo && (*assentos)[j]->numero == numeroAssento) {
                    (*assentos)[j]->status = 0;  // Marca o assento como Livre (status 0)
                    printf("teste: codVoo %d numAssen%d o que foi achado foi %d %d STATUS: %d\n",codigoVoo,numeroAssento,(*assentos)[j]->codigoVoo,(*assentos)[j]->numero,(*assentos)[j]->status);
                    break;
                }
            }

            // Remover a reserva (shiftar as demais para a esquerda)
            for (int j = i; j < *quantidadeReservas - 1; j++) {
                (*reservas)[j] = (*reservas)[j + 1];
            }
            (*quantidadeReservas)--;

            // Reescrever os arquivos de reservas e assentos
            reescreverArquivos(*reservas, *quantidadeReservas, *assentos, *quantidadeAssentos);

            printf("Reserva cancelada com sucesso!\n");
            break;
        }
    }

    // Verifica se a reserva foi encontrada
    if (!reservaEncontrada) {
        printf("Reserva não encontrada.\n");
    }
}

// Função para salvar a reserva no arquivo
void salvarNoArquivoReserva(reserva *r) {
    FILE *arquivo = fopen("reservas.dat", "ab+");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de reservas em salvarNoArquivoReserva");
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
