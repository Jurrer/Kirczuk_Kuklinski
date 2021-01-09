#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON/cJSON.h"


/* return 1 if the monitor supports full hd, 0 otherwise 
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
*/

int status(const char * const bufor)
{
    const cJSON *odczyt = NULL;
    cJSON *ok = cJSON_Parse(bufor);
        if(ok == NULL)
            return 0;
    
    odczyt = cJSON_GetObjectItemCaseSensitive(ok, "status");

    if(strcmp(odczyt->valuestring, "Success") == 0)
        printf("%s", odczyt->valuestring);
        return 1;
}



int main() {
	char buffer[2048];
	FILE *f = fopen("explore.json", "r");
	fread(buffer,1,2048,f);
	fclose(f);
	printf("%d\n",status(buffer));	
	return 0;
}
