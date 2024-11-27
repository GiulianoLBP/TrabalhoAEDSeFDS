#include <stdio.h>
#include <stdlib.h>
#include "passageiro.h"
#include "tripulacao.h"
#include "voo.h"
#include "assento.h"
#include "reserva.h"

// Função que exibe o menu
void exibirMenu() {
    printf("\n===== Menu =====\n");
    printf("1. Cadastrar Passageiro\n");
    printf("2. Cadastrar Tripulante\n");
    printf("3. Cadastrar Voo\n");
    printf("4. Cadastrar Assento\n");
    printf("5. Cadastrar Reserva\n");
    printf("6. Exibir Passageiros\n");
    printf("7. Exibir Tripulantes\n");
    printf("8. Exibir Voos\n");
    printf("9. Exibir Assentos\n");
    printf("10. Exibir Reservas\n");
    printf("11.Cancelar Reservas\n");
    printf("0. Sair\n");
}

int main() {
    passageiro **passageiros = NULL; // Array dinâmico para passageiros
    int quantidadePassageiros = carregarPassageiros(&passageiros); // Carrega os passageiros

    tripulacao **tripulantes = NULL; // Array dinâmico para tripulantes
    int quantidadeTripulacao = carregarTripulacao(&tripulantes); // Carrega tripulantes

    voo **voos = NULL; // Array dinâmico para voos
    int quantidadeVoos = carregarVoos(&voos); // Carrega voos

    assento **assentos = NULL; // Array dinâmico para assentos
    int quantidadeAssentos = carregarAssentos(&assentos); // Carrega assentos

    reserva **reservas = NULL; // Array dinâmico para reservas
    int quantidadeReservas = carregarReservas(&reservas); // Carrega reservas

    int opcao;

    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        switch (opcao) {
            case 1: {
                passageiro *novoPassageiro = cadastrarPassageiro();
                passageiros = realloc(passageiros, (quantidadePassageiros + 1) * sizeof(passageiro *));
                if (!passageiros) {
                    perror("Erro ao alocar memória para passageiros");
                    exit(EXIT_FAILURE);
                }
                passageiros[quantidadePassageiros++] = novoPassageiro;
                printf("Passageiro cadastrado com sucesso!\n");
                break;
            }
            case 2: {
                tripulacao *novoTripulante = cadastrarTripulacao();
                tripulantes = realloc(tripulantes, (quantidadeTripulacao + 1) * sizeof(tripulacao *));
                if (!tripulantes) {
                    perror("Erro ao alocar memória para tripulantes");
                    exit(EXIT_FAILURE);
                }
                tripulantes[quantidadeTripulacao++] = novoTripulante;
                printf("Tripulante cadastrado com sucesso!\n");
                break;
            }
            case 3: {
                voo *novoVoo = cadastrarVoo();
                voos = realloc(voos, (quantidadeVoos + 1) * sizeof(voo *));
                if (!voos) {
                    perror("Erro ao alocar memória para voos");
                    exit(EXIT_FAILURE);
                }
                voos[quantidadeVoos++] = novoVoo;
                printf("Voo cadastrado com sucesso!\n");
                break;
            }
            case 5: {
                reserva *novaReserva = cadastrarReserva();
                reservas = realloc(reservas, (quantidadeReservas + 1) * sizeof(reserva *));
                if (!reservas) {
                    perror("Erro ao alocar memória para reservas");
                    exit(EXIT_FAILURE);
                }
                reservas[quantidadeReservas++] = novaReserva;
                printf("Reserva realizada com sucesso!\n");
                break;
            }
            case 11: {
                int codigoReserva;
                printf("Informe o código da reserva a ser cancelada: ");
                scanf("%d", &codigoReserva);
                cancelarReserva(reservas, &quantidadeReservas, codigoReserva);
                break;
            }
            // Exibição e outras opções continuam iguais
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    // // Salvar os dados no arquivo ao sair
    // salvarPassageirosNoArquivo(passageiros, quantidadePassageiros);
    // salvarTripulacaoNoArquivo(tripulantes, quantidadeTripulacao);
    // salvarVoosNoArquivo(voos, quantidadeVoos);
    // salvarAssentosNoArquivo(assentos, quantidadeAssentos);
    // salvarReservasNoArquivo(reservas, quantidadeReservas);

    // Liberação de memória
    for (int i = 0; i < quantidadePassageiros; i++) free(passageiros[i]);
    free(passageiros);
    for (int i = 0; i < quantidadeTripulacao; i++) free(tripulantes[i]);
    free(tripulantes);
    for (int i = 0; i < quantidadeVoos; i++) free(voos[i]);
    free(voos);
    for (int i = 0; i < quantidadeAssentos; i++) free(assentos[i]);
    free(assentos);
    for (int i = 0; i < quantidadeReservas; i++) free(reservas[i]);
    free(reservas);

    return 0;
}