//#include "../header/funkcje.h"
//#include "../header/komunikacja.h"
#include"../header/struktury.h"
#include "../../cJSON/cJSON.h"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>


field *alloc(field * ala);

field *parameters(const char * const korzen, char *komenda)
{
    field *zodiak = alloc(zodiak);

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
    return zodiak;
}

field *alloc(field * ala){
    ala = (field*) malloc(sizeof(field));
    ala->response = (odp*) malloc(sizeof(odp));
    ala->pole[0] = (expl*) malloc(sizeof(expl));
    ala->pole[1] = (expl*) malloc(sizeof(expl));
    ala->pole[2] = (expl*) malloc(sizeof(expl));
    return ala;
}

void freeee(field *alama){
    free(alama->pole[0]);
    free(alama->pole[1]);
    free(alama->pole[2]);
    free(alama->response);
    free(alama);
}


void main(int argc, char **argv)
{


    char buffer[2048];

    for(int i = 1; i<argc; i++){
        
        field *info = alloc(info);

        if(!strcmp(argv[i], "info") || !strcmp(argv[i], "left") || !strcmp(argv[i], "move") || !strcmp(argv[i], "right") || !strcmp(argv[i], "explore") ){
            
            char nazwa[50] = {"../json/"};
            strcat(nazwa, argv[i]);
            strcat(nazwa, ".json");

            FILE *f = fopen(nazwa, "r");
	        fread(buffer,1,2048,f);
	        fclose(f);

            info = parameters(buffer, argv[i]);

                if(!strcmp(argv[i], "info") || !strcmp(argv[i], "left") || !strcmp(argv[i], "move") || !strcmp(argv[i], "right")){
                    printf("\nCommand %s: \n\n", argv[i]);
                    printf("Info:\n%s\n %s\n %d\n %d\n %s\n %s\n %d\n %s\n\n", info->response->status, info->response->name, info->response->current_x, info->response->current_y, info->response->current_session, info->response->direction, info->response->step, info->response->field_type);
                    }

                if (!strcmp(argv[i], "explore") ){

                    info = parameters(buffer, "explore");
                    printf("Command %s:\n\n", "explore");
                    printf("Info:\n%s\n %d\n %d\n %s\n %d\n %d\n %s\n %d\n %d\n %s\n\n",info->pole[0]->status, info->pole[0]->x, info->pole[0]->y, info->pole[0]->type, info->pole[1]->x, info->pole[1]->y, info->pole[1]->type, info->pole[2]->x, info->pole[2]->y, info->pole[2]->type);
            }
        }    
    }   
}