#include "formatador.hpp"
#include <iostream>

void exibirCabecalho() {
    std::cout << "====================================================\n";
    std::cout << "       CONVERSOR UNIVERSAL DE BASES NUMERICAS       \n";
    std::cout << "====================================================\n";
}

void exibirMenu(bool traceAtivo) {
    std::cout << "\nSelecione uma opcao:\n";
    std::cout << "1  - Converter Decimal para Base (2, 8 ou 16)\n";
    std::cout << "2  - Converter de Base (2, 8 ou 16) para Decimal\n";
    std::cout << "3  - Converter Binario para Octal ou Hexadecimal (Agrupamento Direto)\n";
    std::cout << "4  - Converter entre Octal e Hexadecimal (Binario como Ponte)\n";
    std::cout << "5  - Executar Auto-testes Integrados\n";
    std::cout << "6  - Alternar Modo Trace [Status: " << (traceAtivo ? "ATIVO" : "INATIVO") << "]\n";
    std::cout << "7  - Conversao Universal (qualquer base -> qualquer base)\n";
    std::cout << "8  - Modo Batch (Processar arquivo CSV)\n";
    std::cout << "9  - Modo Quiz (Jogo interativo)\n";
    std::cout << "10 - Calculadora de Valores Maximos (2^k - 1)\n";
    std::cout << "0  - Sair\n";
    std::cout << "Escolha: ";
}

void exibirResultado(const std::string& titulo, const std::string& resultado) {
    std::cout << "\n>>> " << titulo << ": " << resultado << "\n";
}

void exibirResultado(const std::string& titulo, long long resultado) {
    std::cout << "\n>>> " << titulo << ": " << resultado << "\n";
}

void exibirResultado(const std::string& titulo, double resultado) {
    // Configura a precisão para exibir o double de forma limpa
    std::cout << "\n>>> " << titulo << ": " << resultado << "\n";
}
