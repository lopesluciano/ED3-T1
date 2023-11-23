//Luciano Goncalves Lopes Filho nusp:13676520
//Caroline Severiano Clapis nusp:13861923
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datatypesdef.h"
#include "Funcionalidades.h"
#include "lista.h"
#include "ArvoreB.h"


// Programa principal
int main()
{
	int op;
	char nomeArquivoOrigem[100], nomeArquivoDestino[100];
	Cabecalho cabecalho;
	Lista *listaDados = criarLista();

	int i = 0, RRN, n;
	while (i < 1)
	{
		scanf("%d", &op);

		// printf("Opcao lida: %d\n", op);

		switch (op)
		{
		case 1:
			scanf("%s %s", nomeArquivoOrigem, nomeArquivoDestino);

			// Le arquivo CSV e armazena conteudo na lista 'listaDados'
			leCSV(nomeArquivoOrigem, &cabecalho, listaDados);

			// Escrever dados da 'listaDados' em um arquivo bin�rio
			escreveBinario(nomeArquivoDestino, &cabecalho, listaDados);

			// Imprimir o conte�do do arquivo bin�rio usando a fun��o 'binarioNaTela()'
			binarioNaTela(nomeArquivoDestino);

			break;
		case 2:
			scanf("%s", nomeArquivoOrigem); // Arquivo binario

			imprimeRegistro(nomeArquivoOrigem, &cabecalho);

			break;

		case 3:

			i = 0;
			scanf("%s", nomeArquivoOrigem);
			scanf("%d", &n);


			while(i < n){
				PesquisaCampo(nomeArquivoOrigem, &cabecalho);
				i++;
			}

			break;

		case 4:
			scanf("%s", nomeArquivoOrigem);
			scanf("%d", &RRN);

			PesquisaRRN(nomeArquivoOrigem , &cabecalho, RRN);

			break;
	
		case 5:

			// Initialize the B-tree root node
			root = NULL;

			// Insert values into the B-tree
			insert(10);
			insert(20);
			insert(5);
			insert(30);
			insert(7);
			insert(3);
			insert(15);
			insert(25);

			// Print the B-tree values in sorted order
			printf("B-tree values in sorted order: ");
			traversal(root);
			printf("\n");

			// Search for a value in the B-tree
			int searchVal = 20;
			int pos = -1;
			search(searchVal, &pos, root);
			if (pos != -1) {
				printf("%d found at position %d.\n", searchVal, pos);
			} else {
				printf("%d not found in the B-tree.\n", searchVal);
			}

			return 0;

		}

		i++;
	}

	return 0;
}
