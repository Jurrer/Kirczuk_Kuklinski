#ifndef _AUTOMAT_H
#define _AUTOMAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struktury.h"
#include <curl/curl.h>
#include "komunikacja.h"
#include "funkcje.h"

char *make_move(char *token);

char *make_info(char *token);

char *make_left(char *token);

char *make_right(char *token);

char *make_explore(char *token);

int szukaj_obwiedni(odp *m, char *odpo, char *token);

int szukaj_granicy(odp *m, char *odpo, char *token);

int czysc_mape(odp *m, char *odpo, char *token);

#endif