// Weber Silva Borghardt

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Estrutura do Nó da Treap
typedef struct No {
    int chave;
    int prioridade;
    struct No *esq;
    struct No *dir;
} No;

// Função para criar um novo nó
No* criarNo(int chave) {
    No* no = (No*)malloc(sizeof(No));
    no->chave = chave;
    no->prioridade = rand() % 100;  // Prioridade aleatória
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

// Função rotação à direita
No* rotacaoDireita(No* y) {
    No* x = y->esq;
    y->esq = x->dir;
    x->dir = y;
    return x;
}

// Função rotação à esquerda
No* rotacaoEsquerda(No* x) {
    No* y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    return y;
}

// Função para inserir um nó na Treap
No* inserirNo(No* raiz, int chave) {
    if (raiz == NULL) {
        return criarNo(chave);
    }
    if (chave < raiz->chave) {
        raiz->esq = inserirNo(raiz->esq, chave);
        if (raiz->esq->prioridade > raiz->prioridade) {
            raiz = rotacaoDireita(raiz);
        }
    } else if (chave > raiz->chave) {
        raiz->dir = inserirNo(raiz->dir, chave);
        if (raiz->dir->prioridade > raiz->prioridade) {
            raiz = rotacaoEsquerda(raiz);
        }
    }
    return raiz;
}

// Função para buscar um nó na Treap
No* buscarNo(No* raiz, int chave) {
    while (raiz != NULL) {
        if (chave == raiz->chave) {
            return raiz;
        } else if (chave < raiz->chave) {
            raiz = raiz->esq;
        } else {
            raiz = raiz->dir;
        }
    }
    return NULL;
}

// Função para remover um nó da Treap
No* removerNo(No* raiz, int chave) {
    if (raiz == NULL) {
        return NULL;
    }
    if (chave < raiz->chave) {
        raiz->esq = removerNo(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        raiz->dir = removerNo(raiz->dir, chave);
    } else {
        // Encontrou o nó a ser removido
        if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            free(raiz);
            return temp;
        } else {
            // Se tem dois filhos, rotaciona para manter a propriedade da Treap
            if (raiz->esq->prioridade > raiz->dir->prioridade) {
                raiz = rotacaoDireita(raiz);
                raiz->dir = removerNo(raiz->dir, chave);
            } else {
                raiz = rotacaoEsquerda(raiz);
                raiz->esq = removerNo(raiz->esq, chave);
            }
        }
    }
    return raiz;
}

// Função para percorrer a Treap em Ordem
void percorrerEmOrdem(No* raiz) {
    if (raiz == NULL) return;
    percorrerEmOrdem(raiz->esq);
    printf(" [%d(%d)] ", raiz->chave, raiz->prioridade);
    percorrerEmOrdem(raiz->dir);
}

// Função para exibir a Treap no formato visual de árvore (Sedgewick)
void exibirTreap(No* raiz, int profundidade) {
    if (raiz == NULL) return;
    exibirTreap(raiz->dir, profundidade + 1);

    for (int i = 0; i < profundidade; i++) {
        printf("   ");
    }
    printf("%d(%d) \n", raiz->chave, raiz->prioridade);

    exibirTreap(raiz->esq, profundidade + 1);
}

// Função principal
int main() {
    srand(time(0));
    No* raiz = NULL;
    int elementos[] = {50, 30, 20, 40, 70, 60, 80};
    int n = sizeof(elementos) / sizeof(elementos[0]);

    // Inserção de elementos na Treap
    for (int i = 0; i < n; i++) {
        raiz = inserirNo(raiz, elementos[i]);
    }

    // Imprimir a Treap em ordem
    printf("Treap em ordem e sua prioridade: \n");
    percorrerEmOrdem(raiz);
    printf("\n\n");

    // Exibir a Treap no formato visual de árvore Sedgewick
    printf("Treap visual (Formato Sedgewick): \n");
    exibirTreap(raiz, 0);

    // Teste de busca
    int chave = 40;
    No* resultado = buscarNo(raiz, chave);
    if (resultado != NULL) {
        printf("\nElemento %d encontrado na Treap.\n", chave);
    } else {
        printf("\nElemento %d não encontrado na Treap.\n", chave);
    }

    // Teste de remoção
    printf("\nRemovendo o elemento %d \n", chave);
    raiz = removerNo(raiz, chave);

    // Imprimir a Treap em ordem após a remoção
    printf("\nPercorrendo a Treap em ordem após a remoção: \n");
    percorrerEmOrdem(raiz);
    printf("\n\n");

    // Exibir a Treap no formato visual de árvore Sedgewick
    printf("Treap visual (Formato Sedgewick): \n");
    exibirTreap(raiz, 0);

    return 0;
}
