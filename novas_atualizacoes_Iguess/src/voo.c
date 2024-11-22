#include "voo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para inicializar um voo com alocação dinâmica para string
voo* criarVoo(int codigo, int codigoPilot, int codigoCopilot, int codigoComissario, int status, float tarifa, char *data, char *hora, char *origem, char *destino) {
    voo *v = (voo*)malloc(sizeof(voo));
    if (!v) {
        perror("Erro ao alocar memoria para voo");
        exit(EXIT_FAILURE);
    }

    v->codigo = codigo;
    v->codigoPilot = codigoPilot;
    v->codigoCopilot = codigoCopilot;
    v->codigoComissario = codigoComissario;
    v->status = status;
    v->tarifa = tarifa;
    v->data = strdup(data);        // Aloca e copia a data
    v->hora = strdup(hora);        // Aloca e copia a hora
    v->origem = strdup(origem);    // Aloca e copia a origem
    v->destino = strdup(destino);  // Aloca e copia o destino
  

    if (!v->data|| !v->hora || !v->origem || !v->destino) {
        perror("Erro ao alocar memória para strings do voo");
        free(v);
        exit(EXIT_FAILURE);
    }

    return v;
}
// Função para cadastrar um voo
voo* cadastrarVoo() {
    int codigo, codigoPilot, codigoCopilot, codigoComissario, status;
    float tarifa;
    char *data = NULL, *hora = NULL, *origem = NULL, *destino = NULL;
    size_t len = 0;

    // Obtenha os dados do voo
    printf("Codigo do voo: ");
    scanf("%d", &codigo);
    getchar();  // Limpa o buffer de entrada

    printf("Codigo do piloto: ");
    scanf("%d", &codigoPilot);
    getchar();  // Limpa o buffer de entrada

    printf("Codigo do copiloto: ");
    scanf("%d", &codigoCopilot);
    getchar();  // Limpa o buffer de entrada

    printf("Codigo do comissario: ");
    scanf("%d", &codigoComissario);
    getchar();  // Limpa o buffer de entrada

    printf("Status do voo (1 - Ativo, 0 - Inativo): ");
    scanf("%d", &status);
    getchar();  // Limpa o buffer de entrada

    printf("Valor da tarifa do voo: ");
    scanf("%f", &tarifa);
    getchar();  // Limpa o buffer de entrada

    printf("Data: ");
    len = 0;
    getline(&data, &len, stdin);
    data[strcspn(data, "\n")] = '\0';

    printf("Hora: ");
    len = 0;
    getline(&hora, &len, stdin);
    hora[strcspn(hora, "\n")] = '\0';

    printf("Origem: ");
    len = 0;
    getline(&origem, &len, stdin);
    origem[strcspn(origem, "\n")] = '\0';

    printf("Destino: ");
    len = 0;
    getline(&destino, &len, stdin);
    destino[strcspn(destino, "\n")] = '\0';

    
    // Cria o novo voo com strings alocadas dinamicamente
    voo* novoVoo = criarVoo(codigo, codigoPilot, codigoCopilot, codigoComissario, status, tarifa, *data, *hora, *origem, *destino);

    // Libera as strings temporárias
    free(data);
    free(hora);
    free(origem);
    free(destino);

    return novoVoo;
}
// Função para liberar a memória de um voo
void liberarVoo(voo *v) {
    if (v) {
        free(v->data);
        free(v->hora);
        free(v->origem);
        free(v->destino);
        free(v);
    }
}

// Função para exibir informações do voo
void exibirVoo(const voo *v) {
    if (v) {
        printf("Codigo voo: %d\n", v->codigo);
        printf("Codigo piloto: %d\n", v->codigoPilot);
        printf("Codigo copiloto: %d\n", v->codigoCopilot);
        printf("Codigo comissario: %d\n", v->codigoComissario);
        printf("Status (1 - Ativo, 0 - Inativo): %d\n", v->status);
        printf("Valor tarifa: %f\n", v->tarifa);
        printf("Data: %s\n", v->data);
        printf("Hora: %s\n", v->hora);
        printf("Origem: %s\n", v->origem);
        printf("Destino: %s\n", v->destino);
    }
}


// Funcao para exibir informacoes de todos os voos
void exibirTodosVoos(voo **voo, int quantidade) {
    if (quantidade == 0) {
        printf("Nenhum voo cadastrado.\n");
        return;
    }
    
    for (int i = 0; i < quantidade; i++) {
        printf("\nVoo %d:\n", i + 1);
        exibirVoo(voo[i]);
    }
}
