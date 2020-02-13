/*
Em arvore com multiplos filhos, implemente as funcoes:
- Contabilize o total de valores registrados;
- Contabilize o total de nos folha;
- retornar a altura da arvore;
- imprima todos os valores em certo nivel(passado como parametro)

*/




#include <stdio.h>
#include <stdlib.h>

#include "arvore_MF.c"

int main(){

    tipoArvMulti *arv;
    arv = NULL;

    insereArvMulti(&arv,100 );
    insereArvMulti(&arv,7 );
    insereArvMulti(&arv,20 );
    insereArvMulti(&arv,80 );
    insereArvMulti(&arv,25 );
    insereArvMulti(&arv,77 );
    insereArvMulti(&arv,13 );
    insereArvMulti(&arv,23 );
   // insereArvMulti(&arv,77 );
    //insereArvMulti(&arv,13 );
    //insereArvMulti(&arv,23 );



    //insereArvMulti(&arv,101 );


   // imprimePreArvMulti(arv);printf("\n--\n");
    imprimeOrdem(arv); printf("\n--\n");
    //imprimePos(arv); printf("\n--\n");



    //imprimePreArvMulti(arv);printf("\n");

    int vl;
    vl = 77;
    if( buscaArvMulti(arv, vl))
        printf("Valor %d ENCONTRADO!\n", vl);
    else
        printf("NAO ENCONTRADO\n");


    removeArv(&arv, 23);
    return 1;

}
