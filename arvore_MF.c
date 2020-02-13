/*
 * Arvore com multiplos filhos: Esse tipo de arvore é uma generalização de uma arvore binaria.
 * Um parametro de determinar a ordem da arvore implica na capacidade maxima de registros em um nó na arvore com multiplos filhos.Assim, ao defirmos o valor de uma constante T, sabemos que cada nó da arvore tem capacidde p/ armazenar T valores e, consequentemente, terá T+1 filhos.
 * A definição de tipo p/ um nó na arvore com multiplos filhos constante de um vetor de tamanho T p/ armazenar os valores e um vetor de ponteiros de tamanho T+1 p/ levar aos filhos, como segue:
 * Tipo Arv_muli{
        inteiro valore[T]
        Arv_muli *filhos[T+1]
        inteiro quantidade
    }
*/


#include <stdio.h>
#include <stdlib.h>

#ifndef ARV_MULTI_C
#define ARV_MULTI_C


//definicao de constatantes
#define T 3

//definicao de tipo
struct estArvMulti{
    int valores[T];
    struct estArvMulti *filhos[T+1];
    int quant;
};
typedef struct estArvMulti tipoArvMulti;


//prototipos
void insereArvMulti(tipoArvMulti **arv, int valor);
tipoArvMulti *alocaNo( int valor);
int buscaArvMulti( tipoArvMulti *arv,int valor);
void imprimePreArvMulti(tipoArvMulti *arv);
void removeArv(tipoArvMulti **arv, int valor);
int ehFolha(tipoArvMulti *arv);

//Função que ira fazer a inserção na arvore multipla
void insereArvMulti(tipoArvMulti **arv, int valor){
    //procura o intervalo desse
    // chega se o nó esta vazio
    //
    int i;

    //Verifica se um nó nulo foi alcancado
    if(*arv == NULL){
        *arv = alocaNo(valor);
    }else{
        //Verifica se há espaço disponivel
        if((*arv)->quant < T){
            //executa a inserção ordenada
            i = (*arv)->quant;
            while( ((*arv)->valores[i-1] > valor) && ((i -1) >= 0)){
                (*arv)->valores[i] = (*arv)->valores[i-1];
                i--;

            }
            (*arv)->valores[i] = valor;
            (*arv)->quant++;
        }else{//caso o nó esteja cheia, busca pelo filho em que
            i = 0;
            while( (valor > (*arv)->valores[i]) && (i < T) ){
                i++;
                insereArvMulti(&(*arv)->filhos[i],valor);

            }

        }


    }


}

tipoArvMulti *alocaNo( int valor){
    tipoArvMulti *novoNo;
    novoNo = (tipoArvMulti*) malloc(sizeof(tipoArvMulti));
    int i;
    for( i = 0; i < T;i++){
        novoNo->valores[i] = 0;
        novoNo->filhos[i] = NULL;

    }
    novoNo->filhos[T] = NULL;//inicializa o ultimo filho que ficou faltando

    novoNo->valores[0] = valor;
    novoNo->quant = 1;

}


//Funcao de impressao em pre-ordem da arvore com multiplos
void imprimePreArvMulti(tipoArvMulti *arv){
    int i ;
    //Imprime valores
    if(arv != NULL){
        for(i = 0; i < arv->quant; i++){
            printf("[%d]",arv->valores[i]);
        }
        printf("\n");
        //Executa achamda recursiva de impressao
        for(i = 0; i < arv->quant; i++){
            imprimePreArvMulti(arv->filhos[i]);

        }
    }else{
        printf("[NULL]\n");

    }
}



int buscaArvMulti(tipoArvMulti *arv, int valor){
    if(  arv == NULL){
        return 0;
    }else{
        int i;
        i = 0;
        while(  ( (arv->valores[i]) < valor) && (i < arv->quant)   )
            i++;
        if((i < arv->quant) && ( (arv->valores[i]) == valor) )
            return 1;
        else
            return buscaArvMulti(arv->filhos[i], valor);


    }
}



//Funcao de impressao em pre-ordem da arvore com multiplos
void imprimeOrdem(tipoArvMulti *arv){
    int i ;
    //Imprime valores
    if(arv != NULL){
        for(i = 0; i < arv->quant; i++){
            imprimeOrdem(arv->filhos[i]);
            printf("[%d]",arv->valores[i]);
        }
        imprimeOrdem(arv->filhos[i]);
    }
}

//Funcao de impressao em pre-ordem da arvore com multiplos
void imprimePos(tipoArvMulti *arv){
    int i ;
    //Imprime valores
    if(arv != NULL){
        //executa a chamada recursiva da impressao para os filhos
        for(i = 0; i < arv->quant; i++){
            imprimePos(arv->filhos[i]);
        }
        printf("\n");
        //Executa achamda recursiva de impressao
        for(i = 0; i < arv->quant; i++){
            imprimePreArvMulti(arv->filhos[i]);

        }
    }else{
        printf("[NULL]\n");

    }
}



//Função para remoção em arvore com multiplos filhos
void removeArv(tipoArvMulti **arv, int valor){
    /*Sao 3 casos para a remoção . 1) remover valor em no folha(remocao ordenada); 2)
remover um valor que possui filho esquerdo(neste caso o maior valor do filho esquerdo deve subir
;3) remover valor sem filho esquerdo (nesse caso ) seus filhos devem ser reposicionados no no e o
maior valor disponivel no deve subir*/

    //Verifica se o no e diferente de nulo
    if(*arv != NULL){


        //chamada recursiva ate encontrar o valor a ser removido
        int i,j;
        i = 0;
        while( (i < (*arv)->quant) && (valor > (*arv)->valores[i]) ){
            i++;
        }
        //Valor nao encontrado, e verificou todos os valores desce direita
        if(  i == (*arv)->quant ){
            removeArv( &(*arv)->filhos[i], valor);
        }else{
            //se valor nao foi encontrado neste no, faz chamada recursiva
            if( valor < (*arv)->valores[i]){
                removeArv( &(*arv)->filhos[i],valor );
            }else if(valor == (*arv)->valores[i] ){
                //Caso valor foi encontrado, verifica os casos

                //Caso 1: Remoção de um valor em nó folha
                if( ehFolha(*arv)){
                    j = (*arv)->quant;
                    while( i <  (*arv)->quant-1){
                        (*arv)->valores[i] = (*arv->valores[i+1]);
                    }
                    (*arv)->quant--;

                    //Verifica se o no ficou vazio
                    if((*arv)->quant == 0){
                        free(*arv);
                        *arv = NULL;
                    }

                }else 
                        // Caso 2: Caso o valor encotrado tenha filho
                        if((*arv)->filho[i] != NULL){
                            int maior;
                            maior = encontraMaior((*arv)->filhos[i]);
                            (*arv)->valores[i] = maior; 
                            removeArv( &(*arv)->filhos[i],maior);
                            
                        }
            }



        }
    }





}



//Funcao que verifica se um no eh folha(retorna 1) ou nao (retorna 0)
int ehFolha(tipoArvMulti *arv){
    int i;
    for( i = 0; i <= arv->quant; i++){
        if(arv->filhos[i] != NULL){
            return 0;
        }

    }
    return 1;

}

//Função que encontra o maior valor em uma arvore 
int encontraMaior(tipoArvMulti *arv){
    int i;
    if( arv->filhos[arv->quant] != NULL){
        return encontraMaior(arv->filhos[arv->quant]);
    }else{
        return arv->valores[arv->quant-1];
    }
    
    
    
}




#endif

