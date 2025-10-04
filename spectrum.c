/*
============================================================
  Fichero: spectrum.c
  Creado: 03-10-2025
  Ultima Modificacion: dissabte, 4 d’octubre de 2025, 11:07:41
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "spectrum.h"

#include <stdio.h>

void s_background(byte c,byte b) {
	const byte BGT=RBKG|GBKG|BBKG|UBKG;
	byte nval=(c|b)<<4;
	byte* dmc=memory+CLF;
	for(byte n=0;n<2;n++) {
		*dmc &= ~BGT;
		*dmc|=nval;
		dmc++;
	}
	byte *ptr,*init; 
	ptr=init=memory+OCOL;
	while(ptr!=init+DCOL) {
		*ptr &= ~BGT;	
		*ptr|=nval;
		ptr++;
	}
}

void s_foreground(byte c,byte b) {
	const byte FGT=RINK|GINK|BINK|UINK;
	byte nval=c|b;
	byte* dmc=memory+CLF;
	for(byte n=0;n<2;n++) {
		*dmc &= ~FGT;
		*dmc|=nval;
		dmc++;
	}
	byte *ptr,*init; 
	ptr=init=memory+OCOL;
	while(ptr!=init+DCOL) {
		*ptr &= ~FGT;
		*ptr |= nval;
		ptr++;
	}
}

void s_at(byte f,byte c) {
	byte* p=memory+ATF;
	*(p++)=(f%SCRBH);
	*p=(c%SCRBW);
}

void s_paper(byte c,byte b) {
	const byte BGT=RBKG|GBKG|BBKG|UBKG;
	byte* p=memory+CLC;
	*p &= ~BGT;
	*p |= (c|b)<<4;
}

void s_ink(byte c,byte b) {
	const byte FGT=RINK|GINK|BINK|UINK;
	byte* p=memory+CLC;
	*p &= ~FGT;
	*p |= (c|b);
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
	*p--=(c+1)%SCRBW;
	if(!c) *p=(f+1)%SCRBH;
	return dir;
}

static void pos_col() {
	//mira si el color guardado en la posicion de cursor se corresponde al color que
	//hay actualmente, si no, lo cambia
	byte* p=memory+ATF;
	byte f=*p++;
	byte c=*p;
	p=(p-ATC+CLC);
	byte* cc=memory+OCOL+f*SCRBW+c;
	if(*cc!=*p) *cc=*p;
}

void s_print_c(char c) {
	pos_col();
	byte* pc=pos_mem_chr(c);
	byte* inic=pc;
	byte* pm=pos_mem_cur_pix();
	while(pc!=inic+8) {
		*pm=*pc;
		pc++;
		pm+=SCRBW;
	}
}

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

void s_gdu(char n,byte a,byte b,byte c,byte d,byte e,byte f,byte g,byte h) {
	byte data[]={a,b,c,d,e,f,g,h};
	byte *ptr,*ini,*pda;
	ptr=ini=memory+OMEM+n*8;
	pda=data;
	while(ptr!=ini+8) *ptr++=*pda++;
}


//prueba

#include "xvideo.h"

void program() {
	s_gdu(128,192,192,192,192,255,255,66,66);
	s_background(BLACK,NORMAL);
	s_foreground(WHITE,BRIGHT);
	s_at(1,1);
	s_ink(YELLOW,BRIGHT);
	s_print_c('E');
	if(s_inkey('a')) s_clear();
	if(s_inkey('s')) stop;
}

