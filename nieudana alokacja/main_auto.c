#include "header/komunikacja.h"
#include "header/funkcje.h"
#include "header/automat.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    

    field *m;

    m = alloc(m);
    m->rozmiar_x = 50;
    m->rozmiar_y = 50;
    
    wypelnij_plusy(m);

    const char *token = argv[1];
    char *odpo;
    int obw = 0; //zmienna definiująca czy znalezliśmy obwiednię
    obw = szukaj_obwiedni(m, odpo, token);
    obw = szukaj_granicy(m, odpo, token);
    obw = czysc_mape(m, odpo, token);
    printf("%d\n", obw);
    odpo = make_info(token);
    parameters(m, odpo, "info");
    printf("Odkryłem całą mapę w %d krokach\n", m->response->step);

    narysuj_swiat(m);
    
    freeee(m);
    
    return 0;
}