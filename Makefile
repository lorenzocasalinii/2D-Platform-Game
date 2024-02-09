# Compilatore e flags del compilatore
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iheaders
# Librerie da collegare
LIBS = -lncurses

# Cartella che contiene i file sorgente
SRC_DIR = src
# Cartella che contiene i file oggetto
BUILD_DIR = build
# Cartella che contiene il file eseguibile
BIN_DIR = bin

# Creazione di cartelle build e bin
$(shell mkdir -p $(BUILD_DIR))
$(shell mkdir -p $(BIN_DIR))

# File sorgente
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# File oggetto
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
# File eseguibile
TARGET = $(BIN_DIR)/run
# File di testo per salvataggio
TXT = savefile.txt

# Target predefinito
all: $(TARGET)

# Compilazione file sorgente in file oggetto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Collegamento file oggetto nell'eseguibile
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

# Comando per rimuovere le cartelle build, bin e il file di salvataggio
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(TXT)

# Comando per compilare e lanciare l'eseguibile in una sola istruzione
run: $(TARGET)
	./$(TARGET)