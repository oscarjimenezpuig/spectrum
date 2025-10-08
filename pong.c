/*
============================================================
  Fichero: pong.c
  Creado: 08-10-2025
  Ultima Modificacion: mié 08 oct 2025 14:32:07
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "spectrum.h"

#define PG 128
#define BG 129

#define BV 6
#define JV 5
#define OV 7

static int jugp=0;
static int ordp=0;

static int py=12;
static int px=16;

void terreno() {
//dibujo de campo
	ink(WHITE|BRIGHT);
	for(int c=0;c<SCRBW;c++) {
		locate(1,c);
		printc(PG);
		locate(23,c);
		printc(PG);
	}
	for(int f=1;f<23;f++) {
		if(f<10 || f>14) {
			locate(f,0);
			printc(PG);
			locate(f,31);
			printc(PG);
		}
	}
	ink(BLACK);
}

void definicion() {
	static byte init=0;
	if(!init) {
		init=1;
		randomize(-1);
		//gdu's
		gdu(PG,255,255,255,255,255,255,255,255);
		gdu(BG,60,126,255,255,255,255,126,60);
	}
}

void mover_pelota(int inicia) {
	static int dx=0;
	static int dy=0;
	if(inicia) {
		px=16;
		py=12;
		while(dx==0 && dy==0) {
			dx=rnd(-1,1);
			dy=rnd(-1,1);
		}
		ink(WHITE|BRIGHT);
		locate(py,px);
		printc(BG);
	} else {
		int fx=px+dx;
		int fy=py+dy;
		ink(BLACK);
		locate(py,px);
		printc(' ');
		locate(fy,px);
		if(attri & WHITE) {
			dy=-dy;
			if(dx==0) dx=rnd(-1,1);
		} else py=fy;
		locate(py,fx);
		if(attri & WHITE) {
			dx=-dx;
			if(dy==0) dy=rnd(-1,1);
		} else px=fx;
		ink(WHITE|BRIGHT);
		locate(py,px);
		printc(BG);
	}
}

int mover_paleta(int* f,int df,int c) {
	const int LP=3;
	int ff=*f+df;
	if(ff==1 || ff+LP==24) return 0;
	ink(BLACK);
	for(int n=0;n<LP;n++) {
		locate(*f+n,c);
		printc(' ');
	}
	*f=ff;
	ink(WHITE|BRIGHT);
	for(int n=0;n<LP;n++) {
		locate(*f+n,c);
		printc(PG);
	}
	return 1;
}

void mover_jugador(int init) {
	static int jy=11;
	const int JX=4;
	if(init) {
		jy=11;
		mover_paleta(&jy,0,JX);
	} else {
		if(inkey('a')) {
			if(!mover_paleta(&jy,-1,JX)) unkey('a');
		}
		else if(inkey('z')) {
			if(!mover_paleta(&jy,1,JX)) unkey('z');
		}
	}
}

void mover_ordenador(int init) {
	static int oy=11;
	const int OX=28;
	if(init) {
		oy=11;
		mover_paleta(&oy,0,OX);
	} else {
		if(oy+1<py) mover_paleta(&oy,1,OX);
		else if(oy+1>py) mover_paleta(&oy,-1,OX);
	}
}

void marcador() {
	ink(WHITE|BRIGHT);
	locate(0,0);
	prints("PLAYER ");
	printn(jugp);
	locate(0,22);
	printn(ordp);
	prints(" COMPUTER");
}

int gol() {
	int si=0;
	if(px==0) {
		si=1;
		ordp++;
	} else if(px==31) {
		si=1;
		jugp++;
	}
	return si;
}

void program() {
	static int ini=1;
	static int mb=BV;
	static int mj=JV;
	static int mo=OV;
	definicion();
	marcador();
	if(ini) {
		pause(1);
		cls;
		terreno();
		mb=BV;
		mj=JV;
		mo=OV;
	}
	if(mb==BV) {
		mover_pelota(ini);
		mb=0;
	} else mb++;
	if(mj==JV) {
		mover_jugador(ini);
		mj=0;
	} else mj++;
	if(mo==OV) {
		mover_ordenador(ini);
		mo=0;
	} else mo++;
	ini=0;
	if(gol()) {
		locate(12,15);
		ink(WHITE|BRIGHT);
		mode(INVERSE);
		prints("GOL");
		mode(NORMAL);
		ink(BLACK);
		ini=1;
	}
	pause(0.01);
	if(inkey('s')) stop;
}


