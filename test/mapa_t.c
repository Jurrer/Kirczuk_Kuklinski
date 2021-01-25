#include "../header/funkcje.h"
#include "../header/komunikacja.h"
#include "../../cJSON/cJSON.h"
#include <stdio.h>




odp *parameters(const char * const korzen, char *komenda)
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
        zodiak->x[0] = atoi(cJSON_Print(payload->child->child->child));
        zodiak->y[0] = atoi(cJSON_Print(payload->child->child->child->next));
        char *bufer;
        bufer = cJSON_Print(payload->child->child->child->next->next);
        printf("%s", bufer);
        zodiak->type[0][200] = "bufer";
        zodiak->x[1] = atoi(cJSON_Print(payload->child->child->next->child));
        zodiak->y[1] = atoi(cJSON_Print(payload->child->child->next->child->next));
        zodiak->type[1][200] = cJSON_Print(payload->child->child->next->child->next->next);
        zodiak->x[2] = atoi(cJSON_Print(payload->child->child->next->next->child));
        zodiak->y[2] = atoi(cJSON_Print(payload->child->child->next->next->child->next));
        zodiak->type[2][200] = cJSON_Print(payload->child->child->next->next->child->next->next);
        
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
    field m;
    
    char buffer[2048];


    //printf("%s", buffer);
    if(!strcmp(argv[1], "info")){
    FILE *f = fopen("info.json", "r");
	fread(buffer,1,2048,f);
	fclose(f);

    odp info = *parameters(buffer, "info");
    printf("Info:\n%s\n %s\n %d\n %d\n %s\n %s\n %d\n %s\n", info.status, info.name, info.current_x, info.current_y, info.current_session, info.direction, info.step, info.field_type);


    }
    if(!strcmp(argv[1], "explore")){
    FILE *f = fopen("explore.json", "r");
	fread(buffer,1,2048,f);
	fclose(f);

    odp explore = *parameters(buffer, "explore");

    printf("Info:\n%s\n %d\n %d\n %s\n %d\n %d\n %s\n %d\n %d\n %s\n",explore.status, explore.x[0], explore.y[0], explore.type[0], explore.x[1], explore.y[1], explore.type[1], explore.x[2], explore.y[2], explore.type[2]);
    
    }    
    
}