/*
============================================================
  Fichero: gdu.c
  Creado: 11-10-2025
  Ultima Modificacion: lun 13 oct 2025 13:38:43
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "spectrum.h"

#define MAXC 3
#define MAXF 2

#define MALLA 128
#define CURSOR 129
#define MOSTRA 130

typedef unsigned char u1;
typedef signed char s1;

typedef struct {
	u1 f;
	u1 c;
} Cursor;

void gdu_init();
	
void gdu_new();

void gdu_act();

void gdu_calc(u1 f,u1 c,u1* res);

void gdu_act();

void gdu_draw();

void gdu_master();

u1 gdu[MAXF*8][MAXC*8];

Cursor cursor={0,0};

u1 quit=0;

u1 filas,columnas;

static void intro() {
	char* skey[]={"I: up","J: left","L: right","K: down","A: mark","S: unmark","N: new","Q: quit"};
	byte skeys=8;
	byte start=0;
	while(!start) {
		ink(WHITE|BRIGHT);
		paper(BLACK);
		locate(1,11);
		prints("GDU MAKER");
		locate(3,0);
		ink(BLACK);
		paper(WHITE);
		prints("(c) Oscar Jimenez Puig 2025");
		locate(6,0);
		prints("Design GDU from 1x1 to 2x3.");
		ink(WHITE|BRIGHT);
		for(byte n=0;n<skeys;n++) {
			locate(n+9,0);
			prints(skey[n]);
		}
		ink(BLACK);
		locate(23,0);
		prints("Press N to start");
		show;
		pause(0.25);
		listen;
		if(inkey('n')) start=1;
	}
	cls;
}


void gdu_init() {
	gdu(MALLA,255,129,129,129,129,129,129,255);
	gdu(CURSOR,0,0,60,60,60,60,0,0);
	background(WHITE);
	foreground(BLACK);
	intro();
	gdu_new();
}

static u1 inkey_number(u1 limit) {
	u1 answer=0;
	for(u1 k=1;k<=limit;k++) {
		if(inkey('0'+k)) {
			answer=k;
			unkey('0'+k);
			break;
		}
	}
	return answer;
}

void gdu_new() {
repeat:
	cls;
	filas=columnas=0;
	locate(23,0);
	prints("Rows (1-2)? ");
	show;
	while(!filas) {
		listen;
		filas=inkey_number(2);
	}
	cls;
	locate(23,0);
	prints("Columns (1-3)? ");
	show;
	while(!columnas) {
		listen;
		columnas=inkey_number(3);
	}
	cls;
	locate(22,0);
	prints("You try: ");printn(filas);prints(" rows and ");printn(columnas);prints(" columns");
	locate(23,0);
	prints("Is correct (Y/N)?");
	show;
	int answer=0;
	while(!answer) {
		listen;
		if(inkey('y')) answer=1;
		else if(inkey('n')) answer=-1;
	}
	if(answer==-1) goto repeat;
	gdu(MOSTRA,0,0,0,0,0,0,0,0);
	for(byte f=0;f<filas*8;f++) {
		for(byte c=0;c<columnas*8;c++) {
			gdu[f][c]=0;
		}
	}
	cursor=(Cursor){0,0};
	cls;
}

void gdu_act() {
	const u1 DELAY=7;
	static u1 counter=0;
	listen;
	if(counter==DELAY) {
		if(inkey('k') && cursor.f<8*filas-1) cursor.f++;
		else if(inkey('i') && cursor.f>0) cursor.f--;
		if(inkey('l') && cursor.c<8*columnas-1) cursor.c++;
		else if(inkey('j') && cursor.c>0) cursor.c--;
		if(inkey('s')) gdu[cursor.f][cursor.c]=0;
		else if(inkey('a')) gdu[cursor.f][cursor.c]=1;
		if(inkey('q')) quit=1;
		else if(inkey('n')) gdu_new();
		counter=0;
	} else counter++;
}

void gdu_calc(u1 f,u1 c,u1* res) {
	int fi=f*8;
	int ci=c*8;
	for(u1 f=0;f<8;f++) {
		u1 fact=128;
		for(u1 c=0;c<8;c++) {
			int fa=f+fi;
			int ca=c+ci;
			if(gdu[fa][ca]) res[f]+=fact;
			fact=fact>>1;
		}
	}
}

void gdu_draw() {
	//mallas
	for(int f=0;f<filas*8;f++) {
		for(int c=0;c<columnas*8;c++) {
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
	//disposicion
	locate(17,0);
	ink(RED);
	paper(WHITE);
	for(int f=0;f<filas;f++) {
		for(int c=0;c<columnas;c++) {
			mode(INVERSE);
			printn(f);
			printc(',');
			printn(c);
			mode(NORMAL);
			printc(' ');
		}
	}
	ink(BLACK);		
	//muestra y valores
	const int VALLIN=18;
	for(int f=0;f<filas;f++) {
		for(int pc=0;pc<32;pc++) {
			locate(f+VALLIN,pc);
			printc(' ');
		}
	}
	ink(BLACK);
	int line=VALLIN;
	for(int f=0;f<filas;f++) {
		for(int c=0;c<columnas;c++) {
			u1 data[]={0,0,0,0,0,0,0,0};
			gdu_calc(f,c,data);
			locate(f+8,c+26);
			gdu(MOSTRA,data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);
			paper(WHITE|BRIGHT);
			printc(MOSTRA);
			paper(WHITE);
			locate(line++,0);
			for(u1 v=0;v<8;v++) {
				printn(data[v]);
				if(v!=7) printc(',');
			}
		}
	}
	show;
}

void program() {
	gdu_init();
	while(!quit) {
		pause(0.01);
		gdu_act();
		gdu_draw();
	}
}

	


	








