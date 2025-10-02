/*
============================================================
  Fichero: memory.h
  Creado: 01-10-2025
  Ultima Modificacion: dijous, 2 d’octubre de 2025, 20:31:28
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include <stdlib.h>

// NOTAS

//En el entorno de memoria de los pixeles, los 8 valores consecutivos representan
//el bloque de dibujo
//La formula para objtener una posicion de bloque (distribuidos en filas f y columnas c
//es p = c + f*SCRBW
//Almacenamiento de valores de mas de un byte en "little endian", de menos significativo a mas

//CONSTANTES

//dimension de pantalla

#define SCRBW 32
#define SCRBH 24
#define SCRPW (SCRBW*8)
#define SCRPH (SCRBH*8)

//gdu

#define GDU 128

//key

#define KEYS 5

//colores 

#define COLORS 16

//memoria

#define OFLG 0 //inicio de las banderas
#define DFLG 1 //dimension de memoria para las banderas 
#define ODCL (OFLG+DFLG) //inicio de la definicion de colores (4 bytes por colores)
#define DDCL (COLORS*4) //dimension de los colores guardados
#define OPIX (ODCL+DDCL) //inicio de la pantalla de pixels
#define DPIX (SCRPW*SCRPH/8)  //dimension de la pantalla de pixeles
#define OCOL (OPIX+DPIX) //origen de los colores
#define DCOL (SCRBW*SCRBH) //dimension de los colores
#define OMEM (OCOL+DCOL) //origen de la memoria de GDU
#define DMEM GDU*8 //dimension de la memoria de GDU
#define OKEY (OMEM+DMEM) //inicio de la direccion donde se guardan las teclas
#define DKEY (2*KEYS) //guarda el keysym de KEYS teclas

#define MEMORY (DFLG + DDCL + DPIX+DCOL+DMEM+DKEY) //memoria total

//memoria colores

#define RINK 1
#define GINK 2
#define BINK 4
#define UINK 8
#define RBKG 16
#define GBKG 32
#define BBKG 64
#define UBKG 128

//flags

#define END_SIGN 1

//funciones

//funciones de memoria
#define memset(D,B) if((D)<MEMORY) memory[(D)]=(B)
#define memget(D) (((D)<(MEMORY))?memory[(D)]:0)
#define memmov(O,D) memset((D),memget(O))

//TIPOS

typedef unsigned char byte;
typedef unsigned short direction;

//FUNCIONES

void program();
//dentro de esta funcion se debe poner todo el programa





