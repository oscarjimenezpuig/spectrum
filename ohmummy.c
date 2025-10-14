/*
============================================================
  Fichero: ohmummy.c
  Creado: 13-10-2025
  Ultima Modificacion: dilluns, 13 d’octubre de 2025, 20:34:23
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
#define GSTONEA 134
#define GSTONEB 135
#define GSTONEC 136
#define GHUELLA 137

#define COLIN 3
#define FILIN 0

typedef unsigned char u1;
typedef signed char s1;

typedef struct {
	u1 player;
	int f,c;
	s1 direction;
	u1 imagen;
} Psi;

Psi player;

void gdu_init() {
	gdu(GHEROUL,15,63,255,64,140,128,112,8);
	gdu(GHEROUR,240,252,255,240,240,112,16,32);
	gdu(GHERODL,7,8,19,23,16,15,3,7);
	gdu(GHERODR,192,32,144,144,16,224,64,192);
	gdu(GHERODRM,192,32,144,144,16,224,128,128);
	gdu(GSTONEA,255,123,156,239,237,187,59,251);
	gdu(GSTONEB,251,251,245,191,119,246,237,175);
	gdu(GSTONEC,239,245,219,55,253,203,189,190);
	gdu(GHUELLA,0,0,0,24,24,0,0,0);
}

static void player_init() {
	player=(Psi){1,FILIN+1,COLIN+1,1,1};
}

static void stoneprint(byte f,byte c) {
	byte brg=(rnd(0,1))?BRIGHT:NORMAL;
	ink(RED|brg);
	if(rnd(0,4)==0) paper(GREEN);
	else paper(BLACK);
	locate(f,c);
	mode(rnd(0,3));
	byte sgdu=rnd(GSTONEA,GSTONEC);
	printc(sgdu);

}

void scenario() {
	for(byte f=FILIN;f<FILIN+24;f++) {
		stoneprint(f,COLIN);
		stoneprint(f,31);
	}
	for(byte c=COLIN;c<COLIN+29;c++) {
		stoneprint(0,c);
		stoneprint(23,c);
	}
	for(byte pi=0;pi<5;pi++) {
		for(byte pc=0;pc<5;pc++) {
			int fi=pi*4+3;
			int ci=pc*5+COLIN+3;
			for(int f=fi;f<fi+2;f++) {
				for(int c=ci;c<ci+3;c++) {
					stoneprint(f,c);
				}
			}
		}
	}
	ink(BLACK);
	paper(BLACK);
}

void player_draw() {
	int f=player.f;
	int c=player.c;
	ink(WHITE|BRIGHT);
	if(player.direction==-1) {
		mode(NORMAL);
		locate(f,c);
		printc(GHEROUL);
		printc(GHEROUR);
		locate(f+1,c);
		printc(GHERODL);
		if(player.imagen==0) printc(GHERODRM);
		else printc(GHERODR);
	} else {
		locate(f,c);
		mode(FLIPY);
		printc(GHEROUR);
		printc(GHEROUL);
		locate(f+1,c);
		if(player.imagen==0) printc(GHERODRM);
		else printc(GHERODR);
		printc(GHERODL);
		mode(NORMAL);
	}
}

#include <stdio.h> //dbg

static int chk_place(s1 df,s1 dc) {
	u1 obstaculo=0;
	int f=player.f;
	int c=player.c;
	int chk[]={0,0,0,0};
	if(df==1) {
		chk[0]=f+2;
		chk[1]=c;
		chk[2]=f+2;
		chk[3]=c+1;
	} else if(df==-1) {
		chk[0]=f-1;
		chk[1]=c;
		chk[2]=f-1;
		chk[3]=c;
	}
	if(dc==1) {
		chk[0]=f;
		chk[1]=c+2;
		chk[2]=f+1;
		chk[3]=c+2;
	} else if(dc==-1) {
		chk[0]=f;
		chk[1]=c-1;
		chk[2]=f+1;
		chk[3]=c-1;
	}
	for(int n=0;n<2;n++) {
		//continuar la deteccion de atributos



int player_move(s1 df,s1 dc) {
	int ff=player.f+df;
	int fc=player.c+dc;
	locate(ff,fc);
	byte color=attri;
	color &=(~BRIGHT);
	locate(ff+1,fc);
	color+=(attri & (~BRIGHT));
	printf("color=%i\n",color);//dbg
	if(color) return 0;
	ink(YELLOW|BRIGHT);
	locate(player.f,player.c);
	printc(GHUELLA);
	locate(player.f+1,player.c);
	printc(GHUELLA);
	ink(BLACK);
	player.f=ff;
	player.c=fc;
	player.imagen=(player.imagen==0)?1:0;
	return 0;
}

void player_act() {
	int move=0;
	if(inkey('i')) move=player_move(-1,0);
	else if(inkey('k')) move=player_move(1,0);
	if(inkey('j')) {
		player.direction=-1;
		player_move(0,-1);
	} else if(inkey('l')) {
		player.direction=1;
		player_move(0,1);
	}
}

void program() {
	background(BLACK);
	foreground(BLACK);
	gdu_init();
	player_init();
	scenario();
begin:
	player_draw();
	show;
	listen;
	player_act();
	if(inkey('q')==0) goto begin; 
}
	
