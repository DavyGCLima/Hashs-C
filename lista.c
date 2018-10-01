#include "lista.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

void inicializaLista(Lista *L){

    L->primeiro = NULL;
    L->ultimo = NULL;
    L->total = 0;
}

void inserir(Lista *L, Cidade *cid){
    //printf("\n\n\t\t CURSOR: %s", cursor);

    Elemento *no = (Elemento*)malloc(sizeof(Elemento));
    no->conteudo = cid;
    no->ant = NULL;
    no->prox = NULL;
    //printf("\n\t iniciando insercao de: %s", cid->nome);
    if(L->primeiro == NULL){
        //printf("\n\n\t Lista vazia");
        L->primeiro = no;
        L->ultimo = no;

        //printf("%s" ,cid->nome);
    }else{
        L->ultimo->prox = no;
        no->ant = L->ultimo;
        L->ultimo = no;

        //printf("\n\t anterior: %s", no->ant->conteudo->nome);
        L->total++;
        //printf("\n\t inserido: %s", L->ultimo->conteudo->nome);
    }
}

Cidade* buscarPorNome(Lista *L, char* nome){
   Elemento *cursor = buscarElementoPorNome(L, nome);
   if(cursor != NULL)
        return cursor->conteudo;
    else
        return NULL;
}

Cidade* buscarPorCodigo(Lista *L, int cod){
    Elemento *cursor = buscarElementoPorCodigo(L, cod);
    if(cursor != NULL)
        return cursor->conteudo;
    else
        return NULL;
}

Elemento* buscarElementoPorNome(Lista *L, char* nome){
    Elemento *cursor = L->primeiro;
    int cont = 0;
    if(L->primeiro == NULL)
        printf("\n\n\t Lista vazia ======");
    while((cursor != NULL) && (strcmp(cursor->conteudo->nome, nome) != 0)){
        cont++;
        if(cursor->prox == NULL){
            cursor = NULL;
            return NULL;
        }
        else{
            cursor = cursor->prox;
        }
    }
    return cursor;
}

Elemento* buscarElementoPorCodigo(Lista *L, int cod){
      Elemento *cursor = L->primeiro;
    int cont = 0;
    if(L->primeiro == NULL)
        printf("\n\n\t Lista vazia ======");
    while(cursor != NULL && cursor->conteudo->numero != cod){
        cont++;
        if(cursor->prox == NULL){
            cursor = NULL;
            return NULL;
        }
        else{
            cursor = cursor->prox;
        }
    }
    return cursor;
}

void exibirNomeDesordenado(Cidade *cid){
    printf("\n\t Cidade: %s", cid->nome);
    printf("\n\t Numero: %d", cid->numero);
    printf("\n\t Populacao: %d", cid->populacao);
    printf("\n");
}

void gerarListasOrdenadas(Lista *L, Lista *LOrdCod, Lista *LOrdNom){
    printf("\n\t Preparando listas");
    //criar variaveis para comparações de tempo
    //chamada dos metodos de gração individuais
//    exibirLista(L);
//    printf("\n\t Lista desordenada\n");
//    system("PAUSE");
//    system("CLS");
    //gerarArquivo(L, "Verifica.txt");

    clock_t inic1 = clock();
    gerarListaOrdCod(L, LOrdCod);
    clock_t fim1 = clock();

    double res1 = (double)(fim1 - inic1)/CLOCKS_PER_SEC;
    printf("\n\t Tempos L Ordenada Cod: inic %f, fim %f, total %f\n", (float)inic1/CLOCKS_PER_SEC,
            (float)fim1/CLOCKS_PER_SEC, res1);
    system("PAUSE");
    system("CLS");

    //gerarListaOrdNom();
    clock_t inic2 = clock();
    gerarListaOrdNom(L, LOrdNom);
    clock_t fim2 = clock();

    double res2 = (double)(fim2 - inic2)/CLOCKS_PER_SEC;
    printf("\n\t Tempos L Ordenada por Nome: inic %f, fim %f, total %f\n", (float)inic2/CLOCKS_PER_SEC,
           (float)fim2/CLOCKS_PER_SEC, res2);
    system("PAUSE");
    system("CLS");

    //gerar arquivos das listas
    //printf("\n\t QTD: %d\n", LOrdCod->total);
   // system("PAUSE");
//    exibirLista(LOrdCod);
//    printf("\n\t Lista Ordenada por Codigo\n");
//    system("PAUSE");
//    system("CLS");
//    exibirLista(LOrdNom);
//    printf("\n\t Lista Ordenada por Nome\n");
//    system("PAUSE");
//    system("CLS");
    gerarArquivo(LOrdCod, "saidaOrdCod.txt");
    gerarArquivo(LOrdNom, "saidOrdNome.txt");
}

void exibirLista(Lista *L){
    Elemento *cursor = L->primeiro;
    system("CLS");

    while(cursor != NULL){
        printf("\n\t Cidade: %s, Cod: %d, Populacao: %d \n", cursor->conteudo->nome,
               cursor->conteudo->numero, cursor->conteudo->populacao);
        cursor = cursor->prox;
    }
}

void gerarListaOrdCod(Lista *L, Lista *LOrdCod){
    printf("\n\t Gerando lista Ordenada por codigo");
    Elemento *cursor = L->primeiro;
    while(cursor != NULL){
       inserirOrdCod(LOrdCod, cursor->conteudo);
       cursor = cursor->prox;
    }
    printf("\n\t Lista de Nome gerada");
}

void inserirOrdCod(Lista *LOrdCod, Cidade *cid){
    //printf("\n\t Inserindo: %s", cid->nome);
    Elemento *cursor  = LOrdCod->primeiro;
    Elemento *anterior = NULL;
    Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
    novo->conteudo = cid;
    novo->ant = NULL;
    novo->prox = NULL;

    if(cursor == NULL){
        LOrdCod->primeiro = novo;
        LOrdCod->ultimo = novo;
        LOrdCod->total = 1;
    }else{
        while(cursor != NULL && cursor->conteudo->numero < novo->conteudo->numero){
            anterior = cursor;
            cursor = cursor->prox;
        }
        novo->prox = cursor;
        if(anterior == NULL){
            LOrdCod->primeiro = novo;
        }else{
            anterior->prox = novo;
        }

    }
}

void gerarListaOrdNom(Lista *L, Lista *LOrdNom){
    printf("\n\t Gerando lista Ordenada por Nome");
    Elemento *cursor = L->primeiro;
    while(cursor != NULL){
        inserirOrdNom(LOrdNom, cursor->conteudo);
        cursor = cursor->prox;
    }
}

void inserirOrdNom(Lista *L, Cidade *cid){

    Elemento *cursor  = L->primeiro;
    Elemento *anterior = NULL;
    Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
    novo->conteudo = cid;
    novo->ant = NULL;
    novo->prox = NULL;

    if(cursor == NULL){
        L->primeiro = novo;
        L->ultimo = novo;
        L->total = 1;
    }else{
        while(cursor != NULL && strcmp(cursor->conteudo->nome, novo->conteudo->nome) < 0){
            anterior = cursor;
            cursor = cursor->prox;
        }
        novo->prox = cursor;
        //novo->ant = anterior;
        //cursor->ant = novo;
        if(anterior == NULL){
            L->primeiro = novo;
        }else{
            anterior->prox = novo;
        }
    }
}

void gerarArquivo(Lista *listaGen, char* nomeArq){
    FILE *arquivo = fopen(nomeArq,"wt");
    printf("\n\n");
    int res;
    if(arquivo == NULL)
        printf("\n\t Erro ao criar arquivo");
    else{
        Elemento *cursor = listaGen->primeiro;
        while(cursor->prox != NULL){
            printf("\n\t Gravando: %d %s %d %p prox: %s", cursor->conteudo->numero,
                    cursor->conteudo->nome, cursor->conteudo->populacao, cursor->conteudo,
                    /*cursor->prox->conteudo,*/ cursor->prox->conteudo->nome);
            res = fprintf(arquivo, "%d;%s;%d;%p\n", cursor->conteudo->numero,
                    cursor->conteudo->nome, cursor->conteudo->populacao, cursor->conteudo);
            if(res == EOF)
                printf("\n\t Erro ao escrever no arquivo");
            cursor = cursor->prox;
        }
    }
    fclose(arquivo);
}

int excluirPorNome(Lista *L, char* nome){
    int excluido = 1;
    Elemento *elemento = NULL;
    elemento = buscarElementoPorNome(L, nome);
    if(elemento != NULL){
         if(elemento->ant != NULL)
            elemento->ant->prox = elemento->prox;
        else
            L->primeiro = elemento->prox;
        if(elemento->prox != NULL)
            elemento->prox->ant = elemento->ant;
        else
            L->ultimo = elemento->ant;
        free(&elemento);
        excluido = 0;
    }
    return excluido;
}

int excluirPorCodigo(Lista *L, int cod){
    int excluido = 1;
    Elemento *elemento = NULL;
    elemento = buscarElementoPorCodigo(L, cod);
    if(elemento != NULL){
        if(elemento->ant != NULL)
            elemento->ant->prox = elemento->prox;
        else
            L->primeiro = elemento->prox;
        if(elemento->prox != NULL)
            elemento->prox->ant = elemento->ant;
        else
            L->ultimo = elemento->ant;
        free(&elemento);
        excluido = 0;
    }
    return excluido;
}

