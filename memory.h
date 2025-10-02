/*
============================================================
  Fichero: memory.h
  Creado: 01-10-2025
  Ultima Modificacion: dijous, 2 d’octubre de 2025, 05:34:13
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

//memoria

#define OPIX 0 //inicio de la pantalla de pixels
#define DPIX 6144  //dimension de la pantalla de pixeles
#define OCOL (OPIX+DPIX) //origen de los colores
#define DCOL 1567 //dimension de los colores
#define OMEM (OCOL+DCOL) //origen de la memoria de GDU
#define DMEM 1024 //dimension de la memoria de GDU

#define MEMORY (DPIX+DCOL+DMEM) //memoria total

//funciones de memoria

#define memset(D,B) if((D)<MEMORY) memory[(D)]=(B)
#define memget(D) (((D)<(MEMORY))?memory[(D)]:0)
#define memmov(O,D) memset((D),memget(D))

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
typedef unsigned short dir;

void show();





