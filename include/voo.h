#ifndef VOO_H
#define VOO_H

#include "passageiro.h"
#include "tripulacao.h"

#define TAM_BUFFER 256

// Estrutura para Voo
typedef struct {
    int codigo;
    char data[11];      // Formato: dd/mm/aaaa
    char hora[6];       // Formato: hh:mm
    char origem[50];
    char destino[50];
    int codigoAviao;
    int codigoPiloto;
    int codigoCopiloto;
    int codigoComissario;
    int status;         // 1 - Ativo, 0 - Inativo
    float tarifa;
} voo;

// Funções para voo
voo* criarVoo(int codigo, int codigoPilot, int codigoCopilot, int codigoComissario, int status, float tarifa, char *data, char *hora, char *origem, char *destino);
voo* cadastrarVoo();
void exibirVoo(const voo *v);
int verificarCodigoVooExistente(int codigo);
void salvarNoArquivoVoo(voo *v);
voo** carregarVoos(int *quantidade);
int validarTripulacaoParaVoo(int piloto, int copiloto, int comissario);

#endif
