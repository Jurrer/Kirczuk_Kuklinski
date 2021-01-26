#include"header/komunikacja.h"
#include"header/funkcje.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char *make_move(const char *token)
{
    printf("move: \n");
    char *odpowiedz_json = move(token);
    wpisz(odpowiedz_json, "move");
    return odpowiedz_json;
}

char *make_info(const char *token)
{
    printf("info: \n");
    char *odpowiedz_json = info(token);
    wpisz(odpowiedz_json, "info");
    return odpowiedz_json;
}

char *make_left(const char *token)
{
    printf("left: \n");
    char *odpowiedz_json = left(token);
    wpisz(odpowiedz_json, "left");
    return odpowiedz_json;
}

char *make_right(const char *token)
{   
    printf("right: \n");
    char *odpowiedz_json = right(token);
    wpisz(odpowiedz_json, "right");
    return odpowiedz_json;
}

char *make_explore(const char *token)
{
    printf("explore: \n");
    char *odpowiedz_json = explore(token);
    wpisz(odpowiedz_json, "explore");
    return odpowiedz_json;
}

int szukaj_obwiedni(odp *m, char *odpo, const char *token)
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

    while(strcmp(m->type2, "\"wall\"") != 0)
    {        
        odpo = make_move(token);       

        odpo = make_explore(token);
        m = parameters(odpo, "explore");
    }

    odpo = make_left(token);
    odpo = make_explore(token);
    m = parameters(odpo, "explore");

    if((strcmp(m->type2, "\"wall\"") == 0))
    {
        r++;
    }
    else;
    
    odpo = make_right(token);

    odpo = make_right(token);
    m = parameters(odpo, "right");

    x_poczatkowe = m->current_x;
    y_poczatkowe = m->current_y;

    while(m->current_x != x_poczatkowe || m->current_y != y_poczatkowe || ruszyl == 0)
    {
        ruszyl = 1;
        
        odpo = make_info(token);
        m = parameters(odpo, "info");

        strcpy(dir, m->direction);
        
        odpo = make_explore(token);
        m = parameters(odpo, "explore");
        
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
            odpo = make_move(token);

            odpo = make_left(token);

            l++;
        }
        else if((strcmp(m->type2, "\"wall\"") != 0))
        {
            odpo = make_move(token);
        }
        else if((strcmp(m->type2, "\"wall\"") == 0))
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

int szukaj_granicy(odp *m, char *odpo, const char *token)
{
    int wynik = 0;
    
    odpo = make_info(token);
    m = parameters(odpo, "info");

    while(strcmp(m->direction, "S") != 0)
    {
        odpo = make_right(token);
        m = parameters(odpo, "right");
    }

    odpo = make_explore(token);
    m = parameters(odpo, "explore");

    while(strcmp(m->type2, "\"wall\"") != 0)
    {
        odpo = make_move(token);

        odpo = make_explore(token);
        m = parameters(odpo, "explore");
    }

    odpo = make_right(token);
    m = parameters(odpo, "right");

    odpo = make_explore(token);
    m = parameters(odpo, "explore");

    while(strcmp(m->type2, "\"wall\"") != 0)
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

    if(strcmp(m->type2, "\"wall\"") != 0)
    {
        wynik = szukaj_granicy(m, odpo, token);
        return wynik;
    }

    odpo = make_left(token);

    odpo = make_explore(token);
    m = parameters(odpo, "explore");

    while(strcmp(m->type2, "\"wall\"") != 0)
    {
        if(strcmp(m->type3, "\"wall\"") != 0)
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

int odkrywanie_mapy(odp *m, char *odpo, const char *token)
{
    int dolna_granica = 0;

    dolna_granica = szukaj_granicy(m, odpo, token);
}
*/
int main(int argc, char **argv)
{
    wyzeruj();

    odp *m = (odp*) malloc(sizeof(odp));
    
    const char *token = argv[1];
    char *odpo;
    int obw = 0; //zmienna definiująca czy znalezliśmy obwiednię

    obw = szukaj_obwiedni(m, odpo, token);

    //printf("%d\n", obw);

    odpo = make_info(token);
    m = parameters(odpo, "info");

    printf("Odkryłem całą mapę w %d krokach\n", m->step);

    

    zapisz();

    free(m);
    return 0;
}