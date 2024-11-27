#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

// Estrutura passageiro
typedef struct {
    int codigo;               // Código do passageiro que seria como se fosse o id
    char nome[40];               // Nome do passageiro (alocação dinâmica usando malloc)
    char endereco[40];           // Endereço do passageiro (alocação dinâmica usando malloc)
    char telefone[40];           // Telefone do passageiro (alocação dinâmica usando malloc)
    int fidelidade;           // Fidelidade: 1 para "Sim", 0 para "Não"
    int pontosFidelidade;     // Pontos de fidelidade
} passageiro;

// Declaração das funções associadas ao passageiro
passageiro* criarPassageiro(int codigo, const char *nome, const char *endereco, const char *telefone, int fidelidade, int pontosFidelidade);
passageiro** carregarPassageiros(int *quantidade);       // Função para carregar passageiros do arquivo
void liberarPassageiro(passageiro *p);
void exibirPassageiro(const passageiro *p);
passageiro* cadastrarPassageiro();
void salvarNoArquivo(passageiro *p);                      // Função para salvar um passageiro no arquivo
// void listarPassageiros(FILE *arquivo);                    // Função para listar passageiros do arquivo
#endif // PASSAGEIRO_H



