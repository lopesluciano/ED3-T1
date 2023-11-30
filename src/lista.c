#include "lista.h"

Lista *criarLista(){
	Lista *lista = (Lista*) malloc(sizeof(Lista));
	lista->ini = NULL;
	lista->fim = NULL;
	lista->tamanho = 0;

	return lista;
}

Node *criarNode(Dado* dado){
	Node *node = (Node*) malloc(sizeof(Node));
	node->dado = dado;
	node->prox = NULL;

	return node;
}

void inserir(Lista *lista, Dado *dado){
	Node *aux = criarNode(dado);

	if(lista->ini == NULL){
		lista->ini = aux;
		lista->fim = lista->ini;
		lista->tamanho++;
		return;
	}

	lista->fim->prox = aux;
	lista->fim = aux;
	lista->tamanho++;
	return;
}

void imprimir(Lista *lista){
    Node *aux = lista->ini;

    while(aux != NULL){
        if(aux->dado->removido == '0'){
            printf("%c, ", aux->dado->removido);
            printf("%s, ", aux->dado->tecnologiaOrigem.nome);
            printf("%d, ", aux->dado->grupo);
            printf("%d, ", aux->dado->popularidade);
            printf("%s, ", aux->dado->tecnologiaDestino.nome);
            printf("%d\n", aux->dado->peso);
        }

        aux = aux->prox;
    }

}
