#include "voo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verificarCodigoVooExistente(int codigo) {
    FILE *arquivo = fopen("voos.dat", "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de voos");
        return 0;  // Arquivo não existe ou está vazio, código é válido
    }

    voo v;
    while (fread(&v, sizeof(voo), 1, arquivo)) {
        if (v.codigo == codigo) {
            fclose(arquivo);
            return 1;  // Código duplicado
        }
    }

    fclose(arquivo);
    return 0;  // Código não duplicado
}

// Verifica se o código do tripulante existe no arquivo tripulacao.dat
int verificarCodigoTripulanteExistente(int codigo) {
    FILE *arquivo = fopen("tripulacao.dat", "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de tripulação");
        return 0; // Arquivo não encontrado
    }

    int codigoAtual;
    while (fread(&codigoAtual, sizeof(int), 1, arquivo)) {
        if (codigoAtual == codigo) {
            fclose(arquivo);
            return 1; // Código encontrado
        }
    }

    fclose(arquivo);
    return 0; // Código não encontrado
}

voo* cadastrarVoo() {
    voo *v = (voo*)malloc(sizeof(voo));
    if (!v) {
        perror("Erro ao alocar memória para voo");
        exit(EXIT_FAILURE);
    }

    // Captura os dados do voo
    printf("Código do voo: ");
    scanf("%d", &v->codigo);
    getchar();

    printf("Data do voo (dd/mm/aaaa): ");
    fgets(v->data, 11, stdin);
    v->data[strcspn(v->data, "\n")] = '\0';

    printf("Hora do voo (hh:mm): ");
    fgets(v->hora, 6, stdin);
    v->hora[strcspn(v->hora, "\n")] = '\0';

    printf("Origem: ");
    fgets(v->origem, 50, stdin);
    v->origem[strcspn(v->origem, "\n")] = '\0';

    printf("Destino: ");
    fgets(v->destino, 50, stdin);
    v->destino[strcspn(v->destino, "\n")] = '\0';

    printf("Código do avião: ");
    scanf("%d", &v->codigoAviao);

    printf("Status (1 - Ativo, 0 - Inativo): ");
    scanf("%d", &v->status);

    if (v->status == 1) { // Validar tripulação somente se o voo for ativo
        do {
            printf("Código do piloto: ");
            scanf("%d", &v->codigoPiloto);
            if (!verificarCodigoTripulanteExistente(v->codigoPiloto)) {
                printf("Erro: Código do piloto inválido! Tente novamente.\n");
            }
        } while (!verificarCodigoTripulanteExistente(v->codigoPiloto));

        do {
            printf("Código do copiloto: ");
            scanf("%d", &v->codigoCopiloto);
            if (!verificarCodigoTripulanteExistente(v->codigoCopiloto)) {
                printf("Erro: Código do copiloto inválido! Tente novamente.\n");
            }
        } while (!verificarCodigoTripulanteExistente(v->codigoCopiloto));

        do {
            printf("Código do comissário: ");
            scanf("%d", &v->codigoComissario);
            if (!verificarCodigoTripulanteExistente(v->codigoComissario)) {
                printf("Erro: Código do comissário inválido! Tente novamente.\n");
            }
        } while (!verificarCodigoTripulanteExistente(v->codigoComissario));
    } else { 
        // Para voos inativos, aceitar apenas 0 ou códigos válidos
        do {
            printf("Código do piloto (0 para não alocado): ");
            scanf("%d", &v->codigoPiloto);
            if (v->codigoPiloto != 0 && !verificarCodigoTripulanteExistente(v->codigoPiloto)) {
                printf("Erro: Código do piloto inválido! Tente novamente.\n");
            }
        } while (v->codigoPiloto != 0 && !verificarCodigoTripulanteExistente(v->codigoPiloto));

        do {
            printf("Código do copiloto (0 para não alocado): ");
            scanf("%d", &v->codigoCopiloto);
            if (v->codigoCopiloto != 0 && !verificarCodigoTripulanteExistente(v->codigoCopiloto)) {
                printf("Erro: Código do copiloto inválido! Tente novamente.\n");
            }
        } while (v->codigoCopiloto != 0 && !verificarCodigoTripulanteExistente(v->codigoCopiloto));

        do {
            printf("Código do comissário (0 para não alocado): ");
            scanf("%d", &v->codigoComissario);
            if (v->codigoComissario != 0 && !verificarCodigoTripulanteExistente(v->codigoComissario)) {
                printf("Erro: Código do comissário inválido! Tente novamente.\n");
            }
        } while (v->codigoComissario != 0 && !verificarCodigoTripulanteExistente(v->codigoComissario));
    }

    printf("Tarifa: ");
    scanf("%f", &v->tarifa);

    salvarNoArquivoVoo(v);
    return v;
}

void salvarNoArquivoVoo(voo *v) {
    FILE *arquivo = fopen("voos.dat", "ab+");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de voos");
        return;
    }

    fwrite(v, sizeof(voo), 1, arquivo);
    fclose(arquivo);
}

void exibirVoo(const voo *v) {
    if (v) {
        printf("\n--- Informações do Voo ---\n");
        printf("Código: %d\n", v->codigo);
        printf("Data: %s\n", v->data);
        printf("Hora: %s\n", v->hora);
        printf("Origem: %s\n", v->origem);
        printf("Destino: %s\n", v->destino);
        printf("Código do avião: %d\n", v->codigoAviao);
        printf("Código do piloto: %d\n", v->codigoPiloto);
        printf("Código do copiloto: %d\n", v->codigoCopiloto);
        printf("Código do comissário: %d\n", v->codigoComissario);
        printf("Status: %s\n", v->status == 1 ? "Ativo" : "Inativo");
        printf("Tarifa: %.2f\n", v->tarifa);
    }
}
