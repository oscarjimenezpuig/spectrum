/*
============================================================
  Fichero: spectrum.c
  Creado: 03-10-2025
  Ultima Modificacion: diumenge, 5 d’octubre de 2025, 19:35:16
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "spectrum.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void s_attrsetall(byte place,attribute a) {
	const byte BGT=RBKG|GBKG|BBKG|UBKG;
	const byte FGT=RINK|GINK|BINK|UINK;
	byte* dmc=memory+CLF;
	byte todel=(place==INK)?FGT:BGT;
	byte nval=(place==INK)?a.color|a.bright:(a.color|a.bright)<<4;
	for(byte n=0;n<2;n++) {
		*dmc &= ~todel;
		*dmc|=nval;
		dmc++;
	}
	byte *ptr,*init; 
	ptr=init=memory+OCOL;
	while(ptr!=init+DCOL) {
		*ptr &= ~todel;
		*ptr |= nval;
		ptr++;
	}
}

void s_attrset(byte place,attribute a) {
	const byte BGT=RBKG|GBKG|BBKG|UBKG;
	const byte FGT=RINK|GINK|BINK|UINK;
	byte* p=memory+CLC;
	byte todel=(place==INK)?FGT:BGT;
	byte nval=(place==INK)?(a.color|a.bright):(a.color|a.bright)<<4;
	*p &= ~todel;
	*p |= nval;
}

attribute s_attrget(byte place) {
	attribute a;
	byte* p=memory+ATF;
	byte f=*p++;
	byte c=*p;
	byte* pc=memory+OCOL+c+f*SCRBW;
	if(place==INK) {
		a.color=*pc & (RINK|GINK|BINK);
		a.bright=*pc & UINK;
	} else {
		a.color=(*pc & (RBKG|GBKG|BBKG))>>4;
		a.bright=(*pc & UBKG)>>4;
	}
	return a;
}		 	

void s_at(byte f,byte c) {
	byte* p=memory+ATF;
	*(p++)=(f%SCRBH);
	*p=(c%SCRBW);
}


void s_clear() {
	byte* p=memory+OPIX;
	while(p!=memory+OPIX+DPIX) *p++=0;
	p=memory+OCOL;
	byte cfb=memory[CLF];
	while(p!=memory+OCOL+DCOL) *p++=cfb;
	p=memory+ATF;
	*p++=0;
	*p=0;
}

#define pos_mem_chr(C) (memory+OMEM+(C)*8) //devuelve un puntero donde esta el caracter

static byte* pos_mem_cur_pix() {
	//devuelve la posicion de memoria donde se encuentra el cursor en pixeles
	//y incrementa la posicion de las columnas en 1
	byte* p=memory+ATF;
	byte f=*p++;
	byte c=*p;
	byte* dir=memory+OPIX+(f*8*SCRBW)+c;
	*p=(c+1)%SCRBW;
	if(*p==0){
		--p;
		*p=(f+1)%SCRBH;
	}
	return dir;
}

static void prt_c_col() {
	//mira si el color guardado en la posicion de cursor se corresponde al color que
	//hay actualmente, si no, lo cambia
	byte* p=memory+ATF;
	byte f=*p++;
	byte c=*p;
	p=(p-ATC+CLC);
	byte* cc=memory+OCOL+f*SCRBW+c;
	if(*cc!=*p) *cc=*p;
}

static void prt_c_norm(byte* pmc,byte* pmp) {
	byte* pc=pmc;
	byte* pp=pmp;
	while(pc!=pmc+8) {
		*pp=*pc;
		pc++;
		pp+=SCRBW;
	}
}

static void prt_c_flipx(byte* pmc,byte* pmp) {
	pmp=pmp+7*SCRBW;
	byte* pc=pmc;
	byte* pp=pmp;
	while(pc!=pmc+8) {
		*pp=*pc;
		pc++;
		pp-=SCRBW;
	}
}

static byte l_flipy(byte val) {
	byte r=0;
	for(unsigned short i=1;i<=128;i=i<<1) {
		r|=(i & val)?(128/i):0;
	}
	return r;
}

static void prt_c_flipy(byte* pmc,byte* pmp) {
	 byte* pc=pmc;
	byte* pp=pmp;
	while(pc!=pmc+8) {
		*pp=l_flipy(*pc);
		pc++;
		pp+=SCRBW;
	}
}

static void prt_c_inverse(byte* pmc,byte* pmp) {
	byte* pc=pmc;
	byte* pp=pmp;
	while(pc!=pmc+8) {
		*pp=~(*pc);
		pc++;
		pp+=SCRBW;
	}
}

void s_print_c(byte c,byte m) {
	prt_c_col();
	byte* pc=pos_mem_chr(c);
	byte* pm=pos_mem_cur_pix();
	switch(m) {
		case FLIPX:
			prt_c_flipx(pc,pm);
			break;
		case FLIPY:
			prt_c_flipy(pc,pm);
			break;
		case INVERSE:
			prt_c_inverse(pc,pm);
			break;
		default:
			prt_c_norm(pc,pm);
			break;

	}
}

void s_print_n(double n,byte m) {
	char sn[24];
	sprintf(sn,"%lf",n);
	char* p=sn;
	byte coma=0;
	while(*p!='\0') {
		if(*p=='.') coma=1;
		p++;
	}
	p=(p!=sn)?p-1:p;
	while(coma && (*p=='0' || *p=='.')) {
		if(*p=='.') coma=0;
		*p='\0';
		p--;
	}
	s_print_s(sn,m);
}

void s_print_s(char* s,byte m) {
	char* p=s;
	while(*p!='\0') s_print_c(*p++,m);
}

byte s_inkey(char k) {
	byte* p=memory+OKEY;
	while(p!=memory+OKEY+DKEY) {
		if(*p==k) return 1;
		p++;
	}
	return 0;
}

void s_gdu(byte n,byte a,byte b,byte c,byte d,byte e,byte f,byte g,byte h) {
	byte data[]={a,b,c,d,e,f,g,h};
	byte *ptr,*ini,*pda;
	ptr=ini=memory+(OMEM+n*8);
	pda=data;
	while(ptr!=ini+8) *ptr++=*pda++;
}

void s_randomize(int v) {
	unsigned int seed=(v>0)?v:time(NULL);
	srand(seed);
}	

int s_rnd(int a,int b) {
	int max=(a>b)?a:b;
	int min=(a>b)?b:a;
	int dif=max-min+1;
	return min+(rand()%dif);
}

void s_pause(double s) {
	clock_t lim=clock()+s*CLOCKS_PER_SEC;
	while(clock()<lim);
}

//prueba
/*
#include "xvideo.h"

void mem_prt() {
	puts("Pixeles");
	for(int n=OPIX;n<OPIX+DPIX;n++) {
		printf("%03i ",memory[n]);
	}
	puts("Gdu");
	for(int n=OMEM+128*8;n<OMEM+DMEM;n++) {
		printf("%03i ",memory[n]);
	}
	puts("");
}

void program() {
	static byte finish=0;
	s_gdu(128,192,192,192,192,255,255,66,66);
	s_attrsetall(PAPER,Attr(WHITE,NORMAL));
	s_attrsetall(INK,Attr(BLACK,NORMAL));
	s_at(3,1);
	s_attrset(INK,Attr(RED,BRIGHT));
	s_print_c(128,NORMAL);
	if(s_inkey('s')) {
		s_at(3,1);
		s_print_c('A',INVERSE);
		finish=1;
	} else if(finish==1) {
		pause(10);
		stop;
	}
}
*/
