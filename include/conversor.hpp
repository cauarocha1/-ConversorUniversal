#ifndef CONVERSOR_HPP
#define CONVERSOR_HPP

#include <string>

/**
 * @brief Converte um número decimal (que pode ser fracionário) para uma base de destino.
 * 
 * @param decimal O número real em base 10 (decimal) a ser convertido.
 * @param baseDestino A base para a qual converter (2, 8, 10 ou 16).
 * @param trace Se true, exibe no terminal o passo a passo da conversão.
 * @return std::string A representação em string na base de destino.
 */
std::string f1_decimalParaBases(double decimal, int baseDestino, bool trace = false);

/**
 * @brief Converte uma representação em string de um número para decimal.
 * 
 * @param valor A representação do número como string.
 * @param baseOrigem A base do número na string (2, 8, 10 ou 16).
 * @param trace Se true, exibe no terminal o passo a passo do somatório posicional.
 * @return double O valor numérico correspondente em base 10 (decimal).
 */
double f2_basesParaDecimal(const std::string& valor, int baseOrigem, bool trace = false);

/**
 * @brief Converte um número binário (inteiro ou fracionário) diretamente para Octal ou Hexadecimal.
 * 
 * @param binario A string contendo a representação em binário (base 2).
 * @param baseDestino A base de destino (8 ou 16).
 * @param trace Se true, exibe no terminal o passo a passo do agrupamento de bits.
 * @return std::string A representação correspondente na base de destino.
 */
std::string f3_binarioParaOctalHex(const std::string& binario, int baseDestino, bool trace = false);

/**
 * @brief Realiza a conversão direta entre Octal e Hexadecimal (com suporte a fracionários) usando binário.
 * 
 * @param valor A string contendo o valor de origem.
 * @param baseOrigem A base de origem (8 ou 16).
 * @param baseDestino A base de destino (16 ou 8).
 * @param trace Se true, exibe o trace passo a passo de todas as etapas.
 * @return std::string O valor convertido.
 */
std::string f4_ponteOctalHex(const std::string& valor, int baseOrigem, int baseDestino, bool trace = false);

/**
 * @brief Roteador universal de conversões para as bases 2, 8, 10 e 16 (Requisito F8 / F9 / F10).
 * 
 * @param valor A representação textual do número a ser convertido.
 * @param baseOrigem A base de origem (2, 8, 10 ou 16).
 * @param baseDestino A base de destino (2, 8, 10 ou 16).
 * @param trace Se true, exibe o passo a passo.
 * @return std::string O valor convertido.
 */
std::string converterQualquerBase(const std::string& valor, int baseOrigem, int baseDestino, bool trace = false);

#endif // CONVERSOR_HPP
