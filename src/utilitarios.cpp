#include "utilitarios.hpp"
#include "conversor.hpp"
#include "parser.hpp"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

// Auxiliar para converter string para int manualmente
static int stringParaInt(const std::string& s) {
    int res = 0;
    bool ehNegativo = false;
    size_t inicio = 0;
    if (s.empty()) return 0;
    if (s[0] == '-') {
        ehNegativo = true;
        inicio = 1;
    } else if (s[0] == '+') {
        inicio = 1;
    }
    for (size_t i = inicio; i < s.length(); i++) {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            res = res * 10 + (c - '0');
        }
    }
    return ehNegativo ? -res : res;
}

// Auxiliar para normalizar strings para comparação (lowercase e converte vírgula para ponto)
static std::string normalizarString(const std::string& s) {
    std::string res = "";
    // Remover espaços no início e fim
    size_t inicio = 0;
    while (inicio < s.length() && (s[inicio] == ' ' || s[inicio] == '\t' || s[inicio] == '\r')) {
        inicio++;
    }
    size_t fim = s.length();
    while (fim > inicio && (s[fim - 1] == ' ' || s[fim - 1] == '\t' || s[fim - 1] == '\r' || s[fim - 1] == '\n')) {
        fim--;
    }

    for (size_t i = inicio; i < fim; i++) {
        char c = s[i];
        if (c == ',') {
            res += '.';
        } else if (c >= 'A' && c <= 'Z') {
            res += (c - 'A' + 'a');
        } else {
            res += c;
        }
    }
    return res;
}

void executarModoBatch(const std::string& caminhoEntrada, const std::string& caminhoSaida) {
    std::cout << "\n[Modo Batch] Abrindo arquivo de entrada: " << caminhoEntrada << "\n";
    std::ifstream entradaFile(caminhoEntrada);
    if (!entradaFile.is_open()) {
        std::cout << "Erro: Nao foi possivel abrir o arquivo de entrada \"" << caminhoEntrada << "\".\n";
        std::cout << "Dica: Crie o arquivo \"" << caminhoEntrada << "\" com colunas: valor;base_origem;base_destino\n";
        return;
    }

    std::ofstream saidaFile(caminhoSaida);
    if (!saidaFile.is_open()) {
        std::cout << "Erro: Nao foi possivel criar o arquivo de saida \"" << caminhoSaida << "\".\n";
        entradaFile.close();
        return;
    }

    std::string line;
    int totalProcessados = 0;
    int sucessos = 0;
    bool isFirstLine = true;

    while (std::getline(entradaFile, line)) {
        if (line.empty()) continue;

        // Se for cabeçalho
        if (isFirstLine && (line.find("valor") != std::string::npos || line.find("base") != std::string::npos)) {
            saidaFile << "valor;base_origem;resultado;base_destino\n";
            isFirstLine = false;
            continue;
        }
        isFirstLine = false;

        // Fazer split manual da linha por ';'
        size_t pos1 = line.find(';');
        if (pos1 == std::string::npos) continue;

        std::string valor = line.substr(0, pos1);
        size_t pos2 = line.find(';', pos1 + 1);
        if (pos2 == std::string::npos) continue;

        std::string baseOrigemStr = line.substr(pos1 + 1, pos2 - (pos1 + 1));
        std::string baseDestinoStr = line.substr(pos2 + 1);

        // Remover \r residual de arquivos do Windows
        if (!baseDestinoStr.empty() && baseDestinoStr.back() == '\r') {
            baseDestinoStr.pop_back();
        }

        int baseOrigem = stringParaInt(baseOrigemStr);
        int baseDestino = stringParaInt(baseDestinoStr);

        totalProcessados++;

        // Validar base e entrada
        std::string resultado = "";
        if (baseOrigem != 2 && baseOrigem != 8 && baseOrigem != 10 && baseOrigem != 16) {
            resultado = "ERRO: Base de origem invalida";
        } else if (baseDestino != 2 && baseDestino != 8 && baseDestino != 10 && baseDestino != 16) {
            resultado = "ERRO: Base de destino invalida";
        } else if (!validarEntrada(valor, baseOrigem)) {
            resultado = "ERRO: Entrada contem caracteres invalidos";
        } else {
            resultado = converterQualquerBase(valor, baseOrigem, baseDestino, false);
            sucessos++;
        }

        saidaFile << valor << ";" << baseOrigem << ";" << resultado << ";" << baseDestino << "\n";
    }

    entradaFile.close();
    saidaFile.close();

    std::cout << "\n>>> Modo Batch Concluido <<<\n";
    std::cout << "Total de linhas processadas: " << totalProcessados << "\n";
    std::cout << "Conversões bem-sucedidas: " << sucessos << "\n";
    std::cout << "Arquivo de saída gravado em: " << caminhoSaida << "\n";
}

void executarModoQuiz() {
    std::cout << "\n====================================================\n";
    std::cout << "                BEM-VINDO AO QUIZ MODE              \n";
    std::cout << "====================================================\n";
    std::cout << "Regras:\n";
    std::cout << "- O quiz possui 5 niveis de dificuldade crescente.\n";
    std::cout << "- Voce deve acertar 3 perguntas para avancar de nivel.\n";
    std::cout << "- Voce possui 3 vidas no total. Errar uma resposta custa 1 vida.\n";
    std::cout << "- Respostas hexadecimais nao diferenciam maiusculas/minusculas.\n";
    std::cout << "====================================================\n\n";

    // Inicializar gerador pseudo-aleatório robusto
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);

    int vidas = 3;
    int pontuacao = 0;
    int bases[] = {2, 8, 10, 16};

    for (int nivel = 1; nivel <= 5; nivel++) {
        std::cout << ">>> INICIANDO NIVEL " << nivel << " <<<\n";
        
        int acertosNoNivel = 0;
        int perguntaNum = 1;

        while (acertosNoNivel < 3 && vidas > 0) {
            // 1. Gerar o número de acordo com o nível
            double valorDecimal = 0.0;
            if (nivel == 1) {
                std::uniform_int_distribution<int> dist(0, 15);
                valorDecimal = dist(gen);
            } else if (nivel == 2) {
                std::uniform_int_distribution<int> dist(0, 127);
                valorDecimal = dist(gen);
            } else if (nivel == 3) {
                std::uniform_int_distribution<int> dist(0, 1023);
                valorDecimal = dist(gen);
            } else if (nivel == 4) {
                std::uniform_int_distribution<int> distInt(0, 255);
                std::uniform_int_distribution<int> distFrac(0, 3); // Multiplos de 0.25
                valorDecimal = distInt(gen) + distFrac(gen) * 0.25;
            } else {
                std::uniform_int_distribution<int> distInt(0, 1023);
                std::uniform_int_distribution<int> distFrac(0, 7); // Multiplos de 0.125
                valorDecimal = distInt(gen) + distFrac(gen) * 0.125;
            }

            // 2. Escolher baseOrigem e baseDestino
            std::uniform_int_distribution<int> distBase(0, 3);
            int idxO = distBase(gen);
            int idxD = distBase(gen);
            while (idxO == idxD) {
                idxD = distBase(gen);
            }
            int baseOrigem = bases[idxO];
            int baseDestino = bases[idxD];

            // 3. Converter para obter os valores
            std::string valorOrigem = f1_decimalParaBases(valorDecimal, baseOrigem, false);
            std::string respostaCorreta = f1_decimalParaBases(valorDecimal, baseDestino, false);

            std::cout << "\nPergunta " << perguntaNum++ << " (Vidas: " << vidas << " | Pontos: " << pontuacao << "):\n";
            std::cout << "  Converta o valor \"" << valorOrigem << "\" da base " << baseOrigem << " para a base " << baseDestino << ".\n";
            std::cout << "  Sua resposta: ";

            std::string respostaUsuario;
            std::cin >> respostaUsuario;

            // Normalizar para fazer comparação case-insensitive e flexível em ponto decimal
            std::string respUserNorm = normalizarString(respostaUsuario);
            std::string respCorrNorm = normalizarString(respostaCorreta);

            if (respUserNorm == respCorrNorm) {
                std::cout << "  Correto! Parabens!\n";
                acertosNoNivel++;
                pontuacao += 10 * nivel;
            } else {
                std::cout << "  Incorreto! A resposta correta era: \"" << respostaCorreta << "\"\n";
                vidas--;
            }

            if (vidas == 0) {
                break;
            }
        }

        if (vidas == 0) {
            std::cout << "\n====================================================\n";
            std::cout << "                     GAME OVER!                     \n";
            std::cout << "====================================================\n";
            std::cout << "Voce perdeu todas as vidas.\n";
            std::cout << "Pontuacao final: " << pontuacao << " pontos.\n\n";
            return;
        }

        std::cout << "\n>>> NIVEL " << nivel << " CONCLUIDO COM SUCESSO! <<<\n\n";
    }

    std::cout << "====================================================\n";
    std::cout << "             PARABENS! VOCE COMPLETOU O QUIZ!       \n";
    std::cout << "====================================================\n";
    std::cout << "Desempenho perfeito!\n";
    std::cout << "Pontuacao final: " << pontuacao << " pontos.\n\n";
}

void executarCalculadoraMaximos(int k) {
    if (k < 1 || k > 60) {
        std::cout << "Erro: Quantidade de bits invalida (insira um valor entre 1 e 60).\n";
        return;
    }

    // Calcula 2^k - 1 usando bit shift de 64 bits unsigned
    unsigned long long valorMaximo = (1ULL << k) - 1ULL;

    // Converter para as 4 bases
    // Como valorMaximo cabe em double sem perda até 53 bits e com pequenas imprecisões até 60 bits,
    // usamos uma rotina direta convertendo para double para aproveitar nosso conversor genérico.
    double decimalVal = (double)valorMaximo;

    std::string binario = f1_decimalParaBases(decimalVal, 2, false);
    std::string octal = f1_decimalParaBases(decimalVal, 8, false);
    std::string decimal = f1_decimalParaBases(decimalVal, 10, false);
    std::string hex = f1_decimalParaBases(decimalVal, 16, false);

    std::cout << "\n==================================================\n";
    std::cout << "            CALCULADORA DE VALORES MAXIMOS        \n";
    std::cout << "==================================================\n";
    std::cout << "Bits informados (k): " << k << "\n";
    std::cout << "Maior valor representavel (2^k - 1):\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << "  Base Decimal (10) : " << decimal << "\n";
    std::cout << "  Base Binaria (2)  : " << binario << "\n";
    std::cout << "  Base Octal (8)    : " << octal << "\n";
    std::cout << "  Base Hexa (16)    : " << hex << "\n";
    std::cout << "==================================================\n";
}
