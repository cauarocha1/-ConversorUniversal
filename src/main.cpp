#include <iostream>
#include <string>
#include <cmath>
#include "parser.hpp"
#include "conversor.hpp"
#include "formatador.hpp"
#include "utilitarios.hpp"

// Função para comparar se dois doubles são aproximadamente iguais
bool quaseIgual(double a, double b, double epsilon = 1e-9) {
    return std::abs(a - b) < epsilon;
}

// Função para rodar casos de teste automatizados de forma limpa e transparente
void executarTestes() {
    std::cout << "\n--- Iniciando Auto-testes Integrados ---\n";
    
    // Casos de teste de decimal para bases (F1 / F6)
    struct TesteDec {
        double decimal;
        int base;
        std::string esperado;
    };
    
    TesteDec testesDec[] = {
        {255.0, 16, "FF"},
        {255.0, 2, "11111111"},
        {83.0, 8, "123"},
        {0.0, 2, "0"},
        {10.625, 16, "A.A"},
        {10.625, 2, "1010.101"},
        {2.6875, 8, "2.54"},
        {-10.625, 16, "-A.A"},
        {0.1, 2, "0.0001100110011001 ... (truncado)"} // dízima truncada a 16 casas
    };
    
    bool todosPassaram = true;
    
    std::cout << "\nTestando f1_decimalParaBases (Requisito F1 & F6):\n";
    for (const auto& t : testesDec) {
        std::string obtido = f1_decimalParaBases(t.decimal, t.base, false);
        if (obtido == t.esperado) {
            std::cout << "  [PASSOU] " << t.decimal << " -> Base " << t.base << " = \"" << obtido << "\"\n";
        } else {
            std::cout << "  [FALHOU] " << t.decimal << " -> Base " << t.base << " | Esperado: \"" << t.esperado << "\" | Obtido: \"" << obtido << "\"\n";
            todosPassaram = false;
        }
    }
    
    // Casos de teste de bases para decimal (F2 / F6)
    struct TesteBase {
        std::string valor;
        int base;
        double esperado;
    };
    
    TesteBase testesBase[] = {
        {"FF", 16, 255.0},
        {"ff", 16, 255.0},
        {"11111111", 2, 255.0},
        {"123", 8, 83.0},
        {"0", 2, 0.0},
        {"A.A", 16, 10.625},
        {"1010.101", 2, 10.625},
        {"2.54", 8, 2.6875},
        {"-A.A", 16, -10.625}
    };
    
    std::cout << "\nTestando f2_basesParaDecimal (Requisito F2 & F6):\n";
    for (const auto& t : testesBase) {
        double obtido = f2_basesParaDecimal(t.valor, t.base, false);
        if (quaseIgual(obtido, t.esperado)) {
            std::cout << "  [PASSOU] \"" << t.valor << "\" (base " << t.base << ") -> " << obtido << "\n";
        } else {
            std::cout << "  [FALHOU] \"" << t.valor << "\" (base " << t.base << ") | Esperado: " << t.esperado << " | Obtido: " << obtido << "\n";
            todosPassaram = false;
        }
    }

    // Casos de teste de F3: binário para octal/hex por agrupamento direto (F3 & F6)
    struct TesteBinDirect {
        std::string binario;
        int baseDestino;
        std::string esperado;
    };

    TesteBinDirect testesBinDirect[] = {
        {"11111111", 16, "FF"},
        {"1011", 8, "13"},
        {"-1010", 16, "-A"},
        {"10.1011", 8, "2.54"},
        {"10.1011", 16, "2.B"},
        {"-10.1011", 16, "-2.B"}
    };

    std::cout << "\nTestando f3_binarioParaOctalHex (Requisito F3 & F6 - Sem decimal intermediario):\n";
    for (const auto& t : testesBinDirect) {
        std::string obtido = f3_binarioParaOctalHex(t.binario, t.baseDestino, false);
        if (obtido == t.esperado) {
            std::cout << "  [PASSOU] \"" << t.binario << "\" -> Base " << t.baseDestino << " = \"" << obtido << "\"\n";
        } else {
            std::cout << "  [FALHOU] \"" << t.binario << "\" -> Base " << t.baseDestino << " | Esperado: \"" << t.esperado << "\" | Obtido: \"" << obtido << "\"\n";
            todosPassaram = false;
        }
    }

    // Casos de teste de F4: octal <-> hex ponte via binário (F4 & F6)
    struct TestePonte {
        std::string valor;
        int baseOrigem;
        int baseDestino;
        std::string esperado;
    };

    TestePonte testesPonte[] = {
        {"123", 8, 16, "53"},
        {"53", 16, 8, "123"},
        {"12.54", 8, 16, "A.B"},
        {"A.B", 16, 8, "12.54"},
        {"-12.54", 8, 16, "-A.B"}
    };

    std::cout << "\nTestando f4_ponteOctalHex (Requisito F4 & F6 - Binario intermediario):\n";
    for (const auto& t : testesPonte) {
        std::string obtido = f4_ponteOctalHex(t.valor, t.baseOrigem, t.baseDestino, false);
        if (obtido == t.esperado) {
            std::cout << "  [PASSOU] \"" << t.valor << "\" (base " << t.baseOrigem << ") -> Base " << t.baseDestino << " = \"" << obtido << "\"\n";
        } else {
            std::cout << "  [FALHOU] \"" << t.valor << "\" (base " << t.baseOrigem << ") -> Base " << t.baseDestino << " | Esperado: \"" << t.esperado << "\" | Obtido: \"" << obtido << "\"\n";
            todosPassaram = false;
        }
    }

    // Casos de teste de F5: validação robusta (incluindo fracionários)
    struct TesteVal {
        std::string entrada;
        int base;
        bool esperado;
    };

    TesteVal testesVal[] = {
        {"12.54", 8, true},
        {"12,54", 8, true}, // Permite vírgula
        {"1.2.3", 8, false}, // Dois separadores
        {".5", 8, false}, // Separador no início
        {"5.", 8, false}, // Separador no fim
        {"128.5", 8, false}, // Dígito inválido 8 na base 8
        {"A.BG", 16, false} // Letra inválida G na base 16
    };

    std::cout << "\nTestando validarEntrada (Requisito F5 - Validacao Robusta):\n";
    for (const auto& t : testesVal) {
        std::cout << "  Validando \"" << t.entrada << "\" na base " << t.base << ":\n  ";
        bool obtido = validarEntrada(t.entrada, t.base);
        if (obtido == t.esperado) {
            std::cout << "  [PASSOU] Validacao correta: " << (obtido ? "valida" : "invalida") << "\n";
        } else {
            std::cout << "  [FALHOU] Validacao incorreta para \"" << t.entrada << "\" | Esperado: " << (t.esperado ? "true" : "false") << " | Obtido: " << (obtido ? "true" : "false") << "\n";
            todosPassaram = false;
        }
    }
    
    if (todosPassaram) {
        std::cout << "\n>>> SUCESSO: Todos os testes manuais, fracionarios e de ponte passaram! <<<\n";
    } else {
        std::cout << "\n>>> ERRO: Alguns testes falharam! Verifique a lógica. <<<\n";
    }
}

int main() {
    exibirCabecalho();
    
    bool modoTraceAtivo = false;
    int opcao = -1;
    while (opcao != 0) {
        exibirMenu(modoTraceAtivo);
        if (!(std::cin >> opcao)) {
            std::cin.clear();
            std::string lixo;
            std::cin >> lixo;
            std::cout << "Opcao invalida. Digite um numero.\n";
            continue;
        }
        
        if (opcao == 1) {
            double decimal;
            int baseDestino;
            std::cout << "Digite o numero decimal (base 10): ";
            if (!(std::cin >> decimal)) {
                std::cin.clear();
                std::string lixo;
                std::cin >> lixo;
                std::cout << "Numero decimal invalido.\n";
                continue;
            }
            std::cout << "Digite a base de destino (2, 8, 16): ";
            if (!(std::cin >> baseDestino)) {
                std::cin.clear();
                std::string lixo;
                std::cin >> lixo;
                std::cout << "Entrada invalida para a base.\n";
                continue;
            }
            
            if (baseDestino != 2 && baseDestino != 8 && baseDestino != 16) {
                std::cout << "Erro: Apenas as bases 2, 8 e 16 sao suportadas.\n";
                continue;
            }
            
            std::string resultado = f1_decimalParaBases(decimal, baseDestino, modoTraceAtivo);
            exibirResultado("Resultado da conversao", resultado);
            
        } else if (opcao == 2) {
            std::string valor;
            int baseOrigem;
            std::cout << "Digite o valor na base de origem: ";
            std::cin >> valor;
            std::cout << "Digite a base de origem (2, 8, 16): ";
            if (!(std::cin >> baseOrigem)) {
                std::cin.clear();
                std::string lixo;
                std::cin >> lixo;
                std::cout << "Entrada invalida para a base.\n";
                continue;
            }
            
            if (baseOrigem != 2 && baseOrigem != 8 && baseOrigem != 16) {
                std::cout << "Erro: Apenas as bases 2, 8 e 16 sao suportadas.\n";
                continue;
            }
            
            // Validar entrada através do parser antes de processar
            if (!validarEntrada(valor, baseOrigem)) {
                continue;
            }
            
            double resultado = f2_basesParaDecimal(valor, baseOrigem, modoTraceAtivo);
            exibirResultado("Resultado em decimal", resultado);
            
        } else if (opcao == 3) {
            std::string binario;
            int baseDestino;
            std::cout << "Digite o numero binario: ";
            std::cin >> binario;

            // Validar como base 2
            if (!validarEntrada(binario, 2)) {
                continue;
            }

            std::cout << "Digite a base de destino (8 ou 16): ";
            if (!(std::cin >> baseDestino)) {
                std::cin.clear();
                std::string lixo;
                std::cin >> lixo;
                std::cout << "Entrada invalida.\n";
                continue;
            }

            if (baseDestino != 8 && baseDestino != 16) {
                std::cout << "Erro: Apenas as bases 8 e 16 sao suportadas para agrupamento direto.\n";
                continue;
            }

            std::string resultado = f3_binarioParaOctalHex(binario, baseDestino, modoTraceAtivo);
            exibirResultado("Resultado (Agrupamento Direto)", resultado);

        } else if (opcao == 4) {
            std::string valor;
            int baseOrigem;
            std::cout << "Digite a base de origem (8 ou 16): ";
            if (!(std::cin >> baseOrigem)) {
                std::cin.clear();
                std::string lixo;
                std::cin >> lixo;
                std::cout << "Entrada invalida.\n";
                continue;
            }

            if (baseOrigem != 8 && baseOrigem != 16) {
                std::cout << "Erro: Apenas as bases 8 e 16 sao suportadas.\n";
                continue;
            }

            std::cout << "Digite o valor na base de origem: ";
            std::cin >> valor;

            if (!validarEntrada(valor, baseOrigem)) {
                continue;
            }

            int baseDestino = (baseOrigem == 8) ? 16 : 8;
            std::string resultado = f4_ponteOctalHex(valor, baseOrigem, baseDestino, modoTraceAtivo);
            exibirResultado("Resultado (Ponte via Binario)", resultado);

        } else if (opcao == 5) {
            executarTestes();
        } else if (opcao == 6) {
            modoTraceAtivo = !modoTraceAtivo;
            std::cout << "\n>>> Modo Trace alterado para: " << (modoTraceAtivo ? "ATIVO" : "INATIVO") << " <<<\n";
        } else if (opcao == 7) {
            // Conversão Universal: qualquer base para qualquer base
            std::string valor;
            int baseOrigem, baseDestino;
            std::cout << "Digite o valor a converter: ";
            std::cin >> valor;
            std::cout << "Digite a base de origem (2, 8, 10 ou 16): ";
            if (!(std::cin >> baseOrigem)) {
                std::cin.clear();
                std::string lixo;
                std::cin >> lixo;
                std::cout << "Entrada invalida para a base de origem.\n";
                continue;
            }
            std::cout << "Digite a base de destino (2, 8, 10 ou 16): ";
            if (!(std::cin >> baseDestino)) {
                std::cin.clear();
                std::string lixo;
                std::cin >> lixo;
                std::cout << "Entrada invalida para a base de destino.\n";
                continue;
            }

            if ((baseOrigem != 2 && baseOrigem != 8 && baseOrigem != 10 && baseOrigem != 16) ||
                (baseDestino != 2 && baseDestino != 8 && baseDestino != 10 && baseDestino != 16)) {
                std::cout << "Erro: Apenas as bases 2, 8, 10 e 16 sao suportadas.\n";
                continue;
            }

            if (!validarEntrada(valor, baseOrigem)) {
                continue;
            }

            std::string resultado = converterQualquerBase(valor, baseOrigem, baseDestino, modoTraceAtivo);
            exibirResultado("Resultado da conversao", resultado);

        } else if (opcao == 8) {
            // Modo Batch (F8)
            std::string caminhoEntrada, caminhoSaida;
            std::cout << "Digite o caminho do arquivo CSV de entrada (ex: entrada.csv): ";
            std::cin >> caminhoEntrada;
            std::cout << "Digite o caminho do arquivo CSV de saida (ex: saida.csv): ";
            std::cin >> caminhoSaida;
            executarModoBatch(caminhoEntrada, caminhoSaida);

        } else if (opcao == 9) {
            // Modo Quiz (F9)
            executarModoQuiz();

        } else if (opcao == 10) {
            // Calculadora de Máximos (F10)
            int k;
            std::cout << "Digite a quantidade de bits (k, entre 1 e 60): ";
            if (!(std::cin >> k)) {
                std::cin.clear();
                std::string lixo;
                std::cin >> lixo;
                std::cout << "Entrada invalida.\n";
                continue;
            }
            executarCalculadoraMaximos(k);

        } else if (opcao != 0) {
            std::cout << "Opcao invalida. Tente novamente.\n";
        }
    }
    
    std::cout << "\nPrograma encerrado. Bons estudos!\n";
    return 0;
}
