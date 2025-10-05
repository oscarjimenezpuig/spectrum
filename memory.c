/*
============================================================
  Fichero: memory.c
   mreado: 01-10-2025
  Ultima Modificacion: dissabte, 4 d’octubre de 2025, 20:20:05
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "xvideo.h"
#include "memory.h"

#define PIXDIM 4
#define BLCDIM (PIXDIM*8)

byte memory[MEMORY];

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

#undef DATA

static void mem_init() {
	//establecemos toda la memoria a 0
	byte* p=memory;
	while(p!=memory+MEMORY) *p++=0;
	//definicion de gdu, donde se colocaran las letras
	asc_init();
}

static void col_init_one(byte code) {
	double factor=(code>=8)?1:.5;
	byte col=code%8;
	double red,green,blue;
	red=green=blue=0;
	if(col & 1) red=factor;
	if(col & 2) green=factor;
	if(col & 4) blue=factor;
	unsigned long cocol=x_color(red,green,blue);
	byte *ptr,*ini;
	ptr=ini=memory+ODCL+(col+(code>=8)*8)*4;
	while(ptr!=ini+4 && cocol>0) {
		*ptr++=cocol%256;
		cocol=cocol/256;
	}
}

static void col_init() {
	for(byte n=0;n<COLORS;n++) col_init_one(n);
}

static void scr_init() {
	x_init(SCRPW*PIXDIM,SCRPH*PIXDIM);
	col_init();
}

static unsigned long col_get(byte b) {
	byte brg=(b & 8)?1:0;
	byte col=b &(~8);
	unsigned long color=0;
	unsigned long factor=1;
	byte *ptr,*ini;
	ptr=ini=memory+ODCL+(col+8*brg)*4;
	while(ptr!=ini+4) {
		color+=factor*(*ptr);
		ptr++;
		factor*=256;
	}
	return color;
}

static void line_draw(X_Point p,byte val) {
	int c=p.x/(8*PIXDIM);
	int f=p.y/(8*PIXDIM);
	byte ink=(memory[OCOL+c+f*SCRBW]) & (RINK|GINK|BINK|UINK);
	X_Color col=col_get(ink);
	for(byte k=128;k>=1;k=k>>1) {
		if(val & k) x_square(p,PIXDIM,col);
		p.x+=PIXDIM;
	}
}

static void pix_draw() {
	byte *ptr,*ini;
	ptr=ini=memory+OPIX;
	X_Point pos={0,0};
	while(ptr!=ini+DPIX) {
		if(*ptr) line_draw(pos,*ptr);
		ptr++;
		pos.x+=PIXDIM*8;
		if(pos.x>=SCRPW*PIXDIM) {
			pos.x=0;
			pos.y+=PIXDIM;
		}
	}
}

static void bkg_draw() {
	X_Point pos={0,0};
	byte *ptr,*ini;
	ptr=ini=memory+OCOL;
	while(ptr!=ini+DCOL) {
		byte bkg=(*ptr & (RBKG|GBKG|BBKG|UBKG))/16;
		unsigned long col=col_get(bkg);
		x_square(pos,BLCDIM,col);
		ptr++;
		pos.x+=BLCDIM;
		if(pos.x>=SCRPW*PIXDIM) {
			pos.x=0;
			pos.y+=BLCDIM;
		}
	}
}

static void show() {
	bkg_draw();
	pix_draw();
	x_flush();
}

static void ks_ins(byte val) {
	byte* ptr=memory+OKEY;
	while(ptr<memory+OKEY+DKEY && *ptr!=0) ptr++;
	if(ptr!=memory+OKEY+DKEY) *ptr=val;
}

static void ks_era(byte val) {
	byte* ptr=memory+OKEY;
	while(ptr!=memory+OKEY+DKEY) {
		if(*ptr==val) *ptr=0;
		ptr++;
	}
}

static void inkey() {
	KeySym k;
	int stat=0;
	if((stat=x_inkey(&k))) {
		if(stat==1) ks_ins((byte)k);
		else ks_era(k);
	}
}

int main() {
	mem_init();
	scr_init();
	while((memory[OFLG] & END_SIGN)==0) {
		show();
		inkey();
		program();
	};
	x_end();
}


