#include "header/automat.h"

//funkcja scalająca wysłanie zapytania oraz otrzymanie odpowiedzi dla move
char *make_move(const char *token) 
{
    char *odpowiedz_json = make_request(url(token, "move"));
    //wpisz(odpowiedz_json, "move");
    return odpowiedz_json;
}
//funkcja scalająca wysłanie zapytania oraz otrzymanie odpowiedzi dla info
char *make_info(const char *token) 
{
    char *odpowiedz_json = make_request(url(token, "info"));
    //wpisz(odpowiedz_json, "info");
    return odpowiedz_json;
}
//funkcja scalająca wysłanie zapytania oraz otrzymanie odpowiedzi dla left
char *make_left(const char *token) 
{
    char *odpowiedz_json = make_request(url(token, "left"));
    //wpisz(odpowiedz_json, "left");
    return odpowiedz_json;
}
//funkcja scalająca wysłanie zapytania oraz otrzymanie odpowiedzi dla right
char *make_right(const char *token) 
{
    char *odpowiedz_json = make_request(url(token, "right"));
    //wpisz(odpowiedz_json, "right");
    return odpowiedz_json;
}
//funkcja scalająca wysłanie zapytania oraz otrzymanie odpowiedzi dla explore
char *make_explore(const char *token) 
{
    char *odpowiedz_json = make_request(url(token, "explore"));
    //wpisz(odpowiedz_json, "explore");
    return odpowiedz_json;
}

//funkcja szukająca obwiedni
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
    char dir_poczatkowe[3];

    odpo = make_request(url(token, "explore"));
    parameters(m, odpo, "explore");

    while(strcmp(m->pole[1]->type, "\"wall\"") != 0) //czołg dojeżdża do ściany
    {        
        odpo = make_move(token);

        odpo = make_request(url(token, "explore"));
        parameters(m, odpo, "explore");
    }

    odpo = make_left(token);

    odpo = make_request(url(token, "explore"));

    parameters(m, odpo, "explore");

    if((strcmp(m->pole[1]->type, "\"wall\"") == 0)) //sprawdza czy dojechał do rogu
    {
        r++;
    }
    else;

    odpo = make_right(token);
    parameters(m, odpo, "right");
    strcpy(dir_poczatkowe, m->response->direction);
    
    odpo = make_right(token);
    parameters(m, odpo, "right");

    x_poczatkowe = m->response->current_x; //zapisuje współrzędne startowe szukania
    y_poczatkowe = m->response->current_y;


    while(m->response->current_x != x_poczatkowe || m->response->current_y != y_poczatkowe || ruszyl == 0) //główna pętla
    {
        ruszyl = 1;
        
        odpo = make_info(token);
        parameters(m, odpo, "info");

        strcpy(dir, m->response->direction);
        
        odpo = make_request(url(token, "explore"));
        parameters(m, odpo, "explore");
        
        if(strcmp(dir, "E") == 0 || strcmp(dir, "W") == 0) //ujednolica numerację typów podłoża odkrywanych przez explore
        {
            strcpy(pom1, m->pole[0]->type);
            strcpy(pom2, m->pole[2]->type);

            strcpy(m->pole[0]->type, pom2);
            strcpy(m->pole[2]->type, pom1);
        }
        else;

        if((strcmp(m->pole[2]->type, "\"wall\"") != 0) && (strcmp(m->pole[1]->type, "\"wall\"") != 0)) //sprawdza czy może skręcić w lewo
        {
            odpo = make_move(token);

            odpo = make_left(token);

            l++;
        }
        else if((strcmp(m->pole[1]->type, "\"wall\"") != 0)) //sprawdza czy może jechać do przodu
        {
            odpo = make_move(token);
        }
        else if((strcmp(m->pole[1]->type, "\"wall\"") == 0)) //skręca w prawo jeśli się zblokował
        {
            odpo = make_right(token);

            r++;
        }
        else;

        odpo = make_info(token);
        parameters(m, odpo, "info");
    }

    odpo = make_info(token);
    parameters(m, odpo, "info");

    if(strcmp(m->response->direction, dir_poczatkowe) == 0) // zabezpieczenie przed okrążaniem tego samego obiektu kilkukrotnie
    {
        odpo = make_left(token);
        
        odpo = make_request(url(token, "explore"));
        parameters(m, odpo, "explore");
        
        while(strcmp(m->pole[1]->type, "\"wall\"") == 0)
        {
            odpo = make_left(token);
            odpo = make_request(url(token, "explore"));
            parameters(m, odpo, "explore");
        }
    }

    wynik = r-l;

    if(wynik == 4) //jeśli znalazł obwiednię to funkcja się kończy, a jeżeli nie to funkcja wywołuje się rekurencyjnie
        return wynik;

    else
        wynik = szukaj_obwiedni(m, odpo, token);

    return wynik;
}

int szukaj_granicy(field *m, char *odpo, const char *token) //funkcja szukająca dolnej granicy planszy
{
    int wynik = 0;
    
    odpo = make_info(token);
    parameters(m, odpo, "info");

    while(strcmp(m->response->direction, "S") != 0) //skręca na dół
    {
        odpo = make_right(token);
        parameters(m, odpo, "right");
    }

    odpo = make_request(url(token, "explore"));
    parameters(m, odpo, "explore");

    while(strcmp(m->pole[1]->type, "\"wall\"") != 0) //zjeżdża maksymalnie na dół
    {
        odpo = make_move(token);

        odpo = make_request(url(token, "explore"));
        parameters(m, odpo, "explore");
    }

    odpo = make_right(token);
    parameters(m, odpo, "right");

    odpo = make_request(url(token, "explore"));
    parameters(m, odpo, "explore");

    while(strcmp(m->pole[1]->type, "\"wall\"") != 0) //dojeżdża maksymalnie do lewej
    {
        odpo = make_move(token);

        odpo = make_request(url(token, "explore"));
        parameters(m, odpo, "explore");
    }


    odpo = make_left(token);

    odpo = make_request(url(token, "explore"));
    parameters(m, odpo, "explore");

    if(strcmp(m->pole[1]->type, "\"wall\"") != 0) //sprawdza czy pod nim nie ma przejazdu, jeżeli jest to wywołuje się rekurencyjnie
    {
        wynik = szukaj_granicy(m, odpo, token);
        return wynik;
    }

    odpo = make_left(token);

    odpo = make_request(url(token, "explore"));
    parameters(m, odpo, "explore");

    while(strcmp(m->pole[1]->type, "\"wall\"") != 0) //jedzie w kierunku E jednocześnie patrząc, czy nie może skręcić w dół
    {
        if(strcmp(m->pole[2]->type, "\"wall\"") != 0)
        {
            odpo = make_move(token);
            odpo = make_right(token);

            wynik = szukaj_granicy(m, odpo, token);

            return wynik;
        }
        
        odpo = make_move(token);

        odpo = make_request(url(token, "explore"));
        parameters(m, odpo, "explore");

    }

    odpo = make_left(token);
    odpo = make_left(token);

    odpo = make_request(url(token, "explore"));
    parameters(m, odpo, "explore");

    while(strcmp(m->pole[1]->type, "\"wall\"") != 0) // wraca do lewego dolnego rogu i się obkręca
    {
        odpo = make_move(token);

        odpo = make_request(url(token, "explore"));
        parameters(m, odpo, "explore");
    }

    odpo = make_left(token);
    odpo = make_left(token);

    
    return 1;

}

int czysc_mape(field *m, char *odpo, const char *token)
{
    int i = 0;
    int wynik = 0;
    
    odpo = make_info(token);
    parameters(m, odpo, "info");

    while(strcmp(m->response->direction, "E") !=0 )
    {
        odpo = make_left(token);
        parameters(m, odpo, "left");
    }

    for(i = 0; i<25; i++)
    {
        odpo = make_request(url(token, "explore"));
        parameters(m, odpo, "explore");
        
        while(strcmp(m->pole[1]->type, "\"wall\"") != 0)
        {
            odpo = make_move(token);

            odpo = make_request(url(token, "explore"));
            parameters(m, odpo, "explore");
        }
        
        odpo = make_left(token);

        odpo = make_request(url(token, "explore"));
        parameters(m, odpo, "explore");

        if(strcmp(m->pole[0]->type, "\"wall\"") != 0 && strcmp(m->pole[1]->type, "\"wall\"") != 0)
        {
            odpo = make_move(token);
            odpo = make_right(token);
    
            wynik = czysc_mape(m, odpo, token);
            return wynik;
        }

        odpo = make_move(token);
        odpo = make_left(token);
        odpo = make_request(url(token, "explore"));
        parameters(m, odpo, "explore");

        while(strcmp(m->pole[1]->type, "\"wall\"") != 0)
        {
            odpo = make_move(token);

            odpo = make_request(url(token, "explore"));
            parameters(m, odpo, "explore");
        }

        odpo = make_right(token);
        odpo = make_request(url(token, "explore"));
        parameters(m, odpo, "explore");

        if(strcmp(m->pole[2]->type, "\"wall\"") != 0 && strcmp(m->pole[1]->type, "\"wall\"") != 0)
        {
            odpo = make_move(token);
            odpo = make_left(token);
            odpo = make_request(url(token, "explore"));
            parameters(m, odpo, "explore");

            while(strcmp(m->pole[1]->type, "\"wall\"") != 0)
            {
                odpo = make_move(token);

                odpo = make_request(url(token, "explore"));
                parameters(m, odpo, "explore");
            }

            wynik = czysc_mape(m, odpo, token);
            return wynik;
        }

        odpo = make_move(token);
        odpo = make_right(token);

    }
    wynik = 1;

    return wynik;
}