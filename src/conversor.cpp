#include "conversor.hpp"
#include <iostream>
#include <cmath>

// Mapeamentos estáticos locais para expansão de dígitos em bits
static std::string digitoOctalParaBinario(char c) {
    switch (c) {
        case '0': return "000";
        case '1': return "001";
        case '2': return "010";
        case '3': return "011";
        case '4': return "100";
        case '5': return "101";
        case '6': return "110";
        case '7': return "111";
        default: return "";
    }
}

static std::string digitoHexParaBinario(char c) {
    switch (c) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': case 'a': return "1010";
        case 'B': case 'b': return "1011";
        case 'C': case 'c': return "1100";
        case 'D': case 'd': return "1101";
        case 'E': case 'e': return "1110";
        case 'F': case 'f': return "1111";
        default: return "";
    }
}

std::string f1_decimalParaBases(double decimal, int baseDestino, bool trace) {
    if (baseDestino != 2 && baseDestino != 8 && baseDestino != 10 && baseDestino != 16) {
        return "";
    }

    if (decimal == 0.0) {
        return "0";
    }

    bool ehNegativo = false;
    if (decimal < 0.0) {
        ehNegativo = true;
        decimal = -decimal;
    }

    // Separar parte inteira da fracionária
    long long parteInteira = (long long)decimal;
    double parteFracionaria = decimal - parteInteira;

    if (trace) {
        std::cout << "\n[Trace F1] Iniciando conversao de decimal " 
                  << (ehNegativo ? "-" : "") << (parteInteira + parteFracionaria) 
                  << " para base " << baseDestino << "\n";
    }

    // 1. Converter parte inteira (divisões sucessivas)
    std::string inteiroStr = "";
    if (parteInteira == 0) {
        inteiroStr = "0";
        if (trace) {
            std::cout << "  Parte inteira e 0. Resultado da parte inteira: \"0\"\n";
        }
    } else {
        long long valor = parteInteira;
        if (trace) {
            std::cout << "  --- PARTE INTEIRA (Divisoes Sucessivas por " << baseDestino << "): ---\n";
        }
        int passo = 1;
        while (valor > 0) {
            long long resto = valor % baseDestino;
            char digito;
            if (resto < 10) {
                digito = '0' + resto;
            } else {
                digito = 'A' + (resto - 10);
            }
            if (trace) {
                std::cout << "    Passo " << passo++ << ": " << valor << " / " << baseDestino 
                          << " = " << (valor / baseDestino) << ", resto " << resto << " ('" << digito << "')\n";
            }
            inteiroStr += digito;
            valor /= baseDestino;
        }

        // Inverter a string da parte inteira
        int n = inteiroStr.length();
        for (int i = 0; i < n / 2; i++) {
            char temp = inteiroStr[i];
            inteiroStr[i] = inteiroStr[n - 1 - i];
            inteiroStr[n - 1 - i] = temp;
        }

        if (trace) {
            std::cout << "  Resultado da parte inteira invertido: \"" << inteiroStr << "\"\n";
        }
    }

    // 2. Converter parte fracionária (multiplicações sucessivas)
    std::string fracStr = "";
    bool truncado = false;

    if (parteFracionaria > 1e-12) {
        if (trace) {
            std::cout << "  --- PARTE FRACIONARIA (Multiplicacoes Sucessivas por " << baseDestino << "): ---\n";
        }
        double valorFrac = parteFracionaria;
        int passo = 1;

        while (valorFrac > 1e-12 && fracStr.length() < 16) {
            double temp = valorFrac * baseDestino;
            int digitoInt = (int)temp;

            // Tratamento de imprecisões no ponto flutuante (ex: 0.99999999999 -> 1.0)
            if (temp - digitoInt > 0.999999999) {
                digitoInt++;
                valorFrac = 0.0;
            } else {
                valorFrac = temp - digitoInt;
            }

            char digito;
            if (digitoInt < 10) {
                digito = '0' + digitoInt;
            } else {
                digito = 'A' + (digitoInt - 10);
            }

            if (trace) {
                std::cout << "    Passo " << passo++ << ": " << (valorFrac + digitoInt) / baseDestino << " * " << baseDestino 
                          << " = " << temp << " -> digito '" << digito << "', resto decimal " << valorFrac << "\n";
            }

            fracStr += digito;
        }

        // Se ainda sobrou resto fracionário, indica truncamento
        if (valorFrac > 1e-12) {
            truncado = true;
            if (trace) {
                std::cout << "  Atingido limite de 16 casas decimais com resto restante " << valorFrac << ". Truncado!\n";
            }
        }
    }

    std::string resultado = inteiroStr;
    if (!fracStr.empty()) {
        resultado += "." + fracStr;
        if (truncado) {
            resultado += " ... (truncado)";
        }
    }

    if (ehNegativo && resultado != "0") {
        resultado = "-" + resultado;
    }

    if (trace) {
        std::cout << "  => Resultado final da conversao F1: " << resultado << "\n\n";
    }

    return resultado;
}

double f2_basesParaDecimal(const std::string& valor, int baseOrigem, bool trace) {
    if (baseOrigem != 2 && baseOrigem != 8 && baseOrigem != 10 && baseOrigem != 16) {
        return 0.0;
    }

    if (valor.empty()) {
        return 0.0;
    }

    bool ehNegativo = false;
    size_t inicio = 0;
    if (valor[0] == '-') {
        ehNegativo = true;
        inicio = 1;
    } else if (valor[0] == '+') {
        inicio = 1;
    }

    if (inicio == valor.length()) {
        return 0.0;
    }

    // Encontrar separador decimal
    size_t posSeparador = valor.find('.');
    if (posSeparador == std::string::npos) {
        posSeparador = valor.find(',');
    }

    std::string parteInteiraStr = "";
    std::string parteFracionariaStr = "";

    if (posSeparador == std::string::npos) {
        parteInteiraStr = valor.substr(inicio);
    } else {
        parteInteiraStr = valor.substr(inicio, posSeparador - inicio);
        parteFracionariaStr = valor.substr(posSeparador + 1);
    }

    if (trace) {
        std::cout << "\n[Trace F2] Iniciando conversao de base " << baseOrigem 
                  << " \"" << valor << "\" para decimal (Base 10):\n";
    }

    // 1. Somatório da Parte Inteira
    double somaInteira = 0.0;
    double potenciaInteira = 1.0;

    if (!parteInteiraStr.empty()) {
        if (trace) {
            std::cout << "  --- PARTE INTEIRA (Somatorio Posicional com expoentes positivos): ---\n";
        }
        for (int i = (int)parteInteiraStr.length() - 1; i >= 0; i--) {
            char c = parteInteiraStr[i];
            int valorDigito = -1;

            if (c >= '0' && c <= '9') {
                valorDigito = c - '0';
            } else if (c >= 'A' && c <= 'F') {
                valorDigito = c - 'A' + 10;
            } else if (c >= 'a' && c <= 'f') {
                valorDigito = c - 'a' + 10;
            }

            double termo = valorDigito * potenciaInteira;
            somaInteira += termo;

            if (trace) {
                std::cout << "    Dígito '" << c << "' na posicao " << (parteInteiraStr.length() - 1 - i) 
                          << " (peso " << baseOrigem << "^" << (parteInteiraStr.length() - 1 - i) << " = " << potenciaInteira 
                          << "): " << valorDigito << " * " << potenciaInteira << " = " << termo << "\n";
            }

            potenciaInteira *= baseOrigem;
        }
    }

    // 2. Somatório da Parte Fracionária (expoentes negativos)
    double somaFracionaria = 0.0;
    double potenciaFracionaria = 1.0 / baseOrigem;

    if (!parteFracionariaStr.empty()) {
        if (trace) {
            std::cout << "  --- PARTE FRACIONARIA (Somatorio Posicional com expoentes negativos): ---\n";
        }
        for (size_t i = 0; i < parteFracionariaStr.length(); i++) {
            char c = parteFracionariaStr[i];
            int valorDigito = -1;

            if (c >= '0' && c <= '9') {
                valorDigito = c - '0';
            } else if (c >= 'A' && c <= 'F') {
                valorDigito = c - 'A' + 10;
            } else if (c >= 'a' && c <= 'f') {
                valorDigito = c - 'a' + 10;
            }

            double termo = valorDigito * potenciaFracionaria;
            somaFracionaria += termo;

            if (trace) {
                std::cout << "    Dígito '" << c << "' na posicao -" << (i + 1) 
                          << " (peso " << baseOrigem << "^-" << (i + 1) << " = " << potenciaFracionaria 
                          << "): " << valorDigito << " * " << potenciaFracionaria << " = " << termo << "\n";
            }

            potenciaFracionaria /= baseOrigem;
        }
    }

    double resultado = somaInteira + somaFracionaria;
    if (ehNegativo) {
        resultado = -resultado;
    }

    if (trace) {
        std::cout << "  => Soma inteira: " << somaInteira << ", Soma fracionaria: " << somaFracionaria << "\n";
        std::cout << "  => Resultado final decimal F2: " << (ehNegativo ? "-" : "") << resultado << "\n\n";
    }

    return resultado;
}

std::string f3_binarioParaOctalHex(const std::string& binario, int baseDestino, bool trace) {
    if (baseDestino != 8 && baseDestino != 16) {
        return "";
    }

    if (binario.empty()) {
        return "0";
    }

    bool ehNegativo = false;
    size_t inicio = 0;
    if (binario[0] == '-') {
        ehNegativo = true;
        inicio = 1;
    } else if (binario[0] == '+') {
        inicio = 1;
    }

    if (inicio == binario.length()) {
        return "0";
    }

    // Encontrar separador decimal
    size_t posSeparador = binario.find('.');
    if (posSeparador == std::string::npos) {
        posSeparador = binario.find(',');
    }

    std::string parteInteiraStr = "";
    std::string parteFracionariaStr = "";

    if (posSeparador == std::string::npos) {
        parteInteiraStr = binario.substr(inicio);
    } else {
        parteInteiraStr = binario.substr(inicio, posSeparador - inicio);
        parteFracionariaStr = binario.substr(posSeparador + 1);
    }

    int G = (baseDestino == 8) ? 3 : 4;

    if (trace) {
        std::cout << "\n[Trace F3] Iniciando agrupamento direto de bits de binario \"" << binario 
                  << "\" para base " << baseDestino << " (Tamanho do grupo: " << G << "):\n";
    }

    // 1. Converter Parte Inteira (agrupamento da direita para a esquerda)
    std::string resultadoInteiro = "";
    if (parteInteiraStr.empty() || parteInteiraStr == "0") {
        resultadoInteiro = "0";
        if (trace) {
            std::cout << "  Parte inteira e vazia ou zero. Resultado: \"0\"\n";
        }
    } else {
        if (trace) {
            std::cout << "  --- PARTE INTEIRA (Agrupamento Direta para Esquerda): ---\n";
        }
        int acumulador = 0;
        int peso = 1;
        int count = 0;
        int grupoNum = 1;

        for (int i = (int)parteInteiraStr.length() - 1; i >= 0; i--) {
            char c = parteInteiraStr[i];
            if (c != '0' && c != '1') continue;

            int bit = c - '0';
            acumulador += bit * peso;
            peso *= 2;
            count++;

            if (count == G || i == 0) {
                char digito;
                if (acumulador < 10) {
                    digito = '0' + acumulador;
                } else {
                    digito = 'A' + (acumulador - 10);
                }

                if (trace) {
                    std::string bitsGrupo = parteInteiraStr.substr(i, count);
                    std::cout << "    Grupo " << grupoNum++ << ": \"" << bitsGrupo 
                              << "\" -> Valor: " << acumulador << " ('" << digito << "')\n";
                }

                resultadoInteiro += digito;
                acumulador = 0;
                peso = 1;
                count = 0;
            }
        }

        // Remover zeros à esquerda (estão no final da string antes de inverter)
        while (resultadoInteiro.length() > 1 && resultadoInteiro[resultadoInteiro.length() - 1] == '0') {
            resultadoInteiro.pop_back();
        }

        // Inverter a string
        int n = resultadoInteiro.length();
        for (int i = 0; i < n / 2; i++) {
            char temp = resultadoInteiro[i];
            resultadoInteiro[i] = resultadoInteiro[n - 1 - i];
            resultadoInteiro[n - 1 - i] = temp;
        }

        if (trace) {
            std::cout << "  Resultado da parte inteira invertido: \"" << resultadoInteiro << "\"\n";
        }
    }

    // 2. Converter Parte Fracionária (agrupamento da esquerda para a direita)
    std::string resultadoFracionario = "";
    if (!parteFracionariaStr.empty()) {
        if (trace) {
            std::cout << "  --- PARTE FRACIONARIA (Agrupamento Esquerda para Direita): ---\n";
        }
        int acumulador = 0;
        int count = 0;
        int grupoNum = 1;
        std::string bitsGrupo = "";

        for (size_t i = 0; i < parteFracionariaStr.length(); i++) {
            char c = parteFracionariaStr[i];
            if (c != '0' && c != '1') continue;

            bitsGrupo += c;
            count++;

            if (count == G || i == parteFracionariaStr.length() - 1) {
                // Preencher com zeros se incompleto no final
                int zerosAdicionados = 0;
                while (count < G) {
                    bitsGrupo += '0';
                    count++;
                    zerosAdicionados++;
                }

                // Calcular o valor do grupo binário
                acumulador = 0;
                int pesoBit = 1 << (G - 1);
                for (char b : bitsGrupo) {
                    acumulador += (b - '0') * pesoBit;
                    pesoBit /= 2;
                }

                char digito;
                if (acumulador < 10) {
                    digito = '0' + acumulador;
                } else {
                    digito = 'A' + (acumulador - 10);
                }

                if (trace) {
                    std::cout << "    Grupo " << grupoNum++ << ": \"" << bitsGrupo << "\"";
                    if (zerosAdicionados > 0) {
                        std::cout << " (preenchido com " << zerosAdicionados << " zero(s) a direita)";
                    }
                    std::cout << " -> Valor: " << acumulador << " ('" << digito << "')\n";
                }

                resultadoFracionario += digito;
                acumulador = 0;
                count = 0;
                bitsGrupo = "";
            }
        }

        // Remover zeros à direita do resultado fracionário para estética limpa
        while (resultadoFracionario.length() > 1 && resultadoFracionario[resultadoFracionario.length() - 1] == '0') {
            resultadoFracionario.pop_back();
        }
    }

    std::string resultado = resultadoInteiro;
    if (!resultadoFracionario.empty()) {
        resultado += "." + resultadoFracionario;
    }

    if (ehNegativo && resultado != "0") {
        resultado = "-" + resultado;
    }

    if (trace) {
        std::cout << "  => Resultado final do agrupamento F3: " << resultado << "\n\n";
    }

    return resultado;
}

std::string f4_ponteOctalHex(const std::string& valor, int baseOrigem, int baseDestino, bool trace) {
    if ((baseOrigem != 8 && baseOrigem != 16) || (baseDestino != 8 && baseDestino != 16) || (baseOrigem == baseDestino)) {
        return "";
    }

    if (valor.empty()) {
        return "0";
    }

    bool ehNegativo = false;
    size_t inicio = 0;
    if (valor[0] == '-') {
        ehNegativo = true;
        inicio = 1;
    } else if (valor[0] == '+') {
        inicio = 1;
    }

    if (inicio == valor.length()) {
        return "0";
    }

    // Encontrar separador decimal
    size_t posSeparador = valor.find('.');
    if (posSeparador == std::string::npos) {
        posSeparador = valor.find(',');
    }

    std::string parteInteiraStr = "";
    std::string parteFracionariaStr = "";

    if (posSeparador == std::string::npos) {
        parteInteiraStr = valor.substr(inicio);
    } else {
        parteInteiraStr = valor.substr(inicio, posSeparador - inicio);
        parteFracionariaStr = valor.substr(posSeparador + 1);
    }

    if (trace) {
        std::cout << "\n[Trace F4] Iniciando ponte " << (baseOrigem == 8 ? "Octal -> Hexadecimal" : "Hexadecimal -> Octal")
                  << " para valor \"" << valor << "\":\n";
    }

    std::string binarioInteiro = "";
    std::string binarioFracionario = "";

    // 1. Expandir Parte Inteira
    if (baseOrigem == 8) {
        if (trace && !parteInteiraStr.empty()) {
            std::cout << "  --- EXPANSÃO DA PARTE INTEIRA (Cada digito Octal -> 3 bits): ---\n";
        }
        for (char c : parteInteiraStr) {
            std::string bits = digitoOctalParaBinario(c);
            if (trace) {
                std::cout << "    '" << c << "' -> \"" << bits << "\"\n";
            }
            binarioInteiro += bits;
        }
    } else {
        if (trace && !parteInteiraStr.empty()) {
            std::cout << "  --- EXPANSÃO DA PARTE INTEIRA (Cada digito Hex -> 4 bits): ---\n";
        }
        for (char c : parteInteiraStr) {
            std::string bits = digitoHexParaBinario(c);
            if (trace) {
                std::cout << "    '" << c << "' -> \"" << bits << "\"\n";
            }
            binarioInteiro += bits;
        }
    }

    // Remover zeros à esquerda da parte inteira binária
    size_t primeiroDiferenteZero = 0;
    while (primeiroDiferenteZero < binarioInteiro.length() && binarioInteiro[primeiroDiferenteZero] == '0') {
        primeiroDiferenteZero++;
    }

    if (primeiroDiferenteZero == binarioInteiro.length()) {
        binarioInteiro = "0";
    } else {
        binarioInteiro = binarioInteiro.substr(primeiroDiferenteZero);
    }

    // 2. Expandir Parte Fracionária
    if (!parteFracionariaStr.empty()) {
        if (baseOrigem == 8) {
            if (trace) {
                std::cout << "  --- EXPANSÃO DA PARTE FRACIONÁRIA (Cada digito Octal -> 3 bits): ---\n";
            }
            for (char c : parteFracionariaStr) {
                std::string bits = digitoOctalParaBinario(c);
                if (trace) {
                    std::cout << "    '" << c << "' -> \"" << bits << "\"\n";
                }
                binarioFracionario += bits;
            }
        } else {
            if (trace) {
                std::cout << "  --- EXPANSÃO DA PARTE FRACIONÁRIA (Cada digito Hex -> 4 bits): ---\n";
            }
            for (char c : parteFracionariaStr) {
                std::string bits = digitoHexParaBinario(c);
                if (trace) {
                    std::cout << "    '" << c << "' -> \"" << bits << "\"\n";
                }
                binarioFracionario += bits;
            }
        }
    }

    std::string binarioIntermediario = binarioInteiro;
    if (!binarioFracionario.empty()) {
        binarioIntermediario += "." + binarioFracionario;
    }

    if (trace) {
        std::cout << "  => Binario intermediario completo: \"" << binarioIntermediario << "\"\n";
        std::cout << "  Chamando agrupamento direto (F3) no binario intermediario...\n";
    }

    // 3. Chamar f3_binarioParaOctalHex no binário intermediário
    std::string resultado = f3_binarioParaOctalHex(binarioIntermediario, baseDestino, trace);

    if (ehNegativo && resultado != "0") {
        resultado = "-" + resultado;
    }

    if (trace) {
        std::cout << "  => Ponte concluida com sucesso! Resultado: " << resultado << "\n\n";
    }

    return resultado;
}

std::string converterQualquerBase(const std::string& valor, int baseOrigem, int baseDestino, bool trace) {
    if (baseOrigem != 2 && baseOrigem != 8 && baseOrigem != 10 && baseOrigem != 16) {
        return "ERRO: Base de origem invalida";
    }
    if (baseDestino != 2 && baseDestino != 8 && baseDestino != 10 && baseDestino != 16) {
        return "ERRO: Base de destino invalida";
    }

    if (baseOrigem == baseDestino) {
        return valor;
    }

    if (trace) {
        std::cout << "\n>>> ROTEADOR UNIVERSAL: Convertendo \"" << valor << "\" da base " 
                  << baseOrigem << " para a base " << baseDestino << " <<<\n";
    }

    // Caso de base 10 de origem
    if (baseOrigem == 10) {
        double decimalValue = f2_basesParaDecimal(valor, 10, trace);
        return f1_decimalParaBases(decimalValue, baseDestino, trace);
    }

    // Caso de base 10 de destino
    if (baseDestino == 10) {
        double decimalValue = f2_basesParaDecimal(valor, baseOrigem, trace);
        return f1_decimalParaBases(decimalValue, 10, trace);
    }

    // Conversões puras entre bases não decimais
    if (baseOrigem == 2) {
        return f3_binarioParaOctalHex(valor, baseDestino, trace);
    }

    // Conversão de baseOrigem (8, 16) para baseDestino 2
    if (baseDestino == 2) {
        bool ehNegativo = false;
        size_t inicio = 0;
        if (valor[0] == '-') {
            ehNegativo = true;
            inicio = 1;
        } else if (valor[0] == '+') {
            inicio = 1;
        }

        size_t posSeparador = valor.find('.');
        if (posSeparador == std::string::npos) {
            posSeparador = valor.find(',');
        }

        std::string parteInteiraStr = "";
        std::string parteFracionariaStr = "";

        if (posSeparador == std::string::npos) {
            parteInteiraStr = valor.substr(inicio);
        } else {
            parteInteiraStr = valor.substr(inicio, posSeparador - inicio);
            parteFracionariaStr = valor.substr(posSeparador + 1);
        }

        std::string binarioInteiro = "";
        std::string binarioFracionario = "";

        if (baseOrigem == 8) {
            for (char c : parteInteiraStr) {
                binarioInteiro += digitoOctalParaBinario(c);
            }
            for (char c : parteFracionariaStr) {
                binarioFracionario += digitoOctalParaBinario(c);
            }
        } else {
            for (char c : parteInteiraStr) {
                binarioInteiro += digitoHexParaBinario(c);
            }
            for (char c : parteFracionariaStr) {
                binarioFracionario += digitoHexParaBinario(c);
            }
        }

        // Limpar zeros à esquerda da parte inteira
        size_t primeiroDiferenteZero = 0;
        while (primeiroDiferenteZero < binarioInteiro.length() && binarioInteiro[primeiroDiferenteZero] == '0') {
            primeiroDiferenteZero++;
        }

        if (primeiroDiferenteZero == binarioInteiro.length()) {
            binarioInteiro = "0";
        } else {
            binarioInteiro = binarioInteiro.substr(primeiroDiferenteZero);
        }

        // Limpar zeros à direita da parte fracionária
        while (binarioFracionario.length() > 0 && binarioFracionario[binarioFracionario.length() - 1] == '0') {
            binarioFracionario.pop_back();
        }

        std::string resultado = binarioInteiro;
        if (!binarioFracionario.empty()) {
            resultado += "." + binarioFracionario;
        }

        if (ehNegativo && resultado != "0") {
            resultado = "-" + resultado;
        }

        if (trace) {
            std::cout << "  [Trace Roteador] Convertido de base " << baseOrigem << " para Binario por expansao de bits: \"" << resultado << "\"\n";
        }
        return resultado;
    }

    // Se for entre Octal (8) e Hex (16)
    return f4_ponteOctalHex(valor, baseOrigem, baseDestino, trace);
}
