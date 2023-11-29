#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreB.h"
#include "Funcionalidades.h"
#include "datatypesdef.h"

void cria_ArvoreB(char *nomeArquivo, char *NomeArquivoIndice){

    //Abre o arquivo das tecnlologias no modo leitura binaria
    FILE *f_tecnologia = fopen(nomeArquivo, "rb");

    //se o arquivo nao existe, retorna erro
    if (f_tecnologia == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }   

    //structs
    Cabecalho tecnologia_cabecalho; //struct de cabecalho
    Dado      tecnologia_dados;    //struct de registro

    //le o cabecalho do arquivo de registro e verifica se eh inconsistente
    fread(&tecnologia_cabecalho.status, sizeof(char), 1, f_tecnologia);
    if(tecnologia_cabecalho.status != '1'){
        return;
    }

    //abre o arquivo de indice da arvore b no mode de escrita binaria
    FILE *f_arvoreb = fopen(NomeArquivoIndice, "wb"); //arquivo da arvore b
    //se o arquivo nao existe, retorna erro
    if (f_arvoreb == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    //struct de cabecalho 
    header arvoreb_cabecalho;

    //define os valores iniciais do cabecalho
    arvoreb_cabecalho.status = '0';
    arvoreb_cabecalho.noRaiz = -1;
    arvoreb_cabecalho.RRNproxNO = 0;
    memset(&(arvoreb_cabecalho.lixo), '@', 68); //verificar se necessario 

    //escreve o status da arvore b no disco
    fwrite(&arvoreb_cabecalho.status, sizeof(char), 1, f_arvoreb);

    //le os campos restantes do cabecalho de tecnologia
    fread(&tecnologia_cabecalho.nroTecnologias, sizeof(int), 1 , f_tecnologia);
    fread(&tecnologia_cabecalho.proxRRN , sizeof(int), 1 , f_tecnologia);

    //move o ponteiro para o comeco do primeiro registro de dados
    fseek(f_tecnologia, 11, SEEK_SET);

    //le cada registro dos veiculos e insere na arvore B
    int indice = 0;
    while(indice < tecnologia_cabecalho.nroTecnologias){
        //byte offset do atual registro
        long byte_offset = ftell(f_tecnologia);

        //le o atual dado pula para o proximo regitro
        fread(&tecnologia_dados.removido, sizeof(char), 1, f_arvoreb);

        //se o registro atual for removido, nao havera insercao
        if(tecnologia_dados.removido == '0'){
            fseek(f_tecnologia, 74, SEEK_CUR);
            continue;
        }

        //le o dado atual do registro
        fread(&tecnologia_dados.peso, sizeof(int), 1, f_arvoreb);
        fseek(f_tecnologia, 74, SEEK_CUR);

        //conversao para inteiro


        //insere a tecnologia na arvore
        insere_arvoreB(tecnologia_dados.peso, byte_offset, f_arvoreb, &arvoreb_cabecalho.noRaiz, &arvoreb_cabecalho.RRNproxNO);

        //incrementa o indice
        indice++;
    }
        //define o cabecalho da arvore b para 1
        arvoreb_cabecalho.status = '1';
        fseek(f_arvoreb, 0, SEEK_SET);
        fwrite(&arvoreb_cabecalho.status, sizeof(char), 1, f_arvoreb);

        //fecha os arquivos
        fclose(f_tecnologia);
        fclose(f_arvoreb);

        return;

} 