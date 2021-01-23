#ifndef _FUNKCJE_H
#define _FUNKCJE_H


#include <curl/curl.h>
#include "../cJSON/cJSON.h"
#include <string.h>

#define Rozmiar 50

char swiat[Rozmiar][Rozmiar];


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

Mapa *parameters(const char * const korzen, char *komenda);

void wyzeruj();

Mapa *wpisz(char *response, char *komenda);

void zapisz();

void narysuj_swiat();

#endif