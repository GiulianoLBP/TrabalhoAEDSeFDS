
# Estrutura do Projeto

Este é o projeto de exemplo para gerenciar tripulantes e aeronaves. A estrutura do projeto é organizada da seguinte maneira:

projeto/ ├── include/ # Diretório contendo arquivos de cabeçalho (.h) │ ├── tripulacao.h # Declaração da struct Tripulacao e suas funções │ └── aeronave.h # Declaração da struct Aeronave e suas funções ├── src/ # Diretório contendo arquivos de implementação (.c) │ ├── tripulacao.c # Implementação das funções da struct Tripulacao │ ├── aeronave.c # Implementação das funções da struct Aeronave │ └── main.c # Função principal (main) ├── Makefile # Arquivo Makefile para facilitar a compilação └── README.md # Este arquivo (instruções sobre o projeto)


### Descrição dos Diretórios e Arquivos

- **`include/`**:
  - Contém os arquivos de cabeçalho `.h` que fazem a declaração das structs e as prototipações das funções.
  - **`tripulacao.h`**: Declara a struct `Tripulacao` e os protótipos das funções que manipulam os dados de um tripulante.
  - **`aeronave.h`**: Declara a struct `Aeronave` e os protótipos das funções que manipulam os dados da aeronave e seus tripulantes.

- **`src/`**:
  - Contém os arquivos `.c` com a implementação das funções associadas às structs.
  - **`tripulacao.c`**: Implementa as funções que manipulam a struct `Tripulacao`, como inicializar, exibir e atualizar informações do tripulante.
  - **`aeronave.c`**: Implementa as funções que manipulam a struct `Aeronave`, como inicializar, exibir e adicionar tripulantes.
  - **`main.c`**: Contém a função `main()`, onde o código principal é executado. Aqui são feitas as chamadas às funções definidas nas outras partes do projeto.

- **`Makefile`**:
  - Um arquivo de automação de build que facilita o processo de compilação. Com o comando `make`, ele compila o código automaticamente.

- **`README.md`**:
  - Este arquivo, que contém informações sobre como compilar, executar e usar o projeto.
