#ifndef FORMATADOR_HPP
#define FORMATADOR_HPP

#include <string>

/**
 * @brief Exibe o menu principal do conversor, indicando o status do modo trace.
 * 
 * @param traceAtivo Status atual do modo trace.
 */
void exibirMenu(bool traceAtivo);

/**
 * @brief Exibe uma mensagem de resultado formatada de forma elegante.
 * 
 * @param titulo Descrição do resultado (ex: "Em decimal", "Em binário").
 * @param resultado O valor convertido em string.
 */
void exibirResultado(const std::string& titulo, const std::string& resultado);

/**
 * @brief Exibe uma mensagem de resultado numérico em decimal de forma elegante.
 * 
 * @param titulo Descrição do resultado.
 * @param resultado O valor numérico decimal inteiro.
 */
void exibirResultado(const std::string& titulo, long long resultado);

/**
 * @brief Exibe uma mensagem de resultado real em decimal de forma elegante.
 * 
 * @param titulo Descrição do resultado.
 * @param resultado O valor real decimal.
 */
void exibirResultado(const std::string& titulo, double resultado);

/**
 * @brief Exibe um cabeçalho decorado para o programa.
 */
void exibirCabecalho();

#endif // FORMATADOR_HPP

