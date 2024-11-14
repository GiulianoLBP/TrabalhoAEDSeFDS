# Variáveis de compilação
CC = gcc
CFLAGS = -Iinclude -Wall -g
OBJ = src/main.o src/passageiro.o
TARGET = programa.exe  # Certifique-se de que o nome do executável é 'programa.exe'

# Regra padrão
all: $(TARGET)

# Compila o executável
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compila main.c
src/main.o: src/main.c include/passageiro.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

# Compila passageiro.c
src/passageiro.o: src/passageiro.c include/passageiro.h
	$(CC) $(CFLAGS) -c src/passageiro.c -o src/passageiro.o

# Limpa arquivos objeto e o executável
clean:
	del /f src\*.o $(TARGET)  # Alteração para garantir que o caminho esteja correto

# Rodar o programa
run: all
	./$(TARGET)
