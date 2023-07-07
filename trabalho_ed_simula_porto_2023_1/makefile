# Nome do arquivo executável
TARGET = simulador_de_porto_vitor_rodrigues

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -g

# Arquivos de origem
SOURCES = fila_navios.c funcoes_utilitarias.c pilha_containers.c travessas.c main.c

# Objetos gerados a partir dos arquivos de origem
OBJECTS = $(SOURCES:.c=.o)

# Regra de compilação
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

# Regra para cada arquivo objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra padrão
all: $(TARGET)

# Regra para limpar os arquivos objeto e executável
clean:
	rm -f $(OBJECTS) $(TARGET)

