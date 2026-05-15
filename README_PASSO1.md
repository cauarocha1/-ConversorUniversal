# Conversor Universal de Sistemas de Numeração
## 📅 Passo 1: Estrutura Inicial e Requisitos F1 & F2

**Trabalho Prático 1 - GCC241 (Introdução à Computação)**  
**Departamento de Ciência da Computação - UFLA**

---

## 👥 Identificação da Dupla

* **Aluno 1:** Cauã Rocha Ribeiro de Souza (2026) - Curso
* **Aluno 2:** Pedro de Boucherville da Silva (2026) - Curso
* **Turma:** 14A - 2026/1

---

## 🛠️ Linguagem e Justificativa Técnica

O projeto foi desenvolvido inteiramente em **C++** (padrão C++17), utilizando apenas a biblioteca padrão da linguagem.

**Em total conformidade com as restrições do edital, não foram utilizadas funções prontas de conversão** (como `parseInt`, `strtol`, `std::bitset`, `toBinaryString`, etc.). 

Toda a aritmética de conversão de bases foi codificada manualmente:
- **F1**: Divisões sucessivas puro
- **F2**: Somatório posicional puro

### Justificativa da Arquitetura

A estrutura modular do projeto segue princípios de engenharia de software:

- **`include/`**: Declarações de interface (headers) separando especificação da implementação
- **`src/`**: Implementação dos módulos com baixo acoplamento e alta coesão
- **`Makefile`**: Automação de compilação com targets para programa, testes e limpeza

---

## 📋 Requisitos Implementados (Passo 1)

| Requisito | Descrição | Status |
|-----------|-----------|--------|
| **F1** | Conversão Decimal → Bases (2, 8, 16) via divisões sucessivas | ✅ Implementado |
| **F2** | Conversão Bases → Decimal via somatório posicional | ✅ Implementado |

### Escopo do Passo 1

- ✅ Apenas **números inteiros** (sem suporte a fracionários ainda)
- ✅ Conversão com **suporte a números negativos**
- ✅ Validação simples de entrada (F2)
- ✅ Menu com 3 opções: [1] F1, [2] F2, [0] Sair
- ✅ Implementação sem uso de funções prontas de conversão

---

## 🏗️ Estrutura de Arquivos

```
conversor_bases/
├── include/
│   ├── conversor.hpp       # F1 & F2: conversão de bases
│   ├── parser.hpp          # Validação de entrada
│   └── formatador.hpp      # Interface com usuário
├── src/
│   ├── main.cpp            # Programa principal (menu)
│   ├── conversor.cpp       # Implementação F1 & F2
│   ├── parser.cpp          # Implementação de validação
│   └── formatador.cpp      # Formatação de saída
├── Makefile                # Automação de compilação
└── README.md               # Este arquivo
```

---

## 🚀 Instruções de Compilação e Execução

### Pré-requisitos
- Compilador **GCC** ou **Clang** com suporte a C++17
- **GNU Make** instalado
- Linux/macOS/Windows (com WSL ou MinGW)

### Compilação
```bash
cd /home/caua/Documentos/PROJETOS/Conversor
make clean        # Limpa binários antigos
make              # Compila o programa
```

### Execução
```bash
./conversor_bases
```

### Menu Interativo
```
====================================================
   CONVERSOR UNIVERSAL DE BASES NUMERICAS       
      (Passo 1: F1 e F2 - Inteiros)           
====================================================

Selecione uma opcao:
1 - Converter Decimal para Base (2, 8 ou 16)
2 - Converter de Base (2, 8 ou 16) para Decimal
0 - Sair
Escolha:
```

---

## ✨ Exemplos de Uso

### Exemplo 1: F1 - Decimal para Hexadecimal
```
Escolha: 1
Digite o numero decimal (base 10): 255
Digite a base de destino (2, 8 ou 16): 16

>>> Resultado da conversao: FF
```

### Exemplo 2: F2 - Hexadecimal para Decimal
```
Escolha: 2
Digite o valor na base de origem: FF
Digite a base de origem (2, 8 ou 16): 16

>>> Resultado em decimal: 255
```

### Exemplo 3: F1 - Decimal para Binário
```
Escolha: 1
Digite o numero decimal (base 10): 10
Digite a base de destino (2, 8 ou 16): 2

>>> Resultado da conversao: 1010
```

---

## 🧪 Testes

Os testes automatizados serão implementados nos passos subsequentes.

---

## 📝 Algoritmos Utilizados

### F1: Divisões Sucessivas (Decimal → Base)
```
algoritmo decimal_para_base(numero, base):
    resto = []
    enquanto numero > 0:
        resto.push(numero % base)
        numero = numero / base
    retorna reverse(resto)
```

### F2: Somatório Posicional (Base → Decimal)
```
algoritmo base_para_decimal(string, base):
    resultado = 0
    potencia = 1
    para cada dígito d da direita para esquerda:
        resultado += valor(d) * potencia
        potencia *= base
    retorna resultado
```

---

## ⚙️ Detalhes de Implementação

### F1 - `f1_decimalParaBases(long long decimal, int baseDestino, bool trace)`

**Entrada:** Número inteiro decimal e base de destino (2, 8 ou 16)

**Saída:** String representando o número na base de destino

**Algoritmo:**
1. Verificar se `baseDestino` é válida (2, 8 ou 16)
2. Tratar sinal (negativos)
3. Aplicar divisões sucessivas até número ficar 0
4. Cada resto torna-se um dígito (0-9, A-F)
5. Inverter a sequência de dígitos
6. Retornar resultado como string

### F2 - `f2_basesParaDecimal(const std::string& valor, int baseOrigem, bool trace)`

**Entrada:** String do número e base de origem (2, 8 ou 16)

**Saída:** Número inteiro em decimal

**Algoritmo:**
1. Verificar se `baseOrigem` é válida (2, 8 ou 16)
2. Tratar sinal (negativos)
3. Para cada dígito da esquerda para direita:
   - Converter caractere para valor (0-15)
   - Multiplicar pela potência de base correspondente
   - Acumular à soma
4. Retornar resultado como long long

---

## 📌 Notas Importantes

- O programa **não valida bases inválidas** no menu (apenas aceita 2, 8, 16)
- Números negativos são suportados com prefixo `-`
- A validação robusta será implementada em passos subsequentes
- Sem suporte a fracionários neste passo (apenas inteiros)

---

## 📞 Contato

Para dúvidas ou sugestões sobre este projeto, entrar em contato com os autores.

---

**Última atualização:** 25 de maio de 2026  
**Status:** Passo 1 - Concluído ✅
