/*Implementacao de funcoes auxiliares em C*/

#include "header.h"
#include <stdio.h>
#include <stdlib.h>

static unsigned symhash(char *sym){
    unsigned int hash = 0;
    unsigned c;

    while(c = *sym++){
        hash = hash*9 ^ c;
    }
    return hash;
}

struct symbol *lookup(char *sym){
    struct symbol *sp = &symtab[symhash(sym)%NHASH];
    int scount = NHASH; 

    while(--scount >= 0){
        if(sp->name && !strcasecmp(sp->name, sym)){
            return sp;
        }

        if(!sp->name){// nova entrada na Ts
            sp->name = strdup(sym);
            sp->reflist = 0;
            return sp;
        }

        if(++sp >= symtab+NHASH){
            sp = symtab; //tenta a proxima entrada
        }
    }
    fputs("overflow na tab de simbolos\n", stderr);
    abort(); // tabela cheia
}