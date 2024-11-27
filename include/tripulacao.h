#ifndef TRIPULACAO_H
#define TRIPULACAO_H

// Cada membro da tripulação deve ter um cargo específico.
// Deve garantir que não haja dois membros da tripulação com o mesmo código.
// Opcionalmente, pode-se gerar o código automaticamente.

// Estrutura tripulação
typedef struct {
    int codigo;        // Código da tripulação (ID)
    char nome[40];     // Nome do membro da tripulação
    char telefone[40]; // Telefone do membro da tripulação
    int cargo;         // Cargo do membro (1 - Piloto, 2 - Copiloto, 3 - Comissário)
} tripulacao;

// Assinatura das funções relacionadas à tripulação
// Função para criar um novo membro da tripulação
tripulacao* criarTripulacao(int codigo, const char *nome, const char *telefone, const int cargo);

// Função para liberar a memória alocada para um membro da tripulação
void liberarTripulacao(tripulacao *t);

// Função para exibir as informações de um membro da tripulação
void exibirTripulacao(const tripulacao *t);

// Função para cadastrar um novo membro da tripulação
tripulacao* cadastrarTripulacao();

// Função para verificar se o código da tripulação já existe no arquivo
int verificarCodigoTripulacaoExistente(int codigo);

// Função para carregar todos os membros da tripulação armazenados no arquivo
tripulacao** carregarTripulacao(int *quantidade);

// Função para salvar um membro da tripulação no arquivo
void salvarNoArquivoTripulacao(tripulacao *t);

#endif // TRIPULACAO_H
