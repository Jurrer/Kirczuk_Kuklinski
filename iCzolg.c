#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON/cJSON.h"

typedef struct _payload
{
    int error;
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

}payload;

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

payload *zczytaj_payload(const char * const bufor, char *komenda)
{
    const cJSON *name_ = NULL;
    const cJSON *current_x_ = NULL;
    const cJSON *current_y_ = NULL;
    const cJSON *current_session_ = NULL;
    const cJSON *direction_ = NULL;
    const cJSON *step_ = NULL;
    const cJSON *field_type_ = NULL;
    const cJSON *field_bonus_ = NULL;
    const cJSON *list_ = NULL;
    const cJSON *payload_ = NULL;

    int status = 0;

    payload *tymczasowo;

    cJSON *haczyk = cJSON_Parse(bufor);
        if(haczyk == NULL)
        {
        tymczasowo->error = 1;
        return tymczasowo;
        }    

    payload_ = cJSON_GetObjectItemCaseSensitive(haczyk, "payload");
    cJSON_ArrayForEach(list_, payload_)
    {
    cJSON * name_ = cJSON_GetObjectItemCaseSensitive(payload_, "name");
    printf("checking %s \n", name_->valuestring);
    tymczasowo->error = 0;
    //tymczasowo->name = name_->valuestring;
/*
    cJSON * current_x_ = cJSON_GetObjectItemCaseSensitive(payload_, "current_x");
    tymczasowo->current_x = current_x_->valueint;
    printf("%d", tymczasowo->current_x);
    */

    return tymczasowo;
    }

    //strcpy((*data)->name, name->valuestring);
    //printf("pierwsze %s", data->name);
    //printf("drugie %s", name_->valuestring);

    

    //current_x = cJSON_GetObjectItemCaseSensitive(haczyk, "current_x");
    //payload = cJSON_GetObjectItemCaseSensitive(haczyk, "payload");
    
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
	
	//printf("%d\n",status(buffer));
    
    
    payload * data = zczytaj_payload(buffer, "info");

    printf("%s", data->name);

    //data = (payload_global) malloc(sizeof(pld));    
    fclose(f);

    if(data->error == 0)
    {	
    printf("działa\n");
	return 0;
    }
    else if(data->error != 0)
    {
    printf("nie działa\n");
    return 1;
    }

    return 0;
}
