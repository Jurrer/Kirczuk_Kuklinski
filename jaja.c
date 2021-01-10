#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../cJSON/cJSON.h"

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
    int x1;
    int y1;
    int x2;
    int y2;
    int x3;
    int y3;
    char *type1;
    char *type2;
    char *type3;
}Mapa;

char swiat[50][50];

void narysuj()
{
    int i,j;
    for(i=0; i<50; i++)
    {
    for(j=0; j<50; j++)
    {
        printf("%c", swiat[i][j]);
    }
    printf("\n");
    }
}

void wczytaj_zapis()
{
    system("touch save.txt");
    FILE *f; 
    f = fopen("save.txt", "r");
    for(int i=0; i<50; i++)
    {
        for(int j =0; j<50;j++)
        {
            fscanf(f, "%c", &swiat[i][j]);
        }
    }
    fclose(f);
    system("rm save.txt");
}

void zapisz()
{
    FILE *fin;
    fin = fopen("save.txt", "w");
    for(int i=0; i<50; i++)
    {
        for(int j =0; j<50;j++)
        {
            fprintf(fin, "%c", swiat[i][j]);
        }
        fprintf(fin, "\n");
    }
    fclose(fin);
}

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
        curl_easy_cleanup(curl);
        printf("%s\n", chunk.response);
    }
    return chunk.response;
}

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
    const char *left = "/left";
    strcat(url, left);
    char *response_json = make_request(url);
    return response_json;
}

char *right(const char *token) {
    char url[100] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
    strcat(url, token);
    const char *right = "/right";
    strcat(url, right);
    char *response_json = make_request(url);
    return response_json;
}

Mapa *parameters(const char * const korzen, char *komenda)
{
    Mapa *zodiak;
    const cJSON *status = NULL;
    const cJSON *payload = NULL;
    const cJSON *x = NULL;
    const cJSON *list = NULL;
    const cJSON *name = NULL;
    const cJSON *current_x = NULL;
    const cJSON *current_y = NULL;
    const cJSON *current_session = NULL;
    const cJSON *direction = NULL;
    const cJSON *name1 = NULL;
    const cJSON *name2 = NULL;
    const cJSON *step = NULL;
    const cJSON *field_type = NULL;
    const cJSON *field_bonus = NULL;
    int *x1 = NULL;
    int *y1 = NULL;
    int *x2 = NULL;
    int *y2 = NULL;
    int *x3 = NULL;
    int *y3 = NULL;
    char *type1 = NULL;
    char *type2 = NULL;
    char *type3 = NULL;

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
    }


    status = cJSON_GetObjectItemCaseSensitive(korzen_cjson, "status");
    if (cJSON_IsString(status) && (status->valuestring != NULL))
    {
        zodiak->status = status->valuestring;
    }

    if(strcmp(komenda, "explore") == 0)
    {
        payload = cJSON_GetObjectItemCaseSensitive(korzen_cjson, "payload");
        zodiak->x1 = atoi(cJSON_Print(payload->child->child->child));
        zodiak->y1 = atoi(cJSON_Print(payload->child->child->child->next));
        zodiak->type1 = cJSON_Print(payload->child->child->child->next->next);
        zodiak->x2 = atoi(cJSON_Print(payload->child->child->next->child));
        zodiak->y2 = atoi(cJSON_Print(payload->child->child->next->child->next));
        zodiak->type2 = cJSON_Print(payload->child->child->next->child->next->next);
        zodiak->x3 = atoi(cJSON_Print(payload->child->child->next->next->child));
        zodiak->y3 = atoi(cJSON_Print(payload->child->child->next->next->child->next));
        zodiak->type3 = cJSON_Print(payload->child->child->next->next->child->next->next);
        
    }
    else
    {
        payload = cJSON_GetObjectItemCaseSensitive(korzen_cjson, "payload");
        cJSON_ArrayForEach(name1, payload)
        {
            cJSON *name = cJSON_GetObjectItemCaseSensitive(payload, "name");
            zodiak->name = name->valuestring;
        
            cJSON *current_x = cJSON_GetObjectItemCaseSensitive(payload, "current_x");
            zodiak->current_x = current_x->valueint;

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
    }

    return zodiak;
}

void wpisz(char *response, char *komenda)
{
    Mapa * odpowiedz;
    if(strcmp(komenda, "explore")==0){
    odpowiedz = parameters(response, komenda);
        if(strcmp(odpowiedz->type1, "\"wall\"") == 0){
            swiat[odpowiedz->x1][odpowiedz->y1] = 'X';
        }
        if(strcmp(odpowiedz->type1, "\"grass\"") == 0){
            swiat[odpowiedz->x1][odpowiedz->y1] = 'g';
        }
        if(strcmp(odpowiedz->type1, "\"sand\"") == 0){
            swiat[odpowiedz->x1][odpowiedz->y1] = 's';
        }
        if(strcmp(odpowiedz->type2, "\"wall\"") == 0){
            swiat[odpowiedz->x2][odpowiedz->y2] = 'X';
        }
        if(strcmp(odpowiedz->type2, "\"grass\"") == 0){
            swiat[odpowiedz->x2][odpowiedz->y2] = 'g';
        }
        if(strcmp(odpowiedz->type2, "\"sand\"") == 0){
            swiat[odpowiedz->x2][odpowiedz->y2] = 's';
        }

        if(strcmp(odpowiedz->type3, "\"wall\"") == 0){
            swiat[odpowiedz->x3][odpowiedz->y3] = 'X';
        }
        if(strcmp(odpowiedz->type3, "\"grass\"") == 0){
            swiat[odpowiedz->x3][odpowiedz->y3] = 'g';
        }
        if(strcmp(odpowiedz->type3, "\"sand\"") == 0){
            swiat[odpowiedz->x3][odpowiedz->y3] = 's';
        }
    }
    else
    {
        odpowiedz = parameters(response, komenda);
        if(strcmp(odpowiedz->field_type, "grass") == 0)
        {
            swiat[odpowiedz->current_x][odpowiedz->current_y] = 'g';
        }
        if(strcmp(odpowiedz->field_type, "sand") == 0)
        {
            swiat[odpowiedz->current_x][odpowiedz->current_y] = 's';
        }
    }
    
}

void wyzeruj()
{
    int i,j;
    for(i=0; i<50; i++)
    {
        for(j=0; j<50; j++)
        {
            swiat[i][j] = '+';
        }
    }
}

void wypisz(Mapa *mapa, char *komenda)
{
    if(strcmp(komenda, "explore") == 0)
    {
        printf("%s\n", mapa->status);
        printf("%d\n", mapa->x1);
        printf("%d\n", mapa->y1);
        printf("%s\n", mapa->type1);
        printf("%d\n", mapa->x3);
        printf("%d\n", mapa->y3);
        printf("%s\n", mapa->type3);

    }
    else
    {
        printf("%s\n", mapa->status);
        printf("%s\n", mapa->name);
        printf("%d\n", mapa->current_x);
        printf("%d\n", mapa->current_y);
        printf("krok nr:%d\n", mapa->step);
        printf("%s\n", mapa->current_session);
        printf("Typ pola: %s\n", mapa->field_type);
    }
}

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
            narysuj();
        }
    }

    zapisz();

    return 0;
}