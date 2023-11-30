#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreB.h"
#include "Funcionalidades.h"
#include "datatypesdef.h"

//Essa fucncao le nos
Pagina leNo(FILE *f_arvoreb, int RRN){

        //struct a ser retornada
        Pagina no;

        //vetores auxiliares
        char C1[55];
        char C2[55];
        char C3[55];

            //leitura do no 
            fread(&no.nroChavesIndexadas, sizeof(int), 1, f_arvoreb);
            fread(&no.alturaNo, sizeof(int), 1, f_arvoreb);
            fread(&no.RRNdoNO, sizeof(int), 1, f_arvoreb);

            //le o Ponteiro 1
            fread(&no.P1, sizeof(int), 1, f_arvoreb );
            #define MAX_LENGTH 100 // Define um comprimento apropiado para string
                int i = 0;//i conta o tamanho da StringaDF
                while (i < MAX_LENGTH - 1) {
                    //le o campo chave, e conta o tamanho da string
                    fread(&C1[i], sizeof(char), 1, f_arvoreb);
                    if (C1[i] == '$') {
                        break; // Sai do loop se lixo '$' eh encontrado
                }
                i++;
                }
                C1[i] = '\0'; // Null-terminate the string
                //Pula o lixo e posiciona o ponteiro no campo Ponteiro de Referencia
                fseek(f_arvoreb, 54 - i , SEEK_CUR);
                //Le o campo Ponteiro de referencia do arquivo binario
                fread(&no.Pr1, sizeof(int), 1, f_arvoreb);
                i = 0;//Reseta o contador 

                //le o Ponteiro 2
                fread(&no.P2, sizeof(int), 1, f_arvoreb);
                while (i < MAX_LENGTH - 1) {
                    //le o campo chave, e conta o tamanho da string
                    fread(&C2[i], sizeof(char), 1, f_arvoreb);
                    if (C2[i] == '$') {
                        break; // Sai do loop se lixo '$' eh encontrado
                }
                i++;
                }
                C2[i] = '\0'; // Null-terminate the string

                //Pula o lixo e posiciona o ponteiro no campo Ponteiro de Referencia
                fseek(f_arvoreb, 54 - i, SEEK_CUR);
                //le o ponteiro de referencia
                fread(&no.Pr2, sizeof(int), 1, f_arvoreb);
                i = 0;//Reseta o contador

                //le o ponteiro 3
                fread(&no.P3, sizeof(int), 1, f_arvoreb );
                while (i < MAX_LENGTH - 1) {
                    //le o campo chave, e conta o tamanho da string
                    fread(&C3[i], sizeof(char), 1, f_arvoreb);
                    if (C3[i] == '$') {
                        break; // Sai do loop se lixo '$' eh encontrado
                    }
                    i++;
                }
                C3[i] = '\0'; // Null-terminate the string

                //Pula o lixo e posiciona o ponteiro no campo Ponteiro de Referencia
                fseek(f_arvoreb, 54 - i, SEEK_CUR);
                //Le o ponteiro de referencia
                fread(&no.Pr3, sizeof(int), 1, f_arvoreb);
                //le o ponteiro 4
                fread(&no.P4, sizeof(int), 1, f_arvoreb);
                i = 0;//reseta o contador

                //passa os valores da strings auxiliares para o struct
                strcpy(no.C1, C1);
                strcpy(no.C2, C2);
                strcpy(no.C3, C3);

                //retorna o no com os valores lidos
                return no;
}

int buscaRecursivaPorChave(char *nomeChave, FILE *f_arvoreb, int RRN){

    //verifica se o RRN eh valido
    if (RRN == -1){
        return -1;
    }

    //posiciona o ponteiro no "no" requerido
    fseek(f_arvoreb, 205*(RRN+1), SEEK_SET);

    //struct 
    Pagina no;

    //funcao que le os campos do no do arquivo indice
    no = leNo(f_arvoreb, RRN);

    //vetores para facilitar a busca usando loops
    int P[4] = {no.P1, no.P2, no.P3 , no.P4};
    char C[3][64] ;
    strcpy(C[0], no.C1);
    strcpy(C[1], no.C2);
    strcpy(C[2], no.C3);
    int Pr[3] = {no.Pr1, no.Pr2 , no.Pr3};


    //verificar se a chave esta no no atual
    for(int j = 0; j<no.nroChavesIndexadas; j++){
        if(strcmp(nomeChave, C[j]) <= 0){
            if(strcmp(nomeChave , C[j]) == 0){
                //achou a chave, retorna rrn
                return Pr[j];
            }
            else{
                //retorna a busca com o ponteiro do atual      
                return buscaRecursivaPorChave(nomeChave, f_arvoreb, P[j]);
                
            }   
        }
        else
            //caso contrario, vai para a proxima iteracao
            continue;
    }


    //se chegou aqui, a chave eh maior que todas as outras
    //retorna a busca com o ultimo ponteiro
    return buscaRecursivaPorChave(nomeChave, f_arvoreb, P[no.nroChavesIndexadas]);
}

void pesquisa_tecnologia_arvoreb(char *nomeArquivo, char *nomeArquivoIndice,  char *nomeChave){

    //abre o arquivo de indice
    FILE *f_arvoreb = fopen(nomeArquivoIndice, "rb");

    //se o arquivo nao pode ser criado, sai do programa
    if(!f_arvoreb){
        return;
    }

    //cabecalho do arquivo de indice    
    header Cabecalho_Indice;

    //le o cabecalho do arquivo de indice e checa inconsistencia
    fread(&Cabecalho_Indice.status, sizeof(char), 1, f_arvoreb);
    if(Cabecalho_Indice.status != '1'){
        printf("Falha no processamento do arquivo.\n");
        fclose(f_arvoreb);
        exit(0);
    }   
    fread(&Cabecalho_Indice.noRaiz, sizeof(int), 1, f_arvoreb);

    //chama a funcao recursiva de busca, comecando pelo no raiz
    int RRN = buscaRecursivaPorChave(nomeChave, f_arvoreb, Cabecalho_Indice.noRaiz);
  
    //funcionalidade 4, pesquisa um registro dado rrn
    Cabecalho cabecalho;
    PesquisaRRN(nomeArquivo, &cabecalho, RRN);

}