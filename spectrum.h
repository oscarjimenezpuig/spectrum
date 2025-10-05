/*
============================================================
  Fichero: spectrum.h
  Creado: 01-10-2025
  Ultima Modificacion: diumenge, 5 d’octubre de 2025, 12:21:26
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "memory.h"

// direcciones auxiliares (en la memoria rom)

#define ATF OROM //posicion del cursor fila
#define ATC (ATF+1) //posicion del cursor columna
#define CLF (ATC+1) //color guardado (background y foreground)
#define CLC (CLF+1) //color guardado del cursor (una vez usado en impresion, desaparece por el valor de CLF)

// constante 0 (para todos los valores)

#define NORMAL 0

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

// tipos de impresion

#define FLIPX 1 //simetria respecto eje de las x's
#define FLIPY 2 //simetria respecto eje de las y's
#define INVERSE 4 //inversion gdu (ocupado es abierto y al reves)

// lugar del color

#define INK 0 //color de los bits conectados
#define PAPER 1 //color de los bits desconectados

// cabecera funciones

#define poke(D,V) if ((D)<MEMORY) memory[D]=(V)  //asignar valor a posicion de memoria
#define peek(D) ((D)<MEMORY)?memory[D]:0 //conseguir el valor de la posicion de memoria
#define move(O,D) poke((D),peek((O))) //mover de una a otra posicion el valor
#define stop (memory[OFLG]|=END_SIGN) //para la ejecucion del programa
#define Attr(C,B) (attribute){(C),(B)} //define un atributo
#define background(A) s_attrsetall(PAPER,A) //fondo de toda la pantalla
#define foreground(A) s_attrsetall(INK,A) //tinta de toda la pantalla
#define paper(A) s_attrset(PAPER,A) //paper de la proxima impresion
#define ink(A) s_attrset(INK,A) //tinta de la proxima impresion
#define attr(A) s_attrget(A) //se consigue donde los atributos de un sector particular
#define locate(F,C) s_at((F),(C)) //coloca en la posicion dicha el cursor
#define clear //limpia la pantalla (ver s_clear())
#define printc(B,M) s_print_c((B),(M)) //impresion de un caracter (0 a 255), M es el modo de impresion (FLIPX,FLIPY,INVERSE)
#define printn(N,M) s_print_n((N),(M)) //impresion de cualquier numero
#define prints(S,M) s_print_s(S,(M)) //impresion de una cadena
#define inkey(A) s_inkey(A) //devuelve si se ha tecleado cierta tecla (a-z,0-9,espacio)
#define gdu(N,A,B,C,D,E,F,G,H) s_gdu((N),(A),(B),(C),(D),(E),(F),(G),(H)) //definicion de un grafico definido por el usuario
#define randomize(A) s_randomize((A)) //introduce la semilla
#define rnd(A,B) s_rnd((A),(B)) //da numero aleatorio del intervalo [A,B]
#define pause(A) s_pause((A)) //pausa de un determinado tiempo
								
// tipos

typedef struct {
	byte color : 3;
	byte bright : 4;
} attribute;

// funciones

void s_attrsetall(byte place,attribute a);
//definicion de todo el fondo o tinta de la pantalla

void s_attrset(byte place,attribute a);
//definicion de fondo o tinta del siguiente sector de impriesion

attribute s_attrget(byte place);
//consigue el attributo de color y brillo segun el valor de place de attribute

void s_at(byte f,byte c);
//pone la posicion del cursor en la fila y columna especificada

void s_clear();
//quita todos los pixeles de pantalla, y restablece los colores de fondo y de tinta originales
//la posicion del cursor la situa en 0,0

//todas las funciones print implican que las posiciones de at varian hasta detras de la
//impresion

void s_print_c(byte c,byte mode);
//impresion de un caracter

void s_print_n(double n,byte mode);
//impresion de cualquier tipo de numero

void s_print_s(char* s,byte mode);
//impresion de una cadena de caracteres

byte s_inkey(char k);
//comprueba si se esta pulsada una tecla.

void s_gdu(byte code,byte a,byte b,byte c,byte d,byte e,byte f,byte g,byte h);
//definicion de un gdu en el caracter c

void s_randomize(int a);
//establecimiento de la semilla del numero aleatorio, si a negativa, en funcion del tiempo

int s_rnd(int a,int b);
//nuemero aleatorio entre dos valores dados

void s_pause(double seconds);
//hacer una pausa de un determinado numero de segundos
