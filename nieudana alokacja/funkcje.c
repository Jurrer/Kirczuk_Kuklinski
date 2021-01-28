#include "header/funkcje.h"

//przetwarza odpowiedź z serwera do innej struktury
void parameters(field * zodiak, const char * const korzen, char *komenda) 
{
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
    const cJSON *name3 = NULL;
    const cJSON *step = NULL;
    const cJSON *field_type = NULL;
    const cJSON *field_bonus = NULL;


    
    cJSON *korzen_cjson = cJSON_Parse(korzen);
    if (korzen_cjson == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
            zodiak->response->status = "Error";
        }
    }

    status = cJSON_GetObjectItemCaseSensitive(korzen_cjson, "status");
    if (cJSON_IsString(status) && (status->valuestring != NULL))
    {
        zodiak->response->status = status->valuestring;
        zodiak->pole[0]->status = status->valuestring;
    }
    
    
    if(strcmp(komenda, "explore") == 0){
        payload = cJSON_GetObjectItemCaseSensitive(korzen_cjson, "payload");
        zodiak->pole[0]->x = atoi(cJSON_Print(payload->child->child->child));
        zodiak->pole[0]->y = atoi(cJSON_Print(payload->child->child->child->next));
        zodiak->pole[0]->type = cJSON_Print(payload->child->child->child->next->next);
        zodiak->pole[1]->x = atoi(cJSON_Print(payload->child->child->next->child));
        zodiak->pole[1]->y = atoi(cJSON_Print(payload->child->child->next->child->next));
        zodiak->pole[1]->type = cJSON_Print(payload->child->child->next->child->next->next);
        zodiak->pole[2]->x = atoi(cJSON_Print(payload->child->child->next->next->child));
        zodiak->pole[2]->y = atoi(cJSON_Print(payload->child->child->next->next->child->next));
        zodiak->pole[2]->type = cJSON_Print(payload->child->child->next->next->child->next->next);
        
        //payload = cJSON_GetObjectItemCaseSensitive(korzen_cjson, "payload");
        // cJSON_ArrayForEach(name1, payload)
        //{
            // list = cJSON_GetObjectItemCaseSensitive(korzen_cjson, "list");
            
            //     puste1 = cJSON_GetObjectItemCaseSensitive(korzen_cjson, "\n");
            //     cJSON_ArrayForEach(name1, puste1)
            //     {
            //         cJSON *x1 = cJSON_GetObjectItemCaseSensitive(puste1, "x");
            //         zodiak->x1 = x1->valueint;
            //     }
                // zodiak->x1 = atoi(cJSON_Print(puste1->child));
                // zodiak->y1 = atoi(cJSON_Print(puste1->child->next));
                // zodiak->type1 = cJSON_Print(puste1->child->next->next);

                // zodiak->x2 = atoi(cJSON_Print(puste1->next->child));
                // zodiak->y2 = atoi(cJSON_Print(puste1->next->child->next));
                // zodiak->type2 = cJSON_Print(puste1->next->child->next->next);

                // zodiak->x3 = atoi(cJSON_Print(puste1->next->next->child));
                // zodiak->y3 = atoi(cJSON_Print(puste1->next->next->child->next));
                // zodiak->type3 = cJSON_Print(puste1->next->next->child->next->next);
                
                // printf("%d\n", zodiak->x1);
                
            //cJSON_ArrayForEach(name2, list)
            //{
                //puste1 = cJSON_GetObjectItemCaseSensitive(list, "");
                //cJSON_ArrayForEach(name3, puste1)
                //{
                    
                //}
            //}
        //}
        
    }
    else{
        payload = cJSON_GetObjectItemCaseSensitive(korzen_cjson, "payload");
        cJSON_ArrayForEach(name1, payload)
        {
            cJSON *name = cJSON_GetObjectItemCaseSensitive(payload, "name");
            zodiak->response->name = name->valuestring;
        
            cJSON *current_x = cJSON_GetObjectItemCaseSensitive(payload, "current_x");
            zodiak->response->current_x = current_x->valueint;

            cJSON *current_y = cJSON_GetObjectItemCaseSensitive(payload, "current_y");
            zodiak->response->current_y = current_y->valueint;
            
            cJSON *current_session = cJSON_GetObjectItemCaseSensitive(payload, "current_session");
            zodiak->response->current_session = current_session->valuestring;

            cJSON *direction = cJSON_GetObjectItemCaseSensitive(payload, "direction");
            zodiak->response->direction = direction->valuestring;
            
            cJSON *step = cJSON_GetObjectItemCaseSensitive(payload, "step");
            zodiak->response->step = step->valueint;
            
            cJSON *field_type = cJSON_GetObjectItemCaseSensitive(payload, "field_type");
            zodiak->response->field_type = field_type->valuestring;
            
            cJSON *field_bonus = cJSON_GetObjectItemCaseSensitive(payload, "field_bonus");
            zodiak->response->field_bonus = field_bonus->valuestring;
        }
    }
    cJSON_Delete(korzen_cjson);
}

field *alloc(field * ala){ //alokuje pamięć dla struktury
    
    ala = (field*) malloc(sizeof(field));
    ala->response = (odp*) malloc(sizeof(odp));
    ala->pole[0] = (expl*) malloc(sizeof(expl));
    ala->pole[1] = (expl*) malloc(sizeof(expl));
    ala->pole[2] = (expl*) malloc(sizeof(expl));

    ala->mapa = (char**) calloc(50, sizeof(char));

    for(int i = 0; i < 50; i++)
    {
        ala->mapa[i] = (char*) calloc(50, sizeof(char));
    }

    return ala;
}

void freeee(field *alama){ //zwalnia pamięć dla struktury (nie działa)
    free(alama->pole[0]);
    free(alama->pole[1]);
    free(alama->pole[2]);
    free(alama->response);
    free(alama);
}

void narysuj_swiat(field * swiat) //rysuje świat
{
    int i,j;
    for(i = 0; i < 40; i++)
        {
        for(j = 0; j < 40; j++)
        {
            printf("%c", swiat->mapa[i][j]);
        }
        printf("\n");
    }
}

void zapisz(field * swiat) //zapisuje świat do pliku
{
    FILE *fin;
    fin = fopen("save.txt", "w");
    for(int i=0; i<50; i++)
    {
        for(int j =0; j<50;j++)
        {
            fprintf(fin, "%c", swiat->mapa[i][j]);
        }
        fprintf(fin, "\n");
    }
    fclose(fin);
}
/*
void wpisz(char *response, char *komenda) //przypisuje elementy otoczenia do świata
{
    odp * odpowiedz = (odp*) malloc(sizeof(odp));

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
    free(odpowiedz);
}
*/


void wypelnij_plusy(field * swiat) //tworzy czystą planszę
{
    int i,j;
    for(i=0; i < 40; i++)
    {
        for(j=0; j < 40; j++)
        {
            swiat->mapa[i][j] = '+';
        }
    }
}