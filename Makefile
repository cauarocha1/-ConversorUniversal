CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
INCLUDES = -I./include

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
BUILD_DIR = build

# Target principal
TARGET = conversor_bases
TEST_TARGET = testes

# Fontes e objetos
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/conversor.cpp $(SRC_DIR)/parser.cpp $(SRC_DIR)/formatador.cpp $(SRC_DIR)/utilitarios.cpp
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Fontes e objetos dos testes (tudo exceto main.cpp)
TEST_SRCS = $(SRC_DIR)/conversor.cpp $(SRC_DIR)/parser.cpp $(SRC_DIR)/formatador.cpp $(SRC_DIR)/utilitarios.cpp $(TEST_DIR)/testes.cpp
TEST_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(filter $(SRC_DIR)/%.cpp,$(TEST_SRCS))) $(BUILD_DIR)/testes.o

# Targets principais
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS)
	@echo "✓ Compilação concluída: ./$(TARGET)"

tests: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TEST_TARGET) $(TEST_OBJS)
	@echo "✓ Compilação de testes concluída: ./$(TEST_TARGET)"

# Regra geral para compilação de objetos
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/testes.o: $(TEST_DIR)/testes.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Limpar artefatos de build
clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET)
	@echo "✓ Limpeza concluída"

# Compilar tudo (programa + testes)
build-all: clean all tests
	@echo "✓ Build completo: $(TARGET) e $(TEST_TARGET)"

# Executar testes
run-tests: tests
	./$(TEST_TARGET)

# Executar programa principal
run: all
	./$(TARGET)

# Ajuda
help:
	@echo "Targets disponíveis:"
	@echo "  make              - Compila o programa principal"
	@echo "  make tests        - Compila a suíte de testes"
	@echo "  make build-all    - Compila programa + testes"
	@echo "  make clean        - Remove arquivos compilados"
	@echo "  make run          - Compila e executa o programa"
	@echo "  make run-tests    - Compila e executa os testes"
	@echo "  make help         - Exibe esta mensagem"

.PHONY: all clean build-all run tests run-tests help
