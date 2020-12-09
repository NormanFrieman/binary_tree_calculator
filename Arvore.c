#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"
#include "string.h"

struct arv{
    int item;
    struct arv* esq;
    struct arv* dir;
};

static int max2(int a, int b){
    return (a > b) ? a : b;
}

// CRIA UMA ARVORE VAZIA
Arv* criaArvoreVazia(void){
    return NULL;
}

// CRIA UMA ARVORE COM alRMACAO NO NO RAIZ, E COM SUBARVORE ESQUERDA E SUBARVORE DIREITA
Arv* criaArvore(int item, Arv *sae, Arv *sad){
    Arv *novaArv = (Arv *)malloc(sizeof(Arv));

    novaArv->item = item;
    novaArv->esq = sae;
    novaArv->dir = sad;

    return novaArv;
}

// INSERE NÓ
Arv* insereNo(Arv *pai, Arv *filho, int condition){
    if(condition == 1){
        pai->esq = filho;
    }else{
        pai->dir = filho;
    }

    return pai;
}

// INSERE VALOR
Arv *insereValor(Arv *arv, int item){
    arv->item = item;
    return arv;
}

// LIBERA O ESPAÇO DE MEMORIA OCUPADO PELA ARVORE
Arv* liberaArvore(Arv *arv){
    if(!verificaArvore(arv)){
        liberaArvore(arv->esq);
        liberaArvore(arv->dir);
        free(arv);
    }

    return NULL;
}

// RETORNA "TRUE" SE A ARVORE ESTIVER VAZIA E "FALSE" CASO CONTRARIO
int verificaArvore(Arv *arv){
    return arv == NULL;
}

// RETORNA 0 SE A ARVORE ESTIVER VAZIA E 1 SE A POSICAO ESQ ESTIVER OCUPADA
int verificaGalhoArvore(Arv *arv){
    if(arv->esq == NULL){
        return 0;
    }else if(arv->esq != NULL && arv->dir == NULL){
        return 1;
    }else{
        return -1;
    }
}

// INDICA OCORRENCIA (1) OU NAO (0) DO CARACTER chave
int pertence(Arv *arv, int chave){
    if(verificaArvore(arv)){
        return 0;
    }else{
        return (arv->item == chave) || pertence(arv->esq, chave) || pertence(arv->dir, chave);
    }
}

// IMPRIME AS INFORMACOES DOS NÓS DA ARVORE
void imprimeArvore(Arv *arv){
    printf("<");
    if(!verificaArvore(arv)){
        if(arv->esq == NULL && arv->dir == NULL){
            printf("%d", arv->item);
        }else{
            printf("%c", arv->item);
        }
        imprimeArvore(arv->esq);        // mostra sae
        imprimeArvore(arv->dir);        // mostra sad
    }
    printf(">");
}

// RETORNA O QUE ESTA ABAIXO DA RAIZ
// 0 -> ESQUERDA
// 1 -> DIREITA
Arv* retornaArv(Arv *arv, int code){
    if(code == 0){
        return arv->esq;
    }else{
        return arv->dir;
    }
}

// RETORNA ALUNO DA RAIZ DA ARVORE
int retornaItem(Arv *arv){
    return arv->item;
}

// CALCULA ALTURA DA ARVORE
int alturaArvore(Arv *arv){
    if(verificaArvore(arv)){
        return -1;
    }else{
        return 1 + max2(alturaArvore(arv->esq), alturaArvore(arv->dir));
    }
}

// RETORNA O PAI DE UM NÓ
Arv* paiArvore(Arv *arv, int chave){
    if(verificaArvore(arv)){
        return NULL;
    }
    
    if(!verificaArvore(arv->esq) && arv->esq->item == chave || (!verificaArvore(arv->dir) && arv->dir->item == chave)){
        return arv;
    }
    
    Arv *aux = paiArvore(arv->esq, chave);
    
    if(aux == NULL){
        aux = paiArvore(arv->dir, chave);
    }
    
    return aux;
}

// RETORNA A QUANTIDADE DE FOLHAS DE UMA ARVORE
int folhas(Arv *arv){
    if(verificaArvore(arv->esq) && verificaArvore(arv->dir)){
        return 1;
    }else if(!verificaArvore(arv->esq) && verificaArvore(arv->dir)){
        return folhas(arv->esq);
    }else if(verificaArvore(arv->esq) && !verificaArvore(arv->dir)){
        return folhas(arv->dir);
    }

    return folhas(arv->esq) + folhas(arv->dir);
}

// RETORNA A QUANTIDADE DE OCORRENCIAS EM UMA ARVORE
int ocorrencias(Arv *arv, int chave){
    if(verificaArvore(arv)){
        return 0;
    }
    if(arv->item == chave){
        return (1 + ocorrencias(arv->esq, chave) + ocorrencias(arv->dir, chave));
    }

    return (ocorrencias(arv->esq, chave) + ocorrencias(arv->dir, chave));
    
}