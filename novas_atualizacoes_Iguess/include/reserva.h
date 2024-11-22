#ifndef RESERVA_H
#define RESERVA_H

// Estrutura reserva
typedef struct {
    int numeroAssento;        // Número do assento no voo
    int codVoo;               // Código do voo
    int codPassageiro;        // Código do passageiro
} reserva;

// Declaração das funções associadas a reserva
reserva* criarReserva(int numeroAssento, int codVoo, int codPassageiro);
void liberarReserva(reserva *r);
void exibirReserva(const reserva *r);
reserva* cadastrarReserva();

#endif // RESERVA_H


