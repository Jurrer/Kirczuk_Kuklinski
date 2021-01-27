#include "../header/komunikacja.h"
#include "../header/funkcje.h"
#include "../header/automat.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    odp *m = (odp*) malloc(sizeof(odp));
    
    const char *token = argv[1];
    char *odpo;
    int gra = 0;

    gra = szukaj_granicy(m, odpo, token);

    printf("%d\n", gra);
    if(gra == 1)
    {
        printf("UDAŁO SIĘ!!\n");
    }

    free(m);

    return 0;

}