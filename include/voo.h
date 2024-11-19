#ifndef VOO_H
#define VOO_H


// Estrutura Voo

typedef struct {
    int codigo; //Código do voo que seria como se fosse o id
    int codigoPilot; //Código do piloto do voo
    int codigoCopilot; //Código do copiloto do voo
    int codigoComissario; //Código do comissário do voo
    int status; //(1 - Ativo, 0 - Inativo)
    float tarifa; //Tarifa, valor voo
    char *data; //Data voo (alocação dinâmica usando malloc)
    char *hora; //Hora voo (alocação dinâmica usando malloc)
    char *origem; //Origem do voo
    char *destino; //Destino do voo
} voo;

//Assinatura das funções relacionadas a voo
voo* criarVoo(int codigo, int codigoPilot, int codigoCopilot, int codigoComissario, int status, float tarifa, char *data, char *hora, char *origem, char *destino);
void liberarVoo(voo *v);
void exibirVoo(const voo *v);
voo* cadastrarVoo();

#endif // VOO_H