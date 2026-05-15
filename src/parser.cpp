#include "parser.hpp"
#include <iostream>

bool validarEntrada(const std::string& entrada, int base) {
    if (entrada.empty()) {
        std::cout << "Erro: A entrada nao pode estar vazia.\n";
        return false;
    }

    size_t inicio = 0;
    // Pula caractere de sinal se houver
    if (entrada[0] == '-' || entrada[0] == '+') {
        inicio = 1;
    }

    // Se houver apenas o caractere de sinal, é inválido
    if (inicio == entrada.length()) {
        std::cout << "Erro: A entrada nao pode conter apenas o caractere de sinal ('" << entrada[0] << "').\n";
        return false;
    }

    int separadores = 0;
    size_t posSeparador = 0;

    for (size_t i = inicio; i < entrada.length(); i++) {
        char c = entrada[i];

        // Verificar separador decimal
        if (c == '.' || c == ',') {
            separadores++;
            posSeparador = i;
            if (separadores > 1) {
                std::cout << "Erro: A entrada contem mais de um separador decimal (encontrado na posicao " << (i + 1) << ").\n";
                return false;
            }
            continue;
        }

        int valorDigito = -1;

        // Mapeamento ASCII de forma manual
        if (c >= '0' && c <= '9') {
            valorDigito = c - '0';
        } else if (c >= 'A' && c <= 'F') {
            valorDigito = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
            valorDigito = c - 'a' + 10;
        }

        // Se o caractere não for um dígito hexadecimal válido
        if (valorDigito < 0) {
            std::cout << "Erro: Caractere invalido '" << c << "' na posicao " << (i + 1) << ".\n";
            std::cout << "       Apenas digitos 0-9, letras A-F (ou a-f) e um unico separador ('.' ou ',') sao permitidos.\n";
            return false;
        }

        // Se o caractere for maior ou igual à base especificada
        if (valorDigito >= base) {
            std::cout << "Erro: Caractere '" << c << "' na posicao " << (i + 1) << " e invalido para a base " << base << ".\n";
            std::cout << "       Dica: Na base " << base << ", os digitos permitidos sao de 0 ate " << (base - 1) << ".\n";
            return false;
        }
    }

    // Se houver um separador, validar que ele não está no início nem no fim do número
    if (separadores == 1) {
        if (posSeparador == inicio) {
            std::cout << "Erro: O separador decimal nao pode estar no inicio do numero.\n";
            return false;
        }
        if (posSeparador == entrada.length() - 1) {
            std::cout << "Erro: O separador decimal nao pode estar no final do numero.\n";
            return false;
        }
    }

    return true;
}
