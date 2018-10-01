#include <stdio.h>
#include <stdlib.h>
#include "hashFechada.h"
#include "hashAberta.h"

void zerarString(char *s){
    int i;
    for(i = 0; i < sizeof(s); i++){
        s[i] = "\0";
    }
    //linha[50] = "\0";
}

void lerArquivo(Lista *L){
    clock_t inic = clock();
    FILE *arquivo = fopen("entrada.txt", "r");
    if(!arquivo){
        printf("\n\t Erro ao ler o arquivo");
    }else{
    	while(!feof(arquivo)){
            char linha[40];
            zerarString(linha);
	        Cidade *cidade = (Cidade*)malloc(sizeof(Cidade));
	        char* conteudo = fgets(linha, sizeof(linha), arquivo);
	        if(conteudo != NULL){
                cidade->numero = atoi(strtok(conteudo, ";"));
                char *nom = (char *)malloc(10 * sizeof(char));
                char *nomAux;
                nomAux = strtok(NULL, ";");
                strcpy(nom, nomAux);
                cidade->nome = nom;
                cidade->populacao = atoi(strtok(NULL, ";"));
                inserir(L, cidade);
	        }
		}
    }
    clock_t fim = clock();
        printf("\n\t Arquivo lido!");
        double res = (double)(fim - inic)/CLOCKS_PER_SEC;
        printf("\n\t tempo: %f",res);
    fclose(arquivo);
}

void gerarArquivoHashAberta(HashAberta *h){
     FILE *arquivo = fopen("saidaHashAberta.txt", "w");
    if(!arquivo){
        printf("\n\t Erro ao criar o arquivo saidaHashAberta");
    }else{
    	int i;
    	for(i = 0; i < h->tamanho; i++){
            if(h->conteudo[i].flag == 1){
                fprintf(arquivo, "%d;%d;%s;%d\n", i, h->conteudo[i].cidade->numero, h->conteudo[i].cidade->nome
                        , h->conteudo[i].cidade->populacao);
            }
    	}
    }
    fclose(arquivo);
}

void gerarArquivoHashFechada(THashFechada *h){
     FILE *arquivo = fopen("saidaHashFechada.txt", "w");
    if(!arquivo){
        printf("\n\t Erro ao criar o arquivo saidaHashFechada");
    }else{
        int tam = h->tamanho;
        int i;
        for(i = 0; i < tam; i++){
            Elemento *cursor = h->conteudo[i].listaOrd->primeiro;
            while(cursor != NULL){
                fprintf(arquivo, "%d;%d;%s;%d\n", i, cursor->conteudo->numero,
                        cursor->conteudo->nome, cursor->conteudo->populacao);
                cursor = cursor->prox;
            }
        }
    }
    fclose(arquivo);
}

void lerOperacoes(Lista *L, HashAberta *hA, THashFechada *hF){
    FILE *arquivo = fopen("operacoes.txt", "r");
    if(!arquivo){
        printf("\n\t Erro ao ler o arquivo");
    }else{
        FILE *arqTempo = fopen("temposdebusca.txt", "w");
        if(!arqTempo){
            printf("\n\t Erro ao criar arquivo de tempo de busca ");
        }else{
            while(!feof(arquivo)){
                char* linhaTempo = (char*)malloc(40*sizeof(char));
                zerarString(linhaTempo);

                char linha[40];
                zerarString(linha);
                char* conteudo = fgets(linha, sizeof(linha), arquivo);
                char *operacao = strtok(conteudo, ";");
                printf("\n\t ===== OPERACAO: %s ", operacao);
                if(operacao == NULL || strcmp(operacao, "\n") == 0 || operacao == EOF || strcmp(operacao, "\0") == 0 || operacao == '\0') {
                    printf("\n\t FIM DA EXECUCAO ");
                }else{
                    if(strcmp(operacao, "I") == 0){
                    printf("\n\t ===== I ");
                    Cidade *cid = (Cidade*)malloc(sizeof(Cidade));
                    cid->numero = atoi(strtok(NULL, ";"));
                    char *nom = (char *)malloc(10 * sizeof(char));
                    char *nomAux;
                    nomAux = strtok(NULL, ";");
                    strcpy(nom, nomAux);
                    cid->nome = nom;
                    cid->populacao = atoi(strtok(NULL, ";"));
                    inserir(L, cid);
                    insereHashFechada(hF, cid);
                    inserirHashAberta(hA, cid);

                    }else if(strcmp(operacao, "B") == 0){
                        printf("\n\t ===== B ");
                        int cod = atoi(strtok(NULL, ";"));
                        char *nom = (char*)malloc(40*sizeof(char));
                        char *nomAux;
                        zerarString(nom);
                        nomAux = strtok(NULL, ";");
                        nomAux = strtok(nomAux, "\n");
                        strcpy(nom, nomAux);

                        int encontrouL = 0;
                        clock_t inicL = clock();
                        Cidade *busca = buscarPorCodigo(L, cod);
                        clock_t fimL = clock();
                        double resL = (double)(fimL - inicL)/CLOCKS_PER_SEC;
                        if(busca != NULL){
                            printf("\n\t\t Busca Lista tempo: %f",resL);
                            encontrouL = 1;
                        }
                        else{
                            printf("\n\t\t Elemnto não encontrado em Lista %f", resL);
                        }

                        int encontrouHA = 0;
                        clock_t inicAb = clock();
                        int busca3 = buscaHashAberta(hA, cod);
                        clock_t fimAb = clock();
                        double resAb = (double)(fimAb - inicAb)/CLOCKS_PER_SEC;
                        if(busca3 != -1){
                            printf("\n\t\t  Busca Hash Aberta tempo: %f",resAb);
                            encontrouHA = 1;
                        }
                        else
                            printf("\n\t\t Elemnto não encontrado em HashAberta %f", resAb);

                        int encontrouHF = 0;
                        clock_t inicFe = clock();
                        Cidade *busca2 = buscaHashFechadaPorNome(hF, nom);
                        clock_t fimFe = clock();
                        double resFe = (double)(fimFe - inicFe)/CLOCKS_PER_SEC;
                        if(busca2 != NULL){
                            printf("\n\t\t Busca hash fechada tempo: %f",resFe);
                            encontrouHF = 1;
                        }
                        else
                            printf("\n\t\t Elemnto não encontrado em HashFechada %f", resFe);

                       int verificador =  fprintf(arqTempo, "%d;%d;%.2f;%d;%.2f;%d;%.2f\n", cod, encontrouL, resL, encontrouHA, resAb, encontrouHF, resFe);
                        if (verificador == EOF)
                            printf("\n\n\t Nao sucedido em escrever linha");

                    }else if(strcmp(operacao, "E") == 0){
                        printf("\n\t ===== E ");
                        int ex = atoi(strtok(NULL, ";"));
                        Cidade *cid = buscarPorCodigo(L, ex);
                        char* nom = (char*)malloc(40*sizeof(char));
                        zerarString(nom);
                        strcpy(nom, cid->nome);
                        int exclusao1 = excluiHashAberta(hA, ex);
                        if(exclusao1 != 1)
                            printf("\n\t excluido da hashAberta ");
                        int exclusao2 = excluirPorCodigo(L, ex);
                        if(exclusao2 != 1)
                            printf("\n\t excluido da lista ");
                        int exclusao3 = excluiHashFechada(hF, nom);
                        if(exclusao3 != 1)
                            printf("\n\t excluido da hash fechada");
                    }else{
                        printf("\n\t ============ Operacao Ivalida %s =========== ", operacao);
                        system("PAUSE");
                        system("EXIT");
                    }
                }

            }//FIM WHILE
        }// FIM ELSE ARQTEMPO
        fclose(arqTempo);
    }//FIM ELSE
    fclose(arquivo);
}//FIM METODO

int main()
{
   printf("\t Iniciando leitura\n");
   Lista *L;
   L = (Lista*)malloc(sizeof(Lista));
   inicializaLista(L);

   THashFechada *hFechada = (THashFechada*)malloc(sizeof(THashFechada));
   inicializaHashFechada(hFechada, 676);

   int tam1 = 3530000;
   int tam2 = 10000;
   HashAberta *hAberta = (HashAberta*)malloc(sizeof(HashAberta));
   iniciarHashAberta(hAberta, 0.98, tam1);

   lerArquivo(L);
   printf("\n\t Arquivo Lido!");

   clock_t inic_Fe = clock();
   populaHashFechada(L, hFechada);
   clock_t fim_Fe = clock();
   double res = (double)(fim_Fe - inic_Fe)/CLOCKS_PER_SEC;
   printf("\n\t hash fechada tempo: %f",res);
   printf("\n\t Hash Fechada populada");

   clock_t inic_Ab = clock();
   populaHashAberta(hAberta, L);
   clock_t fim_Ab = clock();
   double res2 = (double)(fim_Ab - inic_Ab)/CLOCKS_PER_SEC;
   printf("\n\t hash aberta tempo: %f",res2);
   printf("\n\t Hash Aberta populada");

   //TESTES================================
    lerOperacoes(L, hAberta, hFechada);

    gerarArquivoHashAberta(hAberta);

    gerarArquivoHashFechada(hFechada);


    printf("\n\n\t Fim do programa\n");
    system("PAUSE");
    system("EXIT");
}
