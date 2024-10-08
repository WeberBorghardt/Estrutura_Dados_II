#include <stdio.h>
#include <stdlib.h>

struct noAVL {
    int valor;
    struct noAVL *esq;
    struct noAVL *dir;
    int altura;
};

/*
    Função que cria um novo nó
    x -> valor a ser inserido no nó
    Retorna o endereço do nó criado
 */
struct noAVL *criarNo(int x) {
    struct noAVL *novoNo = (struct noAVL *)malloc(sizeof(struct noAVL));

    if (novoNo) {
        novoNo->valor = x;
        novoNo->esq = NULL;
        novoNo->dir = NULL;
        novoNo->altura = 0;
    } else {
        printf("\nErro ao alocar nó em memoria!\n");
    }
    return novoNo;
}

// Função que retorna o maior valor entre dois valores a,b -> altura de dois nós da árvore
int maior(int a, int b) {
    return (a > b) ? a : b;
}

// Função que retorna a altura de um nó ou -1 caso ele seja null
int alturaNo(struct noAVL *no) {
    if (no == NULL)
        return -1;
    else
        return no->altura;
}

// Função para calcular o fator de balanceamento de um nó
int fatorBalanceamento(struct noAVL *no) {
    if (no)
        return (alturaNo(no->esq) - alturaNo(no->dir));
    else
        return 0;
}

// ------Rotações --------//

// Função para a rotação à esquerda
struct noAVL *rotacaoEsquerda(struct noAVL *r) {
    struct noAVL *y, *f;

    y = r->dir;
    f = y->esq;

    y->esq = r;
    r->dir = f;

    r->altura = maior(alturaNo(r->esq), alturaNo(r->dir)) + 1;
    y->altura = maior(alturaNo(y->esq), alturaNo(y->dir)) + 1;

    return y;
}

// Função para rotacionar à direita
struct noAVL *rotacaoDireita(struct noAVL *r) {
    struct noAVL *y, *f;

    y = r->esq;
    f = y->dir;

    y->dir = r;
    r->esq = f;

    r->altura = maior(alturaNo(r->esq), alturaNo(r->dir)) + 1;
    y->altura = maior(alturaNo(y->esq), alturaNo(y->dir)) + 1;

    return y;
}

// Função para rotacionar à esquerda-direita
struct noAVL *rotacaoEsquerdaDireita(struct noAVL *r) {
    r->esq = rotacaoEsquerda(r->esq);
    return rotacaoDireita(r);
}

// Função para rotacionar à direita-esquerda
struct noAVL *rotacaoDireitaEsquerda(struct noAVL *r) {
    r->dir = rotacaoDireita(r->dir);
    return rotacaoEsquerda(r);
}

/* Função para realizar o balanceamento da árvore após uma inserção ou remoção
Recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento
*/
struct noAVL *balancear(struct noAVL *raiz) {
    int fb = fatorBalanceamento(raiz);

    // Rotação à esquerda
    if (fb < -1 && fatorBalanceamento(raiz->dir) <= 0)
        raiz = rotacaoEsquerda(raiz);

    // Rotação à direita
    else if (fb > 1 && fatorBalanceamento(raiz->esq) >= 0)
        raiz = rotacaoDireita(raiz);

    // Rotação dupla à esquerda
    else if (fb > 1 && fatorBalanceamento(raiz->esq) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

    // Rotação dupla à direita
    else if (fb < -1 && fatorBalanceamento(raiz->dir) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}

/* Função para inserir um novo nó na árvore AVL
raiz -> raiz da árvore AVL
x -> valor a ser inserido na árvore
Retorno: endereço do novo nó ou nova raiz após o balanceamento
*/
struct noAVL *inserir(struct noAVL *raiz, int x) {
    if (raiz == NULL) // árvore vazia
        return criarNo(x);
    else { // inserção será à esquerda ou à direita
        if (x < raiz->valor)
            raiz->esq = inserir(raiz->esq, x);
        else if (x > raiz->valor)
            raiz->dir = inserir(raiz->dir, x);
        else
            printf("\nInsercao nao realizada!\nO elemento %d já existe!\n", x);
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;

    // Verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);

    return raiz;
}

/* Função para remover um nó da árvore AVL */
struct noAVL *remover(struct noAVL *raiz, int chave) {
    if (raiz == NULL) {
        printf("Valor nao encontrado!\n");
        return NULL;
    } else { // procura o nó a remover
        if (raiz->valor == chave) {
            // remove nós folhas (nós sem filhos)
            if (raiz->esq == NULL && raiz->dir == NULL) {
                free(raiz);
                printf("Elemento folha removido: %d \n", chave);
                return NULL;
            } else {
                // remover nós que possuem 2 filhos
                if (raiz->esq != NULL && raiz->dir != NULL) {
                    struct noAVL *aux = raiz->esq;
                    while (aux->dir != NULL)
                        aux = aux->dir;
                    raiz->valor = aux->valor;
                    aux->valor = chave;
                    printf("Elemento trocado: %d \n", chave);
                    raiz->esq = remover(raiz->esq, chave);
                    return raiz;
                } else {
                    // remover nós que possuem apenas 1 filho
                    struct noAVL *aux;
                    if (raiz->esq != NULL)
                        aux = raiz->esq;
                    else
                        aux = raiz->dir;
                    free(raiz);
                    printf("Elemento com 1 filho removido: %d \n", chave);
                    return aux;
                }
            }
        } else {
            if (chave < raiz->valor)
                raiz->esq = remover(raiz->esq, chave);
            else
                raiz->dir = remover(raiz->dir, chave);
        }

        // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;

        // Verifica a necessidade de rebalancear a árvore
        raiz = balancear(raiz);

        return raiz;
    }
}

// Função para imprimir a árvore AVL
void imprimir(struct noAVL *raiz, int nivel) {
    int i;
    if (raiz) {
        imprimir(raiz->dir, nivel + 1);
        printf("\n\n");

        for (i = 0; i < nivel; i++)
            printf("\t");

        printf("%d", raiz->valor);
        imprimir(raiz->esq, nivel + 1);
    }
}




int main() {
    int opcao, valor;
    struct noAVL *raiz = NULL;

     
    do {
        printf("\n\n\n------------------------MENU------------------------\n");
        printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\n");
        scanf("%d", &opcao);
        printf("\n---------------------------------------------------\n\n");
            

        switch (opcao) {
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            printf("\tDigite o valor a ser inserido: ");
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);  
            break;
        case 2:
            printf("\tDigite o valor a ser removido: ");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;
        case 3:
            imprimir(raiz, 1);
            break;
        default:
            printf("\nOpcao invalida!\n");
         }
    } while (opcao != 0);
        
        
    return 0;
}
