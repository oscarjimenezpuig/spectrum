/*
============================================================
  Fichero: spectrum.c
  Creado: 03-10-2025
  Ultima Modificacion: lun 13 oct 2025 14:02:21
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "spectrum.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

//XVIDEO

typedef XPoint X_Point;
typedef long unsigned int X_Color;

X_Color X_BLACK=0;
X_Color X_WHITE=0;

unsigned int X_WINW=0;
unsigned int X_WINH=0;
static Display* display=NULL;
static Colormap colormap;
static Window window;
static Pixmap virtual;
static GC graphic;
static X_Color background;
static int min_key_code=0;
static int max_key_code=0;

X_Color x_color(double red,double green,double blue);
void x_flush();

int x_init(unsigned int w,unsigned int h) {
	X_WINW=w;
	X_WINH=h;
	int screenum=0;
	display=XOpenDisplay(0);
	if(display) {
		int screennum=XDefaultScreen(display);
		colormap=XDefaultColormap(display,screenum);
		X_BLACK=x_color(0,0,0);
		X_WHITE=x_color(1,1,1);
		window=XCreateSimpleWindow(display,RootWindow(display,screennum),0,0,X_WINW,X_WINH,0,0,0);
		XWindowAttributes xwa;
		XGetWindowAttributes(display,window,&xwa);
		virtual=XCreatePixmap(display,window,X_WINW,X_WINH,xwa.depth);
		static XGCValues gv;
		gv.line_width=1;
		gv.foreground=X_WHITE;
		gv.background=background=X_BLACK;
		graphic=XCreateGC(display,window,GCForeground|GCBackground|GCLineWidth,&gv);
		XSelectInput(display,window,StructureNotifyMask);
		XMapWindow(display,window);
		XEvent event;
		int mapped=0;
		while(XEventsQueued(display,QueuedAlready) || !mapped) {
			XNextEvent(display,&event);
			mapped=(!mapped)?(event.type==MapNotify):1;
		}
		XDisplayKeycodes(display,&min_key_code,&max_key_code);
		XSetForeground(display,graphic,gv.background);
		XFillRectangle(display,virtual,graphic,0,0,X_WINW,X_WINH);
		x_flush();
		return 1;
	}
	return 0;
}

void x_end() {
	XUnmapWindow(display,window);
	XDestroyWindow(display,window);
	XFreePixmap(display,virtual);
	XFreeColormap(display,colormap);
	XFreeGC(display,graphic);
	XEvent e;
	while(XEventsQueued(display,QueuedAlready)) {
			XNextEvent(display,&e);
	}
	XCloseDisplay(display);
}

X_Color x_color(double r,double g,double b) {
	const double FAC=65535;
	XColor xc;
	xc.flags=DoRed|DoGreen|DoBlue;
	xc.red=FAC*r;
	xc.green=FAC*g;
	xc.blue=FAC*b;
	XAllocColor(display,colormap,&xc);
	return xc.pixel;
}

void x_square(X_Point b,unsigned int d,X_Color c) {
	XSetForeground(display,graphic,c);
	XFillRectangle(display,virtual,graphic,b.x,b.y,d,d);
}

void x_flush() {
	XCopyArea(display,virtual,window,graphic,0,0,X_WINW,X_WINH,0,0);
	while(XPending(display)==0);
	XFlush(display);
}

int x_inkey(KeySym* keysym) {
	const int KCC=1;
	const unsigned char POS=0;
	int return_type=0;
	XEvent event;
	long event_mask=KeyPressMask|KeyReleaseMask;
	XSelectInput(display,window,event_mask);
	if(XPending(display)>0 && XCheckMaskEvent(display,event_mask,&event)) {
		int counter=0;
		XKeyEvent kevent=event.xkey;
		if(kevent.keycode>=min_key_code && kevent.keycode+KCC-1<=max_key_code) {
			KeySym* ks=XGetKeyboardMapping(display,kevent.keycode,KCC,&counter);
			if(POS<KCC*counter) {
				return_type=(kevent.type==KeyPress)?1:(kevent.type==KeyRelease)?-1:0;
				*keysym=*(ks+POS);
			}
			XFree(ks);
		}
	}
	return return_type;
}



//MEMORY

#define PIXDIM 3
#define BLCDIM (PIXDIM*8)

#define FADD 8 //dimension de las direcciones del programa

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

void output() {
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

void input() {
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
	program();
	x_end();
}

//SPECTRUM

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

void s_unkey(char k) {
	byte* p=memory+OKEY;
	while(p!=memory+OKEY+DKEY) {
		if(*p==k) *p=0;
		p++;
	}
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


