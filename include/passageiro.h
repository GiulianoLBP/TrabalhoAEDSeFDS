// passageiro.h
#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H



typedef struct {
    char nome[100];
    int idade;
    int fidelidade;  // Exemplo de atributo
} PASSAGEIRO;

void cadastrarPassageiro(PASSAGEIRO *passageiros[], int *contador);
void verificarFidelidadeMenu(PASSAGEIRO *passageiros[], int contador);
void liberarPassageiro(PASSAGEIRO *passageiro);

#endif
