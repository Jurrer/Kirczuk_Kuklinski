#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON/cJSON.h"

struct payload
{
    char *name;
    int current_x;
    int current_y;
    char *current_session;
    char *direction;
    int step;
    char *field_type;
    char *field_bonus;

    int list_x_1;
    int list_y_1;
    char type_1[10];
    
    int list_x_2;
    int list_y_2;
    char type_2[10];
    
    int list_x_3;
    int list_y_3;
    char type_3[10];

};

 //return 1 if the monitor supports full hd, 0 otherwise 
/*
int supports_full_hd(const char * const monitor)
{
    const cJSON *resolution = NULL;
    const cJSON *resolutions = NULL;
    const cJSON *name = NULL;
    int status = 0;
    cJSON *monitor_json = cJSON_Parse(monitor);
    if (monitor_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        status = 0;
        goto end;
    }

    name = cJSON_GetObjectItemCaseSensitive(monitor_json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL))
    {
        printf("Checking monitor \"%s\"\n", name->valuestring);
    }

    resolutions = cJSON_GetObjectItemCaseSensitive(monitor_json, "resolutions");
    cJSON_ArrayForEach(resolution, resolutions)
    {
        cJSON *width = cJSON_GetObjectItemCaseSensitive(resolution, "width");
        cJSON *height = cJSON_GetObjectItemCaseSensitive(resolution, "height");

        if (!cJSON_IsNumber(width) || !cJSON_IsNumber(height))
        {
            status = 0;
            goto end;
        }

        if ((width->valuedouble == 3840) && (height->valuedouble == 2160))
        {
            status = 1;
            goto end;
        }
    }

end:
    cJSON_Delete(monitor_json);
    return status;
}


int status(const char * const bufor)
{


    cJSON *ok = cJSON_Parse(bufor);
        if(ok == NULL)
            return 0;
    
    odczyt = cJSON_GetObjectItemCaseSensitive(ok, "status");

    if(strcmp(odczyt->valuestring, "Success") == 0)
        printf("%s", odczyt->valuestring);
        return 1;
}
*/

int zczytaj_payload(const char * const bufor, char *komenda, struct payload *data)
{
    const cJSON *name = NULL;
    const cJSON *current_x = NULL;
    const cJSON *current_y = NULL;
    const cJSON *current_session = NULL;
    const cJSON *direction = NULL;
    const cJSON *step = NULL;
    const cJSON *field_type = NULL;
    const cJSON *field_bonus = NULL;
    const cJSON *list = NULL;
    const cJSON *payload = NULL;

    int status = 0;

    cJSON *haczyk = cJSON_Parse(bufor);
        if(haczyk == NULL)
            return 1;
    
    
    name = cJSON_GetObjectItemCaseSensitive(haczyk, "name");

    //strcpy((*data)->name, name->valuestring);
    printf("pierwsze %s", data->name);
    printf("drugie %s", name->valuestring);

    //current_x = cJSON_GetObjectItemCaseSensitive(haczyk, "current_x");
    //payload = cJSON_GetObjectItemCaseSensitive(haczyk, "payload");
    
    return 0;
/*
    if(strcmp(komenda, "info") == 0 || strcmp(komenda, "right") == 0 || strcmp(komenda, "left") == 0)
    {
    ;
    }
    else
    {
        return 1;
    }
*/
}

int main() {
	char buffer[2048];
	FILE *f = fopen("info.json", "r");
	fread(buffer,1,2048,f);
	fclose(f);
	//printf("%d\n",status(buffer));
    int i,j;
    
    struct payload *payload_pointer, data;

    //data = (payload_global) malloc(sizeof(pld));    
    printf("%p", payload_pointer);
    if(zczytaj_payload(buffer, "info", payload_pointer) == 0)
    {	
    printf("działa\n");
	return 0;
    }
    else if(zczytaj_payload(buffer, "info", payload_pointer) == 1)
    {
    printf("nie działa\n");
    return 1;
    }
}
