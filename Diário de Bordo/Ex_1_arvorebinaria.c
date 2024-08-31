// Nome: WEBER SILVA BORGHARDT

#include <stdio.h>
#include <stdlib.h>

//Definição da estrutura de um nó na árvore binária
struct No {
    int dado;           //Dado armazenado no nó
    struct No* esq;     //Ponteiro para o nó filho da esquerda
    struct No* dir;     //Ponteiro para o nó filho da direita
};

//Função para criar um novo nó com valor especificado
struct No* criarNo(int dado){
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));  //Alocar a memória para um novo nó
    novoNo->dado = dado;    //Atribuir um valor ao nó
    novoNo->esq = NULL;     //Inicializa o filho a esquerda como NULL
    novoNo->dir = NULL;     //Inicializa o filho a direita como NULL
}

//Função para inserir um valor na árvore
struct No* inserir(struct No* raiz, int valor){
    if (raiz == NULL){          //Caso a raiz estiver vazia, um nó sera criado e retorna com nova raiz
        return criarNo(valor);
    }
    
    //Caso contrário o nó será inserido na suarvore correta
    if (valor < raiz->dado){
        raiz->esq = inserir(raiz->esq, valor);
    }
    else if (valor > raiz->dado){
        raiz->dir = inserir(raiz->dir, valor);
    }
    return raiz;    //Retorna o ponteiro para raiz
}

//Função para Pesquisar um elemento na subarvore
struct No* pesquisar(struct No* raiz, int valor){
    //Verificar se a raiz está vazia ou valor encontrado
    if (raiz == NULL || raiz->dado == valor){
        return raiz;
    }
    //Se valor for menor que a raiz, a busca será feita na subarvore á esquerda
    if (valor < raiz->dado){
        return pesquisar(raiz->esq, valor);
    }
    //Se valor for maior busca na arvore a direita
    return pesquisar(raiz->dir, valor);
}

//Função para encontrar o nó com menor valor ( é necessário para excluir )
struct No* menorValor(struct No* no){
    struct No* atual = no;
    //percorre a subárvore a esquerda até encontrar o nó mais a esquerda
    while (atual && atual->esq != NULL){
        atual = atual->esq;
    }
    return atual;
}

//Função para remover um valor da árvore
struct No* excluir(struct No* raiz, int valor){
    //Verificar se a árvore está vazia
    if (raiz == NULL){
        return raiz;
    }
    //Se o valor para excluir for menor que o valor da raiz, procura na subárvore a esquerda
    if (valor < raiz->dado){
        raiz->esq = excluir(raiz->esq, valor);
    }
    //Caso o valor for maior, procura na subárvore a direita
    else if (valor > raiz->dado){
        raiz->dir = excluir(raiz->dir, valor);
    }
    //Se valor for igual a raiz, este será o nó a ser excluido
    else{
        //No com um filhos
        if (raiz->esq == NULL){
            struct No* temp = raiz->dir;
            free(raiz);
            return temp;
        }
        else if (raiz->dir == NULL){
            struct No* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        //Nó com dois filhos
        struct No* temp = menorValor(raiz->dir);
        //Substituir o valor da raiz pelo valor do sucessor
        raiz->dado = temp->dado;
        
        //Excluir o sucessor
        raiz->dir = excluir(raiz->dir, temp->dado);
    }
    return raiz;
}

//Função para imprimir a árvore em Grafo
void imprimirArvore(struct No *raiz, int nivel){
    if (raiz == NULL){
        return;
    }
    imprimirArvore(raiz->dir, nivel + 1);
    for (int i = 0; i < nivel; i++){
        printf("    ");    
    }
    printf("%d\n", raiz->dado);
    imprimirArvore(raiz->esq, nivel + 1);
}



//Função principal
int main(){
    struct No* raiz = NULL;
    
    raiz = inserir(raiz,5);
    raiz = inserir(raiz,3);
    raiz = inserir(raiz,7);
    raiz = inserir(raiz,2);
    raiz = inserir(raiz,4);
    raiz = inserir(raiz,6);
    raiz = inserir(raiz,8);
    
    //Mostrar a árvore em forma de Grafo
    printf("Árvore Binária em forma de grafo:\n");
    imprimirArvore(raiz,0);
    printf("\n--------------------------------------------\n");
    
    //Pesquisar um elemento na Árvore
    struct No* encontrar = pesquisar(raiz, 7);
    if (encontrar != 0) {
        printf("Elemento [ %d ] encontrado na árvore.\n", encontrar->dado);
    }else{
        printf("Elemento não encontrado\n");
    }
    printf("--------------------------------------------\n");
    
    //Excluir um elemento da árvore
    raiz = excluir(raiz,3);
    printf("\n");
    printf("Árvore binária após a exclusão do elemento:\n");
    imprimirArvore(raiz,0);
    
    
    return 0;

}
