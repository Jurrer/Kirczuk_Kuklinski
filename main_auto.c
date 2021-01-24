#include"header/komunikacja.h"
#include"header/funkcje.h"
#include<stdlib.h>

char *make_move(const char *token)
{
    char *odpowiedz_json = move(token);
    wpisz(odpowiedz_json, "move");
    return odpowiedz_json;
}

char *make_info(const char *token)
{
    char *odpowiedz_json = info(token);
    wpisz(odpowiedz_json, "info");
    return odpowiedz_json;
}

char *make_left(const char *token)
{
    char *odpowiedz_json = left(token);
    wpisz(odpowiedz_json, "left");
    return odpowiedz_json;
}

char *make_right(const char *token)
{
    char *odpowiedz_json = right(token);
    wpisz(odpowiedz_json, "right");
    return odpowiedz_json;
}

char *make_explore(const char *token)
{
    char *odpowiedz_json = explore(token);
    wpisz(odpowiedz_json, "explore");
    return odpowiedz_json;
}

int szukaj_obwiedni(Mapa *m, char *odp, const char *token)
{
    int wynik = 0;
    int l = 0;
    int r = 0;
    int x_poczatkowe = 0;
    int y_poczatkowe = 0;
    int x_stare = 0;
    int y_stare = 0;
    int ruszyl = 0;

    odp = make_explore(token);
    m = parameters(odp, "explore");
    printf("%s\n", m->type2);

    while(strcmp(m->type2, "\"wall\"") != 0)
    {
        odp = make_move(token);
        m = parameters(odp, "move");
        odp = make_explore(token);
        m = parameters(odp, "explore");
    }
    
    odp = make_right(token);
    m = parameters(odp, "right");

    odp = make_info(token);
    m = parameters(odp, "info");
    
    x_poczatkowe = m->current_x;
    y_poczatkowe = m->current_y;

    odp = make_move(token);
    m = parameters(odp, "move");

    while(m->current_x != x_poczatkowe || m->current_y != y_poczatkowe)
    {
        odp = make_explore(token);
        m = parameters(odp, "explore");

        if((strcmp(m->type1, "\"wall\"") != 0) && (strcmp(m->type2, "\"wall\"") != 0))
        {
            odp = make_move(token);
            m = parameters(odp, "move");

            odp = make_left(token);
            m = parameters(odp, "left");

            l++;
        }
        else if((strcmp(m->type2, "\"wall\"") != 0))
        {
            odp = make_move(token);
            m = parameters(odp, "move");

        }
        else if((strcmp(m->type2, "\"wall\"") == 0))
        {
            odp = make_right(token);
            m = parameters(odp, "right");
            r++;
        }

    }

    wynik = l-r;
    printf("%d\n", wynik);

    return wynik;
}

int main(int argc, char **argv)
{
    wyzeruj();

    const char *token = argv[1];
    Mapa *m = (Mapa*) malloc(sizeof(Mapa));
    char *odp;
    int obw = 0; //zmienna definiująca czy znalezliśmy obwiednię

    obw = szukaj_obwiedni(m, odp, token);

    zapisz();
    


    return 0;
}