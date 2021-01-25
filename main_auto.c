#include"header/komunikacja.h"
#include"header/funkcje.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

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

int szukaj_obwiedni(Odp *m, char *odp, const char *token)
{
    int wynik = 0;
    int l = 0;
    int r = 0;
    int x_poczatkowe = 0;
    int y_poczatkowe = 0;
    int x_stare = 0;
    int y_stare = 0;
    int ruszyl = 0;
    char pom1[8];
    char pom2[8];
    char dir[3];
    
    
    odp = make_explore(token);
    m = parameters(odp, "explore");

    while(strcmp(m->type2, "\"wall\"") != 0)
    {
        odp = make_move(token);
        m = parameters(odp, "move");
        odp = make_explore(token);
        m = parameters(odp, "explore");
    }

    odp = make_left(token);
    odp = make_explore(token);
    m = parameters(odp, "explore");

    if((strcmp(m->type2, "\"wall\"") == 0))
    {
        r++;
    }
    else;
    
    odp = make_right(token);
    odp = make_right(token);
    m = parameters(odp, "right");

    x_poczatkowe = m->current_x;
    y_poczatkowe = m->current_y;

    while(m->current_x != x_poczatkowe || m->current_y != y_poczatkowe || ruszyl == 0)
    {
        ruszyl = 1;
        
        odp = make_info(token);
        m = parameters(odp, "info");

        strcpy(dir, m->direction);
        
        odp = make_explore(token);
        m = parameters(odp, "explore");
        
        if(strcmp(dir, "E") == 0 || strcmp(dir, "W") == 0)
        {
            strcpy(pom1, m->type1);
            strcpy(pom2, m->type3);

            strcpy(m->type1, pom2);
            strcpy(m->type3, pom1);
        }
        else;

        if((strcmp(m->type3, "\"wall\"") != 0) && (strcmp(m->type2, "\"wall\"") != 0))
        {
            odp = make_move(token);

            odp = make_left(token);

            l++;
        }
        else if((strcmp(m->type2, "\"wall\"") != 0))
        {
            odp = make_move(token);
        }
        else if((strcmp(m->type2, "\"wall\"") == 0))
        {
            odp = make_right(token);

            r++;
        }

        odp = make_info(token);
        m = parameters(odp, "info");

        system("clear");
        printf("Szukanie w toku...\n");
    }

    wynik = r-l;

    if(wynik == 4)
        return wynik;

    else
        wynik = szukaj_obwiedni(m, odp, token);

    return wynik;
}

int main(int argc, char **argv)
{
    wyzeruj();

    const char *token = argv[1];
    Odp *m = (Odp*) malloc(sizeof(Odp));
    char *odp;
    int obw = 0; //zmienna definiująca czy znalezliśmy obwiednię

    obw = szukaj_obwiedni(m, odp, token);

    zapisz();
    
    
    free(m);
    return 0;
}