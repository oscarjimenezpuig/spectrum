/*
============================================================
  Fichero: spectrum.h
  Creado: 01-10-2025
  Ultima Modificacion: vie 03 oct 2025 11:54:45
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "memory.h"

// colores

#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7

#define BRIGHT 8
#define NORMAL 0

// cabecera funciones

#define POKE(D,V) memset((D),(V)) //asignar valor a posicion de memoria
#define PEEK(D) memget((D)) //conseguir el valor de la posicion de memoria
#define MOVE(O,D) memmov((D),(O)) //mover de una a otra posicion el valor

// funciones

void s_background(byte color,byte bright);
//definicion de todo el background

void s_foreground(byte color,byte bright);
//definicion de toda la tinta de la pantalla
