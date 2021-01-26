#ifndef _AUTOMAT_H
#define _AUTOMAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struktury.h"
#include <curl/curl.h>
#include "komunikacja.h"
#include "funkcje.h"

char *make_move(const char *token);

char *make_info(const char *token);

char *make_left(const char *token);

char *make_right(const char *token);

char *make_explore(const char *token);

int szukaj_obwiedni(odp *m, char *odpo, const char *token);

int szukaj_granicy(odp *m, char *odpo, const char *token);

int odkrywanie_mapy(odp *m, char *odpo, const char *token);

#endif