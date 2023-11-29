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
	char nomeArquivoOrigem[100], nomeArquivoDestino[100], nomeChave[55];
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

		case 6:

			scanf("%s", nomeArquivoOrigem);
			scanf("%s", nomeArquivoDestino);
			scanf("%d" , &n);


			while(i < n){
				PesquisaCampo(nomeArquivoOrigem, nomeArquivoDestino, &cabecalho);
				i++;
			}

			break;

		case 4:
			scanf("%s", nomeArquivoOrigem);
			scanf("%d", &RRN);

			PesquisaRRN(nomeArquivoOrigem , &cabecalho, RRN);

			break;
	
		case 5:

			scanf("%s", nomeArquivoOrigem);
			scanf("%s", nomeArquivoDestino);
			
			//cria_ArvoreB(nomeArquivoOrigem, nomeArquivoDestino);

			binarioNaTela(nomeArquivoDestino);

			break;

		case 7:

			scanf("%s", nomeArquivoOrigem);
			scanf("%s", nomeArquivoDestino);

			scanf("%s", nomeChave);

			pesquisa_tecnologia_arvoreb(nomeArquivoOrigem, nomeArquivoDestino, nomeChave);

		}

		i++;
	}

	return 0;
}
