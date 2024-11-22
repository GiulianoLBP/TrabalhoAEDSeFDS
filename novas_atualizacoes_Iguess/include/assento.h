#ifndef ASSENTO_H
#define ASSENTO_H

// Estrutura assento
typedef struct {
    int codigo;               // Número do assento no voo
    int codVoo;               // Código do voo
    int status;               // (1 - Ocupado, 0 - Desocupado)
} assento;

// Declaração das funções associadas ao assento
assento* criarAssento(int codigo, int codVoo, int status);
void liberarAssento(assento *a);
void exibirAssento(const assento *a);
assento* cadastrarAssento();

#endif // ASSENTO_H


