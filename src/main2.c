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
    printf("11. Cancelar Reserva\n");
    printf("0. Sair\n");
}

int main() {
    passageiro **passageiros = NULL; // Array dinâmico para passageiros
    int quantidadePassageiros = 0; // Quantidade de passageiros carregados
    tripulacao **tripulantes = NULL; // Array dinâmico para tripulantes
    int quantidadeTripulacao = 0; // Quantidade de tripulantes carregados
    voo **voos = NULL; // Array dinâmico para voos
    int quantidadeVoos = 0; // Quantidade de voos carregados
    assento **assentos = NULL; // Array dinâmico para assentos
    int quantidadeAssentos = 0; // Quantidade de assentos carregados
    reserva **reservas = NULL; // Array dinâmico para reservas
    int quantidadeReservas = 0; // Quantidade de reservas carregadas

    // Carregar dados a partir dos arquivos
    passageiros = carregarPassageiros(&quantidadePassageiros);
    tripulantes = carregarTripulacao(&quantidadeTripulacao);
    voos = carregarVoos(&quantidadeVoos);
    assentos = carregarAssentos(&quantidadeAssentos);
    reservas = carregarReservas(&quantidadeReservas);

    int opcao;

    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer de entrada

        switch (opcao) {
            case 1: {
                // Cadastrar Passageiro
                passageiro *novoPassageiro = cadastrarPassageiro();

                // Redimensiona o array de passageiros e adiciona o novo passageiro
                passageiros = realloc(passageiros, (quantidadePassageiros + 1) * sizeof(passageiro *));
                if (!passageiros) {
                    perror("Erro ao alocar memória para passageiros");
                    exit(EXIT_FAILURE);
                }
                passageiros[quantidadePassageiros] = novoPassageiro;
                quantidadePassageiros++;

                printf("Passageiro cadastrado com sucesso!\n");
                break;
            }
            case 2: {
                // Cadastrar Tripulante
                tripulacao *novoTripulante = cadastrarTripulacao();

                // Redimensiona o array de tripulantes e adiciona o novo tripulante
                tripulantes = realloc(tripulantes, (quantidadeTripulacao + 1) * sizeof(tripulacao *));
                if (!tripulantes) {
                    perror("Erro ao alocar memória para tripulantes");
                    exit(EXIT_FAILURE);
                }
                tripulantes[quantidadeTripulacao] = novoTripulante;
                quantidadeTripulacao++;

                printf("Tripulante cadastrado com sucesso!\n");
                break;
            }
            case 3: {
                // Cadastrar Voo
                voo *novoVoo = cadastrarVoo();

                // Redimensiona o array de voos e adiciona o novo voo
                voos = realloc(voos, (quantidadeVoos + 1) * sizeof(voo *));
                if (!voos) {
                    perror("Erro ao alocar memória para voos");
                    exit(EXIT_FAILURE);
                }
                voos[quantidadeVoos] = novoVoo;
                quantidadeVoos++;

                printf("Voo cadastrado com sucesso!\n");
                break;
            }
            case 4: {
                // Cadastrar Assento
                assento *novoAssento = cadastrarAssento();

                // Redimensiona o array de assentos e adiciona o novo assento
                assentos = realloc(assentos, (quantidadeAssentos + 1) * sizeof(assento *));
                if (!assentos) {
                    perror("Erro ao alocar memória para assentos");
                    exit(EXIT_FAILURE);
                }
                assentos[quantidadeAssentos] = novoAssento;
                quantidadeAssentos++;

                printf("Assento cadastrado com sucesso!\n");
                break;
            }
            case 5: {
                // Cadastrar Reserva
                reserva *novaReserva = cadastrarReserva();

                // Redimensiona o array de reservas e adiciona a nova reserva
                reservas = realloc(reservas, (quantidadeReservas + 1) * sizeof(reserva *));
                if (!reservas) {
                    perror("Erro ao alocar memória para reservas");
                    exit(EXIT_FAILURE);
                }
                reservas[quantidadeReservas] = novaReserva;
                quantidadeReservas++;

                printf("Reserva realizada com sucesso!\n");
                break;
            }
            case 6: {
                // Exibir Passageiros
                printf("\nLista de Passageiros:\n");
                for (int i = 0; i < quantidadePassageiros; i++) {
                    exibirPassageiro(passageiros[i]);
                }
                break;
            }
            case 7: {
                // Exibir Tripulantes
                printf("\nLista de Tripulantes:\n");
                for (int i = 0; i < quantidadeTripulacao; i++) {
                    exibirTripulacao(tripulantes[i]);
                }
                break;
            }
            case 8: {
                // Exibir Voos
                printf("\nLista de Voos:\n");
                for (int i = 0; i < quantidadeVoos; i++) {
                    exibirVoo(voos[i]);
                }
                break;
            }
            case 9: {
                // Exibir Assentos
                printf("\nLista de Assentos:\n");
                for (int i = 0; i < quantidadeAssentos; i++) {
                    exibirAssento(assentos[i]);
                }
                break;
            }
            case 10: {
                // Exibir Reservas
                printf("\nLista de Reservas:\n");
                for (int i = 0; i < quantidadeReservas; i++) {
                    exibirReserva(reservas[i]);
                }
                break;
            }
            case 11: {
                // Cancelar Reserva
                int codigoVoo,numeroAssento,codigoPassageiro;
                printf("Informe o código da reserva a ser cancelada: ");
                scanf("%d %d %d", &codigoVoo,&numeroAssento,&codigoPassageiro);
                cancelarReserva(codigoVoo, numeroAssento, codigoPassageiro, &reservas, &quantidadeReservas, assentos, quantidadeAssentos);
                assentos = carregarAssentos(&quantidadeAssentos);
                reservas = carregarReservas(&quantidadeReservas);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

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
