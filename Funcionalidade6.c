#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreB.h"
#include "Funcionalidades.h"
#include "datatypesdef.h"

int buscaRecursivaPorChave(char *nomeChave, FILE *f_arvoreb, int RRN){

    if (RRN == -1){
        return -1;
    }

    //posiciona o ponteiro no "no" requerido
    fseek(f_arvoreb, 205*(RRN+1), SEEK_SET);

    Pagina no;

    char C1[55];
    char C2[55];
    char C3[55];

    //leitura do no *modularizar uma funcao le no*
            fread(&no.nroChavesIndexadas, sizeof(int), 1, f_arvoreb);
        //  printf("no chaves indexadas: %d\n", no.nroChavesIndexadas);
            fread(&no.alturaNo, sizeof(int), 1, f_arvoreb);
        //  printf("%d\n", no.alturaNo);
            fread(&no.RRNdoNO, sizeof(int), 1, f_arvoreb);
        //  printf("%d\n", no.RRNdoNO);
            fread(&no.P1, sizeof(int), 1, f_arvoreb );
        //  printf("%d\n", no.P1);
            #define MAX_LENGTH 100 // Define an appropriate maximum length for your string
                int i = 0;
                while (i < MAX_LENGTH - 1) {
                fread(&C1[i], sizeof(char), 1, f_arvoreb);
                if (C1[i] == '$') {
                    break; // Exit the loop if '$' is encountered
                }
                i++;
                }
                C1[i] = '\0'; // Null-terminate the string
            // printf("%s\n" , C1);
                
                fseek(f_arvoreb, 54 - i , SEEK_CUR);
                fread(&no.Pr1, sizeof(int), 1, f_arvoreb);
                
                i = 0;
                fread(&no.P2, sizeof(int), 1, f_arvoreb);
            //  printf("%d\n", no.P2);
                while (i < MAX_LENGTH - 1) {
                fread(&C2[i], sizeof(char), 1, f_arvoreb);
                if (C2[i] == '$') {
                    break; // Exit the loop if '$' is encountered
                }
                i++;
                }
                C2[i] = '\0'; // Null-terminate the string
            //    printf("%s\n" , C2);

                fseek(f_arvoreb, 54 - i, SEEK_CUR);
                fread(&no.Pr2, sizeof(int), 1, f_arvoreb);
                
                i = 0;
                fread(&no.P3, sizeof(int), 1, f_arvoreb );
                while (i < MAX_LENGTH - 1) {
                fread(&C3[i], sizeof(char), 1, f_arvoreb);
                if (C3[i] == '$') {
                    break; // Exit the loop if '$' is encountered
                }
                i++;
                }
                C3[i] = '\0'; // Null-terminate the string
            //   printf("%s\n", C3);
                

                fseek(f_arvoreb, 54 - i, SEEK_CUR);
                fread(&no.Pr3, sizeof(int), 1, f_arvoreb);
                fread(&no.P4, sizeof(int), 1, f_arvoreb);
                i = 0;


        

    //vetores para facilitar a busca usando loops
    int P[4] = {no.P1, no.P2, no.P3 , no.P4};
    char C[3][64] ;
    strcpy(C[0], C1);
    strcpy(C[1], C2);
    strcpy(C[2], C3);
    int Pr[3] = {no.Pr1, no.Pr2 , no.Pr3};

/*
    printf("%d\n", no.P1);
    printf("%s\n", C[0]);
 */
    //return;

    //verificar se a chave esta no no atual
    for(int j = 0; j<no.nroChavesIndexadas; j++){
        if(strcmp(nomeChave, C[j]) <= 0){
            if(strcmp(nomeChave , C[j]) == 0){
                //achou a chave, retorna rrn
                return Pr[j];
            }
            else{
                //verifica se o no eh folha, caso seja o registro nao existe
                // if(no.alturaNo == 0){
                //     printf("Registro Inexistente\n");
                //     return NULL;
                // }
                //retorna a busca com o ponteiro do atual
                
                return buscaRecursivaPorChave(nomeChave, f_arvoreb, P[j]);
                
            }   
        }
        else
            continue;
    }


    //se chegou aqui, a chave eh maior que todas as outras
    //verifica se o no eh folha, caso seja o registro nao existe
    // if(no.alturaNo == 0){
    //          printf("Registro Inexistente\n");
    //          return NULL;
    // }
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