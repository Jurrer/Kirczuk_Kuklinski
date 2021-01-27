//#include "../header/funkcje.h"
//#include "../header/komunikacja.h"
#include"../header/struktury.h"
#include "../../cJSON/cJSON.h"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define M 10
#define U 3

void wypisz(){
    ;
}

void let_go_map(field *maaaapaaa){
    
    for(int i = 0; i < maaaapaaa->rozmiar_x; i++)
    {
        free(maaaapaaa->mapa[i]);
    }
    free(maaaapaaa->mapa);
    free(maaaapaaa);
}


field *do_map(int wiersze, int kolumny){
    field *new = calloc(1, sizeof(field));
    new->rozmiar_x = wiersze;
    new->rozmiar_y = kolumny;

    new->mapa = (char**) calloc(new->rozmiar_x, sizeof(char*));
    int i;
    for(i = 0; i <new->rozmiar_x; i++){
            new->mapa[i] = (char*) calloc(new->rozmiar_y, sizeof(char));
    }
    new->d_x = U;
    new->d_y = U;

    return new;
}


field * res_right(field *map){

    int i, j; 
    field * new_map = NULL;
    new_map = do_map(map->rozmiar_x*2, map->rozmiar_y);

    for(i = 0; i<map->rozmiar_x; i++)
        for(j = 0; map->rozmiar_y; j++){
            new_map->mapa[i][j] = map->mapa[i][j];
        }
    
    let_go_map(map);
    return new_map;
}

field * res_left(field *map){
    
    int i, j; 
    field * new_map = NULL;
    new_map = do_map(map->rozmiar_x*2, map->rozmiar_y);

    for(i = 0; i<map->rozmiar_x; i++)
        for(j = 0; map->rozmiar_y; j++){
            new_map->mapa[i+map->rozmiar_x][j] = map->mapa[i][j];
        }
    
    let_go_map(map);
    return new_map;
}

field * res_up(field *map){
    
    int i, j; 
    field * new_map = NULL;
    new_map = do_map(map->rozmiar_x, map->rozmiar_y*2);

    for(i = 0; i<map->rozmiar_x; i++)
        for(j = 0; map->rozmiar_y; j++){
            new_map->mapa[i][j] = map->mapa[i][j];
        }
    
    let_go_map(map);
    return new_map;
}

field * res_down(field *map){
    
    int i, j; 
    field * new_map = NULL;
    new_map = do_map(map->rozmiar_x, map->rozmiar_y*2);

    for(i = 0; i<map->rozmiar_x; i++)
        for(j = 0; map->rozmiar_y; j++){
            new_map->mapa[i][j + map->rozmiar_y] = map->mapa[i][j];
        }
    
    let_go_map(map);
    return new_map;
}



field * resize(field * info, field * map, int offsetx, int offsety){
    int x, y;
    field * result = NULL;
    
    x = offsetx + info->response->current_x;
    y = offsety + info->response->current_y;

    if(x == map->rozmiar_x-1){
        result = res_right(map);
        return result;
    }

    if(y == map->rozmiar_y-1){
        result = res_up(map);
        return result;
    }

    if(x == map->rozmiar_x-1){
        result = res_left(map);
        return result;
    }

    if(y == map->rozmiar_y-1){
        result = res_down(map);
        return result;
    }    
}



void main(int argc, char **argv)
{
    field * struktura_gry = do_map(10, 10);
    wypisz(struktura_gry);
}