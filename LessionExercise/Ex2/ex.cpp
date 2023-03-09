#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

// Esempio per allocazione vettori in CPP.


struct numero{
    int val_;

    // Qaundo vogliamo inizializzare gli attributi di una classe lo facciamo prima delle graffe.
    numero(){
        val_ = 7;
    }
};

int main(int argc, char *argv[]) {
    /*
        Quando facciamo una malloc allochiamo solo la memoria,
        quindi non andiamo a chiamare il costruttore di numero
        quando chiamiamo la malloc.

        In CPP abbiamo bisogno di un nuovo metodo per allocare memoria
        per cui dopo aver allocato la memria chiama il costruttore delle classi.
        Per questo usamo "new", dove non solo alloca memoria ma chiama
        anche il costruttore.
    */
    // numero *pn = (numero*) malloc(sizeof(numero));

    numero *pn = new numero;
    int q = pn->val_;

    printf("q:\t\'%d\'\n", q);

    // Esmpio sintassi molteplici oggetti.
    numero *pns = new numero[10];    //Alloco per 10 numeri, e chiamo il costruttore di tutti.
    int h = pns->val_;

    printf("h:\t\'%d\'\n", h);

    /*
        In CPP non è possibile ridimensionare la dimensione della new, tipo renew, come
        invece è possibile con la realloc.
    */

    /*
        Il CPP rimane un linguaggio di basso livello, quindi
        dobbiamo gestire la memoria, uno dei più consueti errori dei dev CPP
        è quello dei memory leak.
    */
    //free(pn); per la malloc.
    delete pn;

    /*
        Sintassi, purtroppo, per liberare molteplici elementi.
        Spesso se ne dimentica.
        Questo è diverso perchè prima eliminarei dati il compilatore deve capire
        quan'è grande la memoria che deve liberare, quinid quanti elemnti sono salvati.
    */
    delete[] pns;

    return 0;
}