/*
============================================================
  Fichero: memory.c
   mreado: 01-10-2025
  Ultima Modificacion: dijous, 2 d’octubre de 2025, 05:34:13
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "memory.h"

#define COLORS 16
#define PIXDIM 4
#define BLCDIM (PIXDIM*8)

byte memory[MEMORY];

XColor color[COLORS];

static void mem_init() {
	//establecemos todos los pixeles en blanco
	byte* p=memory+OPIX;
	while(p!=memory+OPIX+DPIX) *p++=0;
	//establecemos el color fondo blanco y paper negro en el color
	*p=memory+OCOL;
	while(p!=memory+OCOL+DCOL) *p++=RINK|GINK|BINK|UINK;
	//definicion de gdu, donde se colocaran las letras
}

static void scr_init() {
	x_init();
	for(int r=1;r<=2;r=r+1) {
		double factor=0.5*(double)r;
		for(int k=0;k<8;k++) {
			double red=0;
			double green=0;
			double blue=0;
			if(k & 1) red=factor;
			else if(k & 2) green=factor;
			else if(k & 4) blue=factor;
			color[k+8*(r-1)]=x_color(red,green,blue);
		}
	}
}

void show() {
	static byte init=0;
	if(!init) {
		mem_init();
		scr_init();
	}



			

	

