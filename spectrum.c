/*
============================================================
  Fichero: spectrum.c
  Creado: 03-10-2025
  Ultima Modificacion: dilluns, 6 d’octubre de 2025, 20:09:31
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "spectrum.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void s_attrsetall(byte place,byte a) {
	const byte BGT=RBKG|GBKG|BBKG|UBKG;
	const byte FGT=RINK|GINK|BINK|UINK;
	byte* dmc=memory+CLF;
	byte todel=(place==PINK)?FGT:BGT;
	byte nval=(place==PINK)?a:a<<4;
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

void s_attrset(byte place,byte a) {
	const byte BGT=RBKG|GBKG|BBKG|UBKG;
	const byte FGT=RINK|GINK|BINK|UINK;
	byte* p=memory+CLC;
	byte todel=(place==PINK)?FGT:BGT;
	byte nval=(place==PINK)?a:a<<4;
	*p &= ~todel;
	*p |= nval;
}

byte s_attrget(byte place) {
	const byte BGT=RBKG|GBKG|BBKG|UBKG;
	const byte FGT=RINK|GINK|BINK|UINK;
	byte a=0;
	byte* p=memory+ATF;
	byte f=*p++;
	byte c=*p;
	byte* pc=memory+OCOL+c+f*SCRBW;
	if(place==PINK) a=*pc & FGT;
	else a=(*pc & BGT)>>4;
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

void s_mode(byte m) {
	if(m<=(FLIPX|FLIPY|INVERSE)) memory[MOI]=m;
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

static void prt_swap(byte* a,byte* b) {
	byte c=*b;
	*b=*a;
	*a=c;
}

static void prt_c_flipx(byte* pmp) {
	byte* pp=pmp;
	byte* ppc=pmp+7*SCRBW;
	for(byte n=1;n<=4;n++) {
		prt_swap(pp,ppc);
		pp+=SCRBW;
		ppc-=SCRBW;
	}
}

static void l_flipy(byte* l) {
	for(unsigned short i=1;i<=8;i=i<<1) {
		byte ci=128/i;
		byte a=(i & *l);
		byte b=(ci & *l);
		*l&=~(a|b);
		byte ta=(a)?1:0;
		byte tb=(b)?1:0;
		*l|=(ta*ci)|tb*i;
	}
}

static void prt_c_flipy(byte* pmp) {
	byte* pp=pmp;
	for(byte n=0;n<8;n++) {
		l_flipy(pp);
		pp+=SCRBW;
	}
}

static void prt_c_inverse(byte* pmp) {
	byte* pp=pmp;
	for(byte n=0;n<8;n++) {
		*pp=~(*pp);
		pp+=SCRBW;
	}
}

void s_print_c(byte c) {
	prt_c_col();
	byte* pc=pos_mem_chr(c);
	byte* pm=pos_mem_cur_pix();
	prt_c_norm(pc,pm);
	byte mm=memory[MOI];
	if(mm & FLIPX) prt_c_flipx(pm);
	if(mm & FLIPY) prt_c_flipy(pm);
	if(mm & INVERSE) prt_c_inverse(pm);
}

#undef pos_mem_chr

void s_print_n(double n) {
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
	s_print_s(sn);
}

void s_print_s(char* s) {
	char* p=s;
	while(*p!='\0') s_print_c(*p++);
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
