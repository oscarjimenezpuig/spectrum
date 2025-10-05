/*
============================================================
  Fichero: gugu.c
  Creado: 05-10-2025
  Ultima Modificacion: diumenge, 5 d’octubre de 2025, 20:03:09
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "spectrum.h"

void program() {
	const int PAGU=10;
	static byte init=0;
	static int score;
	static byte gugu_x,gugu_y,gost_x,gost_y;
	static int moves=0;
	if(!init) {
		gugu_x=1;
		gugu_y=2;
		gost_x=31;
		gost_y=23;
		gdu(129,0,126,126,126,126,126,126,0); //pared
		gdu(130,60,126,126,219,255,255,255,219); //fantasma
		gdu(131,0,102,102,0,0,60,24,0); //gugu
		score=0;
		init=1;
		for(byte f=1;f<24;f++) {
			for(byte c=0;c<32;c++) {
				locate(f,c);
				if(c==0 || c==31 || f==1 || f==23) {
					paper(Attr(WHITE,BRIGHT));
					ink(Attr(BLUE,NORMAL));
					printc(129,NORMAL);
				}
			}
		}
		for(byte n=0;n<50;n++) {
			byte c=rnd(1,30);
			byte f=rnd(2,22);
			locate(f,c);
			paper(Attr(WHITE,BRIGHT));
			ink(Attr(BLUE,NORMAL));
			printc(129,NORMAL);
		}
		for(byte c=0;c<32;c++) {
			locate(0,c);
			ink(Attr(GREEN,NORMAL));
			printc(' ',INVERSE);
		}
	}
	locate(0,0);
	ink(Attr(GREEN,NORMAL));
	paper(Attr(WHITE,BRIGHT));
	prints("SCORE ",INVERSE);
	printn(score,INVERSE);
	locate(gugu_y,gugu_x);
	paper(Attr(BLACK,NORMAL));
	ink(Attr(CYAN,BRIGHT));
	printc(131,INVERSE);
	byte y=gugu_y;
	byte x=gugu_x;
	if(inkey('j')) x--;
	else if(inkey('l')) x++;
	if(inkey('i')) y--;
	else if(inkey('k')) y++;
	if(moves++%PAGU==0) {
		locate(y,x);
		attribute a=attr(PAPER);
		if(a.color!=WHITE && (gugu_x!=x || gugu_y!=y)) {
			if(a.color!=YELLOW) score++;
			locate(gugu_y,gugu_x);
			paper(Attr(YELLOW,BRIGHT));
			printc(' ',NORMAL);
			gugu_y=y;
			gugu_x=x;
		}
	}
	pause(0.001);
	if(inkey('s')) stop;
}

