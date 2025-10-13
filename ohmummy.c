/*
============================================================
  Fichero: ohmummy.c
  Creado: 13-10-2025
  Ultima Modificacion: lun 13 oct 2025 14:23:39
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "spectrum.h"

#define GHEROUL 128
#define GHEROUR 129
#define GHERODL 130
#define GHERODR 131
#define GHERODLM 132
#define GHERODRM 133

void gdu_init() {
	gdu(GHEROUL,15,63,255,64,140,128,112,8);
	gdu(GHEROUR,240,252,255,240,240,112,16,32);
	gdu(GHERODL,7,8,19,23,16,15,3,7);
	gdu(GHERODR,192,32,144,144,16,224,64,192);
	gdu(GHERODRM,192,32,144,144,16,224,128,128);
}

void program() {
	gdu_init();
	ink(CYAN|BRIGHT);
	locate(10,10);
	printc(GHEROUL);
	printc(GHEROUR);
	locate(11,10);
	printc(GHERODL);
	printc(GHERODRM);
	show;
begin:
	listen;
	if(inkey('q')==0) goto begin; 
}
	
