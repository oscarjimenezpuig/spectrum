/*
============================================================
  Fichero: gdum.c
  Creado: 10-10-2025
  Ultima Modificacion: divendres, 10 d’octubre de 2025, 19:30:14
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "gdum.h"

#define GDUD 8

#define MALLA 128
#define CURSOR 129
#define MOSTRA 130

struct flag {
	u1 quit : 2;
} flag={0};

Cursor cursor={0,0};

u1 gdu[GDUD][GDUD];

void gdu_init() {
	static u1 init=0;
	if(!init) {
		gdu_new();
		gdu(MALLA,255,129,129,129,129,129,129,255);
		gdu(CURSOR,0,0,60,60,60,60,0,0);
		background(WHITE);
		foreground(BLACK);
		init=1;
	}
}

#define loop(A) for((A)=0;(A)<8;(A)++)

void gdu_new() {
	u1 f,c;
	loop(f) {
		loop(c) {
			gdu[f][c]=0;
		}
	}
	cursor=(Cursor){0,0};
	gdu(MOSTRA,0,0,0,0,0,0,0,0);
	cls;
}

void gdu_move(s1 df,s1 dc) {
	if(df==1 && cursor.f<7) cursor.f++;
	else if(df==-1 && cursor.f>0) cursor.f--;
	if(dc==1 && cursor.c<7) cursor.c++;
	else if(dc==-1 && cursor.c>0) cursor.c--;
}

void gdu_set() {
	gdu[cursor.f][cursor.c]=1;
}

void gdu_era() {
	gdu[cursor.f][cursor.c]=0;
}

void gdu_quit() {
	if(flag.quit==1) {
		locate(23,0);
		ink(BLACK);
		prints("Sure to quit (Y/N)?");
		flag.quit=2;
	} else if(flag.quit==2) {
		if(inkey('y')) flag.quit=3;
		else if(inkey('n')) flag.quit=0;
	} else if(flag.quit==3) {
		stop;
	}
}

void gdu_act() {
	const int DELAY=7;
	static int counter=0;
	if(!flag.quit) {
		if(counter>=DELAY) {
			if(inkey('j')) gdu_move(0,-1);
			else if(inkey('l')) gdu_move(0,1);
			if(inkey('i')) gdu_move(-1,0);
			else if(inkey('k')) gdu_move(1,0);
			if(inkey('a')) gdu_set();
			else if(inkey('s')) gdu_era();
			if(inkey('q')) flag.quit=1;
			else if(inkey('n')) gdu_new();
			counter=0;
		} else counter++;
	} else gdu_quit();
}

void gdu_calc(u1* res) {
	u1 f,c;
	loop(f) {
		u1 factor=128;
		res[f]=0;
		loop(c) {
			if(gdu[f][c]) res[f]+=factor;
			factor=factor>>1;
		}
	}
}

void gdu_draw() {
	u1 f,c;
	loop(f) {
		loop(c) {
			u1 val=gdu[f][c];
			locate(f,c);
			if(f==cursor.f && c==cursor.c) {
				ink(RED|BRIGHT);
				if(val==1) {
					paper(BLACK);
				} else {
					paper(WHITE|BRIGHT);
				}
				printc(CURSOR);
			} else if(val==1) {
				ink(BLACK);
				mode(INVERSE);
				printc(' ');
				mode(NORMAL);
			} else {
				ink(BLACK);
				paper(WHITE|BRIGHT);
				printc(MALLA);
			}
		}
	}
	u1 val[8];
	gdu_calc(val);
	gdu(MOSTRA,val[0],val[1],val[2],val[3],val[4],val[5],val[6],val[7]);
	locate(4,16);
	paper(WHITE|BRIGHT);
	ink(BLACK);
	printc(MOSTRA);
	locate(10,0);
	ink(BLACK);
	paper(WHITE)
	loop(f) {
		printn(val[f]);
		if(f<7) prints(",");
	}
}

void program() {
	gdu_init();
	gdu_act();
	gdu_draw();
	pause(0.01);
}




	
	


