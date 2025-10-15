/*
============================================================
  Fichero: ohmummy.c
  Creado: 13-10-2025
  Ultima Modificacion: mié 15 oct 2025 12:32:27
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "spectrum.h"

#define GPLAYER 128
#define GMUMMY 129
#define GSTONE 130
#define GHUELLA 131
#define GLLAVE 132
#define GPAPIRO 133
#define GTUMBA 134

#define MFI 23
#define MCO 31

typedef unsigned char u1;
typedef signed char s1;

#define VACIO 0
#define HUELLA 1
#define PARED 2
#define LLAVE 4
#define PAPIRO 8
#define TUMBA 16
#define AGUA 32
#define MOMIA 64

#define MUMMIES 20

typedef struct {
	u1 gdu;
	u1 color;
	int f,c;
	int delay;
	int counter_delay;
	int df,dc;
	u1 vivo;
	
} Psi;

typedef struct {
	u1 numero;
	u1 papiro;
	u1 tumba;
	u1 llave;
	u1 momias;
} Nivel;

u1 malla[MFI][MCO];
Psi player;
Psi mummie[MUMMIES];
u1 mummies=0;
Nivel nivel={0,0,0,0,0};


void gdu_init() {
	gdu(GPLAYER,60,66,165,129,255,24,36,102);
	gdu(GMUMMY,153,153,255,36,36,24,36,102);
	gdu(GSTONE,0,126,86,106,86,106,126,0);
	gdu(GHUELLA,0,0,0,24,24,0,0,0);
	gdu(GLLAVE,56,8,56,8,28,34,34,28);
	gdu(GPAPIRO,255,129,90,129,153,66,153,255);
	gdu(GTUMBA,24,36,24,126,126,24,24,24);
}

static void momia_posicion_random(int* f,int* c) {
	do {
		*f=rnd(MFI/2,MFI-1);
		*c=rnd(MCO/2,MCO-1);
	} while (malla[*f][*c]!=VACIO);
}

static void malla_mapa_init() {
	for(u1 f=0;f<MFI;f++) {
		for(u1 c=0;c<MCO;c++) {
			if(f==0 || f==MFI-1 || c==0 || c==MCO-1) malla[f][c]=PARED;
			else if((f%4)==1 || (c%4)==1) malla[f][c]=VACIO;
			else malla[f][c]=PARED|AGUA;
		}
	}
	u1 flag[]={LLAVE,PAPIRO,TUMBA,MOMIA};
	int bef=(MFI-3)/4;
	int bec=(MCO-3)/4;
	for(int n=0;n<4;n++) {
		while(1) {
			int fe=rnd(0,bef-1);
			int ce=rnd(0,bec-1);
			int f=3+4*fe;
			int c=3+4*ce;
			if(malla[f][c]==(PARED|AGUA)) {
				malla[f][c]|=flag[n];
				break;
			}
		}
	}
}

static void player_init() {
	player=(Psi){GPLAYER,WHITE|BRIGHT,1,1,5,5,0,0,1};
}

static void mummie_init(u1 f,u1 c) {
	if(mummies<MUMMIES) {
		u1 delay=rnd(7,10);
		mummie[mummies++]=(Psi){GMUMMY,GREEN|BRIGHT,f,c,delay,delay,0,0,1};
	}
}

void nivel_init(u1 incrementa) {
	if(incrementa) {
		nivel.numero++;
		nivel.momias++;
	}
	nivel.papiro=nivel.tumba=nivel.llave=0;
	malla_mapa_init();
	player_init();
	mummies=0;
	for(u1 n=0;n<nivel.momias;n++) {
		int f,c;
		momia_posicion_random(&f,&c);
		mummie_init(f,c);
	}
}

static void pared_prt() {
	paper(YELLOW);
	ink(RED);
	printc(GSTONE);
}

static void llave_prt() {
	ink(MAGENTA|BRIGHT);
	printc(GLLAVE);
	nivel.llave=1;
}

static void tumba_prt() {
	ink(YELLOW|BRIGHT);
	printc(GTUMBA);
	nivel.tumba=1;
}

static void papiro_prt() {
	ink(WHITE|BRIGHT);
	printc(GPAPIRO);
	nivel.papiro=1;
}

static void agua_prt() {
	paper(BLUE);
	printc(' ');
	paper(BLACK);
}

static void huella_prt() {
	paper(BLACK);
	ink(WHITE);
	printc(GHUELLA);
}

static void vacio_prt() {
	paper(BLACK);
	ink(BLACK);
	printc(' ');
}

void open_block(int f,int c) {
	//abre el bloque que tiene centro esta fila y esta columna
	u1 extra=malla[f][c]&~(PARED|AGUA);
	u1 papel=BLUE;
	if(extra==MOMIA) {
		papel=BLACK;
	}
	for(int cf=f-1;cf<=f+1;cf++) {
		for(int cc=c-1;cc<=c+1;cc++) {
			locate(cf,cc);
			malla[cf][cc]&=(~PARED);
			if(papel==BLACK) malla[cf][cc]&=(~AGUA);
			paper(papel);
			if(cf==f && cc==c) {
				switch(extra) {
					case LLAVE:
						llave_prt();
						break;
					case PAPIRO:
						papiro_prt();
						break;
					case TUMBA:
						tumba_prt();
						break;
					case MOMIA:
						mummie_init(cf,cc);
						break;
					default:
						agua_prt();
				}
			} else printc(' ');
		}
	}
}

static u1 check_border_block(int f,int c) {
	int fi=f-2;
	int ci=c-2;
	int huellas=0;
	for(int cf=fi;cf<fi+5;cf++) {
		for(int cc=ci;cc<ci+5;cc++) {
			if(malla[cf][cc] & HUELLA) huellas++;
		}
	}
	if(huellas==16) return 1;
	return 0;
}

void detect_close_blocks() {
	//localiza los bloques cerrados y los abre si estan rodeados de huellas
	int bef=(MFI-3)/4;
	int bec=(MCO-3)/4;
	for(int ff=0;ff<bef;ff++) {
		for(int cc=0;cc<bec;cc++) {
			int f=3+4*ff;
			int c=3+4*cc;
			byte val=malla[f][c];
			if(val & PARED) {
				if(check_border_block(f,c)) {
					open_block(f,c);
				}
			}
		}
	}
}	

void mapa_draw() {
	for(int f=0;f<MFI;f++) {
		for(int c=0;c<MCO;c++) {
			u1 val=malla[f][c];
			locate(f,c);
			if(val & PARED) pared_prt();
		}
	}
	paper(BLACK);
}

void psi_draw(Psi p) {
	locate(p.f,p.c);
	ink(p.color);
	paper(BLACK);
	printc(p.gdu);
	ink(BLACK);
}

void player_act() {
	listen;
	if(player.vivo) {
		if(player.counter_delay==player.delay) {
			int ff=player.f;
			int cf=player.c;
			if(inkey('i')) ff--;
			else if(inkey('k')) ff++;
			if(inkey('j')) cf--;
			else if(inkey('l')) cf++;
			int val=malla[ff][cf];
			if((val & (AGUA|PARED))==0) {
				malla[player.f][player.c]=HUELLA;
				locate(player.f,player.c);
				huella_prt();
				player.f=ff;
				player.c=cf;
			}
			player.counter_delay=0;
			detect_close_blocks();
		} else player.counter_delay++;
		psi_draw(player);
	}
}

static void momia_act(Psi* p) {
	if(p->counter_delay==p->delay) {
		if(p->df==p->f && p->dc==p->c) {
			p->df=player.f;
			p->dc=player.c;
		}
	begin:
		s1 dirf=(p->df>p->f)?1:(p->df<p->f)?-1:0;
		s1 dirc=(p->dc>p->c)?1:(p->dc<p->c)?-1:0;
		int ff=p->f+dirf;
		if(malla[ff][p->c]>HUELLA) dirf=0;
		int fc=p->c+dirc;
		if(malla[p->f][fc]>HUELLA) dirc=0;
		if(dirf!=0 && dirc!=0) {
			if(rnd(0,1)) dirf=0;
			else dirc=0;
		} else if(dirf==0 && dirc==0) {
			p->df=rnd(0,MFI-1);
			p->dc=rnd(0,MCO-1);
			goto begin;
		}
		u1 f=p->f;
		u1 c=p->c;
		locate(f,c);
		if(malla[f][c]==HUELLA) huella_prt();
		else vacio_prt();
		f=p->f+=dirf;
		c=p->c+=dirc;
		psi_draw(*p);	
		p->counter_delay=0;
	} else p->counter_delay++;
}

void momias_act() {
	for(int k=0;k<mummies;k++) {
		Psi* m=mummie+k;
		if(m->vivo) momia_act(m);
	}
}

void encuentros() {
	for(int k=0;k<mummies;k++) {
		Psi* m=mummie+k;
		if(m->f==player.f && m->c==player.c) {
			if(nivel.papiro) {
				//kill a mummy
				m->vivo=0;
			} else {
				//kill player
				player.vivo=0;
				break;
			}
		}
	}
}

void program() {
	gdu_init();
	nivel_init(1);
	mapa_draw();
begin:
	player_act();
	encuentros();
	momias_act();
	encuentros();
	show;
	pause(0.005);
	while(inkey('q')==0) goto begin;
}

