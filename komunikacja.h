#ifndef _KOMUNIKACJA_H
#define _KOMUNIKACJA_H

#include <curl/curl.h>
#include "../cJSON/cJSON.h"
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct _Memory {
    char *response;
    size_t size;
}Memory;

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);

char *make_request(char *url);

char *right(const char *token);

char *left(const char *token);

char *explore(const char *token);

char *move(const char *token);

char *info(const char *token);

#endif