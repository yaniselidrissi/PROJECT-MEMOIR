# === Paramètres de compilation ===
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# === Répertoire de sortie ===
BIN_DIR = bin
EXEC = $(BIN_DIR)/mpm.exe

# === Fichiers sources ===
SRCS = main.c canevas/job.c canevas/io.c canevas/rank.c canevas/list.c

# === Fichier d'entrée par défaut ===
DATA = data/graph.dta

# === Cible par défaut ===
all: $(EXEC)

# === Compilation de l'exécutable ===
$(EXEC): $(SRCS)
	if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CC) $(CFLAGS) -Iinclude -o $(EXEC) $(SRCS)

# === Nettoyage
clean:
	@rmdir /S /Q $(BIN_DIR) 2>nul || exit 0
	@del /Q *.o 2>nul || exit 0

# === Exécution du programme (avec fichier en argument)
run: all
	$(EXEC) $(DATA)
