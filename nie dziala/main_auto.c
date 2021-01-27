#include "header/komunikacja.h"
#include "header/funkcje.h"
#include "header/automat.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    field *glowny = (field*) malloc(sizeof(field));
    glowny->rozmiar = 10;

    &glowny = wyzeruj(glowny);
    printf("dupa\n");

    narysuj_swiat(glowny);


    odp *m = (odp*) malloc(sizeof(odp));
    glowny->offset = 0;
    glowny->maxoffset = 0;
    
    const char *token = argv[1];
    char *odpo;
    int obw = 0; //zmienna definiująca czy znalezliśmy obwiednię

    //obw = szukaj_obwiedni(m, odpo, token);
    //obw = szukaj_granicy(m, odpo, token);
    //obw = czysc_mape(m, odpo, token);

    printf("%d\n", obw);

    //odpo = make_info(token);
    //m = parameters(odpo, "info");

    printf("Odkryłem całą mapę w %d krokach\n", m->step);

    

    zapisz();

    free(m);
    return 0;
}