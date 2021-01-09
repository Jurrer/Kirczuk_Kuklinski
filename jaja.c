#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON/cJSON.h"

typedef struct _Memory {
    char *response;
    size_t size;
}Memory;

typedef struct _Mapa {
    char *status;
    char *name;
    char *xyz;
    int current_x;
    int current_y;
    char *current_session;
    char *direction;
    int step;
    char *field_type;
    char *field_bonus;

}Mapa;

typedef struct _Luneta {
    int x1, y1, x2, y2, x3, y3;
    char *type1;
    char *type2;
    char *type3;

}Luneta;

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
        else {
            FILE *fin = fopen("reply.cjson", "w+");
            //printf("%s", chunk.response); /*informacja zwrotna z serwera*/
            fprintf(fin, "%s", chunk.response);
            fclose(fin);
            // printf("alamakota\n");
        }

        /* zawsze po sobie sprzątaj */
        free(chunk.response);
        curl_easy_cleanup(curl);
    }
    return 0;
}

void info(char *token) {
    char *url = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/qwerty_25";
    make_request(url);
}

void move(char *token) {
    char *url = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/qwerty_25";
    make_request(url);
}

void explore(char *token) {
    char *url = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/qwerty_25";
    make_request(url);
}

void left(char *token) {
    char *url = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_25/left";
    make_request(url);
}

void right(char *token) {
    char *url = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_25/right";
    make_request(url);
}

Mapa *parameters(const char * const korzen)//musi btc status (korzen)
{
    Mapa *zodiak;
    const cJSON *status = NULL;
    const cJSON *payload = NULL;
    const cJSON *name = NULL;
    const cJSON *current_x = NULL;
    const cJSON *current_y = NULL;
    const cJSON *current_session = NULL;
    const cJSON *direction = NULL;
    const cJSON *name1 = NULL;
    const cJSON *step = NULL;
    const cJSON *field_type = NULL;
    const cJSON *field_bonus = NULL;

    int statuskodu = 0;
    
    cJSON *korzen_cjson = cJSON_Parse(korzen);
    if (korzen_cjson == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        statuskodu = 0;
        // goto end;
    }


    status = cJSON_GetObjectItemCaseSensitive(korzen_cjson, "status");
    if (cJSON_IsString(status) && (status->valuestring != NULL))
    {
        //printf("Checking %s \n", status->valuestring);
        zodiak->status = status->valuestring;
    }

    payload = cJSON_GetObjectItemCaseSensitive(korzen_cjson, "payload");
    cJSON_ArrayForEach(name1, payload)
    {
        cJSON *name = cJSON_GetObjectItemCaseSensitive(payload, "name");
        //printf("Checking %s\n", name1->valuestring);
        zodiak->name = name->valuestring;
    
        cJSON *current_x = cJSON_GetObjectItemCaseSensitive(payload, "current_x");
        zodiak->current_x = current_x->valueint;
        //printf("Checking %d\n", zodiak->current_x);

        cJSON *current_y = cJSON_GetObjectItemCaseSensitive(payload, "current_y");
        zodiak->current_y = current_y->valueint;
        
        cJSON *current_session = cJSON_GetObjectItemCaseSensitive(payload, "current_session");
        zodiak->current_session = current_session->valuestring;
        
        cJSON *direction = cJSON_GetObjectItemCaseSensitive(payload, "direction");
        zodiak->direction = direction->valuestring;
        
        cJSON *step = cJSON_GetObjectItemCaseSensitive(payload, "step");
        zodiak->step = step->valueint;
        
        cJSON *field_type = cJSON_GetObjectItemCaseSensitive(payload, "field_type");
        zodiak->field_type = field_type->valuestring;
        
        cJSON *field_bonus = cJSON_GetObjectItemCaseSensitive(payload, "field_bonus");
        zodiak->field_bonus = field_bonus->valuestring;
    
    
    }
    
    // payload = cJSON_GetObjectItemCaseSensitive(korzen_cjson, "payload");
    // cJSON_ArrayForEach(xyz, direction)
    // {
    //     cJSON *dir = cJSON_GetObjectItemCaseSensitive(xyz, "direction");
    //     zodiak->direction = xyz->valuestring;
    // }


//     cJSON_ArrayForEach(current_x, payload)
//     {
//         cJSON *current_x = cJSON_GetObjectItemCaseSensitive(name, "name");
//     }

//     cJSON_ArrayForEach(current_y, payload)
//     {
//         cJSON *current_y = cJSON_GetObjectItemCaseSensitive(name, "name");
//     }






//     payload = cJSON_GetObjectItemCaseSensitive(monitor_json, "payload");
//     cJSON_ArrayForEach(resolution, resolutions)
//     {
//         cJSON *width = cJSON_GetObjectItemCaseSensitive(resolution, "width");
//         cJSON *height = cJSON_GetObjectItemCaseSensitive(resolution, "height");

//         if (!cJSON_IsNumber(width) || !cJSON_IsNumber(height))
//         {
//             status = 0;
//             goto end;
//         }

//         if ((width->valuedouble == 1920) && (height->valuedouble == 1080))
//         {
//             statuskodu = 1;
//             goto end;
//         }
//     }

// end:
    //cJSON_Delete(korzen_cjson);
    return zodiak;
}

int odkrywanie(const char * const korzen)
{

}

void wypisz (Mapa *mapa)
{
    printf("%s\n", mapa->status);
    printf("%s\n", mapa->name);
    printf("%d\n", mapa->current_x);
    printf("%d\n", mapa->current_y);
    printf("krok nr:%d\n", mapa->step);
}

int main(int argc, char **argv)
{
    char *token= argv[1];

    for(int i=2; i<argc;i++)
    {
        if(strcmp(argv[i], "info") == 0)
        {
            info(token);
        }
        if(strcmp(argv[i], "explore") == 0)
        {
            explore(token);
        }
        if(strcmp(argv[i], "right") == 0)
        {
            right(token);
        }
        if(strcmp(argv[i], "move") == 0)
        {
            move(token);
        }
        if(strcmp(argv[i], "left") == 0)
        {
            left(token);
        }
    }

    char tab[2048];
	FILE *f = fopen("reply.cjson", "r");
	fread(tab,1,2048,f);
    Mapa * glowna = parameters(tab);
    wypisz(glowna);
    fclose(f);


    return 0;
}