#include "../header/komunikacja.h"
#include "../header/struktury.h"

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{
    /* to jest rzeczywista liczba bajtów przekazanych przez curl */
    size_t realsize = size * nmemb;

    /* jawnie konwertujemy (void*) na naszą strukturę, bo wiemy, że będziemy ją tutaj otrzymywać */
    Memory *mem = (Memory *)userp;

    char *ptr = NULL;

    /* Sprawdzamy czy pierwszy raz wywołujemy funkcję i trzeba zaalokować pamięć po raz pierwszy,
    czy trzeba zrobić reallokację (która kopiuje automatycznie starą zawartość w nowe miejsce) */
    if (mem->response != NULL)
    {
        ptr = realloc(mem->response, mem->size + realsize + 1);
    }
    else
    {
        ptr = malloc(mem->size + realsize + 1);
    }

    if (ptr == NULL)
    {
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
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        // curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

        /* to jest funkcja 'callback', która będzie wywołana przez curl gdy odczyta on kawałek danych,
       ta funkcja musi mieć wywołanie zgodne z wymaganiami, które możesz sprawdzić tutaj:
       https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        /* to jest adress struktury, który będzie przekazywany do naszej funkcji 'callback',
       do tej struktury nasz funkcja 'callback' będzie dopisywać wynik */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        /* Wykonaj zapytanie 'synchronicznie', to znaczy następna linijka kodu nie wykona się
       dopóki nie nadejdzie odpowiedź z serwera. */
        res = curl_easy_perform(curl);

        /* Sprawdzamy czy wystapił jakis błąd? */
        if (res != CURLE_OK)
        {
            fprintf(stderr, "Błąd! curl_easy_perform() niepowodzenie: %s\n", curl_easy_strerror(res));
        }

        /* zawsze po sobie sprzątaj */
        //free(chunk.response);
        curl_easy_cleanup(curl);
        //printf("%s\n", chunk.response);
    }
    return chunk.response;
}

char* concat(const char *s1, const char *s2)
{   
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char *url(char * token, const char * action){

    char *url = {"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/"};
    char * wynik;
    char * nazwa;


    if(!strcmp(action, "info") || !strcmp(action, "move") || !strcmp(action, "explore")){
        
        nazwa = concat(url, action);
        nazwa = concat(nazwa, "/");        
        nazwa = concat(nazwa, token);
    }
    if(!strcmp(action, "left") || !strcmp(action, "right")){
        
        nazwa = concat(url, "rotate");
        nazwa = concat(nazwa, "/");        
        nazwa = concat(nazwa, token);
        nazwa = concat(nazwa, "/");   
        nazwa = concat(nazwa, action);        
    }
    return nazwa;
}

void main(int argc, char ** argv){  
    
    for(int i = 2; i<argc; i++){
        char * buffer = make_request(url(argv[1], argv[i]));
        printf("\n%s\n", buffer);
    }
}