#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreB.h"
#include "Funcionalidades.h"
#include "datatypesdef.h"

#define INVALID -1

typedef struct {
    int chave;
    long long referencia;
    int rrn_no_filho;
} info_promocao;

//vai para o posicao especificada do RRN no arquivo e retorna a posicao

long fseek_rrn(FILE *file, int rrn){

    long posicao_atual_no = (rrn + 1);

    if(ftell(file) != posicao_atual_no){
        fseek(file, posicao_atual_no, SEEK_SET);
    }

    return posicao_atual_no; 
}

int busca_raiz_rrn(FILE *file){
    //raiz
    int raiz_rrn;

    //le o RRN da raiz da arvore B
    fseek(file, 1 , SEEK_SET);
    fread(&raiz_rrn, sizeof(int), 1, file);

    return raiz_rrn;
}


//recebe um no e escreve no disco
void fwrite_no(Pagina no, FILE *file){
    //vai para a posicao do no, no arquivo binario
    fseek_rrn(file, no.RRNdoNO);

    //escreve o no, no disco
    fwrite(&no.folha, sizeof(char), 1, file);
    fwrite(&no.RRNdoNO, sizeof(int), 1, file);
    fwrite(&no.P1, sizeof(int), 1, file);
    fwrite(&no.C1, sizeof(int), 1, file);
    fwrite(&no.Pr1, sizeof(long long), 1, file);
    fwrite(&no.P2, sizeof(int), 1, file);
    fwrite(&no.C2, sizeof(int), 1, file);
    fwrite(&no.Pr2, sizeof(long long), 1, file);
    fwrite(&no.P3, sizeof(int), 1, file);
    fwrite(&no.C3, sizeof(int), 1, file);
    fwrite(&no.Pr3, sizeof(long long), 1, file);
    fwrite(&no.P4, sizeof(int), 1, file);
    fwrite(&no.C4, sizeof(int), 1, file);
    fwrite(&no.Pr4, sizeof(long long), 1, file);
    fwrite(&no.P5, sizeof(int), 1, file);
}
 
Pagina fread_no(int RRN, FILE *file){
    Pagina no;
    
    //vai para a posicao do no, no arquivo binario
    fseek_rrn(file, RRN);

    //escreve o no, no disco
    fread(&no.folha, sizeof(char), 1, file);
    fread(&no.RRNdoNO, sizeof(int), 1, file);
    fread(&no.P1, sizeof(int), 1, file);
    fread(&no.C1, sizeof(int), 1, file);
    fread(&no.Pr1, sizeof(long long), 1, file);
    fread(&no.P2, sizeof(int), 1, file);
    fread(&no.C2, sizeof(int), 1, file);
    fread(&no.Pr2, sizeof(long long), 1, file);
    fread(&no.P3, sizeof(int), 1, file);
    fread(&no.C3, sizeof(int), 1, file);
    fread(&no.Pr3, sizeof(long long), 1, file);
    fread(&no.P4, sizeof(int), 1, file);
    fread(&no.C4, sizeof(int), 1, file);
    fread(&no.Pr4, sizeof(long long), 1, file);
    fread(&no.P5, sizeof(int), 1, file);

    return no;
}

// verifica se o no contem a chave
// apenas para atalho, posso usar a funcao so pra nao precisar repetir a expressao 
int no_contem_chave(Pagina no, int chave){
    return no.C1 == chave || no.C2 == chave || no.C3 == chave || no.C4 ==chave;
}

//compara uma chave nova a uma chave de no e verifica
// apenas para atalho, posso usar a funcao so pra nao precisar repetir a expressao 
int chave_esta_na_posicao(int chave_no, int nova_chave){
    return nova_chave <= chave_no || chave_no == INVALID; 
}


info_promocao divide(info_promocao inserido, Pagina no_atual, FILE *file, int *rrn_livre){
//pagina de disco porem com um ponteiro extra, filho e chave
    struct pagina_maior{
        int P1; // "ponteiro para o no filho"
        int C1; // chave de busca
        long long Pr1; //ponteiro pra referecia de dados
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
        int C5;
        long long Pr5;
        int P6;
    };
    struct pagina_maior no_maior;

    if(inserido.chave < no_atual.C1){
        no_maior.P1 = no_atual.P1;

        no_maior.C1 = inserido.chave;
        no_maior.Pr1 = inserido.referencia;
        no_maior.P2 = inserido.rrn_no_filho;

        no_maior.C2 = no_atual.C1;
        no_maior.Pr2 = no_atual.Pr1;
        no_maior.P3 = no_atual.P2;

        no_maior.C3 = no_atual.C2;
        no_maior.Pr3 = no_atual.Pr2;
        no_maior.P4 = no_atual.P3;

        no_maior.C4 = no_atual.C3;
        no_maior.Pr4 = no_atual.Pr3;
        no_maior.P5 = no_atual.P4;

        no_maior.C5 = no_atual.C4;
        no_maior.Pr5 = no_atual.Pr4;
        no_maior.P6 = no_atual.P5;
    }

    if(inserido.chave < no_atual.C2){
        no_maior.P1 = no_atual.P1;

        no_maior.C1 = no_atual.C1;
        no_maior.Pr1 = no_atual.Pr1;
        no_maior.P2 = no_atual.P2;

        no_maior.C2 = inserido.chave;
        no_maior.Pr2 = inserido.referencia;
        no_maior.P2 = inserido.rrn_no_filho;

        no_maior.C3 = no_atual.C2;
        no_maior.Pr3 = no_atual.Pr2;
        no_maior.P4 = no_atual.P3;

        no_maior.C4 = no_atual.C3;
        no_maior.Pr4 = no_atual.Pr3;
        no_maior.P5 = no_atual.P4;

        no_maior.C5 = no_atual.C4;
        no_maior.Pr5 = no_atual.Pr4;
        no_maior.P6 = no_atual.P5;
    }

    if(inserido.chave < no_atual.C3){
        no_maior.P1 = no_atual.P1;

        no_maior.C1 = no_atual.C1;
        no_maior.Pr1 = no_atual.Pr1;
        no_maior.P2 = no_atual.P2;

        no_maior.C2 = no_atual.C2;
        no_maior.Pr2 = no_atual.Pr2;
        no_maior.P3 = no_atual.P3;

        no_maior.C3 = inserido.chave;
        no_maior.Pr3 = inserido.referencia;
        no_maior.P4 = inserido.rrn_no_filho;

        no_maior.C4 = no_atual.C3;
        no_maior.Pr4 = no_atual.Pr3;
        no_maior.P5 = no_atual.P4;

        no_maior.C5 = no_atual.C4;
        no_maior.Pr5 = no_atual.Pr4;
        no_maior.P6 = no_atual.P5;
    }

    if(inserido.chave < no_atual.C4){
        no_maior.P1 = no_atual.P1;

        no_maior.C1 = no_atual.C1;
        no_maior.Pr1 = no_atual.Pr1;
        no_maior.P2 = no_atual.P2;

        no_maior.C2 = no_atual.C2;
        no_maior.Pr2 = no_atual.Pr2;
        no_maior.P3 = no_atual.P3;

        no_maior.C3 = no_atual.C3;
        no_maior.Pr3 = no_atual.Pr3;
        no_maior.P4 = no_atual.P4;

        no_maior.C4 = inserido.chave;
        no_maior.Pr4 = inserido.referencia;
        no_maior.P5 = inserido.rrn_no_filho;

        no_maior.C5 = no_atual.C4;
        no_maior.Pr5 = no_atual.Pr4;
        no_maior.P6 = no_atual.P5;
    }

    else{
        no_maior.P1 = no_atual.P1;

        no_maior.C1 = no_atual.C1;
        no_maior.Pr1 = no_atual.Pr1;
        no_maior.P2 = no_atual.P2;

        no_maior.C2 = no_atual.C2;
        no_maior.Pr2 = no_atual.Pr2;
        no_maior.P3 = no_atual.P3;

        no_maior.C3 = no_atual.C3;
        no_maior.Pr3 = no_atual.Pr3;
        no_maior.P4 = no_atual.P4;

        no_maior.C4 = no_atual.C4;
        no_maior.Pr4 = no_atual.Pr4;
        no_maior.P5 = no_atual.P5;

        no_maior.C5 = inserido.chave;
        no_maior.Pr5 = inserido.referencia;
        no_maior.P6 = inserido.rrn_no_filho;
    }

    // dados do no atual
    no_atual.nroChavesIndexadas = 2;
    no_atual.P1                 = no_maior.P1;
    no_atual.C1                 = no_maior.C1;
    no_atual.Pr1                = no_maior.Pr1;
    no_atual.P2                 = no_maior.P2;
    no_atual.C2                 = no_maior.C2;
    no_atual.Pr2                = no_maior.Pr2;
    no_atual.P3                 = no_maior.P3;
    no_atual.C3                 = INVALID;
    no_atual.Pr3                = INVALID;
    no_atual.P4                 = INVALID;
    no_atual.C4                 = INVALID;
    no_atual.Pr4                = INVALID;
    no_atual.P5                 = INVALID;

    // dados do novo no
    Pagina novo_no;
    novo_no.folha              = no_atual.folha;
    novo_no.nroChavesIndexadas = 2;
    novo_no.RRNdoNO            = *rrn_livre;
    novo_no.P1                 = no_maior.P4;
    novo_no.C1                 = no_maior.C4;
    novo_no.Pr1                = no_maior.Pr4;
    novo_no.P2                 = no_maior.P5;
    novo_no.C2                 = no_maior.C5;
    novo_no.Pr2                = no_maior.Pr5;
    novo_no.P3                 = no_maior.P6;
    novo_no.C3                 = INVALID;
    novo_no.Pr3                = INVALID;
    novo_no.P4                 = INVALID;
    novo_no.C4                 = INVALID;
    novo_no.Pr4                = INVALID;
    novo_no.P5                 = INVALID;

    //reescreve o no atual
    fwrite_no(no_atual, file);

    //escreve o novo no no disco
    fwrite_no(novo_no, file);

    return(info_promocao){
        no_maior.C3,
        no_maior.Pr3,
        novo_no.RRNdoNO
    };
}

info_promocao insercao_recursiva(int rrn_atual, int chave_inserido, long long referencia_inserido, FILE *file, int *rrn_livre){
    //se o no atual nao existe, promove a chave inserida
    if (rrn_atual == INVALID) { return (info_promocao) { chave_inserido, referencia_inserido, INVALID }; }


    //dados do no atual
    Pagina no = fread_no(rrn_atual, file);
    
    //se a chave inserida ja existe na arvore, retorna erro;
    if(no_contem_chave(no, chave_inserido)){
        exit(1);
    }

    //no filho o qual a chave inserida de entrar
    int rrn_filho;

    //encontra a posicao em que a chave inserida vai entrar
    if(chave_esta_na_posicao(no.C1, chave_inserido))
        rrn_filho = no.P1;
    else if(chave_esta_na_posicao(no.C2, chave_inserido))
        rrn_filho = no.P2;
    else if(chave_esta_na_posicao(no.C3, chave_inserido))
        rrn_filho = no.P3;
    else if(chave_esta_na_posicao(no.C4, chave_inserido))
        rrn_filho = no.P4;
    else
        rrn_filho = no.P5;
    

    info_promocao promocao = insercao_recursiva(rrn_filho, chave_inserido, referencia_inserido, file, rrn_livre); 

    if(promocao.chave == INVALID){
        return promocao;
    }

    //se nao ha espaco no "no" atual (necessaria divisao de no)
    else if(no.nroChavesIndexadas == 4){
        return divide(promocao, no, file, rrn_livre);
    }

    //se nao eh necessaria divisao insere a chave promovida ao no atual
    if(chave_esta_na_posicao(no.C1, promocao.chave)){
        //move as chaves 1 posicao para frente
        no.C4  = no.C3;
        no.Pr4 = no.Pr3;
        no.P5  = no.P4;

        no.C3  = no.C2;
        no.Pr3 = no.Pr2;
        no.P4  = no.P3;

        no.C2  = no.C1;
        no.Pr2 = no.Pr1;
        no.P3  = no.P2;

        // e insere a chave na posicao 1
        no.C1  = promocao.chave;
        no.Pr1 = promocao.referencia;
        no.P2  = promocao.rrn_no_filho;
    }

    //se a chave for entrar na posicao 2
    else if(chave_esta_na_posicao(no.C2, promocao.chave)){
        //move as chaves 1 posicao para frente
        no.C4  = no.C3;
        no.Pr4 = no.Pr3;
        no.P5  = no.P4;

        no.C3  = no.C2;
        no.Pr3 = no.Pr2;
        no.P4  = no.P3;

        // e insere a chave na posicao 2
        no.C2  = promocao.chave;
        no.Pr2 = promocao.referencia;
        no.P3  = promocao.rrn_no_filho;
    }

    else if(chave_esta_na_posicao(no.C3, promocao.chave)){
        //move as chaves 1 posicao para frente
        no.C4  = no.C3;
        no.Pr4 = no.Pr3;
        no.P5  = no.P4;

        // e insere a chave na posicao 3
        no.C3  = promocao.chave;
        no.Pr3 = promocao.referencia;
        no.P4  = promocao.rrn_no_filho;
    }

    else{

        //e insere a chave na posicao 4
        no.C4  = promocao.chave;
        no.Pr4 = promocao.referencia;
        no.P4  = promocao.rrn_no_filho;
        
    }

    // uma nova chave foi indexada
    (no.nroChavesIndexadas)++;

    //reescreve o no atual
    fwrite_no(no, file);

    //nao houve promocao
    return(info_promocao){
        INVALID,
        INVALID,
        INVALID
    };
}

long long busca_recursiva(int rrn_atual, int chave_buscada, FILE *file){
    //se o no nao existe
    if(rrn_atual == INVALID){
        return INVALID;
    }

    //dados do no atual
    Pagina no = fread_no(rrn_atual, file);

    //procura o no atual e seus filhos
    
    if(chave_esta_na_posicao(no.C1, chave_buscada)){
        //se a chave estiber aqui, retorna a referencia
        //se nao estiver, retorna o no filho
        if (chave_buscada == no.C1) {
        return no.Pr1;
        } else {
        //se nao estiver, retorna o no filho
        return busca_recursiva(no.P1, chave_buscada, file);
        }
    }
    else if(chave_esta_na_posicao(no.C2, chave_buscada)){
        //se a chave estiber aqui, retorna a referencia
        //se nao estiver, retorna o no filho
        if (chave_buscada == no.C2) {
        return no.Pr2;
        } else {
        //se nao estiver, retorna o no filho
        return busca_recursiva(no.P2, chave_buscada, file);
        }
    }
    else if(chave_esta_na_posicao(no.C3, chave_buscada)){
        //se a chave estiber aqui, retorna a referencia
        //se nao estiver, retorna o no filho
        if (chave_buscada == no.C3) {
        return no.Pr3;
        } else {
        //se nao estiver, retorna o no filho
        return busca_recursiva(no.P3, chave_buscada, file);
        }
    }
    else if(chave_esta_na_posicao(no.C4, chave_buscada)){
        //se a chave estiber aqui, retorna a referencia
        //se nao estiver, retorna o no filho
        if (chave_buscada == no.C4) {
        return no.Pr4;
        } else {
        //se nao estiver, retorna o no filho
        return busca_recursiva(no.P4, chave_buscada, file);
        }
    }
    else{
        return busca_recursiva(no.P5, chave_buscada, file);
    }
}

void insere_arvoreB(int chave, long long referencia, FILE *file, int *raiz_rrn, int *rrn_livre){
//insere a chave no comeco da raiz de forma recursiva
    info_promocao promocao = insercao_recursiva(*raiz_rrn, chave, referencia, file, rrn_livre);
        
    if(promocao.chave != INVALID){
        //cria um novo no folha
        Pagina no;
        no.folha              = *raiz_rrn == INVALID ? '1' : '0';
        no.nroChavesIndexadas = 1;
        no.RRNdoNO = *rrn_livre;
        no.P1   = *raiz_rrn;
        no.C1   = promocao.chave;
        no.Pr1  = promocao.referencia;
        no.P2   = promocao.rrn_no_filho;
        no.C2   = INVALID;
        no.Pr2  = INVALID;
        no.P3   = INVALID;
        no.C3   = INVALID;
        no.Pr3  = INVALID;
        no.P4   = INVALID;
        no.C4   = INVALID;
        no.Pr4  = INVALID;
        no.P5   = INVALID;

        //escreve o novo no
        fwrite_no(no, file);
        
        //defino o no criado como novo no
        *raiz_rrn = no.RRNdoNO;

        //incrementa o proximo RRN livre
        (*rrn_livre)++;
    }

    return;

}

long long busca_arvoreb(int chave, FILE *file){
    //busca recursivamente pela chave comecando pela raiz
    return busca_recursiva(busca_raiz_rrn(file), chave, file);
}