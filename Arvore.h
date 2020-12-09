#ifndef ArvoreBinaria_h
#define ArvoreBinaria_h

#include <stdio.h>

typedef struct arv Arv;

// CRIA UMA ARVORE VAZIA
Arv* criaArvoreVazia(void);

// CRIA UMA ARVORE COM INFORMACAO NO NO RAIZ, E COM SUBARVORE ESQUERDA E SUBARVORE DIREITA
Arv* criaArvore(int item, Arv *sae, Arv *sad);

// INSERE NÓ
Arv* insereNo(Arv *pai, Arv *filho, int condition);

// INSERE VALOR
Arv *insereValor(Arv *arv, int item);

// LIBERA O ESPAÇO DE MEMORIA OCUPADO PELA ARVORE
Arv* liberaArvore(Arv *arv);

// RETORNA "TRUE" SE A ARVORE ESTIVER VAZIA E "FALSE" CASO CONTRARIO
int verificaArvore(Arv *arv);

// RETORNA 0 SE A ARVORE ESTIVER VAZIA E 1 SE A POSICAO ESQ ESTIVER OCUPADA
int verificaGalhoArvore(Arv *arv);

// INDICA OCORRENCIA (1) OU NAO (0) DO CARACTER Chave
int pertence(Arv *arv, int chave);

// IMPRIME AS INFORMACOES DOS NÓS DA ARVORE
void imprimeArvore(Arv *arv);

// RETORNA ITEM DA RAIZ DA ARVORE
int retornaItem(Arv *arv);

// RETORNA O QUE ESTA ABAIXO DA RAIZ
// 0 -> ESQUERDA
// 1 -> DIREITA
Arv* retornaArv(Arv *arv, int code);

// CALCULA ALTURA DA ARVORE
int alturaArvore(Arv *arv);

// RETORNA O PAI DE UM NÓ
Arv* paiArvore(Arv *arv, int chave);

// RETORNA A QUANTIDADE DE FOLHAS DE UMA ARVORE
int folhas(Arv *arv);

// RETORNA A QUANTIDADE DE OCORRENCIAS EM UMA ARVORE
int ocorrencias(Arv *arv, int chave);

#endif