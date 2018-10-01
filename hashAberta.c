#include "hashAberta.h"

void iniciarHashAberta(HashAberta *H, float fatorCarga, int tamanhoInicial){
    H->conteudo = (ElementoHashAberta*)malloc(tamanhoInicial*sizeof(ElementoHashAberta));
    H->loadFactor = fatorCarga;
    H->quantidade = 0;
    H->tamanho = tamanhoInicial;

    int i;
    for(i = 0; i < tamanhoInicial; i++){
        H->conteudo[i].flag = 0;
        H->conteudo[i].cidade = NULL;
    }
}

int hashCodeAberto(HashAberta *H, int chave){
    return (chave % H->tamanho);
}

void expandeHashAberta(HashAberta *H){
    int antTam = H->tamanho;
    int novoTam = (antTam + 10000);
    ElementoHashAberta *conteudoAntigo = H->conteudo;
    iniciarHashAberta(H, H->loadFactor, novoTam);

    int i;
    for(i = 0; i < antTam; i++){
        if(conteudoAntigo[i].flag == 1){
            inserirHashAberta(H, conteudoAntigo[i].cidade);
        }
    }
    free(conteudoAntigo);
}

void inserirHashAberta(HashAberta *Hash, Cidade *cid){
    int hasCode = hashCodeAberto(Hash, cid->numero);
    if(((float)Hash->quantidade/(float)Hash->tamanho) >= Hash->loadFactor){
        expandeHashAberta(Hash);
    }
    //printf("\n\t\t Hash: %d CodCId: %d", hasCode, cid->numero);
    while(Hash->conteudo[hasCode].flag == 1){
        hasCode = (hasCode + 1) % Hash->tamanho;
    }
    Hash->conteudo[hasCode].cidade = cid;
    Hash->quantidade++;
    Hash->conteudo[hasCode].flag = 1;
}

int buscaHashAberta(HashAberta *H, int chave){
    int hashCode = hashCodeAberto(H, chave);
    int cont = 0;
    int hashOriginal = hashCode;
    while(1){
        if(H->conteudo[hashCode].flag == 1){
            //if(H->quantidade == cont)
               // return -1;
            if(H->conteudo[hashCode].cidade->numero == chave){
                return hashCode;
            }
            cont++;
        }
        hashCode = (hashCode+1)%H->tamanho;
        if(H->quantidade == cont)
            return -1;
        //cont++;
    }
}

void populaHashAberta(HashAberta *H, Lista *L){
    Elemento *cursor = L->primeiro;
    int cont = 0;
    while(cursor->prox != NULL){
        //printf("\n\t Inserindo %d codCit: %d", cont++, cursor->conteudo->numero);
        inserirHashAberta(H, cursor->conteudo);
        cursor = cursor->prox;
    }
}

int excluiHashAberta(HashAberta *H, int chave){
    int excluido = 1;
    int hashCode = hashCodeAberto(H, chave);
    int item = -1;
    item = buscaHashAberta(H, chave);
    H->conteudo[item].cidade = NULL;
    H->conteudo[item].flag = -1;
    if(item != -1)
        excluido = 0;
    return excluido;
}

