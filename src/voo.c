#include "voo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verificarCodigoVooExistente(int codigo) {
    FILE *arquivo = fopen("voos.dat", "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de voos em verificarCodigoVooExistente");
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
        perror("Erro ao abrir o arquivo de tripulação em verificarCodigoTripulanteExistente(voos)");
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
            printf("Código do piloto: sex");
            scanf("%d", &v->codigoPiloto);
            if (!verificarCodigoTripulanteExistente(v->codigoPiloto)) {
                printf("Erro: Código do piloto inválido! Tente novamente.\n");
            }
        } while (!verificarCodigoTripulanteExistente(v->codigoPiloto));

        do {
            printf("Código do copiloto: sex");
            scanf("%d", &v->codigoCopiloto);
            if (!(v->codigoCopiloto)) {
                printf("Erro: Código do copiloto inválido! Tente novamente.\n");
            }
        } while (!verificarCodigoTripulanteExistente(v->codigoCopiloto));

        do {
            printf("Código do comissário: sex");
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
        perror("Erro ao abrir o arquivo de voos em salvarNoArquivoVoo");
        return;
    }

    fwrite(v, sizeof(voo), 1, arquivo);
    fclose(arquivo);
    printf("salvo no arquvio de voos xD");
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

// Funcao para carregar passageiros do arquivo
voo** carregarVoos(int *quantidade) {
    FILE *arquivo = fopen("voos.dat", "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de voos em carregarVoos");
        *quantidade = 0;
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    *quantidade = tamanhoArquivo / sizeof(voo);
    if (*quantidade == 0) {
        fclose(arquivo);
        return NULL;
    }

    voo **voos = malloc(*quantidade * sizeof(voo*));
    if (!voos) {
        perror("Erro ao alocar memoria para voos");
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < *quantidade; i++) {
        voos[i] = malloc(sizeof(voo));
        if (!voos[i]) {
            perror("Erro ao alocar memoria para voo");
            fclose(arquivo);
            return NULL;
        }
        size_t bytesLidos = fread(voos[i], sizeof(voo), 1, arquivo);
        if (bytesLidos != 1) {
            printf("Erro ao ler voo %d do arquivo\n", i + 1);
            free(voos[i]);
            voos[i] = NULL;
        }
    }

    fclose(arquivo);
    return voos;
}
//OI BEATRIX, basicamente fiz umas condiçoes para se o voo tiver status ativo ele TEM QUE TER 
//piloto e copiloto, a outra parte da condiçao e basicamente verificar se esse piloto e copiloto existe
//alem disso se o status for inativo ou ela cadastra como 0 vulgo nao tem copiloto e piloto
// ou ela cadastra um valido para nao dar problemas futuros
//com relaçao a horario nao coloquei nenhuma restriçao porque ia ficar grande
//e a outra parte

// descobri um bug que nao sei porque ta rolando mas to conseguindo cadastrar voo com um codigo = 2 pro piloto
// no tengo a menor ideia do porque