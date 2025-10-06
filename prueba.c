/*
============================================================
  Fichero: prueba.c
  Creado: 06-10-2025
  Ultima Modificacion: lun 06 oct 2025 14:31:11
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include <stdio.h>

#include "spectrum.h"

PROCEDURE(Hola)
	LOCATE(0,0);
	INK(WHITE);
	
	NUMBER n;
	FOR(n,NORMAL,n<=INVERSE,n=n<<1)
	MODE(FLIPX);
	PRINTS("a");
	MODE(NORMAL);
END

PROGRAM
	CALL(Hola);
	IF(INKEY('s')) 
		STOP;
	ENDIF
END
	


