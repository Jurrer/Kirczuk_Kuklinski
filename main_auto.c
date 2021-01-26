#include"header/komunikacja.h"
#include"header/funkcje.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char *make_move(const char *token)
{
    char *odpowiedz_json = move(token);
    //wpisz(odpowiedz_json, "move");
    return odpowiedz_json;
}

char *make_info(const char *token)
{
    char *odpowiedz_json = info(token);
    //wpisz(odpowiedz_json, "info");
    return odpowiedz_json;
}

char *make_left(const char *token)
{
    char *odpowiedz_json = left(token);
    //wpisz(odpowiedz_json, "left");
    return odpowiedz_json;
}

char *make_right(const char *token)
{
    char *odpowiedz_json = right(token);
    //wpisz(odpowiedz_json, "right");
    return odpowiedz_json;
}

char *make_explore(const char *token)
{
    char *odpowiedz_json = explore(token);
    //wpisz(odpowiedz_json, "explore");
    return odpowiedz_json;
}

int szukaj_obwiedni(field *stare, char *odp, const char *token)
{
    field *m = alloc(m);

    field *u = alloc(u);
    
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

    while(strcmp(m->pole[1]->type, "\"wall\"") != 0)
    {        
        odp = make_move(token);       

        odp = make_explore(token);
        m = parameters(odp, "explore");
    }

    odp = make_left(token);
    odp = make_explore(token);
    m = parameters(odp, "explore");

    if((strcmp(m->pole[1]->type, "\"wall\"") == 0))
    {
        r++;
    }
    else;
    
    odp = make_right(token);
    
    odp = make_right(token);
    u = parameters(odp, "right");

    x_poczatkowe = u->response->current_x;
    y_poczatkowe = u->response->current_y;

    while(u->response->current_x != x_poczatkowe || u->response->current_y != y_poczatkowe || ruszyl == 0)
    {
        ruszyl = 1;
        
        odp = make_info(token);
        u = parameters(odp, "info");

        strcpy(dir, u->response->direction);
        
        odp = make_explore(token);
        m = parameters(odp, "explore");
        
        if(strcmp(dir, "E") == 0 || strcmp(dir, "W") == 0)
        {
            strcpy(pom1, m->pole[0]->type);
            strcpy(pom2, m->pole[2]->type);

            strcpy(m->pole[0]->type, pom2);
            strcpy(m->pole[2]->type, pom1);
        }
        else;

        if((strcmp(m->pole[2]->type, "\"wall\"") != 0) && (strcmp(m->pole[1]->type, "\"wall\"") != 0))
        {
            odp = make_move(token);

            odp = make_left(token);

            l++;
        }
        else if((strcmp(m->pole[1]->type, "\"wall\"") != 0))
        {
            odp = make_move(token);
        }
        else if((strcmp(m->pole[1]->type, "\"wall\"") == 0))
        {
            odp = make_right(token);

            r++;
        }

        odp = make_info(token);
        u = parameters(odp, "info");
    }

    wynik = r-l;

    if(wynik == 4)
        return wynik;

    else
        wynik = szukaj_obwiedni(m, odp, token);

    return wynik;
}

int szukaj_granicy(field *m, char *odp, const char *token)
{
    int wynik = 0;
    
    odp = make_info(token);
    m = parameters(odp, "info");

    while(strcmp(m->response->direction, "S") != 0)
    {
        odp = make_right(token);
        m = parameters(odp, "right");
    }

    odp = make_explore(token);
    m = parameters(odp, "explore");

    while(strcmp(m->pole[1]->type, "\"wall\"") != 0)
    {
        odp = make_move(token);

        odp = make_explore(token);
        m = parameters(odp, "explore");
    }

    odp = make_right(token);
    m = parameters(odp, "right");

    odp = make_explore(token);
    m = parameters(odp, "explore");

    while(strcmp(m->pole[1]->type, "\"wall\"") != 0)
    {
        odp = make_move(token);

        odp = make_explore(token);
        m = parameters(odp, "explore");
    }

    odp = make_right(token);
    odp = make_right(token);
    odp = make_right(token);

    odp = make_explore(token);
    m = parameters(odp, "explore");

    if(strcmp(m->pole[1]->type, "\"wall\"") != 0)
    {
        wynik = szukaj_granicy(m, odp, token);
        return wynik;
    }

    odp = make_left(token);

    odp = make_explore(token);
    m = parameters(odp, "explore");

    while(strcmp(m->pole[1]->type, "\"wall\"") != 0)
    {
        if(strcmp(m->pole[2]->type, "\"wall\"") != 0)
        {
            odp = make_move(token);
            odp = make_right(token);

            wynik = szukaj_granicy(m, odp, token);

            return wynik;
        }
        
        odp = make_move(token);

        odp = make_explore(token);
        m = parameters(odp, "explore");

    }

    return 1;

}

int odkrywanie_mapy(field *m, char *odp, const char *token)
{
    int dolna_granica = 0;

    dolna_granica = szukaj_granicy(m, odp, token);
}

int main(int argc, char **argv)
{
    wyzeruj();

    const char *token = argv[1];
    field *m = alloc(m);
    char *odp;
    int obw = 0; //zmienna definiująca czy znalezliśmy obwiednię

    obw = szukaj_obwiedni(m, odp, token);

    printf("%d\n", obw);

    //printf("Znalazłem obwiednię!\n");

    // odp = make_explore(token);
    // m = parameters(odp, "explore");

    zapisz();
    return 0;
}