/*
============================================================
  Fichero: starwars.c
  Creado: 08-10-2025
  Ultima Modificacion: lun 13 oct 2025 13:36:42
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
#define GHOUSE1 132
#define GHOUSE2 133

#define DBKG 7
#define DSHP 5
#define DEXP 1

#define MINF 100
#define INIF 300

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

int fuel=INIF;
int score=0;
byte exploded=0;
byte stop_move=0;
Object* ship=0;
byte finish_explosion=0;

void gdu_def() {
	gdu(GTREE1,24,60,124,239,103,126,60,48);
	gdu(GTREE2,66,107,127,219,207,126,60,44);
	gdu(GSHIP,24,24,60,36,60,126,255,195);
	gdu(GFUEL,126,231,239,231,239,255,0,255);
	gdu(GHOUSE1,24,60,124,254,230,231,195,195);
	gdu(GHOUSE2,60,60,102,66,66,102,255,255);

}

void intro() {
	char* skey[]={"I: up","J: left","L: right","K: down","Q: quit"};
	byte skeys=5;
	byte start=0;
	while(!start) {
		ink(WHITE|BRIGHT);
		paper(rnd(0,6)|BRIGHT);
		locate(1,11);
		prints("STAR WARS");
		locate(3,0);
		ink(RED|BRIGHT);
		paper(BLACK);
		prints("(c) Oscar Jimenez Puig 2025");
		locate(5,0);
		ink(WHITE|BRIGHT);
		prints("Cross the forest avoiding all the trees and houses...");
		locate(7,0);
		prints("Be careful with the fuel...");
		ink(YELLOW|BRIGHT);
		for(byte n=0;n<skeys;n++) {
			locate(n+9,0);
			prints(skey[n]);
		}
		ink(BLUE|BRIGHT);
		locate(23,0);
		prints("Press S to start game");
		show;
		pause(0.25);
		listen;
		if(inkey('s')) start=1;
	}
	cls;
}

void tree_new(int id,int x,int y) {
	byte const DEC[]={GTREE1,GTREE2,GHOUSE1,GHOUSE2};
	byte const INK[]={GREEN,GREEN,RED,RED};
	Object* o=object+id;
	o->type=TREE;
	o->id=id;
	do {
		o->x=(x<0)?rnd(0,31):x;
		o->y=(y<0)?rnd(1,23):y;
	}while(o->x==16 && o->y==22);
	byte brg=(rnd(0,1))?BRIGHT:NORMAL;
	o->mode=rnd(0,3);
	int limit=(score<7500)?1:3;
	byte val=rnd(0,limit);
	o->color=INK[val]|brg;
	o->gdu=DEC[val];
	o->mode=(val<=1)?rnd(0,3):NORMAL;
}

void init_tree_def() {
	const int INTREE=1;
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
	ship=o;
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

void object_colision() {
	Object* p=object;
	while(p!=object+objects) {
		if(p!=ship && p->x==ship->x && p->y==ship->y) {
			p->x=p->y=-1;
			if(p->type==FUEL) {
				p->x=p->y=-1;
				fuel+=rnd(100,300);
			} else exploded=1;
		}
		p++;
	}
}

void move_tree(Object* o) {
	if(!stop_move) {
		score++;
		locate(o->y,o->x);
		ink(BLACK);
		printc(' ');
		o->y++;
		if(o->y==24) {
			tree_new(o->id,-1,1);
		}
	}
}

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
		stop_move=1;
	}
	ink(BLACK);
	locate(y,x);
	printc(' ');
	locate(y,x);
	if(counter==0) {
		ink(RED|BRIGHT);
		printc(GSHIP);
	} else if(counter>0 && counter<MAXCO) {
		byte color=(counter%2)?RED:YELLOW;
		color|=BRIGHT;
		byte* pc=memory+OCOL+SCRBW*y+x;
		*pc=color;
		int atoms=(-MAXAT*counter+MAXAT*MAXCO)/9;
		byte* ini=memory+OPIX+y*8*SCRBW+x;
		for(int k=0;k<atoms;k++) {
			int ppx=rnd(0,7);
			byte* pos=ini+rnd(0,7)*SCRBW;
			*pos|=1<<ppx;
		}
	 } else finish_explosion=1;
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
	static int next_fuel=MINF;
	if(!stop_move) {
		if(o->y==-1 && fuel<next_fuel) {
			o->y=1;
			o->x=rnd(0,31);
			next_fuel=rnd(100,300);
		} else if(o->y<24 && o->y!=-1) {
			locate(o->y,o->x);
			ink(BLACK);
			printc(' ');
			o->y=o->y+1;
			o->y=(o->y==24)?-1:o->y;
		}
	}
}

void move_objects() {
	static int newtree=500;
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
	if(score>=newtree && objects<OBJECTS) {
		newtree+=500;
		tree_new(objects++,-1,1);
	}
	object_colision();
}

void marcador() {
	mode(NORMAL);
	locate(0,0);
	prints("          ");
	locate(0,0);
	ink(MAGENTA|BRIGHT);
	prints("FUEL ");
	printn(fuel);
	locate(0,20);
	prints("            ");
	locate(0,21);
	ink(CYAN|BRIGHT);
	prints("SCORE ");
	printn(score);
}

void init() {
	randomize(-1);
	gdu_def();
	intro();
	init_tree_def();
	init_ship_def();
	init_fuel_def();
}

void game_over() {
	const int TIME=25;
	int counter=0;
	while(counter!=TIME) {
		locate(12,11);
		mode(INVERSE);
		ink(rnd(0,6));
		paper(WHITE|BRIGHT);
		prints("GAME OVER");
		show;
		pause(0.25);
		counter++;
	}

}

void program() {
	int gameover=0;
	init();
	while(!gameover) {
		listen;
		marcador();
		move_objects();
		object_draw();
		if(fuel==0) exploded=1;
		pause(0.01);
		if(inkey('q') || (exploded && finish_explosion)) gameover=1;
		show;
	}
	game_over();
}

