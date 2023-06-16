/* 
 * Implementa o TAD Lista Ordenada
 * Feito em C para a disciplina CI1001 - Programacao 1 
 *
 * Versao 1.0.0 23/05/2023
 */

/*
 * A  Lista ordenada eh uma lista que armazena dados ordenados pelo membro
 * chave do tipo ponteiro para elemento_t. 
 * A diferenca para a implementacao da Pilha e da Fila eh que ao invez
 * do nodo conter um int, ele contem um apontador para uma struct
 * que contem um int.
*/

/*
 * elemento_t possui o campo chave, quem sabe pode ter mais coisas depois
*/
typedef struct elemento {
    int chave;  /* chave da struct */
    /* pode ter mais campos, mas a chave sera usada sempre nas operacoes */
} elemento_t;

/*
 * nodo_t eh uma estrutura interna que representa cada nodo da Lista.
 * Cada nodo aponta para o proximo e tambem para o anterior.
 * Externamente o usuario da biblioteca nao vai poder usa-la, pois
 * nao pode ter acesso direto ao ponteiro prox.
*/
typedef struct nodo {
    elemento_t *elemento;
    struct nodo *prox;
    struct nodo *prev;
} nodo_t;

/*
 * Representacao da Lista 
*/
typedef struct lista {
    nodo_t *ini;
} lista_t;

/* 
 * Cria uma Lista vazia 
*/
lista_t *lista_cria ();

/* Retorna 1 se a lista esta vazia e 0 caso contrario */
int lista_vazia (lista_t *l);

/* 
 * Cria um elemento 
*/
elemento_t *elemento_cria (int dado);

/* 
 * Destroi a Lista e a aponta para NULL
*/ 
void lista_destroi (lista_t **l);

/* 
 * Destroi um elemento e o aponta para null
*/ 
void elemento_destroi(elemento_t **elemento);

/* 
 * Adiciona um elemento em ordem de acordo com o valor elemento->chave na Lista. 
 * Retorna 1 em caso de sucesso e 0 caso contrario.
*/
int lista_insere_ordenado (lista_t *l, elemento_t *elemento);

/* 
 * Retira o elemento da Lista e a mantem em ordem.
 * Retorna 1 em caso de sucesso e 0 caso elemento nao esteja na Lista.
*/
int lista_remove_ordenado (lista_t *l, elemento_t *elemento);

/* 
 * Busca o elemento na Lista sem inserir ou remover.
 * Retorna 1 caso o elemento exista e 0 se não existir na Lista.
*/
int lista_search_ordenado (lista_t *l, elemento_t *elemento);
