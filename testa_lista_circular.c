#include <stdio.h>
#include <stdlib.h>
#include "liblista_circular.h"
#define MAX 5

lista_t *teste_criar_lista()
{
    lista_t* l;

    if(!(l = lista_cria()))
    {
        printf("Lista nao foi criada\n");
        return NULL;
    }

    printf("Lista criada com sucesso\n");
    return l;
}

elemento_t* teste_criar_elemento(int dado)
{
    elemento_t* e;

    if(!(e = elemento_cria(dado)))
    {
        printf("Falha na alocacao do elemento \n");
        return NULL;
    }

    printf("\telemento criado com sucesso\n");
    return e;
}

void teste_lista_vazia (lista_t* l)
{
    if(lista_vazia(l))
        printf ("\tLista esta vazia");
    else
        printf ("\tLista nao esta vazia");
}

void teste_imprime_lista(lista_t *l) {
    if (lista_vazia(l)) {
        printf("Lista vazia\n");
        return;
    }

    nodo_t *aux = l->ini;

    do {
        printf("Chave atual é: %d\n", aux->elemento->chave);
        aux = aux->prox;
    } while (aux != l->ini);
}


void teste_insere(lista_t *l, elemento_t *e)
{
    printf ("\tTentando inserir a chave %d\n", e->chave);

    if (!lista_insere_ordenado(l, e))
    {
        printf ("Elemento nao inserido.\n");
        return;
    }

    printf ("Elemento inserido com sucesso.\n");
    return;
}

void teste_remove(lista_t *l, elemento_t *e)
{
    printf ("\tTentando remover a chave %d\n", e->chave);

    if (!lista_remove_ordenado(l, e))
    {
        printf ("Elemento nao removido. Elemento inexistente na lista ou lista vazia.\n");
        return;
    }

    printf ("Elemento removido com sucesso.\n");
    return;
}

void teste_search(lista_t *l, elemento_t *e)
{
    printf ("\tBuscando a chave %d\n", e->chave);

    if (!lista_search_ordenado(l, e))
    {
        printf ("Elemento inexistente na lista.\n");
        return;
    }

    printf ("Elemento encontrado com sucesso.\n");
    return;
}

int main (void)
{
    lista_t *lista1, *lista2;
    elemento_t *e1, *e2, *e3, *e4, *e5;

    printf("Teste 1: criar lista e ver se esta vazia:\n");
    printf("Esperado: tem que dar lista vazia\n");
    lista1 = teste_criar_lista();
    teste_lista_vazia(lista1);
    printf("\n\n");

    printf("Teste 2: criar elemento:\n");
    printf("Esperado: tem que criar elemento alocado\n");
    e1 = teste_criar_elemento(15);
    printf("\n\n");

    printf("Teste 3: tenta remover elemento com lista vazia:\n");
    printf("Esperado: nao pode ter dado segfault\n");
    teste_remove(lista1, e1);
    free(e1);
    e1 = NULL;
    lista_destroi(&lista1);
    printf ("\n\n");

    printf("Teste 4: inserir 5 elementos:\n");
    printf("Esperado: tem que inserir 5 elementos de forma ordenada\n");
    printf("          A lista NAO PODE estar vazia\n");
    lista1 = lista_cria();
    e1 = elemento_cria(15);
    e2 = elemento_cria(99);
    e3 = elemento_cria(2);
    e4 = elemento_cria(0);
    e5 = elemento_cria(11);
    teste_insere(lista1,e1);
    teste_insere(lista1,e2);
    teste_insere(lista1,e3);
    teste_insere(lista1,e4);
    teste_insere(lista1,e5);
    printf ("\n\n");

    printf("Teste 5: imprimir lista ordenada:\n");
    printf("Esperado: imprimir uma lista que foi preenchida de forma ordenada\n");
    printf("          E nao pode ter segfault\n");
    teste_imprime_lista(lista1);
    printf("\n\n");

    printf ("Teste 6: destruir uma lista vazia:\n");
    printf ("Esperado: nao pode ter leak (conferir com valdrind)\n");
    printf ("          E nao pode ter segfault\n");
    lista2 = lista_cria();
    lista_destroi(&lista2);
    printf ("\n\n");

    printf ("Teste 7: destruir uma lista com elementos:\n");
    printf ("Esperado: nao pode ter leak (conferir com valdrind)\n");
    printf ("          E nao pode ter segfault\n");
    lista_destroi(&lista1);
    printf ("\n\n");

    printf ("Teste 8: destruir um elemento criado:\n");
    printf ("Esperado: nao pode ter leak (conferir com valdrind)\n");
    printf ("          E nao pode ter segfault\n");
    e1 = elemento_cria(123);
    elemento_destroi(&e1);
    printf ("\n\n");

    printf("Teste 9: tenta remover elemento inexistente da lista:\n");
    printf("Esperado: nao pode ter dado segfault\n");
    lista2 = lista_cria();
    e1 = elemento_cria(10);
    e2 = elemento_cria(25);
    e3 = elemento_cria(5);
    e4 = elemento_cria(7);
    lista_insere_ordenado(lista2, e1);
    lista_insere_ordenado(lista2, e2);
    lista_insere_ordenado(lista2, e3);
    teste_remove(lista2, e4);
    lista_destroi(&lista2);
    elemento_destroi(&e4);
    printf ("\n\n");

    printf("Teste 10: encontrar elemento na lista:\n");
    printf("Esperado: nao pode ter dado segfault\n");
    lista2 = lista_cria();
    e1 = elemento_cria(10);
    e2 = elemento_cria(25);
    e3 = elemento_cria(5);
    e4 = elemento_cria(7);
    lista_insere_ordenado(lista2, e1);
    lista_insere_ordenado(lista2, e2);
    lista_insere_ordenado(lista2, e3);
    teste_search(lista2, e3);
    teste_search(lista2, e4);
    lista_destroi(&lista2);
    elemento_destroi(&e4);
    printf ("\n\n");

    return 0;
}
