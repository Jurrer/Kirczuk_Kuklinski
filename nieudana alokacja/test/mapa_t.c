//#include "../header/funkcje.h"
//#include "../header/komunikacja.h"
#include"../header/struktury.h"
#include "../../cJSON/cJSON.h"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define M 10
#define U 3


field * resize(odp * info, field * map, int offsetx, int offsety);

void wypisz(field *cale){
    int i, j;
    for(i=0; i<cale->rozmiar_y; i++){
        for(j=0;j<cale->rozmiar_x; j++){
            printf("%c", cale->mapa[i][j]);
        }
    printf("\n");
    }
}


void wpisz_plusy(field *cale){
    int i, j;
    for(i=0; i<cale->rozmiar_y; i++){
        for(j=0;j<cale->rozmiar_x; j++){
            cale->mapa[i][j] = '+';
        }
    }
}

field * wpisz(field *cale, odp * odpowiedz){

if(cale->rozmiar_x<=odpowiedz->current_x || cale->rozmiar_y<=odpowiedz->current_y){
    //cale = resize(odpowiedz, cale, 7, 10);
}

      if(strcmp(cale->komenda, "explore") == 0){
        if(strcmp(odpowiedz->type1, "\"wall\"") == 0){
           cale->mapa[odpowiedz->x1][odpowiedz->y1] = 'X';
        }
        if(strcmp(odpowiedz->type1, "\"grass\"") == 0){
            cale->mapa[odpowiedz->x1][odpowiedz->y1] = 'g';
        }
        if(strcmp(odpowiedz->type1, "\"sand\"") == 0){
            cale->mapa[odpowiedz->x1][odpowiedz->y1] = 's';
        }
        if(strcmp(odpowiedz->type2, "\"wall\"") == 0){
            cale->mapa[odpowiedz->x2][odpowiedz->y2] = 'X';
        }
        if(strcmp(odpowiedz->type2, "\"grass\"") == 0){
            cale->mapa[odpowiedz->x2][odpowiedz->y2] = 'g';
        }
        if(strcmp(odpowiedz->type2, "\"sand\"") == 0){
            cale->mapa[odpowiedz->x2][odpowiedz->y2] = 's';
        }

        if(strcmp(odpowiedz->type3, "\"wall\"") == 0){
            cale->mapa[odpowiedz->x3][odpowiedz->y3] = 'X';
        }
        if(strcmp(odpowiedz->type3, "\"grass\"") == 0){
            cale->mapa[odpowiedz->x3][odpowiedz->y3] = 'g';
        }
        if(strcmp(odpowiedz->type3, "\"sand\"") == 0){
            cale->mapa[odpowiedz->x3][odpowiedz->y3] = 's';
        }
    }
    else
    {
        if(strcmp(odpowiedz->field_type, "grass") == 0)
        {
            cale->mapa[odpowiedz->current_x][odpowiedz->current_y] = 'g';
        }
        if(strcmp(odpowiedz->field_type, "sand") == 0)
        {
            cale->mapa[odpowiedz->current_x][odpowiedz->current_y] = 's';
        }
    }
    return cale;
}



void let_go_map(field *map){
    
    for(int i = 0; i < map->rozmiar_x; i++)
    {
        free(map->mapa[i]);
    }
    free(map->mapa);
    free(map);
}



field *do_map(int wiersze, int kolumny){
    field *new = calloc(1, sizeof(field));
    new->rozmiar_x = wiersze;
    new->rozmiar_y = kolumny;

    new->mapa = (char**) calloc(new->rozmiar_x, sizeof(char*));
    int i;
    for(i = 0; i <new->rozmiar_x; i++){
            new->mapa[i] = (char*) calloc(new->rozmiar_y, sizeof(char));
    }
    new->d_x = U;
    new->d_y = U;

    return new;
}


field * res_right(field *map){

    int i, j; 
    field * new_map = NULL;
    new_map = do_map(map->rozmiar_x*2, map->rozmiar_y);

    for(i = 0; i<map->rozmiar_x; i++)
        for(j = 0; map->rozmiar_y; j++){
            new_map->mapa[i][j] = map->mapa[i][j];
        }
    
    let_go_map(map);
    return new_map;
}

field * res_left(field *map){
    
    int i, j; 
    field * new_map = NULL;
    new_map = do_map(map->rozmiar_x*2, map->rozmiar_y);

    for(i = 0; i<map->rozmiar_x; i++)
        for(j = 0; map->rozmiar_y; j++){
            new_map->mapa[i+map->rozmiar_x][j] = map->mapa[i][j];
        }
    
    let_go_map(map);
    return new_map;
}

field * res_up(field *map){
    
    int i, j; 
    field * new_map = NULL;
    new_map = do_map(map->rozmiar_x, map->rozmiar_y*2);

    for(i = 0; i<map->rozmiar_x; i++)
        for(j = 0; map->rozmiar_y; j++){
            new_map->mapa[i][j] = map->mapa[i][j];
        }
    
    let_go_map(map);
    return new_map;
}

field * res_down(field *map){
    
    int i, j; 
    field * new_map = NULL;
    new_map = do_map(map->rozmiar_x, map->rozmiar_y*2);

    for(i = 0; i<map->rozmiar_x; i++)
        for(j = 0; map->rozmiar_y; j++){
            new_map->mapa[i][j + map->rozmiar_y] = map->mapa[i][j];
        }
    
    let_go_map(map);
    return new_map;
}



field * resize(odp * info, field * map, int offsetx, int offsety){
    int x, y;
    field * result = NULL;
    
    x = offsetx + info->current_x;
    y = offsety + info->current_y;

    if(x == map->rozmiar_x-1){
        result = res_right(map);
        return result;
    }

    if(y == map->rozmiar_y-1){
        result = res_up(map);
        return result;
    }

    if(x == map->rozmiar_x-1){
        result = res_left(map);
        return result;
    }

    if(y == map->rozmiar_y-1){
        result = res_down(map);
        return result;
    }    
}

odp *parameters(const char * const korzen, char *komenda) //przetwarza odpowiedź z serwera
{
    odp *zodiak = (odp*) malloc(sizeof(odp));
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

void main(int argc, char **argv)
{
        char buffer[2048];
            FILE *f = fopen("../json/info.json", "r");
	        fread(buffer,1,2048,f);
	        fclose(f);
    //printf("%s", buffer);
    
    field * struktura_gry = do_map(M, M);

    odp * costam = parameters(buffer, "info");

    struktura_gry->komenda = "info";

    wpisz_plusy(struktura_gry);

    struktura_gry = wpisz(struktura_gry, costam);
    
    wypisz(struktura_gry);

}