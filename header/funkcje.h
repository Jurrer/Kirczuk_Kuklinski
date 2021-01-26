#ifndef _FUNKCJE_H
#define _FUNKCJE_H


#include <curl/curl.h>
#include "../../cJSON/cJSON.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "struktury.h"

#define MAX 50

char swiat[MAX][MAX];

odp *parameters(const char * const korzen, char *komenda);

field *alloc(field * ala);

void freeee(field * alama);

void wyzeruj();

void wpisz(char *response, char *komenda);

void zapisz();

void narysuj_swiat();

#endif