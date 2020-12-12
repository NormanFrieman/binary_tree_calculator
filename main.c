#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "Arvore.h"

int identificaPosicao(char *entrada, int code){
    int aux = code;
    if(entrada[code+1] != '(' && entrada[code+1] != ')'){
        aux = identificaPosicao(entrada, code+1);
    }
    return aux;
}

int retornaNumero(char *entrada, int inicio, int fim){
    int num = 0, aux = 1;
    if(inicio != fim){
        for(int i = fim; i >= inicio; i--){
            aux = 1;
            for(int j = 0; j <= (fim - i - 1); j++){
                aux = aux * 10;
            }
            num += (entrada[i] - 48) * aux;
        }
    }else{
        num = entrada[inicio] - 48;
    }

    return num;
}

int montaArvore(char *entrada, Arv *expressao, int code){
    int final, num;

    if(entrada[code] == '('){
        Arv *novaArv = criaArvore('f', NULL, NULL);
        
        if(verificaGalhoArvore(expressao) == 0){
            expressao = insereNo(expressao, novaArv, 1);
        }else{
            expressao = insereNo(expressao, novaArv, 0);
        }
        code = montaArvore(entrada, novaArv, code+1);

    }else if(entrada[code] == ')'){
        return code;
    }else if(entrada[code] >= '0' && entrada[code] <= '9'){
        final = identificaPosicao(entrada, code);
        num = retornaNumero(entrada, code, final);

        code = final;
        insereValor(expressao, num);
    }else{
        insereValor(expressao, entrada[code]);
    }

    if(code < strlen(entrada)){ 
        montaArvore(entrada, expressao, code+1);
    }
}

int resolveArvore(Arv *expressao){
    int resultExp = retornaItem(expressao);
    int resultado = 0;

    if(resultExp == '+' || resultExp == '-' || resultExp == '*' || resultExp == '/'){
        Arv *esquerdaArv = retornaArv(expressao, 0);
        Arv *direitaArv = retornaArv(expressao, 1);

        int esq = retornaItem(esquerdaArv);
        int dir = retornaItem(direitaArv);

        if(esq == '+' || esq == '-' || esq == '*' || esq == '/'){
            if(folhas(esquerdaArv) > 1){
                esq = resolveArvore(esquerdaArv);
            }
        }
        if(dir == '+' || dir == '-' || dir == '*' || dir == '/'){
            if(folhas(direitaArv) > 1){
                dir = resolveArvore(direitaArv);
            }
        }

        if(resultExp == '+'){
            resultado = resultado + (esq + dir);
        }else if(resultExp == '-'){
            resultado = resultado + (esq - dir);
        }else if(resultExp == '*'){
            resultado = resultado + (esq * dir);
        }else{
            resultado = resultado + (esq / dir);
        }

        return resultado;
    }
    
    return resultExp;
}

char* retornaExpressao(FILE *fp){
    char linha[120];
    char *entrada;

    fscanf(fp, "%s", linha);
    entrada = strdup(linha);

    return entrada;
}

void resetarSaida(){
    FILE *saida;

    saida = fopen("saida.txt", "w");
    fclose(saida);
}

int main(){
    FILE *fp, *fout;

    fp = fopen("entrada.txt", "r");
    resetarSaida();
    fout = fopen("saida.txt", "a");
    
    // LER VARIAS EXPRESSOES ESCRITAS NO ARQUIVO TXT
    if(fp != NULL){
        while(!feof(fp)){
            char *entrada = retornaExpressao(fp);
            Arv *expressao = criaArvore('p', NULL, NULL);
            
            montaArvore(entrada, expressao, 1);

            imprimeArvore(expressao);
            printf("\n");

            int resultado = resolveArvore(expressao);
            fprintf(fout, "%d\n", resultado);
            printf("Resultado: %d\n", resultado);

            free(entrada);
            liberaArvore(expressao);
        }
    }else{
        printf("Erro ao ler o arquivo...\n");
    }

    fclose(fp);
    fclose(fout);

    return 0;
}

/*
Casos para exemplo:
((((5)-(3))*((4)/(1)))+(10))    = 18
((((10)*(3))+(5))/((10)-(5)))   = 7
((((47)-(7))*(2))-(3))          = 77
((((120)*(2))-(100))*(10))      = 1400
((5)+(1))                       = 6
(((4)+((3)*(1)))/(7))           = 1
*/