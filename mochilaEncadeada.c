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
    struct Item *prox; // ponteiro para o próximo item
} Item;

// Estrutura que representa a mochila
typedef struct Mochila {
    Item *inicio; // ponteiro para o primeiro item
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
    mochila->inicio = NULL;
    mochila->quantidade = 0;
}

// Função para adicionar um item a mochila
void adicionarItem(Mochila *mochila, const char* nome, const char* tipo, int numero) {
    Item *novo = (Item *) malloc(sizeof(Item));

    if (!novo) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    strcpy(novo->nome, nome);
    strcpy(novo->tipo, tipo);
    novo->numero = numero;

    // insere no início da lista
    novo->prox = mochila->inicio;
    mochila->inicio = novo;
    mochila->quantidade++;

    printf("Item \"%s\" (Tipo: %s, Quantidade: %d) adicionado com sucesso!\n", nome, tipo, numero);
    printf("\n");
}

// Função para remover item da mochila
void removerItem(Mochila *mochila, const char* nome) {
    if (mochila->inicio == NULL) {
        return;
    }

    // Procura o item na lista
    Item *atual = mochila->inicio;
    Item *anterior = NULL;
    
    // Encontra o item
    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Erro: Item \"%s\" não encontrado na mochila!\n", nome);
        printf("\n");
        return;
    }

    if (anterior == NULL) {
        mochila->inicio = atual->prox; // remove o primeiro
    } else {
        anterior->prox = atual->prox; // pula o item atual
    }

    // Libera memória
    free(atual);
    mochila->quantidade--;

    printf("Item \"%s\" removido com sucesso!\n", nome);
    printf("\n");
}

// Função para listar os itens da mochila
void listar(const Mochila *mochila) {
    if (mochila->inicio == NULL) {
        printf("A mochila está vazia!\n");
        return;
    }

    printf("==================== ITENS NA MOCHILA (%d/10) ===================\n", mochila->quantidade);
    printf("================================================================\n");
    Item *atual = mochila->inicio;
    int i = 1;

    while (atual != NULL) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",i++, atual->nome, atual->tipo, atual->numero);
        atual = atual->prox;
    }

    printf("================================================================\n\n");
    printf("Pressione Enter para continuar...");
    getchar();
}



void buscarItem(const Mochila *mochila, const char* nome) {
    int comparacoes = 0;
    Item *atual = mochila->inicio;

    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->nome, nome) == 0) {
            printf("Item encontrado: %s (Tipo: %s, Quantidade: %d)\n", atual->nome, atual->tipo, atual->numero);
            printf("Foram feitas %d comparações para encontrar o item.\n", comparacoes);
            return;
        }
        atual = atual->prox;
    }

    printf("Item \"%s\" não encontrado na mochila!\n", nome);
}

// --- Limpa o buffer do teclado ---
void limpaBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menu(Mochila *mochila) {
    int opcao = -1;
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
        limpaBufferEntrada();
        printf("\n");

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