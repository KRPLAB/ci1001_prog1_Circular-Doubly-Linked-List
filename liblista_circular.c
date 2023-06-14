#include <stdio.h>
#include <stdlib.h>
#include "liblista_circular.h"

lista_t *lista_cria()
{
	lista_t *l;

	if(!(l = malloc(sizeof(lista_t))))
        return NULL;

    l->ini = NULL;

    return l;
}

elemento_t *elemento_cria(int dado)
{
	elemento_t *e;

	if(!(e = malloc(sizeof(elemento_t))))
		return NULL;

	e->chave = dado;

	return e;
}

int lista_vazia (lista_t *l)
{
    return !l->ini;   
}

void lista_destroi(lista_t **l)
{
	nodo_t *atual, *proximo;

	if(lista_vazia((*l)))
		return;

	atual = (*l)->ini;
	proximo = atual;

	/*enquanto a lista ter mais que um elemento e
	* e não estiver vazia o looping eh feito*/
	while (proximo != NULL && proximo != (*l)->ini)
	{
		proximo = atual->prox;

		free(atual->elemento);
		free(atual);
		atual = proximo;
	}

	free(atual->elemento);
	free(atual);

	free(*l);
	(*l) = NULL;
	return;
}

int lista_insere_ordenado(lista_t *l, elemento_t *elemento)
{
	nodo_t *novo, *aux, *ant;

	if (!(novo = malloc(sizeof(nodo_t))))
		return 0;

	novo->elemento = elemento;

	/*caso lista esteja vazia e o novo elemento
	* venha a ser o primeiro da lista*/
	if (lista_vazia(l))
	{
		novo->prox = novo;
		novo->prev = novo;
		l->ini = novo;
		return 1;
	}
	
	/*caso o novo elemento seja o maior da lista
	* e venha a ser o último da lista*/
	if (novo->elemento->chave > l->ini->prev->elemento->chave)
	{
		novo->prox = l->ini;
		novo->prev = l->ini->prev;
		l->ini->prev->prox = novo;
		l->ini->prev = novo;
		l->ini = novo;
		return 1;
	}
	
	/*caso a posicao do novo elemento seja outro 
	* lugar exceto a menor e maior posicao*/
	aux = l->ini;
	while (novo->elemento->chave > aux->elemento->chave)
	{
		ant = aux;
		aux = aux->prox;
	}

	novo->prox = aux;
	novo->prev = ant;
	ant->prox = novo;
	aux->prev = novo;

	return 1;
}

int lista_remove_ordenado (lista_t *l, elemento_t *elemento)
{

}