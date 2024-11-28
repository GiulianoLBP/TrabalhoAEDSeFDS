#ifndef RESERVA_H
#define RESERVA_H

#include "voo.h"
#include "passageiro.h"
#include "assento.h"

#define TAM_BUFFER 256

// Estrutura para Reserva
typedef struct {
    int codigoVoo;
    int numeroAssento;
    int codigoPassageiro;
} reserva;

// Funções para reserva
reserva* criarReserva(int numeroAssento, int codVoo, int codPassageiro);
reserva* cadastrarReserva();
void exibirReserva(const reserva *r);
int validarReserva(int codigoVoo, int numeroAssento, int codigoPassageiro);
void salvarNoArquivoReserva(reserva *r);
void cancelarReserva(int codigoVoo, int numeroAssento, int codigoPassageiro, reserva ***reservas, int *quantidadeReservas, assento **assentos, int quantidadeAssentos);
reserva** carregarReservas(int *quantidade);

#endif
