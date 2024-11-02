// Weber Silva Borghardt

#include <stdio.h>
#include <stdlib.h>

#define MAX 3 //Numero maximo de elementos
#define MIM 2 //Numero minimo de elementos

//Estrutura para um nó da árvore B
struct NoBtree {
int val[MAX + 1];
int contagem;  //Chaves e contagem das chaves
struct NoBtree *link[MAX + 1]; //Ponteiros para os filhos
};

//Raiz da árvore B
struct NoBtree *raiz = NULL;  // OBS.;

//Função para criar um novo nó da árvore B
struct NoBtree *criarNo(int val, struct NoBtree *filho){
    struct NoBtree *novoNo = (struct NoBtree*)malloc(sizeof(struct NoBtree));
    novoNo->val[1] = val; // Atribui o valor ao novo nó
    novoNo->contagem = 1; // Inicializa a contagem de chaves
    novoNo->link[0] = raiz; // O primeiro link aponta para raiz
    novoNo->link[1] = filho; //o segundo link aponta para o filho    
    return novoNo;
}

//Função para inserir um valor e um nó
void inserirNo(int val, int pos, struct NoBtree *no, struct NoBtree *filho){
    int j = no->contagem;
    while (j > pos) {
        //Move as chaves e links para a direita
        no->val[j + 1] = no->val[j];
        no->link[j + 1] = no->link[j];
        j--;
    }
    no->val[j + 1] = val;     // Insere a nova chave
    no->link[j + 1] = filho;  // Insere o novo filho 
    no->contagem++;           // Atualiza a contagem de chaves
}

//Função para dividir um nó
void dividirNo(int val, int *pval, int pos, struct NoBtree *no, struct NoBtree *filho, struct NoBtree **novoNo){
    int media = (MAX + 1) /2; // Determina o índice da mediana
    int j = media + 1;

    //Cria um novo nó
    *novoNo = (struct NoBtree*)malloc(sizeof(struct NoBtree));
    while (j <= MAX) {
        (*novoNo)->val[j - media] = no->val[j];    //Move as chaves para o novo nó
        (*novoNo)->link[j - media] = no->link[j];  //Move os links para o novo nó
        j++;
    }
    no->contagem = media;  //Atualiza a contagem do nó original
    (*novoNo)->contagem = MAX - media;    //Atualiza a contagem do novo nó

    //Insere o valor na posição correta
    if (pos <= MIM){
        inserirNo(val, pos, no, filho);
    } else{
        inserirNo(val, pos - media, *novoNo, filho);
    }
    *pval = no->val[no->contagem];  //Atribui o valor da media a pval
    (*novoNo)->link[0] = no->link[no->contagem];    //Ajusta o link do novo nó
    no->contagem--;                //Decrementa a contagem do nó original
}

//Função auxiliar para inserir um valor na árvore B
int definirValor(int val, int *pval,struct NoBtree *no, struct NoBtree **filho){
    int pos;
    if (!no) {        //se o nó for nulo, atribui o valor e retorna 
        *pval = val;
        *filho = NULL;
        return 1;
    }

    //Determina a posição onde o valor deve ser inserido
    if (val < no->val[1]) {
        pos = 0;
    } else {
        for (pos = no->contagem; (val < no->val[pos] && pos > 1); 
            pos--);
        if (val == no->val[pos]) {    //Verifica se o valor já existe
            printf("Valor duplicado não permitido\n");
            return 0; // Não permite valores duplicados
        }
    }
    //chama recursivamente para inserir o valor no nó
    if (definirValor(val, pval, no->link[pos], filho)){
        if (no->contagem < MAX) {
            inserirNo(*pval, pos, no, *filho);
        } else {
            dividirNo(*pval, pval, pos, no, *filho, filho);
            return 1;     // Retorna 1 se o nó foi dividido
        }
    }
    return 0;
}

// Função para inserir um valor na árvore B
void inserir(int val){
    int flag, i;
    struct NoBtree *filho;

    flag = definirValor(val, &i, raiz, &filho);  //chama a função auxiliar
    if (flag) raiz = criarNo(i,filho);  //Se houve insersão, cria nova raiz 
}

// Função para buscar valor na arvore B
void buscar(int val, int *pos, struct NoBtree *no){
    if (!no) {
        printf("Valor não encontrado\n");
        return;
    }

    //Determina a posição para buscar
    if (val < no->val[1]){
        *pos = 0;
    } else {
        for (*pos = no->contagem; (val < no->val[*pos] && *pos > 1);
            (*pos)--);
        if (val == no->val[*pos]){        // Se valor foi encontrado
            printf("%d encontrado\n", val);
            return ;
        }
    }
    buscar(val, pos, no->link[*pos]);    // Busca recursivamente no filho
}

// Função para percorrer a arvore para impreção em ordem
void percorrer(struct NoBtree *no){
    int i;
    if (no){
        for (i = 0; i < no->contagem; i++){
            percorrer(no->link[i]);    //Chama recursivamente para imprimir filho
            printf("[%d]", no->val[i + 1]);    //Imprime o valor
        }
        percorrer(no->link[i]);    //Chama para o ultimo filho
    }
}

//Função para remover um valor da arvore B
void removerValor(struct NoBtree *no, int val){
    int i;
    for (i = 0; i < no->contagem && no->val[i +1] < val; i++);  //Encontra a posição

    if (no->val[i + 1] == val) {    //Se o valor for encontrado
        if(no->link[i] == NULL) {    //Se não houver filho
            for (int j = i + 1; j < no->contagem; j++)
                no->val[j] = no->val[j + 1]; //Move os valores para a esquerda
            no->contagem--;    //Decrementa a contagem
        } else {
            printf("Remoção em nó interno não implementado\n");  //Não implementado
        }
    } else if (no->link[i]){
        removerValor(no->link[i], val);    //Busca recursivamente no filho
    } 
}

//Função para exibir a arvore B no formato Sedgewick
void exibirArvore(struct NoBtree *no, int profundidade) {
    if (no) {
        for (int i = no->contagem; i >= 1; i--) {
            exibirArvore(no->link[i], profundidade + 1); // Chama recursivamente para imprimir o filho
            for (int j = 0; j < profundidade; j++)       // Identação para cada nível
                printf("    ");
            printf("%d\n", no->val[i]);                  // Imprime o valor
        }
        exibirArvore(no->link[0], profundidade + 1);     // Chama para o último filho
    }
}

//Função principal
int main() {
    int val, pos;

    //Inserindo valores na arvore
    inserir(11);
    inserir(22);
    inserir(6);
    inserir(7);
    inserir(13);
    inserir(31);

    printf("Árvore B em ordem:\n");
    percorrer(raiz); //Imprime arvore em ordem
    printf("\n");

    printf("\nÁrvore B no fromato Sedgewick:\n");
    exibirArvore(raiz, 0);  //Imprime arvore no formato Sedgewick
    printf("\n");
    
    printf("\nBuscando valor 6...\n");
    buscar(6, &pos, raiz); //Busca o valor 6

    printf("\nRemovendo valor 13...\n");
    removerValor(raiz, 13); //Remove o valor 12

    printf("\nÁrvore B após a remoção do %d:\n", 13);
    percorrer(raiz); //Imprime arvore em ordem
    printf("\n");

    printf("\nÁrvore B no formato Sedgewick após a remoção do %d:\n\n", 13);
    exibirArvore(raiz, 0);  

    
    return 0;
}
