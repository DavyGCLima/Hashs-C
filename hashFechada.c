#include "hashFechada.h"
#include <stdlib.h>


void inicializaHashFechada(THashFechada *H, int tamanhoInicial){
    int cont = 0;
    H->tamanho = tamanhoInicial;
    H->conteudo = (TEHash *)malloc(tamanhoInicial * sizeof(TEHash));
    int i;
    for(i = 0; i < tamanhoInicial; i++){
        H->conteudo[i].listaOrd = (Lista*)malloc(sizeof(Lista));
        inicializaLista(H->conteudo[i].listaOrd);
        cont++;
    }
}

int hashCodeFechado(char* chave){
    int v1 = chave[0]-'A';
    int v2 = chave[1]-'a';

    int res = v1*26+v2;
    return res;
}

void populaHashFechada(Lista *L, THashFechada *H){
    Elemento *cursor = L->primeiro;
    while(cursor->prox != NULL){
        insereHashFechada(H, cursor->conteudo);
        cursor = cursor->prox;
    }
}

void exibeHashFechada(THashFechada *H){
    int tam = H->tamanho;
    printf("\n\t\t TAM: %d ", tam);
    int i;
    for(i = 0; i < tam; i++){
        exibirLista(H->conteudo[i].listaOrd);
        printf("\n\n\t");
    }
}

int insereHashFechada(THashFechada *H, Cidade *cid){
    int cod = hashCodeFechado(cid->nome);
    //printf("\n\t letra1: %d, letra2: %d, total %d", cid->nome[0], cid->nome[1], cod);
    int inserido = 1;
    if(H->conteudo[cod].listaOrd != NULL){
        //printf("\n\t COd: %d, nome: %s", cod, cid->nome);
        inserirOrdNom(H->conteudo[cod].listaOrd, cid);
        inserido = 0;
    }
    return inserido;
}

Cidade* buscaHashFechadaPorNome(THashFechada *H, char* nome){
    int hashCod = hashCodeFechado(nome);
    if(hashCod  > H->tamanho)
        printf("\n\t Informação chave maior que o limite da hash");
    Cidade *cid = buscarPorNome(H->conteudo[hashCod].listaOrd, nome);
    return cid;
}

int excluiHashFechada(THashFechada *H, char* nome){
    int hashCod = hashCodeFechado(nome);
    int excluido = 1;
    excluido = excluirPorNome(H->conteudo[hashCod].listaOrd, nome);
    return excluido;
}


