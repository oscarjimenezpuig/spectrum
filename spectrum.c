/*
============================================================
  Fichero: spectrum.c
  Creado: 03-10-2025
  Ultima Modificacion: vie 03 oct 2025 12:22:10
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "spectrum.h"


#include <stdio.h>

void s_background(byte c,byte b) {
	byte *ptr,*init; 
	ptr=init=memory+OCOL;
	while(ptr!=init+DCOL) {
		byte val=(c|b)<<4;
		*ptr++|=val;
	}
}

void s_foreground(byte c,byte b) {
	byte *ptr,*init; 
	ptr=init=memory+OCOL;
	while(ptr!=init+DCOL) {
		*ptr|=(c|b);
		ptr++;
	}
}


//prueba

void program() {
	s_background(MAGENTA,NORMAL);
}

