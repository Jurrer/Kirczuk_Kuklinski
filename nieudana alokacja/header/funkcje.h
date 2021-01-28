#ifndef _FUNKCJE_H
#define _FUNKCJE_H


#include <curl/curl.h>
#include "../../cJSON/cJSON.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "struktury.h"

#define MAX 50

void parameters(field * zodiak, const char * const korzen, char *komenda);

field *alloc(field * ala);

void freeee(field * alama);

void wypelnij_plusy(field * swiat);

void wpisz(char *response, char *komenda);

void zapisz(field * swiat);

void narysuj_swiat(field * swiat);

#endif