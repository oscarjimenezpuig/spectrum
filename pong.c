/*
============================================================
  Fichero: pong.c
  Creado: 07-10-2025
  Ultima Modificacion: mar 07 oct 2025 12:29:37
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "spectrum.h"

BYTE px,py,dpx,dpy;
BYTE jy,oy;

PROCEDURE(Init)
	PERSISTENT BYTE defined=0;
	IF(defined) 
		GOTO(0);
	ELSE
		GDU(128,60,126,255,255,255,255,126,60);
		GDU(129,255,255,255,255,255,255,255,255);
		BACKGROUND(BLACK);
		FOREGROUND(WHITE|BRIGHT);
		defined=1;
	ENDIF
	LABEL(0)
END

PROCEDURE(Moveball)
	BYTE fx,fy;
	IF(DPX==1)
		fx=px+1;
	ELSIF(DPX==254)
		fx=px-1;
	ENDIF
	IF(DPY==1)
		fy=py+1;
	ELSIF(DPY==254)
		fy=py-1;
	ENDIF
	LOCATE(fx,fy);
	

END
	

PROGRAM
	CALL(Init)
	LOCATE(10,10);
	PRINTC(128);
	LOCATE(20,10);
	PRINTC(129);
	IF(INKEY('s')) 
		STOP;
	ENDIF
END

	
		



