#ifndef _KOMUNIKACJA_H
#define _KOMUNIKACJA_H

#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Memory {
    char *response;
    size_t size;
}Memory;

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);

char *make_request(char *url);

char *right( char *token);

char *left( char *token);

char *explore( char *token);

char *move( char *token);

char *info( char *token);

#endif