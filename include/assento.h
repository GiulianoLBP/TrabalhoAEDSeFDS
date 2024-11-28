#ifndef ASSENTO_H
#define ASSENTO_H

#define TAM_BUFFER 256

// Estrutura para Assento
typedef struct{
    int numero;
    int codigoVoo;
    int status; // 1 - Ocupado, 0 - Livre
} assento;

// Funções para assento
assento* criarAssento(int codigo, int codVoo, int status);
assento* cadastrarAssento();
void exibirAssento(const assento *a);
int verificarAssentoDisponivel(int codigoVoo, int numeroAssento);
int atualizarStatusAssento(int codigoVoo, int numeroAssento);
void salvarNoArquivoAssento(assento *a);
assento** carregarAssentos(int *quantidade);

#endif
