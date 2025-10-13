/*
============================================================
  Fichero: memory.h
  Creado: 01-10-2025
  Ultima Modificacion: diumenge, 12 d’octubre de 2025, 18:50:50
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

// NOTAS

//En el entorno de memoria de los pixeles se representa la pantalla por lineas
//La formula para objtener una posicion de bloque (distribuidos en filas f y columnas c
//es p = c + f*SCRBW
//Almacenamiento de valores de mas de un byte en "little endian", de menos significativo a mas
//Las teclas que se registraran como entrada solo seran todos los keysym que vayan desde 0 a 255


//CONSTANTES

//dimension de pantalla

#define SCRBW 32
#define SCRBH 24
#define SCRPW (SCRBW*8)
#define SCRPH (SCRBH*8)

//gdu

#define GDUS 256

//key

#define KEYS 5

//colores 

#define COLORS 16

//memoria

#define ODCL 0 //inicio de la definicion de colores (4 bytes por colores)
#define DDCL (COLORS*4) //dimension de los colores guardados
#define OPIX (ODCL+DDCL) //inicio de la pantalla de pixels
#define DPIX (SCRPW*SCRPH/8)  //dimension de la pantalla de pixeles
#define OCOL (OPIX+DPIX) //origen de los colores
#define DCOL (SCRBW*SCRBH) //dimension de los colores
#define OMEM (OCOL+DCOL) //origen de la memoria de GDU
#define DMEM (GDUS*8) //dimension de la memoria de GDU
#define OKEY (OMEM+DMEM) //inicio de la direccion donde se guardan las teclas
#define DKEY KEYS //guarda el keysym de KEYS teclas
#define OROM (OKEY+DKEY) //origen de la memoria rom (no a disposicion de usuario)
#define DROM 8 //dimension de la memoria rom
#define ORAM (OROM+DROM) //origen de la ram
#define DRAM 1024 //dimension de la ram

#define MEMORY (DDCL + DPIX + DCOL + DMEM + DKEY + DROM + DRAM) //memoria total

//memoria colores

#define RINK 1
#define GINK 2
#define BINK 4
#define UINK 8
#define RBKG 16
#define GBKG 32
#define BBKG 64
#define UBKG 128

//tipos

typedef unsigned char byte;
typedef unsigned short direction;
typedef long long int faddress;

//memory

extern byte memory[MEMORY];

//FUNCIONES

void output();
//se produce muestra de la pantalla

void input();
//se produce lectura del teclado

void program();
//en su interior se mete todo el programa que se ejecutara. Solo parara la ejecucion en el momento que haya la señal de END_SIGN


