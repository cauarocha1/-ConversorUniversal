#include <iostream>
#include <cmath>
#include "../include/conversor.hpp"
#include "../include/parser.hpp"

// Função para comparar se dois doubles são aproximadamente iguais
bool quaseIgual(double a, double b, double epsilon = 1e-9) {
    return std::abs(a - b) < epsilon;
}

// Suíte de testes automatizados com 30+ casos
int main() {
    std::cout << "\n========================================\n";
    std::cout << "   SUITE DE TESTES AUTOMATIZADOS\n";
    std::cout << "   Conversor Universal v1.0\n";
    std::cout << "========================================\n";

    int totalTestes = 0;
    int testesPassados = 0;
    int testesFalhados = 0;

    // ============ TESTES F1: Decimal para Bases ============
    std::cout << "\n[F1] Testando f1_decimalParaBases (Inteiros):\n";
    
    struct TesteDec {
        double decimal;
        int base;
        std::string esperado;
        const char* descricao;
    };
    
    TesteDec testesDec[] = {
        {255.0, 16, "FF", "255 em hexadecimal"},
        {255.0, 2, "11111111", "255 em binário"},
        {83.0, 8, "123", "83 em octal"},
        {0.0, 2, "0", "Zero em qualquer base"},
        {100.0, 10, "100", "100 em decimal"},
        {31.0, 2, "11111", "31 em binário"},
        {64.0, 16, "40", "64 em hexadecimal"},
        {1000.0, 8, "1750", "1000 em octal"},
        {-255.0, 16, "-FF", "Número negativo em hex"},
    };
    
    for (const auto& t : testesDec) {
        totalTestes++;
        std::string obtido = f1_decimalParaBases(t.decimal, t.base, false);
        if (obtido == t.esperado) {
            std::cout << "  ✓ [PASSOU] " << t.descricao << "\n";
            testesPassados++;
        } else {
            std::cout << "  ✗ [FALHOU] " << t.descricao 
                      << " | Esperado: \"" << t.esperado << "\" | Obtido: \"" << obtido << "\"\n";
            testesFalhados++;
        }
    }

    // ============ TESTES F1: Decimal com Fracionários ============
    std::cout << "\n[F1] Testando f1_decimalParaBases (Fracionários):\n";
    
    TesteDec testesFrac[] = {
        {10.625, 16, "A.A", "10.625 em hexadecimal"},
        {10.625, 2, "1010.101", "10.625 em binário"},
        {2.6875, 8, "2.54", "2.6875 em octal"},
        {-10.625, 16, "-A.A", "Negativo com fração em hex"},
        {0.5, 2, "0.1", "0.5 em binário"},
        {1.25, 8, "1.2", "1.25 em octal"},
    };
    
    for (const auto& t : testesFrac) {
        totalTestes++;
        std::string obtido = f1_decimalParaBases(t.decimal, t.base, false);
        if (obtido == t.esperado) {
            std::cout << "  ✓ [PASSOU] " << t.descricao << "\n";
            testesPassados++;
        } else {
            std::cout << "  ✗ [FALHOU] " << t.descricao 
                      << " | Esperado: \"" << t.esperado << "\" | Obtido: \"" << obtido << "\"\n";
            testesFalhados++;
        }
    }

    // ============ TESTES F2: Bases para Decimal ============
    std::cout << "\n[F2] Testando f2_basesParaDecimal:\n";
    
    struct TesteBase {
        std::string valor;
        int base;
        double esperado;
        const char* descricao;
    };
    
    TesteBase testesBase[] = {
        {"FF", 16, 255.0, "FF em hex para decimal"},
        {"ff", 16, 255.0, "ff (minúsculo) em hex para decimal"},
        {"11111111", 2, 255.0, "11111111 em binário para decimal"},
        {"123", 8, 83.0, "123 em octal para decimal"},
        {"0", 2, 0.0, "Zero em binário para decimal"},
        {"A.A", 16, 10.625, "A.A em hex para decimal"},
        {"1010.101", 2, 10.625, "1010.101 em binário para decimal"},
        {"2.54", 8, 2.6875, "2.54 em octal para decimal"},
        {"-A.A", 16, -10.625, "Negativo em hex para decimal"},
        {"100", 10, 100.0, "100 em decimal para decimal"},
    };
    
    for (const auto& t : testesBase) {
        totalTestes++;
        double obtido = f2_basesParaDecimal(t.valor, t.base, false);
        if (quaseIgual(obtido, t.esperado)) {
            std::cout << "  ✓ [PASSOU] " << t.descricao << "\n";
            testesPassados++;
        } else {
            std::cout << "  ✗ [FALHOU] " << t.descricao 
                      << " | Esperado: " << t.esperado << " | Obtido: " << obtido << "\n";
            testesFalhados++;
        }
    }

    // ============ TESTES F3: Agrupamento Direto Binário → Octal/Hex ============
    std::cout << "\n[F3] Testando f3_binarioParaOctalHex:\n";
    
    struct TesteBinDirect {
        std::string binario;
        int baseDestino;
        std::string esperado;
        const char* descricao;
    };

    TesteBinDirect testesBinDirect[] = {
        {"11111111", 16, "FF", "11111111 (bin) → FF (hex)"},
        {"1011", 8, "13", "1011 (bin) → 13 (oct)"},
        {"-1010", 16, "-A", "-1010 (bin) → -A (hex)"},
        {"10.1011", 8, "2.54", "10.1011 (bin) → 2.54 (oct)"},
        {"10.1011", 16, "2.B", "10.1011 (bin) → 2.B (hex)"},
        {"-10.1011", 16, "-2.B", "-10.1011 (bin) → -2.B (hex)"},
    };

    for (const auto& t : testesBinDirect) {
        totalTestes++;
        std::string obtido = f3_binarioParaOctalHex(t.binario, t.baseDestino, false);
        if (obtido == t.esperado) {
            std::cout << "  ✓ [PASSOU] " << t.descricao << "\n";
            testesPassados++;
        } else {
            std::cout << "  ✗ [FALHOU] " << t.descricao 
                      << " | Esperado: \"" << t.esperado << "\" | Obtido: \"" << obtido << "\"\n";
            testesFalhados++;
        }
    }

    // ============ TESTES F4: Ponte Octal ↔ Hexadecimal ============
    std::cout << "\n[F4] Testando f4_ponteOctalHex:\n";
    
    struct TestePonte {
        std::string valor;
        int baseOrigem;
        int baseDestino;
        std::string esperado;
        const char* descricao;
    };

    TestePonte testesPonte[] = {
        {"123", 8, 16, "53", "123 (oct) → 53 (hex)"},
        {"53", 16, 8, "123", "53 (hex) → 123 (oct)"},
        {"12.54", 8, 16, "A.B", "12.54 (oct) → A.B (hex)"},
        {"A.B", 16, 8, "12.54", "A.B (hex) → 12.54 (oct)"},
        {"-12.54", 8, 16, "-A.B", "-12.54 (oct) → -A.B (hex)"},
    };

    for (const auto& t : testesPonte) {
        totalTestes++;
        std::string obtido = f4_ponteOctalHex(t.valor, t.baseOrigem, t.baseDestino, false);
        if (obtido == t.esperado) {
            std::cout << "  ✓ [PASSOU] " << t.descricao << "\n";
            testesPassados++;
        } else {
            std::cout << "  ✗ [FALHOU] " << t.descricao 
                      << " | Esperado: \"" << t.esperado << "\" | Obtido: \"" << obtido << "\"\n";
            testesFalhados++;
        }
    }

    // ============ TESTES F5: Validação Robusta ============
    std::cout << "\n[F5] Testando validarEntrada:\n";
    
    struct TesteVal {
        std::string entrada;
        int base;
        bool esperado;
        const char* descricao;
    };

    TesteVal testesVal[] = {
        {"12.54", 8, true, "Válido: 12.54 na base 8"},
        {"12,54", 8, true, "Válido: 12,54 (vírgula) na base 8"},
        {"1.2.3", 8, false, "Inválido: dois separadores"},
        {".5", 8, false, "Inválido: separador no início"},
        {"5.", 8, false, "Inválido: separador no fim"},
        {"128.5", 8, false, "Inválido: dígito 8 na base 8"},
        {"A.BG", 16, false, "Inválido: letra G na base 16"},
        {"FF", 16, true, "Válido: FF na base 16"},
        {"ABCD", 16, true, "Válido: ABCD na base 16"},
        {"101010", 2, true, "Válido: 101010 na base 2"},
    };

    for (const auto& t : testesVal) {
        totalTestes++;
        bool obtido = validarEntrada(t.entrada, t.base);
        if (obtido == t.esperado) {
            std::cout << "  ✓ [PASSOU] " << t.descricao << "\n";
            testesPassados++;
        } else {
            std::cout << "  ✗ [FALHOU] " << t.descricao 
                      << " | Esperado: " << (t.esperado ? "true" : "false") 
                      << " | Obtido: " << (obtido ? "true" : "false") << "\n";
            testesFalhados++;
        }
    }

    // ============ TESTES F6: Fracionários com Truncamento ============
    std::cout << "\n[F6] Testando limite de 16 casas decimais:\n";
    
    totalTestes++;
    std::string dízima = f1_decimalParaBases(0.1, 2, false);
    if (dízima.find("... (truncado)") != std::string::npos) {
        std::cout << "  ✓ [PASSOU] Dízima detectada e truncada corretamente\n";
        testesPassados++;
    } else {
        std::cout << "  ✗ [FALHOU] Dízima não truncada adequadamente\n";
        testesFalhados++;
    }

    // ============ RESUMO FINAL ============
    std::cout << "\n========================================\n";
    std::cout << "                RESUMO DOS TESTES\n";
    std::cout << "========================================\n";
    std::cout << "Total de testes:       " << totalTestes << "\n";
    std::cout << "✓ Testes passados:     " << testesPassados << "\n";
    std::cout << "✗ Testes falhados:     " << testesFalhados << "\n";
    
    if (testesFalhados == 0) {
        std::cout << "\n>>> SUCESSO: TODOS OS TESTES PASSARAM! <<<\n";
        return 0;
    } else {
        std::cout << "\n>>> ERRO: " << testesFalhados << " teste(s) falharam! <<<\n";
        return 1;
    }
}
