#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

// Estrutura passageiro
typedef struct {
    int codigo;               // Código do passageiro que seria como se fosse o id
    char *nome;               // Nome do passageiro (alocação dinâmica usando malloc)
    char *endereco;           // Endereço do passageiro (alocação dinâmica usando malloc)
    char *telefone;           // Telefone do passageiro (alocação dinâmica usando malloc)
    int fidelidade;           // Fidelidade: 1 para "Sim", 0 para "Não"
    int pontosFidelidade;     // Pontos de fidelidade
} passageiro;

// Declaração das funções associadas ao passageiro
passageiro* criarPassageiro(int codigo, const char *nome, const char *endereco, const char *telefone, int fidelidade, int pontosFidelidade);
void liberarPassageiro(passageiro *p);
void exibirPassageiro(const passageiro *p);
passageiro* cadastrarPassageiro();

#endif // PASSAGEIRO_H



