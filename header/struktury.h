#ifndef _STRUKTURY_H
#define _STRUKTURY_H


typedef struct _Odp
{
    char *status;
    char *name;
    int current_x;
    int current_y;
    char *current_session;
    char *direction;
    int step;
    char *field_type;
    char *field_bonus;    
    int x[3];
    int y[3];
    char type[200][3];
} odp;

typedef struct _Field
{   
    char **mapa;
    int now_x;
    int now_y;
    int d_x;
    int d_y;
    int rozmiar_x;
    int rozmiar_y;
    char *dir;
    char *field;
} field;

#endif