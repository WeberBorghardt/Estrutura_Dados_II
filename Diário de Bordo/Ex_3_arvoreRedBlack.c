// WEBER SILVA BORGHARDT

// Ex_3_RedBlack.c

#include <stdio.h>
#include <stdlib.h>

//Denifinção dos possiveis valores de cor para os nós(VERMELHO / PRETO)
#define RED 0  
#define BLACK 1

// Denifinição da estrutura de um nó da árvore Red-Black
struct NO{
  int valor;        //Valor armazenado no nó
  int cor;          //Cor do nó(VERMELHO / PRETO)
  struct NO *esq;   //Ponteiro para o filho esquerdo
  struct NO *dir;   //Ponteiro para o filho direito
  struct NO *pai;    //Ponteiro para o pai do nó
};

typedef struct NO NO;   //Criar um alias 'NO' para 'struct NO'

//Função para criar um novo nó
NO *criarNO(int valor){       
  NO *novoNo = (NO*)malloc(sizeof(NO));  //Alocar memória para um novo nó
  if (novoNo == NULL){
    printf("Erro ao alocar memória para o novo nó.\n");
    exit(1);
  }
  novoNo->valor = valor;    // Define o valor do nó
  novoNo->cor = RED;        // Inicialmente, o nó é vermelho conforme as propriedades da árvore Red-Black
  novoNo->esq = NULL;        // Inicializa os ponteiros para os filhos como NULL
  novoNo->dir = NULL;
  novoNo->pai = NULL;      // Inicializa o ponteiro para o pai como NULL
  return novoNo;      // Retorna o ponteiro para o novo nó criado
}

//Função para fazer a rotação à esquerda em torno do nó 'X'
void rotacaoEsq(NO **raiz, NO *x)
{
  NO *y = x->dir;    // Define 'y' como o filho direito de 'x'
  x->dir = y->esq;  // Transfere a subárvore esquerda de 'y' para a direita de 'x'
  if (y->esq != NULL) // Se 'y' tem uma subárvore esquerda
    y->esq->pai = x;  // Atualiza o pai da subárvore esquerda de 'y' para 'x'
  y->pai = x->pai;    // Atualiza o pai de 'y' para o pai de 'x'
  if (x->pai == NULL)  // Se 'x' é a raiz da árvore
    *raiz = y;       // 'y' se torna a nova raiz
  else if(x == x->pai->esq)  // Se 'x' é o filho esquerdo de seu pai
    x->pai->esq = y;   // 'y' se torna o novo filho esquerdo
  else                  // Se 'x' é o filho direito de seu pai
    x->pai->dir = y;    // 'y' se torna o novo filho direito
  y->esq = x;        // 'x' se torna o filho esquerdo de 'y'
  x->pai = y;        // Atualiza o pai de 'x' para 'y'
    
}

//Função para fazer a rotação à direita em torno do nó 'X'
void rotacaoDir(NO **raiz, NO *x){
  NO *y = x->esq;    // Define 'y' como o filho esquerdo de 'x'
  x->esq = y->dir;   // Transfere a subárvore direita de 'y' para a esquerda de 'x'
  
  if(y->dir != NULL)   // Transfere a subárvore direita de 'y' para a esquerda de 'x'
    y->dir->pai = x;   // Atualiza o pai da subárvore direita de 'y' para 'x'
  y->pai = x->pai;   // Atualiza o pai de 'y' para o pai de 'x'
  
  if(x->pai == NULL)   // Se 'x' é a raiz da árvore
    *raiz = y;        // 'y' se torna a nova raiz
  else if(x == x->pai->dir)  // Se 'x' é o filho direito de seu pai
    x->pai->dir = y;    // 'y' se torna o novo filho direito
  else      // 'y' se torna o novo filho direito
    x->pai->esq = y;  // 'y' se torna o novo filho esquerdo
  y->dir = x;    // 'x' se torna o filho direito de 'y'
  x->pai = y;    // Atualiza o pai de 'x' para 'y'
}

//Função para balancear a árvore após a inserção de um nó
void balacear(NO **raiz, NO *z){
  while (z != *raiz && z->pai->cor == RED){  // Enquanto 'z' não for a raiz e o pai de 'z' for vermelho
    if(z->pai == z->pai->pai->esq){  // Se o pai de 'z' é o filho esquerdo do avô
      NO *y= z->pai->pai->dir;  // Define 'y' como o tio de 'z' (filho direito do avô)

      // Caso 1: O tio de 'z' é vermelho
      if(y != NULL && y->cor == RED){
        z->pai->cor = BLACK;  // Pinta o pai de 'z' de preto
        y->cor = BLACK;       // Pinta o tio de 'z' de preto
        z->pai->pai->cor = RED;// Pinta o avô de 'z' de vermelho
        z = z->pai->pai;  // Move 'z' para o avô e continua o loop
      }
      // Caso 2 e 3: O tio de 'z' é preto
      else{
        if(z == z->pai->dir){  // Se 'z' é o filho direito
          z = z->pai;           // Move 'z' para o pai
          rotacaoEsq(raiz, z);   // Realiza uma rotação à esquerda no novo 'z'
        }
        z->pai->cor = BLACK;  // Pinta o pai de 'z' de preto
        z->pai->pai->cor = RED;// Pinta o avô de 'z' de vermelho
        rotacaoDir(raiz, z->pai->pai); // Realiza uma rotação à direita no avô
      }
    }
    else{ // Simétrico: O pai de 'z' é o filho direito do avô
      NO *y = z->pai->pai->esq;  // Define 'y' como o tio de 'z' (filho esquerdo do avô)


      // Caso 1: O tio de 'z' é vermelho
      if(y != NULL && y->cor == RED){
        z->pai->cor = BLACK;  // Pinta o pai de 'z' de preto
        y->cor = BLACK;  // Pinta o tio de 'z' de preto
        z->pai->pai->cor = RED;  // Pinta o avô de 'z' de vermelho
        z = z->pai->pai; // Move 'z' para o avô e continua o loop
      }
      // Caso 2 e 3: O tio de 'z' é preto 
      else{
        if(z == z->pai->esq) // Se 'z' é o filho esquerdo
        {
          z = z->pai; // Move 'z' para o pai
          rotacaoDir(raiz, z); // Realiza uma rotação à direita no novo 'z'
        }
        z->pai->cor = BLACK;  // Pinta o pai de 'z' de preto
        z->pai->pai->cor = RED;// Pinta o avô de 'z' de vermelho
        rotacaoEsq(raiz, z->pai->pai); // Realiza uma rotação à esquerda no avô
      }
    }
  }
  (*raiz)->cor = BLACK;// Garante que a raiz seja preta
}

//Função para inserir um nó na árvore Red-Black
void inserir(NO **raiz, int valor){
  NO *z = criarNO(valor); // Cria um novo nó 'z' com o valor fornecido
  NO *y = NULL;// 'y' será o pai potencial de 'z'
  NO *x = *raiz;// Inicia a busca a partir da raiz

  // Percorre a árvore para encontrar a posição correta para inserir 'z'
  while(x != NULL){
    y = x;  // Mantém o último nó não nulo visitado
    if(z->valor < x->valor)
      x = x->esq;  // Move para a subárvore esquerda
    else
      x = x->dir;  // Move para a subárvore direita
  }
  z->pai = y;  // Define o pai de 'z' como 'y'
  if(y == NULL)
    *raiz = z;  // Se a árvore estava vazia, 'z' se torna a raiz
  else if(z->valor < y->valor)
    y->esq = z;  // Insere 'z' como filho esquerdo de 'y'
  else
    y->dir = z;  // Insere 'z' como filho direito de 'y'

  balacear(raiz, z); // Balanceia a árvore para manter as propriedades Red-Black
}

//Função auxiliar para encontrar o nó com o valor mínimo a partir de um nó dado
NO *min(NO *x){
  while (x->esq != NULL)
    x = x->esq; // Percorre continuamente para a subárvore esquerda
  return x; // Retorna o nó mais à esquerda
}

//Função auxiliar para encontrar o nó com o valor máximo a partir de um nó
NO *max(NO *x){
  while (x->dir != NULL)
    x = x->dir; // Percorre continuamente para a subárvore direita
  return x;  // Retorna o nó mais à direita
}

// Função auxiliar para substituir um nó 'u' por outro nó 'v' na árvore
void substituir(NO **raiz, NO *u, NO *v){
  if(u->pai == NULL){     // Se 'u' é a raiz
    *raiz = v;        // 'v' se torna a nova raiz
  } 
  else if(u == u->pai->esq){  // Se 'u' é o filho esquerdo de seu pai
    u->pai->esq = v;    // 'v' se torna o novo filho esquerdo
  } 
  else{                 // Se 'u' é o filho direito de seu pai
    u->pai->dir = v;  // 'v' se torna o novo filho direito
  }
  
  if(v != NULL) {    // Se 'v' não é NULL
    v->pai = u->pai;  // Atualiza o pai de 'v' para o pai de 'u'
  }
}

//Função para rebalancear a árvore após a remoçõa de um nó
void balancearRemocao(NO **raiz, NO *x){
  while(x != *raiz && (x == NULL || x->cor == BLACK)){ // Enquanto 'x' não for a raiz e 'x' for preto ou NULL
    if(x == x->pai->esq){  // Se 'x' é o filho esquerdo de seu pai
      NO *w = x->pai->dir;  // Define 'w' como o irmão de 'x'
      // Caso 1: O irmão de 'x' é vermelho
      if(w->cor == RED){
        w->cor = BLACK;    // Pinta o irmão de preto
        x->pai->cor = RED;  // Pinta o pai de vermelho
        rotacaoEsq(raiz, x->pai);   // Realiza uma rotação à esquerda no pai
        w = x->pai->dir;  // Atualiza 'w' para o novo irmão de 'x'
      }

      // Caso 2: Os filhos de 'w' são pretos
      if((w->esq == NULL || w->esq->cor == BLACK) &&
        (w->dir == NULL || w->dir->cor == BLACK)) {
        w->cor = RED;    // Pinta o irmão de vermelho
        x = x->pai;      // Move 'x' para o pai
      } 
      else{  // Caso 3: O irmão de 'x' tem pelo menos um filho vermelho
        if(w->dir == NULL || w->dir->cor == BLACK){  // Se o filho direito de 'w' é preto
          if(w->esq != NULL) 
            w->esq->cor = BLACK; // Pinta o filho esquerdo de 'w' de preto
          w->cor = RED;  // Pinta 'w' de vermelho
          rotacaoDir(raiz, w);  // Realiza uma rotação à direita em 'w'
          w = x->pai->dir;  // Atualiza 'w' para o novo irmão de 'x'
        }
        w->cor = x->pai->cor;  // Pinta 'w' com a cor do pai de 'x'
        x->pai->cor = BLACK;   // Pinta o pai de 'x' de preto
        if(w->dir != NULL)
          w->dir->cor = BLACK;   // Pinta o filho direito de 'w' de preto
        rotacaoEsq(raiz, x->pai);  // Realiza uma rotação à esquerda no pai
        x = *raiz;  // Define 'x' como a raiz para terminar o loop
      }
    } 
    else {  // Simétrico: 'x' é o filho direito de seu pai
      NO *w = x->pai->esq;  // Define 'w' como o irmão de 'x'

       // Caso 1: O irmão de 'x' é vermelho
      if (w->cor == RED){
        w->cor = BLACK;    // Pinta o irmão de preto
        x->pai->cor = RED;  // Pinta o pai de vermelho
        rotacaoDir(raiz, x->pai);  // Realiza uma rotação à direita no pai
        w = x->pai->esq;  // Atualiza 'w' para o novo irmão de 'x'
      }

      // Caso 2: Os filhos de 'w' são pretos
      if((w->dir == NULL || w->dir->cor == BLACK) &&
        (w->esq == NULL || w->esq->cor == BLACK)){
        w->cor = RED;    // Pinta o irmão de vermelho
        x = x->pai;    // Move 'x' para o pai
      } 
      else{  // Caso 3: O irmão de 'x' tem pelo menos um filho vermelho
        if(w->esq == NULL || w->esq->cor == BLACK){  // Se o filho esquerdo de 'w' é preto
          if(w->dir != NULL) 
            w->dir->cor = BLACK;  // Pinta o filho direito de 'w' de preto
          w->cor = RED;  // Pinta 'w' de vermelho
          rotacaoEsq(raiz, w);  // Realiza uma rotação à esquerda em 'w'
          w = x->pai->esq;    // Atualiza 'w' para o novo irmão de 'x'
        }
        w->cor = x->pai->cor;   // Pinta 'w' com a cor do pai de 'x'
        x->pai->cor = BLACK;  // Pinta o pai de 'x' de preto
        if(w->esq != NULL) 
          w->esq->cor = BLACK;  // Pinta o filho esquerdo de 'w' de preto
        rotacaoDir(raiz, x->pai);  // Realiza uma rotação à direita no pai
        x = *raiz;  // Define 'x' como a raiz para terminar o loop
      }
    }
  }
  if (x != NULL){    // Após o loop, se 'x' não for NULL
    x->cor = BLACK;  // Pinta 'x' de preto
  }
}

//Função para remover um nó da árvore Red-Black
void remover(NO **raiz, int valor){
  NO *z = *raiz;  // Inicia a busca a partir da raiz
  NO *x, *y; 

  // Busca pelo nó 'z' que contém o valor a ser removido
  while(z != NULL && z->valor != valor){
    if(valor < z->valor)
      z = z->esq;  // Move para a subárvore esquerda
    else
      z = z->dir;    // Move para a subárvore direita
  }
  if(z == NULL){    // Se o valor não foi encontrado na árvore
    printf("\nValor nao encontrado na arvore!\n");
    printf("---------------------------------\n");
    
    return;
  
  }
  

  y = z;  // 'y' é o nó a ser removido ou seu sucessor
  int yCorOriginal = y->cor;  // Armazena a cor original de 'y'

  if(z->esq == NULL) {    // Caso em que 'z' tem no máximo um filho direito
    x = z->dir;     // 'x' é o filho direito de 'z'
    substituir(raiz, z, z->dir);  // Substitui 'z' por seu filho direito
  } 
  else if(z->dir == NULL){  // Caso em que 'z' tem no máximo um filho esquerdo
    x = z->esq;    // 'x' é o filho esquerdo de 'z'
    substituir(raiz, z, z->esq);  // Substitui 'z' por seu filho esquerdo
  }
  else{    // Caso em que 'z' tem dois filhos
    y = max(z->esq);    // Encontra o predecessor de 'z' (máximo na subárvore esquerda)
    yCorOriginal = y->cor;    // Armazena a cor original de 'y'
    x = y->esq;    // 'x' é o filho esquerdo de 'y'
    
    if(y->pai == z){    // Se 'y' é filho direto de 'z'
      if(x != NULL) 
        x->pai = y;     // Atualiza o pai de 'x' para 'y'
    
    }  else{    // Se 'y' não é filho direto de 'z'
      substituir(raiz, y, y->esq);    // Substitui 'y' por seu filho esquerdo
      y->dir = z->dir;    // Transfere o filho direito de 'z' para 'y'
      y->dir->pai = y;    // Atualiza o pai do filho direito de 'y' para 'y'
    }
    substituir(raiz, z, y);    // Substitui 'z' por 'y'
    y->esq = z->esq;           // Transfere o filho esquerdo de 'z' para 'y'
    y->esq->pai = y;           // Atualiza o pai do filho esquerdo de 'y' para 'y'
    y->cor = z->cor;          // Pinta 'y' com a cor original de 'z'
  }

  free(z);  // Libera a memória ocupada por 'z'

  if(yCorOriginal == BLACK){    // Se a cor original de 'y' era preta, a árvore pode violar as propriedades Red-Black
    balancearRemocao(raiz,x);  // Balanceia a árvore após a remoção
  }

}

// Função para imprimir a árvore Red-Black em ordem (esquerda, raiz, direita)
void inOrder(NO *raiz){
    if (raiz != NULL) {
        inOrder(raiz->esq); // Percorre a subárvore esquerda
        printf("%d => %s\n", raiz->valor, raiz->cor == RED ? "Vermelho" : "Preto");  // Imprime o valor e a cor do nó
        inOrder(raiz->dir);  // Percorre a subárvore direita
    }
}


// Função para imprimir a árvore Red-Black em grafo
void imprimirArvRB(NO *raiz, int nivel){
  if(raiz != NULL)
  {
    //Chama a função recursivamente para percorree a subárvore a direita
    imprimirArvRB(raiz->dir, nivel + 1);

    //Imprime o valor do nó atual com um espaçamento proporcional a sua profundidade
    for(int i = 0; i < nivel; i++)
      printf("     "); // espaços entre nível
    
    // Imprime o valor do nó com a cor apropriada (vermelho ou preto)
    if(raiz->cor == 0)
      printf("\033[31m%d\033[0m\n\n", raiz->valor);  // Nó vermelho em vermelho
    else
      printf("%d\n\n", raiz->valor); // Nó preto em cor padrão

    // Chama a funçao recursivamente para percorrer a subárvore a esquerda
    imprimirArvRB(raiz->esq, nivel +1);
  }
}

// Função principal que demonstra a utilização da árvore Red-Black
int main(){
  struct NO *raiz = NULL; // Inicializa a árvore vazia

  // Inserção de vários valores na árvore Red-Black
  inserir(&raiz,12);
  inserir(&raiz,31);
  inserir(&raiz,20);
  inserir(&raiz,17);
  inserir(&raiz,11);
  inserir(&raiz,8);
  inserir(&raiz,3);
  inserir(&raiz,24);
  inserir(&raiz,15);
  inserir(&raiz,33);
  
  // Impressão da árvore Red-Black em formato de grafo
  printf("Árvore Red-Black:\n");
  printf("-----------------\n");
  imprimirArvRB(raiz, 0);
  printf("\n");

  // Impressão da árvore Red-Black em ordem
  printf("Árvore em ordem:\n");
  printf("----------------\n");
  inOrder(raiz);

  //Remover o nó com valor 20
  printf("----------------\n");
  printf("\n----------------------------\n");
  printf("Removendo o nó com valor 20 ...\n");
  printf("----------------------------\n");
  remover(&raiz, 20);

  // Impressão da árvore Red-Black após a remoção
  printf("\nÁrvore Red-Black após a remoção:\n");
  printf("--------------------------------\n");  
  imprimirArvRB(raiz,0);
  printf("---------------------------------\n");
  printf("\nÁrvore em ordem após a remoção:\n");
  printf("---------------------------------\n");
  inOrder(raiz);

  
  return 0;
}
