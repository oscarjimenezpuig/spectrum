/*
============================================================
  Fichero: memory.h
  Creado: 01-10-2025
  Ultima Modificacion: jue 02 oct 2025 12:19:59
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include <stdlib.h>

// notas

//En el entorno de memoria de los pixeles, los 8 valores consecutivos representan
//el bloque de dibujo
//La formula para objtener una posicion de bloque (distribuidos en filas f y columnas c
//es p = c + f*SCRBW

//dimension de pantalla

#define SCRBW 32
#define SCRBH 24
#define SCRPW (SCRBW*8)
#define SCRPH (SCRBH*8)

//GDU

#define GDU 128

//KEY

#define KEYS 5

//memoria

#define OPIX 0 //inicio de la pantalla de pixels
#define DPIX (SCRPW*SCRPH/8)  //dimension de la pantalla de pixeles
#define OCOL (OPIX+DPIX) //origen de los colores
#define DCOL (SCRBW*SCRBH) //dimension de los colores
#define OMEM (OCOL+DCOL) //origen de la memoria de GDU
#define DMEM GDU*8 //dimension de la memoria de GDU
#define OKEY (OMEM+DMEM) //inicio de la direccion donde se guardan las teclas
#define DKEY (2*KEYS) //guarda el keysym de KEYS teclas

#define MEMORY (DPIX+DCOL+DMEM+DKEY) //memoria total

//funciones de memoria

#define memset(D,B) if((D)<MEMORY) memory[(D)]=(B)
#define memget(D) (((D)<(MEMORY))?memory[(D)]:0)
#define memmov(O,D) memset((D),memget(O))

//memoria colores

#define RINK 1
#define GINK 2
#define BINK 4
#define UINK 8
#define RBKG 16
#define GBKG 32
#define BBKG 64
#define UBKG 128


typedef unsigned char byte;
typedef unsigned short direction;

void show();

void inkey();





