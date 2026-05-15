#ifndef UTILITARIOS_HPP
#define UTILITARIOS_HPP

#include <string>

/**
 * @brief Requisito F8: Modo Batch. Lê colunas 'valor;base_origem;base_destino' de entrada.csv,
 * realiza as conversões e grava os resultados em saida.csv.
 * 
 * @param caminhoEntrada Caminho do arquivo CSV de entrada.
 * @param caminhoSaida Caminho do arquivo CSV de saída.
 */
void executarModoBatch(const std::string& caminhoEntrada, const std::string& caminhoSaida);

/**
 * @brief Requisito F9: Modo Quiz. Jogo interativo com 5 níveis de dificuldade.
 */
void executarModoQuiz();

/**
 * @brief Requisito F10: Calculadora de Máximos. Calcula o valor máximo de k bits (2^k - 1)
 * e o exibe formatado nas bases 2, 8, 10 e 16 simultaneamente.
 * 
 * @param k Quantidade de bits (entre 1 e 60).
 */
void executarCalculadoraMaximos(int k);

#endif // UTILITARIOS_HPP
