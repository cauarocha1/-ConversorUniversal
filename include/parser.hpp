#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>

/**
 * @brief Verifica se a representação textual do número é válida para a base informada.
 * 
 * @param entrada A string contendo o número a ser validado.
 * @param base A base numérica correspondente (2, 8, 10 ou 16).
 * @return true Se a string for válida para a base informada.
 * @return false Caso contenha caracteres inválidos para a base.
 */
bool validarEntrada(const std::string& entrada, int base);

#endif // PARSER_HPP
