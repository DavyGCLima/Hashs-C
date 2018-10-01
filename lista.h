#ifndef lista
#define lista
#include <stdlib.h>
#include <time.h>

typedef struct cidade{
    char *nome;
    int numero;
    int populacao;
}Cidade;

typedef struct elemento{
    Cidade *conteudo;
    struct elemento *prox;
    struct elemento *ant;
}Elemento;

typedef struct lista{
    Elemento *primeiro;
    Elemento *ultimo;
    int total;
}Lista;

void inicializaLista(Lista *L);
void inserir(Lista *L, Cidade *cid);
Cidade* buscarPorNome(Lista *L, char* nome);
Cidade* buscarPorCodigo(Lista *L, int cod);
void alterarCidade(Lista *L, Cidade *novaCidade);
void exibirNomeDesordenado(Cidade *cidade);
void exibirLista(Lista *lista);
void gerarListaOrdCod(Lista *L, Lista *LOrdCod);
void gerarListaOrdNom(Lista *L, Lista *LOrdNom);
void gerarListasOrdenadas(Lista *L, Lista *LOrdCod, Lista *LOrdNom);
void inserirOrdCod(Lista *LOrdCod, Cidade *cid);
void inserirOrdNom(Lista *L, Cidade *cid);
void gerarArquivo(Lista *listaGen, char* nomeArq);
Elemento* buscarElementoPorCodigo(Lista *L, int cod);
Elemento* buscarElementoPorNome(Lista *L, char* nome);
int excluirPorNome(Lista *L, char* nome);
int excluirPorCodigo(Lista *L, int cod);

#endif
