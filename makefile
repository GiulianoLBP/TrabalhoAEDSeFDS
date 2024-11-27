# Variáveis de compilação
CC = gcc
CFLAGS = -Iinclude -Wall -g
OBJ = src/main.o src/passageiro.o src/tripulacao.o src/assento.o src/reserva.o src/voo.o  # Adiciona os novos arquivos assento.o e reserva.o
TARGET = programa.exe  # Nome do executável principal

# Nome do executável para os testes
TEST_OBJ = src/main2.o src/passageiro.o src/tripulacao.o src/assento.o src/reserva.o src/voo.o  # Inclui os novos arquivos para testes
TEST_TARGET = test_programa.exe

OS := $(shell uname -s)
ifeq ($(OS), Linux)
    RM = rm -f
    OBJ_PATH = src/*.o
else
    RM = del /f
    OBJ_PATH = src\*.o
endif

# Regra padrão
all: $(TARGET)

# Compila o executável principal
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compila main.c
src/main.o: src/main.c include/passageiro.h include/tripulacao.h include/assento.h include/reserva.h include/voo.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

# Compila passageiro.c
src/passageiro.o: src/passageiro.c include/passageiro.h
	$(CC) $(CFLAGS) -c src/passageiro.c -o src/passageiro.o

# Compila tripulacao.c
src/tripulacao.o: src/tripulacao.c include/tripulacao.h
	$(CC) $(CFLAGS) -c src/tripulacao.c -o src/tripulacao.o

# Compila assento.c
src/assento.o: src/assento.c include/assento.h
	$(CC) $(CFLAGS) -c src/assento.c -o src/assento.o

# Compila reserva.c
src/reserva.o: src/reserva.c include/reserva.h
	$(CC) $(CFLAGS) -c src/reserva.c -o src/reserva.o

# Compila voo.c
src/voo.o: src/voo.c include/voo.h
	$(CC) $(CFLAGS) -c src/voo.c -o src/voo.o

# Limpa arquivos objeto e o executável
clean:
	$(RM) $(OBJ_PATH) $(TARGET) $(TEST_TARGET)

# Rodar o programa
run: all
	./$(TARGET)

# Compila main2.c para testes
src/main2.o: src/main2.c include/passageiro.h include/tripulacao.h include/assento.h include/reserva.h include/voo.h
	$(CC) $(CFLAGS) -c src/main2.c -o src/main2.o

# Regra para rodar os testes
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Compila o executável de teste
$(TEST_TARGET): $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJ)
