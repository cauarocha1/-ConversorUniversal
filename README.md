# Conversor Universal de Sistemas de Numeração

**Trabalho Prático 1 - GCC241 (Introdução à Computação)**
**Departamento de Ciência da Computação - UFLA**

## 👥 Identificação da Dupla

* **Aluno 1:** Cauã Rocha Ribeiro de Souza (202610178) - Curso
* **Aluno 2:** Pedro de Boucherville da Silva (202611441) - Curso
* **Turma:** 14A - 2026/1

## 🎬 Vídeo de Demonstração

* **Link para o vídeo:** [Insira o Link Aqui (YouTube Não Listado ou Google Drive Aberto)]
* *Nota: O vídeo possui X minutos (está entre o limite obrigatório de 8 a 12 minutos) e ambos os integrantes explicam o código.*

## 🛠️ Linguagem e Justificativa Técnica

O projeto foi desenvolvido inteiramente em **C++** (padrão C++17), utilizando apenas a biblioteca padrão da linguagem.

Em total conformidade com a restrição central do edital, **não foram utilizadas funções prontas de conversão** (como `strtol`, `std::stoi` com base, `std::bitset`, etc.). Toda a aritmética de conversão, mapeamento da tabela ASCII e tratamento de arquivos CSV (split por `;`) foram codificados manualmente, caractere por caractere.

### Justificativa da Arquitetura

A estrutura modular do projeto segue princípios de engenharia de software:

- **`include/`**: Declarações de interface (headers) separando a especificação da implementação
- **`src/`**: Implementação dos módulos com baixo acoplamento e alta coesão
- **`tests/`**: Suíte de testes automatizados com mínimo de 30 casos para validação de correção
- **Makefile**: Automação de compilação com targets separados para programa, testes e limpeza

## 📋 Requisitos Implementados (F1-F10)

| Requisito | Descrição | Status |
|-----------|-----------|--------|
| **F1** | Conversão Decimal → Bases (2, 8, 16) via divisões sucessivas | ✅ Implementado |
| **F2** | Conversão Bases → Decimal via somatório posicional | ✅ Implementado |
| **F3** | Agrupamento direto de bits (Binário → Octal/Hexadecimal) | ✅ Implementado |
| **F4** | Ponte Octal ↔ Hexadecimal (via binário intermediário) | ✅ Implementado |
| **F5** | Validação robusta com apontamento de erro | ✅ Implementado |
| **F6** | Fracionários: máximo 16 casas + indicador de truncamento | ✅ Implementado |
| **F7** | Modo Trace: exibição passo a passo das conversões | ✅ Implementado |
| **F8** | Modo Batch: leitura e escrita em CSV (separador `;`) | ✅ Implementado |
| **F9** | Modo Quiz: jogo interativo com 5 níveis de dificuldade | ✅ Implementado |
| **F10** | Calculadora de Máximos: exibe 2^k-1 nas 4 bases simultaneamente | ✅ Implementado |

## 🚀 Instruções de Compilação e Execução

### Pré-requisitos

* Compilador `g++` suportando C++17
* Ferramenta `make`
* Sistema operacional Linux/Unix

### Passo a Passo para Compilar o Programa

No terminal do seu Linux, navegue até a pasta raiz do projeto e execute:

```bash
make clean && make
```

Se a compilação for bem-sucedida, você verá a mensagem:

```
✓ Compilação concluída: ./conversor_bases
```

### Executar o Programa Principal

```bash
./conversor_bases
```

Você verá um menu interativo com as seguintes opções:

```
====================================================
       CONVERSOR UNIVERSAL DE BASES NUMERICAS       
====================================================

Selecione uma opcao:
1  - Converter Decimal para Base (2, 8 ou 16)
2  - Converter de Base (2, 8 ou 16) para Decimal
3  - Converter Binario para Octal ou Hexadecimal (Agrupamento Direto)
4  - Converter entre Octal e Hexadecimal (Binario como Ponte)
5  - Executar Auto-testes Integrados
6  - Alternar Modo Trace [Status: INATIVO]
7  - Conversao Universal (qualquer base -> qualquer base)
8  - Modo Batch (Processar arquivo CSV)
9  - Modo Quiz (Jogo interativo)
10 - Calculadora de Valores Maximos (2^k - 1)
0  - Sair
Escolha: 
```

## 🧪 Compilação e Execução da Suíte de Testes

Para compilar e executar a suíte de testes automatizados (30+ casos de teste):

```bash
make clean && make tests
./testes
```

Exemplo de saída esperada:

```
========================================
   SUITE DE TESTES AUTOMATIZADOS
   Conversor Universal v1.0
========================================

[F1] Testando f1_decimalParaBases (Inteiros):
  ✓ [PASSOU] 255 em hexadecimal
  ✓ [PASSOU] 255 em binário
  ✓ [PASSOU] 83 em octal
  ...

========================================
                RESUMO DOS TESTES
========================================
Total de testes:       31
✓ Testes passados:     31
✗ Testes falhados:     0

>>> SUCESSO: TODOS OS TESTES PASSARAM! <<<
```

## 📁 Estrutura do Projeto

```
projeto/
├── include/
│   ├── conversor.hpp     # Declaração dos algoritmos de conversão (F1-F4, F6, F10)
│   ├── parser.hpp        # Declaração das funções de leitura e validação (F5)
│   ├── formatador.hpp    # Declaração dos menus visuais e lógica do Modo Trace (F7)
│   └── utilitarios.hpp   # Declaração dos modos extras (F8 - Batch e F9 - Quiz)
├── src/
│   ├── conversor.cpp     # Implementação manual dos algoritmos de conversão
│   ├── parser.cpp        # Implementação da validação robusta de caracteres e bases
│   ├── formatador.cpp    # Implementação dos menus e geração de traces detalhados
│   ├── utilitarios.cpp   # Implementação do split manual de arquivos CSV e jogo Quiz
│   └── main.cpp          # Ponto de entrada CLI e gerenciamento de despacho de funções
├── tests/
│   └── testes.cpp        # Suíte de testes automatizados (30+ casos)
├── entrada_exemplo.csv   # Arquivo de exemplo para o modo Batch (separado por ';')
├── Makefile              # Script de automação para compilação limpa do projeto
└── README.md             # Esta documentação

```

## 💡 Exemplos de Uso

### Exemplo 1: Converter 255 (decimal) para Hexadecimal

```
Escolha: 1
Digite o numero decimal (base 10): 255
Digite a base de destino (2, 8 ou 16): 16

>>> Resultado da conversao: FF
```

### Exemplo 2: Converter FF (hexadecimal) para Decimal com Trace

```
Escolha: 6  (Ativar Modo Trace)
Modo Trace alterado para: ATIVO

Escolha: 2
Digite o valor na base de origem: FF
Digite a base de origem (2, 8, 16): 16

[Trace F2] Iniciando conversao de base 16 "FF" para decimal (Base 10):
  --- PARTE INTEIRA (Somatorio Posicional com expoentes positivos): ---
    Dígito 'F' na posicao 0 (peso 16^1 = 16): 15 * 16 = 240
    Dígito 'F' na posicao 1 (peso 16^0 = 1): 15 * 1 = 15
  => Soma inteira: 255, Soma fracionaria: 0
  => Resultado final decimal F2: 255

>>> Resultado em decimal: 255
```

### Exemplo 3: Modo Batch (processamento de arquivo CSV)

1. Crie ou utilize `entrada_exemplo.csv`:
   ```
   valor;base_origem;base_destino
   255;10;16
   1010;2;8
   FF;16;10
   ```

2. No menu, escolha opção 8:
   ```
   Escolha: 8
   Digite o caminho do arquivo CSV de entrada (ex: entrada.csv): entrada_exemplo.csv
   Digite o caminho do arquivo CSV de saida (ex: saida.csv): saida.csv
   
   [Modo Batch] Abrindo arquivo de entrada: entrada_exemplo.csv
   >>> Modo Batch Concluido <<<
   Total de linhas processadas: 3
   Conversões bem-sucedidas: 3
   Arquivo de saída gravado em: saida.csv
   ```

3. Verifique `saida.csv`:
   ```
   valor;base_origem;resultado;base_destino
   255;10;FF;16
   1010;2;12;8
   FF;16;255;10
   ```

### Exemplo 4: Modo Quiz

```
Escolha: 9

====================================================
                BEM-VINDO AO QUIZ MODE              
====================================================
Regras:
- O quiz possui 5 niveis de dificuldade crescente.
- Voce deve acertar 3 perguntas para avancar de nivel.
- Voce possui 3 vidas no total. Errar uma resposta custa 1 vida.
- Respostas hexadecimais nao diferenciam maiusculas/minusculas.
====================================================

>>> INICIANDO NIVEL 1 <<<

Pergunta 1 (Vidas: 3 | Pontos: 0):
  Converta o valor "A" da base 16 para a base 2.
  Sua resposta: 1010
  Correto! Parabens!
```

### Exemplo 5: Calculadora de Máximos

```
Escolha: 10
Digite a quantidade de bits (k, entre 1 e 60): 8

==================================================
            CALCULADORA DE VALORES MAXIMOS        
==================================================
Bits informados (k): 8
Maior valor representavel (2^k - 1):
--------------------------------------------------
  Base Decimal (10) : 255
  Base Binaria (2)  : 11111111
  Base Octal (8)    : 377
  Base Hexa (16)    : FF
==================================================
```

## 🔧 Targets do Makefile

O projeto fornece diversos targets para facilitar compilação e testes:

```bash
make              # Compila apenas o programa principal
make tests        # Compila apenas a suíte de testes
make build-all    # Compila programa + testes
make clean        # Remove todos os arquivos compilados
make run          # Compila e executa o programa principal
make run-tests    # Compila e executa os testes
make help         # Exibe ajuda sobre os targets
```

## 📊 Correspondência com o Edital

| Arquivo | Corresponde a |
|---------|---------------|
| `include/conversor.hpp` | F1, F2, F3, F4, F6, F10 |
| `src/conversor.cpp` | Implementação de F1, F2, F3, F4, F6, F10 |
| `include/parser.hpp` | F5 |
| `src/parser.cpp` | Implementação de F5 |
| `include/formatador.hpp` | F7 (Modo Trace) |
| `src/formatador.cpp` | Implementação de F7 |
| `include/utilitarios.hpp` | F8, F9, F10 |
| `src/utilitarios.cpp` | Implementação de F8, F9, F10 |
| `tests/testes.cpp` | Suíte de testes (mínimo 30 casos) |
| `entrada_exemplo.csv` | Dados de exemplo para F8 |
| `Makefile` | Automação de build |

## 📝 Observações Importantes

### Segurança e Conformidade

1. **Sem funções proibidas**: Todo o código foi escrito manualmente, sem uso de `strtol`, `std::stoi`, `std::bitset`, `std::to_string` ou similares.

2. **Aritmética manual**: Conversões de bases utilizam apenas aritmética de inteiros/floats e manipulação ASCII, sem atalhos automáticos.

3. **Apenas biblioteca padrão**: As únicas bibliotecas incluídas são da biblioteca padrão C++ (`<iostream>`, `<string>`, `<fstream>`, `<random>`, `<cmath>`, `<chrono>`).

4. **Suporte a fracionários**: Todos os algoritmos suportam números fracionários com limite de 16 casas decimais.

5. **Negativos suportados**: Sinais `-` e `+` são tratados corretamente em todas as conversões.

## 🐛 Troubleshooting

### Erro: "command not found: g++"
**Solução**: Instale o compilador GCC:
```bash
sudo apt-get install build-essential  # Debian/Ubuntu
```

### Erro: "command not found: make"
**Solução**: Instale a ferramenta make:
```bash
sudo apt-get install make  # Debian/Ubuntu
```

### Erro na compilação dos testes
**Solução**: Certifique-se de que os headers estão em `include/` e as fontes em `src/`.

### Modo Batch não encontra arquivo
**Solução**: Use o caminho completo ou coloque o arquivo CSV no mesmo diretório onde executa o programa:
```bash
./conversor_bases
# Quando solicitado, digite: entrada_exemplo.csv
```

## 📚 Referências e Material de Estudo

- **C++ Standard Library**: https://en.cppreference.com/w/cpp/
- **Conversão de Bases**: Conceitos de Aritmética Digital e Sistemas de Numeração
- **Makefile Tutorial**: https://www.gnu.org/software/make/manual/


