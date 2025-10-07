/*
============================================================
  Fichero: spectrum.h
  Creado: 01-10-2025
  Ultima Modificacion: mar 07 oct 2025 12:21:43
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "memory.h"

// direcciones auxiliares (en la memoria rom)

#define ATF OROM //posicion del cursor fila
#define ATC (ATF+1) //posicion del cursor columna
#define CLF (ATC+1) //color guardado (background y foreground)
#define CLC (CLF+1) //color guardado del cursor (una vez usado en impresion, desaparece por el valor de CLF)
#define MOI (CLC+1) //guarda el modo de impresion

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

#define PINK 0 //color de los bits conectados
#define PPAPER 1 //color de los bits desconectados

// cabecera funciones

#define POKE(D,V) if ((D)<MEMORY) memory[D]=(V)  //asignar valor a posicion de memoria
#define PEEK(D) ((D)<MEMORY)?memory[D]:0 //conseguir el valor de la posicion de memoria
#define MOVE(O,D) poke((D),peek((O))) //mover de una a otra posicion el valor
#define STOP (memory[OFLG]|=END_SIGN) //para la ejecucion del programa
#define BACKGROUND(A) s_attrsetall(PPAPER,A) //fondo de toda la pantalla
#define FOREGROUND(A) s_attrsetall(PINK,A) //tinta de toda la pantalla
#define PAPER(A) s_attrset(PPAPER,A) //paper de la proxima impresion
#define INK(A) s_attrset(PINK,A) //tinta de la proxima impresion
#define ATTR(P) s_attrget(P) //se consigue donde los atributos de un sector particular
#define MODE(M) s_mode((M)) //almacena el modo de impresion
#define LOCATE(F,C) s_at((F),(C)) //coloca en la posicion dicha el cursor
#define PRINTC(B) s_print_c((B)) //impresion de un caracter (0 a 255), M es el modo de impresion (FLIPX,FLIPY,INVERSE)
#define PRINTN(N) s_print_n((N)) //impresion de cualquier numero
#define PRINTS(S) s_print_s(S) //impresion de una cadena
#define CLS s_clear() //limpia la pantalla (ver s_clear())
#define INKEY(A) s_inkey(A) //devuelve si se ha tecleado cierta tecla (a-z,0-9,espacio)
#define GDU(N,A,B,C,D,E,F,G,H) s_gdu((N),(A),(B),(C),(D),(E),(F),(G),(H)) //definicion de un grafico definido por el usuario
#define RANDOMIZE(A) s_randomize((A)) //introduce la semilla
#define RND(A,B) s_rnd((A),(B)) //da numero aleatorio del intervalo [A,B]
#define PAUSE(A) s_pause((A)) //pausa de un determinado tiempo
#define PROGRAM void program() { //inicio del procedimiento programa
#define PROCEDURE(A) void A() { //inicio de un procedimiento
#define END } //fin de cualquier procedimiento
#define CALL(A) A(); //llamada a cualquier procedimiento
#define GOTO(A) goto label_##A //goto
#define LABEL(A) label_##A: //label de un goto
#define NUMBER double //definicion de una variable tipo double
#define BYTE byte //definicion de una variable tipo byte
#define STRING char* //definicion de una variable tipo char
#define IF(C) if(C) { //definicion de if
#define ELSIF(C) } else if(C) {//else if
#define ELSE } else { //else
#define ENDIF } //final del if
#define FOR(V,O,C,I) for(V=O;C;I) { //bucle for
#define NEXT } //final del bucle for
#define REM(A) //poner anotacion
#define DO do { //bucle do
#define WHILE(A) } while(A); //final del do
#define PERSISTENT static //va delante de las variables de procedimiento para hacerlas static

// funciones

void s_attrsetall(byte place,byte a);
//definicion de todo el fondo o tinta de la pantalla (a=color|bright)

void s_attrset(byte place,byte a);
//definicion de fondo o tinta del siguiente sector de impresion

byte s_attrget(byte place);
//consigue color|bright segun el valor de place de attribute

void s_at(byte f,byte c);
//pone la posicion del cursor en la fila y columna especificada

void s_clear();
//quita todos los pixeles de pantalla, y restablece los colores de fondo y de tinta originales
//la posicion del cursor la situa en 0,0

//todas las funciones print implican que las posiciones de at varian hasta detras de la
//impresion

void s_mode(byte m);
//modo de impresion de caracter, numero o secuencia

void s_print_c(byte c);
//impresion de un caracter

void s_print_n(double n);
//impresion de cualquier tipo de numero

void s_print_s(char* s);
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
