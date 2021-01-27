#include "header/komunikacja.h"
#include "header/funkcje.h"
#include "header/automat.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    

    odp *m = (odp*) malloc(sizeof(odp));
    wyzeruj();
    
    const char *token;;
    system("clear");
    printf("Wpisz token swojego świata\n");

    scanf("%s", token);

    char *odpo;

    int obw = 0; //zmienna definiująca czy znalezliśmy obwiednię

    obw = szukaj_obwiedni(m, odpo, token);
    printf("Znalazłem obwiednię!\n");
    obw = szukaj_granicy(m, odpo, token);
    printf("Znalazłem dolną granicę\n");
    obw = czysc_mape(m, odpo, token);

    printf("%d\n", obw);


    printf("Odkryłem całą mapę w %d krokach\n", m->step);

    

    zapisz();

    free(m);
    return 0;
}