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
} odp;

typedef struct _Expl{
    char *status;
    int x;
    int y;
    char *type;
}expl;

typedef struct _Field
{   
    char **mapa;    //nasza mapka
    int now_x;      //aktualne położenie "x"
    int now_y;      // --||--
    int d_x;        //delta "x", tak zwany offset
    int d_y;
    int rozmiar_x;  //rozmiar naszej planszy
    int rozmiar_y;  //rozmiar naszej planszy
    char *dir;      //zwrot czołgu
    char *komenda;
    expl *pole[2];
    odp *response;
}field;

#endif