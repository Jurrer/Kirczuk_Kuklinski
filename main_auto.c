#include"komunikacja.h"
#include"funkcje.h"

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

int szukaj_obwiedni(Mapa *m, char *odp, const char *token)
{
    int wynik = 0;
    int l, r, x_poczatkowe, y_poczatkowe, x_stare, y_stare, ruszyl = 0;

    odp = make_explore(token);
    //m = wpisz(odp, "explore");
    

    while(m->type2 != "\"wall\"")
    {
        odp = make_move(token);
        m = parameters(odp, "move");
    }
    odp = make_right(token);
    m = wpisz(odp, "right");
    x_poczatkowe = m->current_x;
    y_poczatkowe = m->current_y;

    while(m->current_x != x_poczatkowe && m->current_y != y_poczatkowe && ruszyl == 1)
    {
        odp = make_explore(token);
        m = wpisz(odp, "explore");
        
        if(m->type1 != "\"wall\"")
        {
            x_stare = m->current_x;
            y_stare = m->current_y;
            
            odp = make_move(token);
            m = wpisz(odp, "explore");

            odp = make_left(token);
            m = wpisz(odp, "left");

            l++;
        }
        else
        {
            x_stare = m->current_x;
            y_stare = m->current_y;
            
            odp = make_move(token);
            m = wpisz(odp, "move");

            if(x_stare == m->current_x && y_stare == m->current_y)
            {
                odp = make_right(token);
                m = wpisz(odp, "right");

                r++;
            }
        }
        ruszyl = 1;
        
    }

    wynik = l-r;

    return wynik;
}

int main(int argc, char **argv)
{
    wyzeruj();

    const char *token = argv[1];
    Mapa *m;
    char *odp;
    char *komenda = "explore";
    int obw = 0; //zmienna definiująca czy znalezliśmy obwiednię

    obw = szukaj_obwiedni(m, odp, token);

    //odp = explore(token);
    
    //m = wpisz(odp, "explore");

    //printf("%s\n", m->type2);
    


    return 0;
}