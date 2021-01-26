#include "header/komunikacja.h"

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{
    /* to jest rzeczywista liczba bajtów przekazanych przez curl */
    size_t realsize = size * nmemb;

    /* jawnie konwertujemy (void*) na naszą strukturę, bo wiemy, że będziemy ją tutaj otrzymywać */
    Memory *mem = (Memory*) userp;

    char *ptr = NULL;

    /* Sprawdzamy czy pierwszy raz wywołujemy funkcję i trzeba zaalokować pamięć po raz pierwszy,
    czy trzeba zrobić reallokację (która kopiuje automatycznie starą zawartość w nowe miejsce) */
    if (mem->response != NULL) {
        ptr = realloc(mem->response, mem->size + realsize + 1);
    }
    else {
        ptr = malloc(mem->size + realsize + 1);        
    }

    if (ptr == NULL) {
        return 0;
    }
    /* brak pamięci! */

    /* teraz zapamiętujemy nowy wskaźnik i doklejamy na końcu dane przekazane przez curl w 
    obszarze pamięci wskazywanym przez data */
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0; // to na końcu dodajemy bo to w końcu string, i zawsze powinien się skończyć!

    return realsize;
}

char *make_request(char *url)
{
    CURL *curl;
    CURLcode res;
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        // curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

        /* to jest funkcja 'callback', która będzie wywołana przez curl gdy odczyta on kawałek danych,
       ta funkcja musi mieć wywołanie zgodne z wymaganiami, które możesz sprawdzić tutaj:
       https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        /* to jest adress struktury, który będzie przekazywany do naszej funkcji 'callback',
       do tej struktury nasz funkcja 'callback' będzie dopisywać wynik */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);

        /* Wykonaj zapytanie 'synchronicznie', to znaczy następna linijka kodu nie wykona się
       dopóki nie nadejdzie odpowiedź z serwera. */
        res = curl_easy_perform(curl);

        /* Sprawdzamy czy wystapił jakis błąd? */
        if (res != CURLE_OK) {
            fprintf(stderr, "Błąd! curl_easy_perform() niepowodzenie: %s\n", curl_easy_strerror(res));
        }
        /* zawsze po sobie sprzątaj */
        //free(chunk.response);
        printf("%s", chunk.response);
        curl_easy_cleanup(curl);
    }
    return chunk.response;
}
/*
char *url(char * action, const char *token)
{
    if(strcmp(action, "info") == 0)
        {
            char *odpowiedz_json = info(token);
            wpisz(odpowiedz_json, "info");
        }
    if(strcmp(action, "explore") == 0)
        {
            char *odpowiedz_json = explore(token);
            wpisz(odpowiedz_json, "explore");
        }
    if(strcmp(action, "right") == 0)
        {
            char *odpowiedz_json = right(token);
            wpisz(odpowiedz_json, "right");
        }
    if(strcmp(action, "move") == 0)
        {
            char *odpowiedz_json = move(token);
            wpisz(odpowiedz_json, "move");
        }
    if(strcmp(action, "left") == 0)
        {
            char *odpowiedz_json = left(token);
            wpisz(odpowiedz_json, "left");
        }   
}
*/
char *info(const char *token) {
    char url[100] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/";
    strcat(url, token);
    char *response_json = make_request(url);
    return response_json;
}

char *move(const char *token) {
    char url[100] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/";
    strcat(url, token);
    char *response_json = make_request(url);
    return response_json;
}

char *explore(const char *token) {
    char url[100] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/";
    strcat(url, token);
    char *response_json = make_request(url);
    return response_json;
}

char *left(const char *token) {
    char url[100] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
    strcat(url, token);
    strcat(url, "/left");
    char *response_json = make_request(url);
    return response_json;
}

char *right(const char *token) {
    char url[100] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
    strcat(url, token);
    strcat(url, "/right");
    char *response_json = make_request(url);
    return response_json;
}