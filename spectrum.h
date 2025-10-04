/*
============================================================
  Fichero: spectrum.h
  Creado: 01-10-2025
  Ultima Modificacion: dissabte, 4 d’octubre de 2025, 09:55:01
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "memory.h"

// direcciones auxiliares (en la memoria rom)

#define ATF OROM //posicion del cursor fila
#define ATC (ATF+1) //posicion del cursor columna
#define CLF (ATC+1) //color guardado (background y foreground)
#define CLC (CLF+1) //color guardado del cursor (una vez usado en impresion, desaparece por el valor de CLF)

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

#define poke(D,V) if ((D)<MEMORY) memory[D]=(V)  //asignar valor a posicion de memoria
#define peek(D) ((D)<MEMORY)?memory[D]:0 //conseguir el valor de la posicion de memoria
#define move(O,D) poke((D),peek((O))) //mover de una a otra posicion el valor
#define stop (memory[OFLG]|=END_SIGN)

// tipos


// funciones

void s_background(byte color,byte bright);
//definicion de todo el background

void s_foreground(byte color,byte bright);
//definicion de toda la tinta de la pantalla

void s_at(byte f,byte c);
//pone la posicion del cursor en la fila y columna especificada

void s_paper(byte color,byte bright);
//color de fondo del siguiente sector de impresion

void s_ink(byte color,byte bright);
//color de tinta del siguiente sector de impresion

void s_clear();
//quita todos los pixeles de pantalla, restablece el background y el foreground, pone
//la posicon del cursor en 0,0

//todas las funciones print implican que las posiciones de at varian hasta detras de la
//impresion

void s_print_c(char c);
//impresion de un caracter

void s_print_n(double n);
//impresion de cualquier tipo de numero

void s_print_s(char* s);
//impresion de una cadena de caracteres

byte s_inkey(char k);
//comprueba si se esta pulsada una tecla.

void s_gdu(char n,byte a,byte b,byte c,byte d,byte e,byte f,byte g,byte h);
//definicion de un gdu en el caracter c
