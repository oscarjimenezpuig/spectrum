/*
============================================================
  Fichero: memory.c
   mreado: 01-10-2025
  Ultima Modificacion: jue 02 oct 2025 12:23:16
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include <stdio.h>

#include "xvideo.h"
#include "memory.h"

#define COLORS 16
#define PIXDIM 4
#define BLCDIM (PIXDIM*8)

byte memory[MEMORY];

X_Color color[COLORS];

static void asc_new(char c,byte* data) {
	direction dir=OMEM+c*8;
	byte* ptm=memory+dir;
	byte* ptd=data;
	while(ptm!=memory+dir+8) {
		*ptm++=*ptd++;
	}
}	

#define DATA(A,B,C,D,E,F,G,H) (byte[]){A,B,C,D,E,F,G,H}

static void asc_init() {
	asc_new('0',DATA(0,60,70,74,82,98,60,0));
	asc_new('1',DATA(0,48,80,16,16,16,124,0));
	asc_new('2',DATA(0,60,66,2,60,64,126,0));
	asc_new('3',DATA(0,60,66,12,2,66,60,0));
	asc_new('4',DATA(0,4,12,20,36,62,4,0));
	asc_new('5',DATA(0,126,64,124,2,66,60,0));
	asc_new('6',DATA(0,60,64,124,66,66,60,0));
	asc_new('7',DATA(0,126,2,4,8,16,16,0));
	asc_new('8',DATA(0,60,66,60,66,66,60,0));
	asc_new('9',DATA(0,60,66,66,62,2,60,0));
	asc_new('A',DATA(0,60,66,66,126,66,66,0));
	asc_new('B',DATA(0,124,66,124,66,66,124,0));
	asc_new('C',DATA(0,60,66,64,64,66,60,0));	
	asc_new('D',DATA(0,120,68,66,66,68,120,0));
	asc_new('E',DATA(0,126,64,120,64,64,126,0));
	asc_new('F',DATA(0,126,64,120,64,64,64,0));
	asc_new('G',DATA(0,60,66,64,78,66,60,0));
	asc_new('H',DATA(0,66,66,126,66,66,66,0));
	asc_new('I',DATA(0,124,16,16,16,16,124,0));
	asc_new('J',DATA(0,2,2,2,66,66,60,0));
	asc_new('K',DATA(0,68,72,112,72,68,66,0));
	asc_new('L',DATA(0,64,64,64,64,64,126,0));
	asc_new('M',DATA(0,66,102,90,66,66,66,0));
	asc_new('N',DATA(0,66,98,82,74,70,66,0));
	asc_new('O',DATA(0,60,66,66,66,66,60,0));
	asc_new('P',DATA(0,124,66,66,124,64,64,0));
	asc_new('Q',DATA(0,60,66,66,82,74,60,0));
	asc_new('R',DATA(0,124,66,66,124,68,66,0));
	asc_new('S',DATA(0,60,64,60,2,66,60,0));
	asc_new('T',DATA(0,124,16,16,16,16,16,0));
	asc_new('U',DATA(0,66,66,66,66,66,60,0));
	asc_new('V',DATA(0,66,66,66,66,36,24,0));
	asc_new('W',DATA(0,66,66,66,66,90,36,0));
	asc_new('X',DATA(0,66,36,24,24,36,66,0));
	asc_new('Y',DATA(0,68,40,16,16,16,16,0));
	asc_new('Z',DATA(0,126,4,8,16,32,126,0));
	asc_new('a',DATA(0,0,56,4,60,68,60,0));
	asc_new('b',DATA(0,64,64,120,68,68,120,0));
	asc_new('c',DATA(0,0,28,32,32,32,28,0));
	asc_new('d',DATA(0,4,4,60,68,68,60,0));
	asc_new('e',DATA(0,0,56,68,120,64,60,0));
	asc_new('f',DATA(0,24,32,48,32,32,32,0));
	asc_new('g',DATA(0,0,60,68,68,60,4,56));
	asc_new('h',DATA(0,64,64,120,68,68,68,0));
	asc_new('i',DATA(0,16,0,48,16,16,56,0));
	asc_new('j',DATA(0,4,0,4,4,4,36,24));
	asc_new('k',DATA(0,32,40,48,48,40,36,0));
	asc_new('l',DATA(0,32,32,32,32,32,24,0));
	asc_new('m',DATA(0,0,104,84,84,84,84,0));
	asc_new('n',DATA(0,0,120,68,68,68,68,0));
	asc_new('o',DATA(0,0,56,68,68,68,56,0));
	asc_new('p',DATA(0,0,120,68,68,120,64,64));
	asc_new('q',DATA(0,0,60,68,68,60,4,6));
	asc_new('r',DATA(0,0,60,64,64,64,64,0));
	asc_new('s',DATA(0,0,56,64,56,4,120,0));
	asc_new('t',DATA(0,16,56,16,16,16,12,0));
	asc_new('u',DATA(0,0,68,68,68,68,56,0));
	asc_new('v',DATA(0,0,68,68,40,40,16,0));
	asc_new('w',DATA(0,0,68,84,84,84,40,0));
	asc_new('x',DATA(0,0,68,40,16,40,68,0));
	asc_new('y',DATA(0,0,68,68,68,60,4,56));
	asc_new('z',DATA(0,0,124,8,16,32,124,0));
	asc_new('!',DATA(0,16,16,16,16,0,16,0));
	asc_new('"',DATA(0,36,36,0,0,0,0,0));
	asc_new('#',DATA(0,36,126,36,36,126,36,0));
	asc_new('$',DATA(0,16,124,80,124,20,124,16));
	asc_new('%',DATA(0,98,100,8,16,38,70,0));
	asc_new('&',DATA(0,16,40,16,42,68,58,0));
	asc_new('/',DATA(0,2,4,8,16,32,64,0));
	asc_new('(',DATA(0,8,16,16,16,16,8,0));
	asc_new(')',DATA(0,16,8,8,8,8,16,0));
	asc_new('[',DATA(0,24,16,16,16,16,24,0));
	asc_new(']',DATA(0,24,8,8,8,8,24,0));
	asc_new('\'',DATA(0,8,16,0,0,0,0,0));
	asc_new('*',DATA(0,0,40,16,124,16,40,0));
	asc_new('+',DATA(0,0,16,16,124,16,16,0));
	asc_new(',',DATA(0,0,0,0,0,16,16,32));
	asc_new('-',DATA(0,0,0,0,124,0,0,0));
	asc_new('.',DATA(0,0,0,0,0,24,24,0));
	asc_new(':',DATA(0,0,0,16,0,0,16,0));
	asc_new(';',DATA(0,0,8,0,0,8,8,16));
	asc_new('<',DATA(0,0,8,16,32,16,8,0));
	asc_new('>',DATA(0,0,32,16,8,16,32,0));
	asc_new('?',DATA(0,60,66,4,8,0,8,0));
	asc_new('@',DATA(0,60,74,86,94,64,60,0));
	asc_new('=',DATA(0,0,0,60,0,60,0,0));
	asc_new('\\',DATA(0,64,32,16,8,4,2,0));
	asc_new('^',DATA(0,16,40,68,0,0,0,0));
	asc_new('_',DATA(0,0,0,0,0,0,0,255));
	asc_new('{',DATA(0,28,16,96,16,16,28,0));
	asc_new('}',DATA(0,112,16,12,16,16,112,0));
	asc_new('|',DATA(0,16,16,16,16,16,16,0));
	asc_new('~',DATA(0,20,40,0,0,0,0,0));
}

static void mem_init() {
	//establecemos todos los pixeles en blanco
	byte* p=memory+OPIX;
	while(p!=memory+OPIX+DPIX) *p++=0;
	//establecemos el color fondo blanco y paper negro en el color
	p=memory+OCOL;
	while(p!=memory+OCOL+DCOL) *p++=RBKG|GBKG|BBKG;
	//definicion de gdu, donde se colocaran las letras
	asc_init();
}

static void scr_init() {
	x_init(SCRPW*PIXDIM,SCRPH*PIXDIM);
	for(int r=1;r<=2;r=r+1) {
		double factor=0.5*(double)r;
		for(int k=0;k<8;k++) {
			double red=0;
			double green=0;
			double blue=0;
			if(k & 1) red=factor;
			if(k & 2) green=factor;
			if(k & 4) blue=factor;
			color[k+8*(r-1)]=x_color(red,green,blue);
		}
	}
}

static void scr_end() {
	atexit(x_end);
}

static X_Color col_get(byte b) {
	byte bright=(b & 8)?1:0;
	byte pos=b &(~8);
	return color[pos+8*bright];
}

static void line_draw(byte val,X_Point p,X_Color col) {
	for(byte k=128;k>=1;k=k>>1) {
		if(val & k) x_square(p,PIXDIM,col);
		p.x+=PIXDIM;
	}
}

static void blk_show(int f,int c) {
	X_Point p={c*8*PIXDIM,f*8*PIXDIM};
	byte cb=memget(OCOL+c+f*SCRBW);
	//dibujo del fondo
	X_Color cbkg=col_get((cb & (RBKG|GBKG|BBKG|UBKG))/RBKG);
	x_square(p,BLCDIM,cbkg);
	//dibujo del pixeles
	X_Color cink=col_get(cb & (RINK|GINK|BINK|UINK));
	byte *ptr,*ini;
	ptr=ini=memory+(OPIX+(c+f*SCRBW)*8);
	while(ptr!=ini+8) {
		if(*ptr) line_draw(*ptr,p,cink);
		ptr++;
		p.y+=PIXDIM;
	}
}	

void show() {
	static byte init=0;
	if(!init) {
		mem_init();
		scr_init();
		scr_end();
		init=1;
	}
	for(int f=0;f<SCRBH;f++) {
		for(int c=0;c<SCRBW;c++) {
			blk_show(f,c);
		}
	}
	x_flush();
}

static void ks_ins(KeySym val) {
	byte* ptr=memory+OKEY;
	while(ptr<memory+OKEY+DKEY && (*ptr!=0 || *(ptr+1)!=0)) ptr=ptr+2;
	if(ptr!=memory+OKEY+DKEY) {
		*ptr=val/256;
		*(ptr+1)=val%256;
	}
}

static void ks_era(KeySym val) {
	byte p=val/256;
	byte s=val%256;
	byte* ptr=memory+OKEY;
	while(ptr!=memory+OKEY+DKEY) {
		if(*ptr==p && *(ptr+1)==s) {
			*ptr=*(ptr+1)=0;
		}
		ptr=ptr+2;
	}
}

void inkey() {
	KeySym k;
	int stat=0;
	if((stat=x_inkey(&k))) {
		if(stat==1) ks_ins(k);
		else ks_era(k);
	}
}

//prueba

#include <stdio.h>

void mem_prt() {
	byte* ptr=memory;
	while(ptr!=memory+MEMORY) printf("%03i   ",*ptr++);
}

int main() {
	show();
	memset(0,28);
	memset(1,50);
	memset(2,113);
	memset(3,240);
	memset(4,112);
	memset(5,112);
	memset(6,16);
	memset(7,15);
	memset(OCOL,RINK|GINK|BINK|UINK|RBKG|UBKG);
	for(int i=0;i<8;i++) {
		memmov('A'*8+OMEM+i,16+i);
	}
	show();
	while(memget(OKEY)==0 && memget(OKEY+1)==0) {
		inkey();
	}
	return 0;
}
			

	

