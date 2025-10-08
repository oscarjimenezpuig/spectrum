/*
============================================================
  Fichero: pong.c
  Creado: 07-10-2025
  Ultima Modificacion: dimecres, 8 d’octubre de 2025, 05:28:16
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "spectrum.h"

VAR(BYTE,px,15)
VAR(BYTE,py,12)
VAR(BYTE,dpx,1)
VAR(BYTE,dpy,1)
VAR(BYTE,jy,9)
VAR(BYTE,oy,9)

PROCEDURE(Init)
	PERSISTENT VAR(BYTE,defined,0)
	IF(defined) 
		GOTO(0);
	ELSE
		RANDOMIZE(-1)
		SET(defined,1)
		GDU(128,60,126,255,255,255,255,126,60)
		GDU(129,255,255,255,255,255,255,255,255)
		BACKGROUND(BLACK)
		VAR(BYTE,n,0)
		INK(WHITE|BRIGHT)
		FOR(n,0,n<32,n++)
			LOCATE(1,n)
			PRINTC(129)
			LOCATE(23,n)
			PRINTC(129)
		NEXT
		FOR(n,1,n<24,n++)
			IF(n<9 || n>15)
				LOCATE(n,0)
				PRINTC(129)
				LOCATE(n,31)
				PRINTC(129)
			ENDIF
		NEXT
		INK(BLACK)
		IF(RND(0,1)) 
			NOT(dpx)
		ENDIF
		IF(RND(0,1))
			NOT(dpy)
		ENDIF
	ENDIF
	LABEL(0)
END

PROCEDURE(Moveball)
	LOCATE(py,px)
	PRINTC(' ')
	VAR(BYTE,fx,px)
	VAR(BYTE,fy,py)
	IF(dpx==1)
		INC(fx)
	ELSIF(dpx==254)
		DEC(fx)
	ENDIF
	IF(dpy==1)
		INC(fy)
	ELSIF(dpy==254)
		DEC(fy)
	ENDIF
	LOCATE(py,fx)
	IF(ATTRI & WHITE) 
		SET(dpx,~dpx)
	ELSE
		SET(px,fx)
	ENDIF
	LOCATE(fy,px)
	IF(ATTRI & WHITE)
		SET(dpy,~dpy)
	ELSE
		SET(py,fy)
	ENDIF
	LOCATE(py,px)
	INK(WHITE|BRIGHT)
	PRINTC(128)
	INK(BLACK)
END

PROCEDURE(Moveplayer)
	VAR(BYTE,n,0)
	INK(BLACK)
	FOR(n,0,n<4,n++)
		LOCATE(jy+n,3);
		PRINTC(' ')
	NEXT
	IF(INKEY('a') && jy>2)
		DEC(jy)
	ENDIF
	IF(INKEY('z') && jy+4<23)
		INC(jy)
	ENDIF
	INK(WHITE|BRIGHT)
	FOR(n,0,n<4,n++)
		LOCATE(jy+n,3);
		PRINTC(129)
	NEXT
END

PROGRAM
	CALL(Init)
	INK(BLACK)
	CALL(Moveball)
	CALL(Moveplayer)
	IF(INKEY('s')) 
		STOP;
	ELSE 
		PAUSE(0.05)
	ENDIF
END

	
		



