#include <stdio.h>
#include <stdlib.h>
#include "liblista_circular.h"

lista_t *lista_cria()
{
	lista_t *l;

	if (!(l = malloc(sizeof(lista_t))))
		return NULL;

	l->ini = NULL;

	return l;
}

elemento_t *elemento_cria(int dado)
{
	elemento_t *e;

	if (!(e = malloc(sizeof(elemento_t))))
		return NULL;

	e->chave = dado;

	return e;
}

int lista_vazia(lista_t *l)
{
	return !l->ini;
}

void lista_destroi(lista_t **l)
{
	nodo_t *atual, *proximo;

	if (lista_vazia((*l)))
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

void elemento_destroi(elemento_t **elemento)
{
	if (elemento != NULL && (*elemento) != NULL)
	{
		free(*elemento);
		(*elemento) = NULL;
	}
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
		l->ini = novo;
		novo->prox = l->ini;
		novo->prev = l->ini;
		return 1;
	}

	/*caso o novo elemento seja menor que o
	* primeiro da lista*/
	if (novo->elemento->chave < l->ini->elemento->chave)
	{
		novo->prox = l->ini;
		novo->prev = l->ini->prev;
		novo->prev->prox = novo;
		l->ini = novo;
		return 1;
	}


	/*caso o novo elemento seja o maior da lista
	 * e venha a ser o último da lista*/
	if (novo->elemento->chave > l->ini->prev->elemento->chave)
	{
		novo->prox = l->ini;
		novo->prev = l->ini->prev;
		novo->prev->prox = novo;
		l->ini->prev = novo;
		return 1;
	}

	/*caso a posicao do novo elemento seja outro
	 * lugar exceto a menor e maior posicao*/
	aux = l->ini;
	while (aux->prox != l->ini &&
				novo->elemento->chave > aux->elemento->chave)
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

int lista_remove_ordenado(lista_t *l, elemento_t *elemento)
{
	nodo_t *aux = l->ini;

	if (lista_vazia(l))
		return 0;

	do
	{
		if (elemento->chave == aux->elemento->chave)
		{
			/*se for o primeiro elemento da lista*/
			if (aux == l->ini)
			{
				/*se for o primeiro e UNICO elemento da lista*/
				if (l->ini->prox == l->ini)
				{
					free(l->ini);
					l->ini = NULL;
					return 1;
				}

				l->ini->prev->prox = l->ini->prox;
				l->ini->prox->prev = l->ini->prev;
				l->ini = l->ini->prox;
			}

			/*se for o ultimo elemento da lista*/
			else if (aux == l->ini->prev)
			{
				aux->prev->prox = l->ini;
				l->ini->prev = aux->prev;
			}

			/*elemento no meio da lista*/
			else
			{
				aux->prev->prox = aux->prox;
				aux->prox->prev = aux->prev;
			}

			free(aux);
			return 1;
		}

		aux = aux->prox;

	} while (aux != l->ini);

	/*elemento nao encontrado*/
	return 0;
}

int lista_search_ordenado(lista_t *l, elemento_t *elemento)
{
	nodo_t *aux;

	if (lista_vazia(l))
		return 0;

	/*se o elemento estiver no inicio*/
	if (elemento->chave == l->ini->elemento->chave)
		return 1;

	aux = l->ini;
	while (aux->prox != l->ini &&
			elemento->chave != aux->prox->elemento->chave)
		aux = aux->prox;

	return (aux->prox != l->ini &&
			elemento->chave == aux->prox->elemento->chave);
}