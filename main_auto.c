#include "header/komunikacja.h"
#include "header/funkcje.h"
#include "header/automat.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{

    odp *m = (odp *)malloc(sizeof(odp));
    wyzeruj();

    char *token;
    system("clear");
    printf("Wpisz token swojego świata\n");

    scanf("%s", token);

    char *odpo;

    int obw = 0; //zmienna definiująca czy znalezliśmy obwiednię

    printf("Szukam obwiedni\n");
    
    obw = szukaj_obwiedni(m, odpo, token);
    printf("Znalazłem obwiednię!\nSzukam dolnej granicy\n");
    zapisz();    
    obw = szukaj_granicy(m, odpo, token);
    printf("Znalazłem dolną granicę\nPrzeczesuję mapę\n");
    zapisz();    
    obw = czysc_mape(m, odpo, token);

    odpo = make_info(token);
    m = parameters(odpo, "info");
    narysuj_swiat();

    printf("Odkryłem całą mapę (mam nadzieję) w %d krokach\n", m->step);

    zapisz();

    free(m);
    return 0;
}