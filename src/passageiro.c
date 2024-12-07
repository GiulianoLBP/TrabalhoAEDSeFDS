#include "passageiro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Para validacao de caracteres

#define TAM_BUFFER 256  // Buffer temporario para entrada de strings
// Função para verificar se o código já existe no arquivo
int verificarCodigoExistente(int codigo) {
    int quantidade;
    passageiro **passageiros = carregarPassageiros(&quantidade);  // Carrega os passageiros do arquivo
    if (passageiros == NULL) {
        return 0;  // Nenhum passageiro registrado, o código é válido
    }

    // Verifica se o código já existe
    for (int i = 0; i < quantidade; i++) {
        if (passageiros[i]->codigo == codigo) {
            // Libera a memória alocada para os passageiros
            for (int j = 0; j < quantidade; j++) {
                free(passageiros[j]);
            }
            free(passageiros);
            return 1;  // Código duplicado
        }
    }

    // Libera a memória alocada para os passageiros
    for (int i = 0; i < quantidade; i++) {
        free(passageiros[i]);
    }
    free(passageiros);

    return 0;  // Código não duplicado
}
// Funcao para verificar se uma string e um numero inteiro positivo
int ehNumeroPositivo(const char *str) {
    // Percorre cada caractere da string
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0; // Retorna 0 se encontrar algo que não seja dígito
        }
    }
    return 1; // Retorna 1 se todos os caracteres forem dígitos
}

// Funcao para criar um passageiro
passageiro* criarPassageiro(int codigo, const char *nome, const char *endereco, const char *telefone, int fidelidade, int pontosFidelidade) {
    passageiro *p = (passageiro*)malloc(sizeof(passageiro));  // Aloca a memoria para o struct passageiro
    if (!p) {
        perror("Erro ao alocar memoria para passageiro");
        exit(EXIT_FAILURE);  // Caso a alocacao falhe, sai do programa
    }

    p->codigo = codigo;
    
    // Usa strncpy para copiar as strings, garantindo que o buffer nao seja ultrapassado
    strncpy(p->nome, nome, sizeof(p->nome) - 1);
    p->nome[sizeof(p->nome) - 1] = '\0';  // Garante a terminacao da string

    strncpy(p->endereco, endereco, sizeof(p->endereco) - 1);
    p->endereco[sizeof(p->endereco) - 1] = '\0';  // Garante a terminacao da string

    strncpy(p->telefone, telefone, sizeof(p->telefone) - 1);
    p->telefone[sizeof(p->telefone) - 1] = '\0';  // Garante a terminacao da string

    p->fidelidade = fidelidade;
    p->pontosFidelidade = pontosFidelidade;

    return p;  // Retorna o ponteiro para o passageiro criado
}

void listarPassageiros(FILE *arquivo) {
    passageiro p;
    rewind(arquivo);
    printf("\n--- Lista de Passageiros ---\n");
    while (fread(&p, sizeof(passageiro), 1, arquivo)) {
        printf("Codigo: %d\n", p.codigo);
        printf("Nome: %s\n", p.nome);
        printf("Endereco: %s\n", p.endereco);
        printf("Telefone: %s\n", p.telefone);
        printf("Fidelidade: %s\n", p.fidelidade ? "Sim" : "Nao");
        printf("Pontos de Fidelidade: %d\n", p.pontosFidelidade);
        printf("----------------------------\n");
    }
}

// Funcao para carregar passageiros do arquivo
passageiro** carregarPassageiros(int *quantidade) {
    FILE *arquivo = fopen("passageiro.dat", "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo carregarPassageiros em passageiros");
        *quantidade = 0;
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    *quantidade = tamanhoArquivo / sizeof(passageiro);
    if (*quantidade == 0) {
        fclose(arquivo);
        return NULL;
    }

    passageiro **passageiros = malloc(*quantidade * sizeof(passageiro*));
    if (!passageiros) {
        perror("Erro ao alocar memoria para passageiros");
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < *quantidade; i++) {
        passageiros[i] = malloc(sizeof(passageiro));
        if (!passageiros[i]) {
            perror("Erro ao alocar memoria para passageiro");
            fclose(arquivo);
            return NULL;
        }
        size_t bytesLidos = fread(passageiros[i], sizeof(passageiro), 1, arquivo);
        if (bytesLidos != 1) {
            printf("Erro ao ler passageiro %d do arquivo\n", i + 1);
            free(passageiros[i]);
            passageiros[i] = NULL;
        }
    }

    fclose(arquivo);
    return passageiros;
}

void salvarNoArquivoPassageiro(passageiro *p){
    FILE *arquivo = fopen("passageiro.dat", "ab+");  // Abre o arquivo para leitura/escrita, cria se nao existir
    if (!arquivo) {
        perror("Erro ao abrir o arquivo em salvarNoArquivoPassageiro em passageiros");
    }
    fwrite(p, sizeof(passageiro), 1, arquivo);
    printf("\nPESSOA SALVA NO ARQUIVO\n");

    fclose(arquivo);
}

// Funcao para cadastrar um passageiro
passageiro* cadastrarPassageiro() {
    int codigo, fidelidade, pontosFidelidade;
    char buffer[TAM_BUFFER]; // Buffer temporário para leitura das strings

    // Captura os dados do usuário
    printf("Codigo do passageiro: ");
    while (1) {
        fgets(buffer, TAM_BUFFER, stdin);
        
        // Remover a quebra de linha no final da string
        buffer[strcspn(buffer, "\n")] = '\0';

        // Verifica se a entrada é um número positivo
        if (ehNumeroPositivo(buffer)) {
            codigo = atoi(buffer);
            
            // Verifica se o código é positivo
            if (codigo <= 0) {
                printf("Codigo invalido. Deve ser um numero positivo. Retornando ao menu inicial...\n");
                return NULL;
            }

            // Verifica se o código já existe
            if (verificarCodigoExistente(codigo)) {
                printf("Codigo ja existente. Retornando ao menu inicial...\n");
                return NULL;
            } else {
                break; // Encerra o loop caso o código seja válido
            }
        } else {
            printf("Codigo invalido. Deve ser um numero positivo e unico. Retornando ao menu inicial...\n");
            return NULL;
        }
    }

    printf("Nome do passageiro: ");
    fgets(buffer, TAM_BUFFER, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove o caractere de nova linha
    if (strlen(buffer) < 1 || strlen(buffer) > 40) {
        printf("Nome invalido. Deve ter entre 1 e 40 caracteres. Retornando ao menu inicial...\n");
        return NULL;
    }
    char nome[40]; // Array fixo de tamanho 40
    strncpy(nome, buffer, sizeof(nome) - 1);
    nome[sizeof(nome) - 1] = '\0'; // Garante que a string seja terminada

    printf("Endereco do passageiro: ");
    fgets(buffer, TAM_BUFFER, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) < 1 || strlen(buffer) > 40) {
        printf("Endereco invalido. Deve ter entre 1 e 40 caracteres. Retornando ao menu inicial...\n");
        return NULL;
    }
    char endereco[40]; // Array fixo de tamanho 40
    strncpy(endereco, buffer, sizeof(endereco) - 1);
    endereco[sizeof(endereco) - 1] = '\0'; // Garante que a string seja terminada

    printf("Telefone do passageiro: ");
    fgets(buffer, TAM_BUFFER, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) < 1 || strlen(buffer) > 40) {
        printf("Telefone invalido. Deve ter entre 1 e 40 caracteres. Retornando ao menu inicial...\n");
        return NULL;
    }
    char telefone[40]; // Array fixo de tamanho 40
    strncpy(telefone, buffer, sizeof(telefone) - 1);
    telefone[sizeof(telefone) - 1] = '\0'; // Garante que a string seja terminada

    printf("Fidelidade (1 para Sim, 0 para Nao): ");
    while (1) {
        if (scanf("%d", &fidelidade) != 1 || (fidelidade != 0 && fidelidade != 1)) {
            printf("Entrada invalida. Digite 1 para Sim ou 0 para Nao. Retornando ao menu inicial...\n");
            return NULL;
        }
        break;
    }

    if (fidelidade == 0) {
        pontosFidelidade = 0;
    } else {
        printf("Pontos de fidelidade: ");
        while (1) {
            if (scanf("%d", &pontosFidelidade) != 1 || pontosFidelidade < 0) {
                printf("Entrada invalida. Digite um numero de pontos de fidelidade valido. Retornando ao menu inicial...\n");
                return NULL;
            }
            break;
        }
    }

    // Cria um novo passageiro usando as strings alocadas dinamicamente
    passageiro *novoPassageiro = criarPassageiro(codigo, nome, endereco, telefone, fidelidade, pontosFidelidade);
    salvarNoArquivoPassageiro(novoPassageiro);

    return novoPassageiro;
}


// Funcao para exibir informacoes do passageiro
void exibirPassageiro(const passageiro *p) {
    printf("\n--- Lista de Passageiros ---\n");
    if (p) {
        printf("Codigo: %d\n", p->codigo);
        printf("Nome: %s\n", p->nome);
        printf("Endereco: %s\n", p->endereco);
        printf("Telefone: %s\n", p->telefone);
        printf("Fidelidade: %s\n", p->fidelidade ? "Sim" : "Nao");
        printf("Pontos de Fidelidade: %d\n", p->pontosFidelidade);
    }
    printf("----------------------------\n");
}

void pesquisarPassageiro(int quantidadePassageiros, passageiro **passageiros) {
    char entrada[50];
    printf("Escreva o codigo ou o nome do passageiro: ");
    scanf("%s", entrada);

    int encontrado = 0;
    for (int i = 0; i < quantidadePassageiros; i++) {
        // Verifica se o código (como número) ou o nome (como string) corresponde
        if (atoi(entrada) == passageiros[i]->codigo || strcmp(entrada, passageiros[i]->nome) == 0) {
            exibirPassageiro(passageiros[i]); // Exibe os detalhes do passageiro
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Passageiro não encontrado.\n");
    }
}

void passageiroFidelidade(int codigo,passageiro ***passageiros,int quantidadePassageiros,int fidelidade){
    for (int i = 0; i < quantidadePassageiros; i++) {
        if (codigo == (*passageiros)[i]->codigo) {
            if(fidelidade>0){

            (*passageiros)[i]->fidelidade = 1;
            (*passageiros)[i]->pontosFidelidade +=10; 
            break;
            }
            else{
            (*passageiros)[i]->pontosFidelidade -=10;
            if((*passageiros)[i]->pontosFidelidade == 0){
                (*passageiros)[i]->fidelidade = 0;
            } 
            }
        }
    }
}

void exibirFidelidade(int quantidadePassageiros, passageiro **passageiros) {
    char entrada[50];
    printf("Escreva o codigo ou o nome do passageiro: \n");
    scanf("%s", entrada);

    int encontrado = 0;
    for (int i = 0; i < quantidadePassageiros; i++) {
        // Verifica se o código (como número) ou o nome (como string) corresponde
        if (atoi(entrada) == passageiros[i]->codigo || strcmp(entrada, passageiros[i]->nome) == 0) {
            printf("O passageiro %s tem fidelidade: %d\n",passageiros[i]->nome,passageiros[i]->pontosFidelidade);
            break;
        }
    }

    if (!encontrado) {
        printf("Passageiro não encontrado.\n");
    }
}