#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

/*
-------------------------------------------------------------------------------------------------------------------------------
PROJEIO: MOCHILA SURVIVAL
OBJETIVO: Implementar uma Mochila de um jogo survival para adicionar itens a ela, citando o nome e o tipo do item.

-------------------------------------------------------------------------------------------------------------------------------
*/

// Estrutura que representa um item
typedef struct Item {
    char nome[30];
    char tipo[20];
    int numero; // quantidade do item
} Item;

// Estrutura que representa a mochila
typedef struct Mochila {
    struct Item itens[10]; // até 10 tipos de itens
    int quantidade; // quantos tipos de itens foram adicionados
} Mochila;

//Funções da lista estática da mochila

// Está função prepara a lista para ser usada.
// Ela simplesmente defiine o contador quantidade para 0, indicando que a lista está vazia.
// Recebemos um ponteiro(*lista) para modificar a variável original passada pela função.
void inicializarMochila(Mochila *mochila);

void limpaBufferEntrada();
void adicionarItem(Mochila *mochila, const char* nome, const char* tipo, int numero);
void removerItem(Mochila *mochila, const char* nome);
void listar(const Mochila *mochila);
void buscarItem(const Mochila *mochila, const char* nome);
void menu();

// Função principal
int main() {
    Mochila mochila;
    inicializarMochila(&mochila);
    menu(&mochila);
    return 0;
}

// Funções da lista estática da mochila

// Função para inicializar a mochila vazia
void inicializarMochila(Mochila *mochila) {
    mochila->quantidade = 0;
}

// Função para adicionar um item a mochila
void adicionarItem(Mochila *mochila, const char* nome, const char* tipo, int numero) {
    if (mochila->quantidade == 10) {
        printf("A mochila esta cheia!\n");
        return;
    }
    strcpy(mochila->itens[mochila->quantidade].nome, nome);
    strcpy(mochila->itens[mochila->quantidade].tipo, tipo);
    // Adiciona a quantidade de itens na mochila
    mochila->itens[mochila->quantidade].numero = numero;
    mochila->quantidade++;

     // Ordena os itens por nome (Bubble Sort simples)
    for (int i = 0; i < mochila->quantidade - 1; i++) {
        for (int j = i + 1; j < mochila->quantidade; j++) {
            if (strcmp(mochila->itens[i].nome, mochila->itens[j].nome) > 0) {
                Item temp = mochila->itens[i];
                mochila->itens[i] = mochila->itens[j];
                mochila->itens[j] = temp;
            }
        }
    }

    printf("Item \"%s\" (Tipo: %s, Quantidade: %d) adicionado com sucesso!\n", nome, tipo, numero);
    printf("\n");
}

// Função para remover item da mochila
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

    printf("Item \"%s\" removido com sucesso!\n", nome);
    printf("\n");
}

// Função para listar os itens da mochila
void listar(const Mochila *mochila) {
    if (mochila->quantidade == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }
    printf("==================== ITENS NA MOCHILA (%d/10) ===================\n", mochila->quantidade);
    printf("================================================================\n");
    for (int i = 0; i < mochila->quantidade; i++) {
        printf("%d. Nome: %s          | Tipo: %s          | Quantidade: %d\n", i + 1, mochila->itens[i].nome, mochila->itens[i].tipo, mochila->itens[i].numero);
    }
    printf("================================================================\n");
    printf("\n");
    printf("Pressione Enter para continuar...");
    getchar();
}



void buscarItem(const Mochila *mochila, const char* nome) {
    int inicio = 0;
    int fim = mochila->quantidade - 1;
    int meio;

    // O laço continua enquanto a sub-lista for válida (início não ultrapassou o fim).
    while (inicio <= fim) {
        // Calcula o índice do meio.
        // Usar inicio + (fim - inicio) / 2 evita overflow para listas muito grandes.
        meio = inicio + (fim - inicio) / 2;

        // Compara a string do meio com o item procurado.
        int comparacao = strcmp(mochila->itens[meio].nome, nome);

        if (comparacao == 0) { // Encontrou!
            printf("Item encontrado: %s (Tipo: %s, Quantidade: %d)\n", mochila->itens[meio].nome, mochila->itens[meio].tipo, mochila->itens[meio].numero);
            return;
        }
        else if (comparacao > 0) {
            // O item do meio vem DEPOIS do item procurado
            // Portanto o item só pode estar na metade esquerda da lista.
            // Descartamos a metade direita ajustando o Fim
            fim = meio - 1;
        }
                else { // comparacao < 0
            // O item do meio vem ANTES do item procurado
            // Portanto, o item só pode estar na metade direita.
            // Descartamos a metade esquerda, ajustando o 'inicio'.
            inicio = meio + 1;
        }
    }
    // Se o laço while terminar, significa que o inicio ultrapassou o fim, o espaço de busca se esgotou e o item n foi encontrado
    printf("Item \"%s\" nao encontrado na mochila!\n", nome);
}


// --- Limpa o buffer do teclado ---
void limpaBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menu(Mochila *mochila) {
    int opcao;
    char nome[30];
    char tipo[20];
    int numero;

    do {
        printf("\n================================================================\n");
        printf("======================= MOCHILA SURVIVAL =======================\n");
        printf("================================================================\n");
        printf("Itens na mochila: %d\n", mochila->quantidade);
        printf("\n1 - Adicionar Item\n");
        printf("2 - Remover Item\n");
        printf("3 - Listar Itens\n");
        printf("4 - Buscar Item\n");
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

                printf("Digite o tipo do item: ");
                fgets(tipo, 20, stdin);
                tipo[strcspn(tipo, "\n")] = '\0';

                printf("Digite a quantidade do item: ");
                scanf("%d", &numero);
                limpaBufferEntrada(); // limpa o \n deixado pelo scanf

                adicionarItem(mochila, nome, tipo, numero); // agora passa as variáveis lidas
                listar(mochila);
                break;
            case 2:
                printf("Digite o nome do item a ser removido: ");
                scanf("%s", nome);
                limpaBufferEntrada();
                removerItem(mochila, nome);
                listar(mochila);
                break;
            case 3:
                listar(mochila);
                break;
            case 4:
                printf("Digite o nome do item a ser buscado: ");
                scanf("%s", nome);
                limpaBufferEntrada();
                printf("\n");
                buscarItem(mochila, nome);
                printf("\n");
                listar(mochila);
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