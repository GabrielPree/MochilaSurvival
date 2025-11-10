#  Projeto: Mochila Survival

##  Sobre o Projeto

O **Mochila Survival** é um projeto desenvolvido em **C** que simula uma mochila em um jogo de sobrevivência (*survival*).  
O objetivo é gerenciar os itens que o jogador coleta durante o jogo, permitindo **adicionar**, **remover**, **listar**, **ordenar** e **buscar** itens conforme diferentes critérios.

O projeto utiliza **estruturas de dados estáticas**, **algoritmos de ordenação** (Bubble, Insertion e Selection Sort) e **busca binária adaptada**, além de medir o tempo de execução das ordenações.

---

##  Funcionalidades

-  **Adicionar itens** à mochila (nome, tipo, quantidade e prioridade)  
-  **Remover itens** pelo nome  
-  **Listar** todos os itens armazenados  
-  **Ordenar** os itens por:
  - Nome (Bubble Sort)
  - Tipo (Insertion Sort)
  - Prioridade (Selection Sort)
-  **Buscar** um item pelo nome (busca binária adaptada)
-  **Exibir o tempo de ordenação** em microssegundos

---

##  Estrutura de Dados

### Estrutura `Item`
Representa um item armazenado na mochila:

```c
typedef struct Item {
    char nome[30];
    char tipo[20];
    int numero;       // quantidade do item
    int prioridade;   // 1 (alta) a 5 (baixa)
} Item;
```
### Estrutura `Mochila`
Gerencia até 10 tipos diferentes de itens:
```c
typedef struct Mochila {
    Item itens[10];
    int quantidade;
    int estaOrdenada;
    char criterioOrdenacao[20];
} Mochila;
```
---
##  Algoritmos Utilizados

| Tipo de Operação | Algoritmo | Descrição |
|------------------|------------|------------|
| Ordenação por nome | **Bubble Sort** | Ordena alfabeticamente |
| Ordenação por tipo | **Insertion Sort** | Ordena por categorias (arma, cura, etc.) |
| Ordenação por prioridade | **Selection Sort** | Ordena do mais importante (1) ao menos importante (5) |
| Busca | **Busca Binária Adaptada** | Localiza um item pelo nome, considerando o critério de ordenação atual |

---
##  Menu Principal
Exemplo de interação no terminal:
```bash
======================
== MOCHILA SURVIVAL ==
======================
Itens na mochila: 0

1 - Adicionar Item
2 - Remover Item
3 - Listar Itens
4 - Ordenar Mochila
5 - Buscar Item
0 - Sair
Escolha uma opcao:
```
##  Exemplo de Uso
### Adicionando Itens:
```bash
Digite o nome do item: Água
Digite o tipo do item (arma, cura, protecao, comida, bebida e etc): bebida
Digite a quantidade do item: 3
Digite a prioridade do item 1 a 5 (1 = alta a 5 = baixa): 2
Item "Água" (Tipo: bebida, Quantidade: 3, Prioridade: 2) adicionado com sucesso!
```
### Listando Itens:
```bash
======================= ITENS NA MOCHILA (2/10) ========================
| #   | Nome                 | Tipo            | Qtd      | Prioridade |
|-----|----------------------|-----------------|----------|------------|
| 1   | Água                 | bebida          | 3        | 2          |
| 2   | Espada               | arma            | 1        | 1          |
========================================================================
(A mochila ainda nao foi ordenada.)
```
### Ordenando Itens
```bash
--- MENU DE ORDENACAO ---

1 - Ordenar por Nome (Ordem Alfabetica)
2 - Ordenar por Tipo
3 - Ordenar por Prioridade
0 - Sair
Escolha uma opcao: 1

Itens ordenados por nome (Ordem alfabetica).
Tempo de ordenação: 12.554 μs
```
---
##  Como Compilar e Executar
### 🔧 Compilação
Use o GCC (ou outro compilador C compatível):
```bash
gcc mochila_survival.c -o mochila_survival
```
###  Execução
```bash
./mochila_survival
```
---
##  Medição de Desempenho

#### Cada algoritmo de ordenação mede o tempo de execução em microsegundos, permitindo comparar o desempenho entre eles.
---
##  Tecnologias e Conceitos Utilizados

- Linguagem C

- Structs

- Vetores estáticos

- Ponteiros

- Manipulação de strings (strcmp, strcpy, etc.)

- Algoritmos clássicos de ordenação e busca

- Medição de tempo com clock()

---
## Autor
#### Gabriel Preé
Estudante de Análise e Desenvolvimento de Sistemas

Projeto desenvolvido para prática de estruturas de dados e algoritmos em C.

---

##  Licença

Este projeto é de código aberto e pode ser usado livremente para fins educacionais.

#### Contribuições e melhorias são bem-vindas! 
