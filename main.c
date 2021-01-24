#include "header/funkcje.h"
#include "header/komunikacja.h"


int main(int argc, char **argv)
{
    wyzeruj();

    const char *token= argv[1];    

    for(int i=2; i<argc;i++)
    {
        if(strcmp(argv[i], "info") == 0)
        {
            char *odpowiedz_json = info(token);
            wpisz(odpowiedz_json, "info");
        }
        if(strcmp(argv[i], "explore") == 0)
        {
            char *odpowiedz_json = explore(token);
            wpisz(odpowiedz_json, "explore");
        }
        if(strcmp(argv[i], "right") == 0)
        {
            char *odpowiedz_json = right(token);
            wpisz(odpowiedz_json, "right");
        }
        if(strcmp(argv[i], "move") == 0)
        {
            char *odpowiedz_json = move(token);
            wpisz(odpowiedz_json, "move");
        }
        if(strcmp(argv[i], "left") == 0)
        {
            char *odpowiedz_json = left(token);
            wpisz(odpowiedz_json, "left");
        }
        if(i == (argc-1))
        {
            narysuj_swiat();
        }
    }

    zapisz();

    return 0;
}