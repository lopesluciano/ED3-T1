#include <stdio.h>
#include <stdlib.h>

#define Pagina_de_Disco 205
#define NO_PROMOTION 0
#define PROMOTION 1

typedef struct {
  char status;
  int noRaiz; //valor inicial eh -1
  int RRNproxNO;
  char lixo[68];
} header;

typedef struct {
  char folha; 
  int nroChavesIndexadas; // 0 <= x <= 4
  int RRNdoNO; // RRN deste no
  int P1; // "ponteiro" para o no filho
  int C1; // Chave de Busca
  long long Pr1; // "ponteiro" para a referencia no arquivo de dados
  int P2;
  int C2;
  long long Pr2;
  int P3;
  int C3;
  long long Pr3;
  int P4;
  int C4;
  long long Pr4;
  int P5;
} Pagina;

typedef struct{
  header *Header;
  Pagina *dados;
  int comprimento_arvore;
} ArvoreB;

void insere_arvoreB(int chave, long long referencia, FILE *file, int *raiz_rrn, int *rrn_livre);

long long busca_arvoreb(int chave, FILE *file);

void cria_ArvoreB(char *nomeArquivo, char *NomeArquivoIndice);

void pesquisa_tecnologia_arvoreb(char *nomeArquivo, char *nomeArquivoIndice, char *nomeTecnologia);