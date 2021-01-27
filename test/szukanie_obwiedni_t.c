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
    int obw = 0;

    obw = szukaj_obwiedni(m, odpo, token);

    printf("%d\n", obw);

    free(m);

    return 0;

}