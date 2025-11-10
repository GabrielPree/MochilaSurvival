#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>

/*
-------------------------------------------------------------------------------------------------------------------------------
PROJETO: MOCHILA SURVIVAL
OBJETIVO: Implementar uma Mochila de um jogo survival para adicionar itens a ela, citando o nome e o tipo do item.

-------------------------------------------------------------------------------------------------------------------------------
*/

// Estrutura que representa um item
typedef struct Item {
    char nome[30];
    char tipo[20];
    int numero; // quantidade do item
    int prioridade; // 1 (prioridade baixa) a 5 (prioridade alta)
} Item;

// Estrutura que representa a mochila
typedef struct Mochila {
    struct Item itens[10]; // até 10 tipos de itens
    int quantidade; // quantos tipos de itens foram adicionados
    int estaOrdenada;
    char criterioOrdenacao[20]; // nome, tipo ou prioridade
} Mochila;

//Funções da lista estática da mochila

// Está função prepara a lista para ser usada.
// Ela simplesmente defiine o contador quantidade para 0, indicando que a lista está vazia.
// Recebemos um ponteiro(*lista) para modificar a variável original passada pela função.
void inicializarMochila(Mochila *mochila);

void limpaBufferEntrada();

// Funções da Mochila
void adicionarItem(Mochila *mochila, const char* nome, const char* tipo, int numero, int prioridade);
void removerItem(Mochila *mochila, const char* nome);
void listar(const Mochila *mochila);
void buscarItem(const Mochila *mochila, const char* nome);

// Menus
void menu(Mochila *mochila);
void menuOrdenar(Mochila *mochila);

// Ordenações
int tipoParaValor(const char* tipo);
void ordenarPorNome(Mochila *mochila);       // Bubble sort
void ordenarPorTipo(Mochila *mochila);       // Insertion sort
void ordenarPorPrioridade(Mochila *mochila); // Selection sort

// --- Função principal ---
int main() {
    Mochila mochila;
    inicializarMochila(&mochila);
    menu(&mochila);
    return 0;
}

// --- Função para inicializar a mochila vazia ---
void inicializarMochila(Mochila *mochila) {
    mochila->quantidade = 0;
    mochila->estaOrdenada = 0;
    mochila->criterioOrdenacao[0] = '\0';
}

// --- Função para adicionar um item a mochila ---
void adicionarItem(Mochila *mochila, const char* nome, const char* tipo, int numero, int prioridade) {
    if (mochila->quantidade == 10) {
        printf("A mochila esta cheia!\n");
        return;
    }
    strcpy(mochila->itens[mochila->quantidade].nome, nome);
    strcpy(mochila->itens[mochila->quantidade].tipo, tipo);
    // Adiciona a quantidade de itens na mochila
    mochila->itens[mochila->quantidade].numero = numero;
    mochila->itens[mochila->quantidade].prioridade = prioridade;
    mochila->quantidade++;
    mochila->estaOrdenada = 0; // Sempre que adicioa um item na mochila, ela precisa ser reordenada.

    printf("Item \"%s\" (Tipo: %s, Quantidade: %d, Prioridade: %d) adicionado com sucesso!\n", nome, tipo, numero, prioridade);
    printf("\n");
}

// --- Função para remover item da mochila ---
void removerItem(Mochila *mochila, const char* nome) {

    // A função percorre os itens em uso na lista (de 0 até quantidade)
    // Essa função retorna 0 se as strings forem idênticas. Se encontrar, guarda a posição (pos) e para o loop.
    int pos = -1;

    // Procura pelo nome e se encontrar, guarda a posiçao e para o loop.
    for (int i = 0; i < mochila->quantidade; i++) {
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }
    // Tratamento de Erro: Se o loop terminar e pos continuar -1, o item n foi encontrado
    if (pos == -1) {
        printf("Erro: Item \"%s\" não encontrado na mochila!\n", nome);
        printf("\n");
        return;
    }

    // Atualização do Contador: Se removemos um item do meio  da lista, criamos um buraco na lista.
    // Para resolver isso, precisamos movemos todos os itens subsequentes uma posiçao para esquerda.
    for (int i = pos; i < mochila->quantidade - 1; i++) {
        mochila->itens[i] = mochila->itens[i + 1];
    }
    // Atualização do Contador: Finalmente, quantidade é decrementado para refletir que a lista tem um item a menos.
    mochila->quantidade--;
    mochila->estaOrdenada = 0;

    printf("Item \"%s\" removido com sucesso!\n", nome);
    printf("\n");
}

// --- Função para listar os itens da mochila ---
void listar(const Mochila *mochila) {
    if (mochila->quantidade == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }
    printf("======================= ITENS NA MOCHILA (%d/10) ========================\n", mochila->quantidade);
    printf("| %-3s | %-20s | %-15s | %-8s | %-10s |\n", "#", "Nome", "Tipo", "Qtd", "Prioridade");
    printf("|-----|----------------------|-----------------|----------|------------|\n");
    for (int i = 0; i < mochila->quantidade; i++) {
        printf("| %-3d | %-20s | %-15s | %-8d | %-10d |\n", i + 1, mochila->itens[i].nome, mochila->itens[i].tipo, mochila->itens[i].numero, mochila->itens[i].prioridade);
    }
    printf("========================================================================\n");
    if (mochila->estaOrdenada)
    printf("(A mochila foi Ordenada por: %s)\n", mochila->criterioOrdenacao);
    else
    printf("(A mochila ainda nao foi ordenada.)\n");
    printf("\n");
}

// --- Limpa o buffer do teclado ---
void limpaBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ---- Conversão de tipo para número para o Insertion Sort ----
int tipoParaValor(const char* tipo) {
    if (strcmp(tipo, "arma") == 0) return 1;
    if (strcmp(tipo, "cura") == 0) return 2;
    if (strcmp(tipo, "protecao") == 0) return 3;
    if (strcmp(tipo, "comida") == 0) return 4;
    if (strcmp(tipo, "bebida") == 0) return 5;
    return 999; // tipos desconhecidos vão pro final
}

// --- Ordenação por nome (Bubble Sort) ---
void ordenarPorNome(Mochila *mochila) {
     // Ordena os itens por nome (Bubble Sort simples)
    for (int i = 0; i < mochila->quantidade - 1; i++) {
        for (int j = 0; j < mochila->quantidade - i - 1; j++) {
            if (strcmp(mochila->itens[j].nome, mochila->itens[j + 1].nome) > 0) {
                Item temp = mochila->itens[j];
                mochila->itens[j] = mochila->itens[j + 1];
                mochila->itens[j + 1] = temp;
            }
        }
    }
    mochila->estaOrdenada = 1;
    strcpy(mochila->criterioOrdenacao, "nome");
    printf("Itens ordenados por nome (Ordem alfabetica).\n");
}

// --- Ordenação por tipo (Insertion Sort) ---
void ordenarPorTipo(Mochila *mochila) {
    for (int i = 1; i < mochila->quantidade; i++) {
        Item chave = mochila->itens[i];
        int j = i - 1;
        while (j >= 0 && tipoParaValor(mochila->itens[j].tipo) > tipoParaValor(chave.tipo)) {
            mochila->itens[j + 1] = mochila->itens[j];
            j--;
        }
        mochila->itens[j + 1] = chave;
    }
    mochila->estaOrdenada = 1;
    strcpy(mochila->criterioOrdenacao, "tipo");
    printf("Itens ordenados por tipo.\n");
}

// --- Ordena os itens por prioridade (Selection Sort) ---
void ordenarPorPrioridade(Mochila *mochila) {
    // menor número = maior prioridade
    for (int i = 0; i < mochila->quantidade - 1; i++) {
        int indice_min = i;
        for (int j = i + 1; j < mochila->quantidade; j++) {
            if (mochila->itens[j].prioridade < mochila->itens[indice_min].prioridade) {
                indice_min = j;
            }
        }
        if (indice_min != i) {
            Item temp = mochila->itens[i];
            mochila->itens[i] = mochila->itens[indice_min];
            mochila->itens[indice_min] = temp;
        }
    }
    mochila->estaOrdenada = 1;
    strcpy(mochila->criterioOrdenacao, "prioridade");
    printf("Itens ordenados por prioridade.\n");
}

// ---- Medição de tempo ----
void medirTempo(void (*func)(Mochila *), Mochila *mochila) {
    clock_t inicio, fim;
    double tempo_us;

    inicio = clock();
    func(mochila);
    fim = clock();

    tempo_us = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000000.0;

    if (tempo_us < 1.0) {
        printf("\nTempo de ordenação: < 1 μs (microsegundos, muito rápido para medir)\n");
    } else {
        printf("\nTempo de ordenação: %.3f μs (microsegundos)\n", tempo_us);
    }
}

// --- Função para buscar um item na mochila ---
void buscarItem(const Mochila *mochila, const char* nome) {
    if (!mochila->estaOrdenada) {
        printf("A mochila precisa estar ordenada para usar busca binária!\n");
        printf("Pressione Enter para continuar...");
        getchar();
        return;
    }

    int comparacoes = 0;
    int encontrado = 0;
    int posicaoEncontrada = -1;

    // Se está ordenado por NOME, busca binária direta por nome
    if (strcmp(mochila->criterioOrdenacao, "nome") == 0) {
        int inicio = 0;
        int fim = mochila->quantidade - 1;
        
        while (inicio <= fim) {
            int meio = inicio + (fim - inicio) / 2;
            comparacoes++;
            
            int cmp = strcmp(mochila->itens[meio].nome, nome);
            
            if (cmp == 0) {
                posicaoEncontrada = meio;
                encontrado = 1;
                break;
            } else if (cmp > 0) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
        }
    }
    // Se está ordenado por TIPO, precisamos de uma estratégia diferente
    else if (strcmp(mochila->criterioOrdenacao, "tipo") == 0) {
        // Como está ordenado por tipo, não podemos fazer busca binária direta por nome
        // Mas podemos fazer uma busca binária adaptada que percorre todos os itens
        // de forma "binária" mas verificando cada nome
        int inicio = 0;
        int fim = mochila->quantidade - 1;
        
        // Busca binária adaptada - percorre a lista de forma binária mas verifica cada nome
        while (inicio <= fim && !encontrado) {
            int meio = inicio + (fim - inicio) / 2;
            comparacoes++;
            
            // Verifica se encontrou o nome no meio
            if (strcmp(mochila->itens[meio].nome, nome) == 0) {
                posicaoEncontrada = meio;
                encontrado = 1;
                break;
            }
            
            // Se não encontrou, continua a busca binária normalmente
            // Mesmo estando ordenado por tipo, ainda podemos dividir o espaço de busca
            if (meio > inicio) {
                // Busca na metade esquerda
                for (int i = inicio; i < meio && !encontrado; i++) {
                    comparacoes++;
                    if (strcmp(mochila->itens[i].nome, nome) == 0) {
                        posicaoEncontrada = i;
                        encontrado = 1;
                    }
                }
            }
            
            if (!encontrado && meio < fim) {
                // Busca na metade direita
                for (int i = meio + 1; i <= fim && !encontrado; i++) {
                    comparacoes++;
                    if (strcmp(mochila->itens[i].nome, nome) == 0) {
                        posicaoEncontrada = i;
                        encontrado = 1;
                    }
                }
            }
            
            // Se não encontrou em nenhuma metade, para a busca
            break;
        }
    }
    // Se está ordenado por PRIORIDADE, estratégia similar à do tipo
    else if (strcmp(mochila->criterioOrdenacao, "prioridade") == 0) {
        int inicio = 0;
        int fim = mochila->quantidade - 1;
        
        // Busca binária adaptada para prioridade
        while (inicio <= fim && !encontrado) {
            int meio = inicio + (fim - inicio) / 2;
            comparacoes++;
            
            // Verifica se encontrou o nome no meio
            if (strcmp(mochila->itens[meio].nome, nome) == 0) {
                posicaoEncontrada = meio;
                encontrado = 1;
                break;
            }
            
            // Se não encontrou, continua a busca nas metades
            if (meio > inicio) {
                // Busca na metade esquerda
                for (int i = inicio; i < meio && !encontrado; i++) {
                    comparacoes++;
                    if (strcmp(mochila->itens[i].nome, nome) == 0) {
                        posicaoEncontrada = i;
                        encontrado = 1;
                    }
                }
            }
            
            if (!encontrado && meio < fim) {
                // Busca na metade direita
                for (int i = meio + 1; i <= fim && !encontrado; i++) {
                    comparacoes++;
                    if (strcmp(mochila->itens[i].nome, nome) == 0) {
                        posicaoEncontrada = i;
                        encontrado = 1;
                    }
                }
            }
            
            // Se não encontrou em nenhuma metade, para a busca
            break;
        }
    }

    if (encontrado && posicaoEncontrada != -1) {
        printf("\n======== ITEM ENCONTRADO ========\n");
        printf("Nome: %s\n", mochila->itens[posicaoEncontrada].nome);
        printf("Tipo: %s\n", mochila->itens[posicaoEncontrada].tipo);
        printf("Quantidade: %d\n", mochila->itens[posicaoEncontrada].numero);
        printf("Prioridade: %d\n", mochila->itens[posicaoEncontrada].prioridade);
        printf("Foram feitas %d comparações para encontrar o item.\n", comparacoes);
        printf("==================================\n");
    } else {
        printf("\nItem \"%s\" não encontrado na mochila!\n", nome);
        printf("Foram feitas %d comparações.\n", comparacoes);
    }
}

// --- Menu de Ordenação ---
void menuOrdenar(Mochila *mochila) {
    int opcao;

    do {
    printf("\n--- MENU DE ORDENACAO ---\n");
    printf("\n1 - Ordenar por Nome (Ordem Alfabetica)\n");
    printf("2 - Ordenar por Tipo\n");
    printf("3 - Ordenar por Prioridade\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    printf("\n");
    limpaBufferEntrada();
    
    switch (opcao) {
        case 1:
            medirTempo(ordenarPorNome, mochila);
            listar(mochila);
            printf("Pressione Enter para continuar...");
            getchar();
            opcao = 0;
            break;
        case 2:
            medirTempo(ordenarPorTipo, mochila);
            listar(mochila);
            printf("Pressione Enter para continuar...");
            getchar();
            opcao = 0;
            break;
        case 3:
            medirTempo(ordenarPorPrioridade, mochila);
            listar(mochila);
            printf("Pressione Enter para continuar...");
            getchar();
            opcao = 0;
            break;
        case 0:
            printf("Voltando ao menu principal...\n");
            printf("\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (opcao != 0);
}

// --- Menu Principal ---
void menu(Mochila *mochila) {
    int opcao;
    char nome[30];
    char tipo[20];
    int numero;
    int prioridade;

    do {
        printf("\n======================\n");
        printf("== MOCHILA SURVIVAL ==\n");
        printf("======================\n");
        printf("Itens na mochila: %d\n", mochila->quantidade);
        printf("\n1 - Adicionar Item\n");
        printf("2 - Remover Item\n");
        printf("3 - Listar Itens\n");
        printf("4 - Ordenar Mochila\n");
        printf("5 - Buscar Item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("\n");
        limpaBufferEntrada();

        switch (opcao) {
            case 1:
                printf("Digite o nome do item: ");
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Digite o tipo do item (arma, cura, protecao, comida, bebida e etc): ");
                fgets(tipo, 20, stdin);
                tipo[strcspn(tipo, "\n")] = '\0';

                printf("Digite a quantidade do item: ");
                scanf("%d", &numero);
                limpaBufferEntrada(); // limpa o \n deixado pelo scanf

                do {
                    printf("Digite a prioridade do item 1 a 5 (1 = alta a 5 = baixa): ");
                    scanf("%d", &prioridade);

                    if (prioridade < 1 || prioridade > 5) {
                        printf("Prioridade invalida! Digite um valor entre 1 e 5.\n");
                    }
                } while (prioridade < 1 || prioridade > 5);

                limpaBufferEntrada();

                adicionarItem(mochila, nome, tipo, numero, prioridade); // agora passa as variáveis lidas
                listar(mochila);
                printf("Pressione Enter para continuar...");
                getchar();
                break;
            case 2:
                printf("Digite o nome do item a ser removido: ");
                scanf("%s", nome);
                limpaBufferEntrada();
                removerItem(mochila, nome);
                listar(mochila);
                printf("Pressione Enter para continuar...");
                getchar();
                break;
            case 3:
                listar(mochila);
                printf("Pressione Enter para continuar...");
                getchar();
                break;
            case 4:
                menuOrdenar(mochila);
                break;
            case 5:
                if (!mochila->estaOrdenada) {
                    printf("A mochila precisa estar ordenada antes de realizar a busca!\n");
                    printf("\n");
                    printf("Pressione Enter para voltar ao menu...");
                    getchar();
                    continue;
                }
                if (mochila->quantidade == 0) {
                    printf("A mochila esta vazia!\n");
                    printf("\n");
                    printf("Pressione Enter para voltar ao menu...");
                    getchar();
                    continue;
                }
                char chave[50];
                printf("Digite o nome do item a ser buscado: ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = '\0';
                buscarItem(mochila, chave);
                printf("Pressione Enter para continuar...");
                getchar();
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    
    } while (opcao != 0);
}
