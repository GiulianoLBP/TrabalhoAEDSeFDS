#ifndef TRIPULACAO_H
#define TRIPULACAO_H

// Cada membro da tripulação deve ter um cargo específico.
//  o Deve garantir que não haja dois membros da tripulação com o mesmo código.
//  o Opcionalmente, pode-se gerar o código automaticamente.

// Estrutura tripulação

typedef struct {
    int codigo; //Código da tripulação que seria como se fosse o id
    char *nome; //Nome do cara da tripulação (alocação dinâmica usando malloc)
    char *telefone; //Telefone do cara da tripulação (alocação dinâmica usando malloc)
    int cargo; //Cargo do cara (1 - Piloto, 2 - Copiloto, 3 - Comissário)
} tripulacao;

//Assinatura das funções relacionadas a tripulação
tripulacao* criarTripulacao(int codigo, const char *nome, const char *telefone, const int cargo);
void liberarTripulacao(tripulacao *t);
void exibirTripulacao(const tripulacao *t);
tripulacao* cadastrarTripulacao();

#endif // TRIPULACAO_H