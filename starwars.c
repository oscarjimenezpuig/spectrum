/*
============================================================
  Fichero: starwars.c
  Creado: 08-10-2025
  Ultima Modificacion: dijous, 9 d’octubre de 2025, 05:32:55
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

int fuel=100;

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
	o->x=1;
	o->y=24;
	o->mode=NORMAL;
	o->color=MAGENTA|BRIGHT;
	o->gdu=GFUEL;
}

void object_draw() {
	Object* p=object;
	while(p!=object+objects) {
		locate(p->y,p->x);
		ink(p->color);
		mode(p->mode);
		printc(p->gdu);
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

void move_ship(Object* o) {
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
}

void move_fuel(Object* o) {
	if(o->y==24 && fuel<50) {
		o->y=1;
		o->x=rnd(0,31);
	} else if(o->y<24) {
		locate(o->y,o->x);
		ink(BLACK);
		printc(' ');
		o->y=o->y+1;
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
	pause(0.01);
	if(inkey('s')) stop;
}

