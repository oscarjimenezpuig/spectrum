/*
============================================================
  Fichero: prueba.c
  Creado: 06-10-2025
  Ultima Modificacion: dilluns, 6 d’octubre de 2025, 19:58:27
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include <stdio.h>

#include "spectrum.h"

REM(Ejemplo de programa)

PROCEDURE(Hola)
	LOCATE(0,0);
	INK(WHITE);
	LOCATE(10,10);
	MODE(RND(0,7));
	PRINTS("a");
	MODE(NORMAL);
END

PROGRAM
	CALL(Hola);
	IF(INKEY('s')) 
		STOP;
	ENDIF
	PAUSE(1);
END
	


