/*
============================================================
  Fichero: starwars.c
  Creado: 08-10-2025
  Ultima Modificacion: dijous, 9 d’octubre de 2025, 20:26:53
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "spectrum.h"

#define TREE 1
#define FUEL 2
#define SHIP 3

#define OBJECTS 100

#define GTREE1 128
#define GTREE2 129
#define GSHIP 130
#define GFUEL 131

#define DBKG 7
#define DSHP 5
#define DEXP 1

typedef struct {
	byte id;
	byte type;
	byte color;
	byte mode;
	byte gdu;
	int x,y;
} Object;

Object object[OBJECTS];
int objects=0;

int fuel=5;
byte exploded=0;

void gdu_def() {
	gdu(GTREE1,24,60,124,239,103,126,60,48);
	gdu(GTREE2,66,107,127,219,207,126,60,44);
	gdu(GSHIP,24,24,60,36,60,126,255,195);
	gdu(GFUEL,126,231,239,231,239,255,0,255);
}

void tree_new(int id,int x,int y) {
	Object* o=object+id;
	o->type=TREE;
	o->id=id;
	do {
		o->x=(x<0)?rnd(0,31):x;
		o->y=(y<0)?rnd(1,23):y;
	}while(o->x==16 && o->y==22);
	byte brg=(rnd(0,1))?BRIGHT:NORMAL;
	o->color=GREEN|brg;
	o->mode=rnd(0,3);
	o->gdu=(rnd(0,1))?GTREE1:GTREE2;

}

void init_tree_def() {
	const int INTREE=10;
	for(int k=0;k<INTREE;k++) tree_new(objects++,-1,-1);
}

void init_ship_def() {
	Object* o=object+objects;
	o->id=objects++;
	o->type=SHIP;
	o->x=16;
	o->y=22;
	o->mode=NORMAL;
	o->color=CYAN|BRIGHT;
	o->gdu=GSHIP;
}

void init_fuel_def() {
	Object* o=object+objects;
	o->id=objects++;
	o->type=FUEL;
	o->x=-1;
	o->y=-1;
	o->mode=NORMAL;
	o->color=MAGENTA|BRIGHT;
	o->gdu=GFUEL;
}

void object_draw() {
	Object* p=object;
	while(p!=object+objects) {
		if(p->x>=0 && p->x<32 && p->y>0 && p->y<24) {
			locate(p->y,p->x);
			ink(p->color);
			mode(p->mode);
			printc(p->gdu);
		}
		p++;
	}
}

void move_tree(Object* o) {
	locate(o->y,o->x);
	ink(BLACK);
	printc(' ');
	o->y++;
	if(o->y==24) {
		tree_new(o->id,-1,1);
	}
}

#include <stdio.h> //dbg

void expl_ship(Object* o) {
	const int MAXAT=32;
	const int MAXCO=10;
	static int x,y;
	static int counter=0;
	static int init=0;
	if(!init) {
		x=o->x;
		y=o->y;
		o->x=o->y=-1;
		init=1;
	}
	ink(BLACK);
	locate(y,x);
	printc(' ');
	locate(y,x);
	if(counter==0) {
		ink(RED|BRIGHT);
		printc(GSHIP);
	} else if(counter>0 && counter<MAXCO) {
		ink(YELLOW+BRIGHT);
		int atoms=(-MAXAT*counter+MAXAT*MAXCO)/9;
		byte* ini=memory+OPIX+y*8*SCRBW+x;
		for(int k=0;k<atoms;k++) {
			int ppx=rnd(0,7);
			byte* pos=ini+rnd(0,7)*SCRBW;
			*pos|=1<<ppx;
		}
	}
	counter++;
}

void move_ship(Object* o) {
	if(!exploded) {
		int fx=o->x;
		int fy=o->y;
		locate(o->y,o->x);
		ink(BLACK);
		printc(' ');
		fuel--;
		if(inkey('i') && fy>1) fy--;
		else if(inkey('k') && fy<23) fy++;
		if(inkey('j')) {
			fx--;
			if(fx<0) fx=31;
		} else if(inkey('l')) {
			fx++;
			if(fx==32) fx=0;
		}
		o->x=fx;
		o->y=fy;
	} else expl_ship(o);
}

void move_fuel(Object* o) {
	if(o->y==-1 && fuel<50) {
		o->y=1;
		o->x=rnd(0,31);
	} else if(o->y<24 && o->y!=-1) {
		locate(o->y,o->x);
		ink(BLACK);
		printc(' ');
		o->y=o->y+1;
		o->y=(o->y==24)?-1:o->y;
	}
}

void move_objects() {
	Object* p=object;
	static int dbkg=DBKG;
	static int dshp=DSHP;
	int mbkg=0;
	int mshp=0;
	if(dbkg==DBKG) {
		mbkg=1;
		dbkg=0;
	} else dbkg++;
	if(dshp==DSHP) {
		mshp=1;
		dshp=0;
	} else dshp++;
	while(p!=object+objects) {
		if(p->type==TREE && mbkg) {
			move_tree(p);
		} else if(p->type==SHIP && mshp) {
			move_ship(p);
		} else if(p->type==FUEL && mbkg) {
			move_fuel(p);
		}
		p++;
	}
}


void init() {
	static int doit=0;
	if(!doit) {
		randomize(-1);
		gdu_def();
		init_tree_def();
		init_ship_def();
		init_fuel_def();
		doit=1;
	}
}

void program() {
	init();
	move_objects();
	object_draw();
	if(fuel==0) exploded=1;
	pause(0.1);
	if(inkey('s')) stop;
}

