/*
============================================================
  Fichero: gdum.h
  Creado: 10-10-2025
  Ultima Modificacion: divendres, 10 d’octubre de 2025, 19:18:51
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "spectrum.h"

typedef unsigned char u1;
typedef signed char s1;

typedef struct {
	u1 f : 4;
	u1 c : 4;
} Cursor;

void gdu_init();
	
void gdu_new();

void gdu_move(s1 df,s1 dc);

void gdu_set();

void gdu_era();

void gdu_quit();

void gdu_calc(u1* res);

void gdu_act();

void gdu_draw();

