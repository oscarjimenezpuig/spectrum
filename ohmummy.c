/*
============================================================
  Fichero: ohmummy.c
  Creado: 13-10-2025
  Ultima Modificacion: mar 14 oct 2025 14:33:23
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "spectrum.h"

#define GPLAYER 128
#define GMUMMY 129
#define GSTONE 130
#define GHUELLA 131
#define GLLAVE 132
#define GPAPIRO 133
#define GTUMBA 134

#define MFI 23
#define MCO 31

typedef unsigned char u1;

u1 malla[MFI][MCO];

#define VACIO 0
#define HUELLA 1
#define PARED 2
#define LLAVE 4
#define PAPIRO 8
#define TUMBA 16
#define AGUA 32
#define MOMIA 64

void gdu_init() {
	gdu(GPLAYER,60,66,165,129,255,24,36,102);
	gdu(GMUMMY,153,153,255,36,36,24,36,102);
	gdu(GSTONE,0,126,86,106,86,106,126,0);
	gdu(GHUELLA,0,0,0,24,24,0,0,0);
	gdu(GLLAVE,56,8,56,8,28,34,34,28);
	gdu(GPAPIRO,255,129,189,128,189,129,189,255);
	gdu(GTUMBA,24,36,24,126,126,24,24,24);
}

void malla_mapa_init() {
	for(u1 f=0;f<MFI;f++) {
		for(u1 c=0;c<MCO;c++) {
			if(f==0 || f==MFI-1 || c==0 || c==MCO-1) malla[f][c]=PARED;
			else if((f%4)==1 || (c%4)==1) malla[f][c]=VACIO;
			else malla[f][c]=PARED|AGUA;
		}
	}
	u1 flag[]={LLAVE,PAPIRO,TUMBA,MOMIA};
	int bef=(MFI-3)/4;
	int bec=(MCO-3)/4;
	for(int n=0;n<4;n++) {
		while(1) {
			int fe=rnd(0,bef-1);
			int ce=rnd(0,bec-1);
			int f=3+4*fe;
			int c=3+4*ce;
			if(malla[f][c]==(PARED|AGUA)) {
				malla[f][c]|=flag[n];
				break;
			}
		}
	}
}

static void pared_prt() {
	paper(YELLOW);
	ink(RED);
	printc(GSTONE);
}

static void llave_prt() {
	ink(MAGENTA|BRIGHT);
	printc(GLLAVE);
}

static void tumba_prt() {
	ink(YELLOW|BRIGHT);
	printc(GTUMBA);
}

static void papiro_prt() {
	ink(WHITE|BRIGHT);
	printc(GPAPIRO);
}

#include <stdio.h>

void open_block(int f,int c) {
	//abre el bloque que tiene centro esta fila y esta columna
	u1 extra=malla[f][c]&~(PARED|AGUA);
	printf("%i,%i->%i\n",f,c,extra);//dbg
	u1 papel=BLUE;
	if(extra==MOMIA) {
		papel=BLACK;
	}
	for(int cf=f-1;cf<=f+1;cf++) {
		for(int cc=c-1;cc<=c+1;cc++) {
			locate(cf,cc);
			malla[cf][cc]&=(~PARED);
			if(papel==BLACK) malla[cf][cc]&=(~AGUA);
			paper(papel);
			if(cf==f && cc==c) {
				switch(extra) {
					case LLAVE:
						llave_prt();
						break;
					case PAPIRO:
						papiro_prt();
						break;
					case TUMBA:
						tumba_prt();
						break;
					case MOMIA:
						//este no es definitivo
						//momia_print();
						break;
				}
			} else printc(' ');
		}
	}
}

void mapa_draw() {
	for(int f=0;f<MFI;f++) {
		for(int c=0;c<MCO;c++) {
			u1 val=malla[f][c];
			locate(f,c);
			if(val & PARED) pared_prt();
		}
	}
}

void program() {
	gdu_init();
	malla_mapa_init();
	mapa_draw();
	show;
	pause(2);
	for(int f=0;f<5;f++) {
		for(int c=0;c<7;c++) {
			open_block(3+4*f,3+4*c);
		}
	}
	show;
	while(inkey('q')==0) listen;
}

