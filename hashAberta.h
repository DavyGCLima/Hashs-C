#ifndef hash_Aberta
#define hash_Aberta
#include "lista.h"
#include <string.h>

typedef struct elemntoHashAberta{
    Cidade *cidade;
    int flag; //0 - nunca utilizado, 1 - ocupado, -1 excluido
}ElementoHashAberta;

typedef struct hashAberta{
    ElementoHashAberta *conteudo;
    int quantidade;
    int tamanho;
    float loadFactor;
}HashAberta;

void iniciarHashAberta(HashAberta *H, float fatorCarga, int tamanhoInicial);
int hashCodeAberto(HashAberta *H, int chave);
void expandeHashAberta(HashAberta *H);
void inserirHashAberta(HashAberta *Hash, Cidade *cid);
int buscaHashAberta(HashAberta *H, int chave);
void populaHashAberta(HashAberta *H, Lista *L);
int excluiHashAberta(HashAberta *H, int chave);

#endif
