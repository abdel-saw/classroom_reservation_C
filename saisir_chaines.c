#include <stdio.h>
#include <malloc.h>
#include "saisir_chaine.h"


char * saisir_chaine()
{
    char *ch = NULL ;
    unsigned int c,nbc=0;
    while ((c = getchar())!= '\n')
    {
        ch=(char*)realloc(ch,(nbc+1)*sizeof(char));
        ch[nbc++]=c;
    }
    ch = (char*) realloc(ch,(nbc+1)*sizeof(char));
    ch[nbc]='\0';
    return ch;
}


