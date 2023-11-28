#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreB.h"
#include "Funcionalidades.h"
#include "datatypesdef.h"

void pesquisa_tecnologia_arvoreb(char *nomeArquivo, char *nomeArquivoIndice, char *nomeTecnologia){
    //abre o arquivo de indice
    FILE *f_arvoreb = fopen(nomeArquivoIndice, "rb");

    //if o arquivo nao pode ser criado, sai do programa
    if(!f_arvoreb){
        return;
    }

    //campo do cabecalho arvore b
    char arvoreb_status;

    //le o cabecalho do arquivo de indice e checa inconsistencia
    fread(&arvoreb_status, sizeof(char), 1, f_arvoreb);
    if(arvoreb_status != '1'){
        printf("Arquivo Inconsistente");
        return;
    }


    //char chave = *nomeTecnologia

    int convertido = atoi(nomeTecnologia);

    //procura pelo nome na arvore B
    long long byte_offset = busca_arvoreb(convertido, f_arvoreb);

    //Se registro nao existe, retorna errro
    if(byte_offset == -1){
        printf("Registro Inexistente");
        return;
    }

    //abre o arquivo de tecnologias no mode de leitura binaria
    FILE *f_tecnologias = fopen(nomeArquivo, "rb");
    if(!f_tecnologias){
        return;
    }   

    //structs
    Cabecalho tecnologia_cabecalho;
    Dado      tecnologia_dado;

    //le o status de cabecalho e verifica inconsistencias
    fread(&tecnologia_cabecalho.status, sizeof(char), 1, f_tecnologias);
    if(tecnologia_cabecalho.status != '1'){
        printf("Arquivo Inconsistente");
        return ;
    }

    //le os campos do cabecalho
    fread(&tecnologia_cabecalho.nroTecnologias, sizeof(int), 1, f_tecnologias);
    fread(&tecnologia_cabecalho.proxRRN, sizeof(int), 1, f_tecnologias);
    
    //vai para o comeco do campo do dado consultado
    fseek(f_tecnologias, byte_offset +5, SEEK_SET);

    //le os tamanhos dos campos de busca
    fread(&tecnologia_dado.grupo, sizeof(int), 1 , f_tecnologias);
    fread(&tecnologia_dado.peso, sizeof(int), 1 , f_tecnologias);
    fread(&tecnologia_dado.popularidade, sizeof(int), 1 , f_tecnologias);
    //fread(tecnologia_dado.tecnologiaDestino, sizeof(char), 50 , f_tecnologias); 
    //fread(tecnologia_dado.tecnologiaDestino, sizeof(char), 50 , f_tecnologias);
    //pensar um jeito de lidar com strings variaveis(olhar funcionalidades anteriores)
    /*
    
    // reads the current register's "modelo" field (variable size)
    fread(&_vehicle_data.tamanhoModelo, sizeof(int),  1,                           f_vehicles);
    _vehicle_data.modelo = (char *)malloc(sizeof(char) * _vehicle_data.tamanhoModelo);
    fread(_vehicle_data.modelo,         sizeof(char), _vehicle_data.tamanhoModelo, f_vehicles);
    */

    //se o campo possuir valor nulo {implementar}
    //printa os campos atuais do registro
    
    /*
    imprimeCampos();
    */

    //fechar os arquivos
    fclose(f_arvoreb);
    fclose(f_tecnologias);   

    return;
}