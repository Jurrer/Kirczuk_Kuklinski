#include"header/komunikacja.h"
#include"header/funkcje.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char *make_move(const char *token)
{
    printf("move: \n");
    char *odpowiedz_json = move(token);
    printf("%s\n", odpowiedz_json);
    wpisz(odpowiedz_json, "move");
    return odpowiedz_json;
}

char *make_info(const char *token)
{
    printf("info: \n");
    char *odpowiedz_json = info(token);
        printf("%s\n", odpowiedz_json);
    wpisz(odpowiedz_json, "info");
    return odpowiedz_json;
}

char *make_left(const char *token)
{
    printf("left: \n");
    char *odpowiedz_json = left(token);
        printf("%s\n", odpowiedz_json);
    wpisz(odpowiedz_json, "left");
    return odpowiedz_json;
}

char *make_right(const char *token)
{   
    printf("right: \n");
    char *odpowiedz_json = right(token);
        printf("%s\n", odpowiedz_json);
    wpisz(odpowiedz_json, "right");
    return odpowiedz_json;
}

char *make_explore(const char *token)
{
    printf("explore: \n");
    char *odpowiedz_json = explore(token);
        printf("%s\n", odpowiedz_json);
    //wpisz(odpowiedz_json, "explore");
    return odpowiedz_json;
}

int szukaj_obwiedni(field *m, char *odpo, const char *token)
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
    
    odpo = make_explore(token);
    m = parameters(odpo, "explore");
    //printf("TUTAJ!!\n");
    while(strcmp(m->pole[1]->type, "\"wall\"") != 0)
    {         
        odpo = make_move(token);       
        odpo = make_explore(token);
        m = parameters(odpo, "explore");
    }    //printf("TUTAJ!!\n");

    odpo = make_left(token);
    odpo = make_explore(token);
    m = parameters(odpo, "explore");

    if((strcmp(m->pole[1]->type, "\"wall\"") == 0))
    {
        r++;
    }
    else;
    
    odpo = make_right(token);
    
    odpo = make_right(token);
    m = parameters(odpo, "right");

    x_poczatkowe = m->response->current_x;
    y_poczatkowe = m->response->current_y;

    while(m->response->current_x != x_poczatkowe || m->response->current_y != y_poczatkowe || ruszyl == 0)
    {
        ruszyl = 1;
        
        odpo = make_info(token);
        m = parameters(odpo, "info");

        strcpy(dir, m->response->direction);
        
        odpo = make_explore(token);
        m = parameters(odpo, "explore");
        
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
            odpo = make_move(token);

            odpo = make_left(token);

            l++;
        }
        else if((strcmp(m->pole[1]->type, "\"wall\"") != 0))
        {
            odpo = make_move(token);
        }
        else if((strcmp(m->pole[1]->type, "\"wall\"") == 0))
        {
            odpo = make_right(token);

            r++;
        }

        odpo = make_info(token);
        m = parameters(odpo, "info");
    }

    wynik = r-l;

    if(wynik == 4)
        return wynik;

    else
        wynik = szukaj_obwiedni(m, odpo, token);

    return wynik;
}

/*
int szukaj_granicy(field *m, char *odpo, const char *token)
{
    int wynik = 0;
    
    odpo = make_info(token);
    m = parameters(odpo, "info");

    while(strcmp(m->response->direction, "S") != 0)
    {
        odpo = make_right(token);
        m = parameters(odpo, "right");
    }

    odpo = make_explore(token);
    m = parameters(odpo, "explore");

    while(strcmp(m->pole[1]->type, "\"wall\"") != 0)
    {
        odpo = make_move(token);

        odpo = make_explore(token);
        m = parameters(odpo, "explore");
    }

    odpo = make_right(token);
    m = parameters(odpo, "right");

    odpo = make_explore(token);
    m = parameters(odpo, "explore");

    while(strcmp(m->pole[1]->type, "\"wall\"") != 0)
    {
        odpo = make_move(token);

        odpo = make_explore(token);
        m = parameters(odpo, "explore");
    }

    odpo = make_right(token);
    odpo = make_right(token);
    odpo = make_right(token);

    odpo = make_explore(token);
    m = parameters(odpo, "explore");

    if(strcmp(m->pole[1]->type, "\"wall\"") != 0)
    {
        wynik = szukaj_granicy(m, odpo, token);
        return wynik;
    }

    odpo = make_left(token);

    odpo = make_explore(token);
    m = parameters(odpo, "explore");

    while(strcmp(m->pole[1]->type, "\"wall\"") != 0)
    {
        if(strcmp(m->pole[2]->type, "\"wall\"") != 0)
        {
            odpo = make_move(token);
            odpo = make_right(token);

            wynik = szukaj_granicy(m, odpo, token);

            return wynik;
        }
        
        odpo = make_move(token);

        odpo = make_explore(token);
        m = parameters(odpo, "explore");

    }

    return 1;

}

int odkrywanie_mapy(field *m, char *odpo, const char *token)
{
    int dolna_granica = 0;

    dolna_granica = szukaj_granicy(m, odpo, token);
}
*/
int main(int argc, char **argv)
{
    wyzeruj();

    const char *token = argv[1];
    field *m;
    m = calloc(1, sizeof(field));
   // field *m = (field*) malloc(sizeof(field));
   // m->response = (odp*) malloc(sizeof(odp));
   // m->pole[0] = (expl*) malloc(sizeof(expl));
   // m->pole[1] = (expl*) malloc(sizeof(expl));
   // m->pole[2] = (expl*) malloc(sizeof(expl));

    char *odpo;
    int obw = 0; //zmienna definiująca czy znalezliśmy obwiednię

    obw = szukaj_obwiedni(m, odpo, token);

    //printf("%d\n", obw);

    //printf("Znalazłem obwiednię!\n");

    // odpo = make_explore(token);
    // m = parameters(odpo, "explore");

    zapisz();
    return 0;
}