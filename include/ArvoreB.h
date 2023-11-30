#include <stdio.h>
#include <stdlib.h>

#define Pagina_de_Disco 205
#define NO_PROMOTION 0
#define PROMOTION 1

typedef struct {
  char status;
  int noRaiz; //valor inicial eh -1
  int RRNproxNO;
  char lixo[196];
} header;

typedef struct {
  char folha; 
  int alturaNo;
  int nroChavesIndexadas; // 0 <= x <= 4  
  int RRNdoNO; // RRN deste no
  int P1; // "ponteiro" para o no filho
  char C1[55]; // Chave de Busca
  int Pr1; // "ponteiro" para a referencia no arquivo de dados
  int P2;
  char C2[55];
  int Pr2;
  int P3;
  char C3[55];
  int Pr3;
  int P4;

} Pagina;

typedef struct{
  header *Header;
  Pagina *dados;
  int comprimento_arvore;
} ArvoreB;

void insere_arvoreB(int chave, long long referencia, FILE *file, int *raiz_rrn, int *rrn_livre);
  
long long busca_arvoreb(int chave, FILE *file);

void cria_ArvoreB(char *nomeArquivo, char *NomeArquivoIndice);

void pesquisa_tecnologia_arvoreb(char *nomeArquivo, char *nomeArquivoIndice, char *nomeChave);