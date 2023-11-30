#include "Funcionalidades.h"
#include "datatypesdef.h"
#include "lista.h"

void PesquisaRRN(char *nomeArquivo, Cabecalho *cabecalho, int RRN) {
    leCabecalho(nomeArquivo, cabecalho);

    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        return;
    }

    // Verifica se o RRN eh valido (nao negativo)
  	fread(&cabecalho->status, sizeof(cabecalho->status), 1, arquivo);
    fread(&cabecalho->proxRRN, sizeof(cabecalho->proxRRN), 1, arquivo);
    fread(&cabecalho->nroTecnologias, sizeof(cabecalho->nroTecnologias), 1, arquivo);
    fread(&cabecalho->nroParesTecnologias, sizeof(cabecalho->nroParesTecnologias), 1, arquivo);

    if (RRN < 0 || RRN >= cabecalho->proxRRN) {
        printf("Registro inexistente.\n");
        fclose(arquivo);
        return;
    }

    // Calcula a posicao do byte
    long int position = sizeof(Cabecalho) + (sizeof(Dado)+(5*sizeof(int))) * (RRN);

    // Usa fseek para posicionar o ponteiro no byte desejado
    if (fseek(arquivo, position , SEEK_SET) != 0) {
        printf("Falha no processamento do arquivo.\n");
        fclose(arquivo);
        return;
    }
    
    char deletado;
    fread(&deletado, sizeof(char), 1, arquivo);
    //verifica se o registro foi deletado
    if(deletado == '1'){
        printf("Registro inexistente.");
        return;
    }

    int int_a;//grupo
    int int_b;//popularidade
    int int_c;//peso
    int int_d;//tamanho string1
    int int_f;//tamanho string 2
    
    //le os ints do registro
    fread(&int_a, sizeof(int), 1 ,arquivo);
    fread(&int_b, sizeof(int), 1 ,arquivo);
    fread(&int_c, sizeof(int), 1 ,arquivo);
      
    fread(&int_d, sizeof(int), 1, arquivo); // Tamanho da str1
    char str1[int_d + 1]; // adiciona +1 para o termino nulo
    fread(str1, sizeof(char), int_d, arquivo);
    str1[int_d] = '\0'; // termina nulo

    fread(&int_f, sizeof(int), 1, arquivo); // Tamanho da str2
    char str2[int_f + 1]; // adiciona +1 para o termino nulo
    fread(str2, sizeof(char), int_f, arquivo);
    str2[int_f] = '\0'; // termina nulo


    imprimeCampos(str1, int_a, int_b, int_f, str2, int_c);//imprime os campo na ordem formatada
    
    fclose(arquivo);

}
