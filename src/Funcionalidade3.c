#include "Funcionalidades.h"
#include "datatypesdef.h"
#include "lista.h"
#include "ArvoreB.h"

void PesquisaCampo(char *nomeArquivo, char *nomeArquivoIndice,Cabecalho *cabecalho) {
    leCabecalho(nomeArquivo, cabecalho);

    char nomeCampo[50];
    char valorCampo[50];
    scanf("%49s", nomeCampo);
    scan_quote_string(valorCampo);

    //essa parte foi adicionada para tornar a funcionalidade 3 a funcionalidade 6, o resto do codigo eh identico ao utilizado no trabalho introdutorio.
    if(strcmp(nomeCampo, "nomeTecnologiaOrigemDestino") == 0){
        //chama a funcao de pesquisa por chaves do indice arvore B
        pesquisa_tecnologia_arvoreb(nomeArquivo, nomeArquivoIndice, valorCampo);
        return;
    }







    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Calcula a posição do byte
    long int position = sizeof(Cabecalho);

    // Usa fseek para posicionar o ponteiro no byte desejado
    if (fseek(arquivo, position, SEEK_SET) != 0) {
        printf("Falha no processamento do arquivo.\n");
        fclose(arquivo);
        return;
    }

    int int_a; // grupo
    int int_b; // popularidade
    int int_c; // peso
    int int_d; // tamanho string1
    int int_f; // tamanho string 2
    char deletado;

    while (fread(&deletado, sizeof(char), 1, arquivo) && !feof(arquivo)) {

        // le os ints do registro
        fread(&int_a, sizeof(int), 1, arquivo);
        fread(&int_b, sizeof(int), 1, arquivo);
        fread(&int_c, sizeof(int), 1, arquivo);

        fread(&int_d, sizeof(int), 1, arquivo); // Tamanho da str1
        char str1[int_d + 1]; // adiciona +1 para o termino nulo
        fread(str1, sizeof(char), int_d, arquivo);
        str1[int_d] = '\0'; // termina nulo

        fread(&int_f, sizeof(int), 1, arquivo); // Tamanho da str2
        char str2[int_f + 1]; // adiciona +1 para o termino nulo
        fread(str2, sizeof(char), int_f, arquivo);
        str2[int_f] = '\0'; // termina nulo

        char auxlixo[150]; // criado para armazenar o lixo entre a string 2 e o comeco do proximo registro
        size_t tamlixo = (sizeof(Dado) + 20) * (1) - 1 - 5 * sizeof(int) - int_d - int_f;

        fread(&auxlixo, sizeof(char), tamlixo, arquivo); // le e armazena o lixo
        //verifica se o registro foi deletado
        if (deletado == '1') {
            
            continue;
        }

        if (strcmp(nomeCampo, "nomeTecnologiaOrigem") == 0) {
            if (strcmp(valorCampo, str1) == 0) {
                imprimeCampos(str1, int_a, int_b, int_f, str2, int_c);
            }
        } else if (strcmp(nomeCampo, "nomeTecnologiaDestino") == 0) {
            if (strcmp(valorCampo, str2) == 0) {
                imprimeCampos(str1, int_a, int_b, int_f, str2, int_c);
            }
        } else if (strcmp(nomeCampo, "grupo") == 0) {
            if (atoi(valorCampo) == int_a) {
                imprimeCampos(str1, int_a, int_b, int_f, str2, int_c);
            }
        } else if (strcmp(nomeCampo, "popularidade") == 0) {
            if (atoi(valorCampo) == int_b) {
                imprimeCampos(str1, int_a, int_b, int_f, str2, int_c);
            }
        } else if (strcmp(nomeCampo, "peso") == 0) {
            if (atoi(valorCampo) == int_c) {
                imprimeCampos(str1, int_a, int_b, int_f, str2, int_c);
            }
        }

        // volta para o início do loop
    }

    fclose(arquivo);
}
