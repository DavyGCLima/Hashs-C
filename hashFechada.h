#ifndef hash_Fechada
#define hash_Fechada
#include "lista.h"
#include <string.h>

typedef struct elementoHash{
    Lista *listaOrd;
}TEHash;

typedef struct hashFechada{
    TEHash *conteudo;
    int tamanho;
}THashFechada;

void inicializaHashFechada(THashFechada *H, int tamanhoInicial);
int hashCodeFechado(char* chave);
int insereHashFechada(THashFechada *H, Cidade *cid);
Cidade* buscaHashFechadaPorNome(THashFechada *H, char* nome);
int excluiHashFechada(THashFechada *H, char* nome);
void populaHashFechada(Lista *L, THashFechada *H);
void exibeHashFechada(THashFechada *H);

#endif
