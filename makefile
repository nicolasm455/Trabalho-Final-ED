# Variáveis
CC = gcc
CFLAGS = -Wall -g
TARGET = main

# Lista de arquivos fonte
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar os arquivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados
clean:
	rm -f $(OBJS) $(TARGET)

# Regra para executar o programa
run: $(TARGET)
	./$(TARGET)