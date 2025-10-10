/*
============================================================
  Fichero: prueba.c
  Creado: 09-10-2025
  Ultima Modificacion: dijous, 9 d’octubre de 2025, 20:35:41
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "spectrum.h"

#include <stdio.h>

void memprt() {
	int counter=0;
	for(int n=OPIX;n<OPIX+DPIX;n++) {
		printf("%03i ",peek(n));
		counter++;
		if(counter%32==0) puts("");
	}
}

void program() {
	static int doneit=0;
	if(!doneit) {
		ink(WHITE);
		locate(0,0);
		printc('A');
		ink(YELLOW);
		for(int n=5713;n<=5937;n+=SCRBW) {
			poke(n,1);
		}
		doneit=1;
	}
	if(inkey('s')) stop;
}
