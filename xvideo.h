/*
============================================================
  Fichero: xvideo.h
  Creado: 20-03-2024
  Ultima Modificacion: diumenge, 16 de juny de 2024, 13:53:18
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#ifndef XVIDEO_H
#define XVIDEO_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef XPoint X_Point;
typedef long unsigned int X_Color;

extern unsigned int X_WINW,X_WINH;
extern X_Color X_BLACK,X_WHITE;

int x_init(unsigned int w,unsigned int h);

void x_end();

X_Color x_color(double red,double green,double blue);

void x_point(X_Point point,X_Color color);

void x_line(X_Point point_a,XPoint point_b,X_Color color);

void x_square(XPoint base,unsigned int dimension,X_Color color);

void x_quadrilateral(X_Point* points,X_Color color);

void x_background(X_Color color);

void x_clear();

void x_flush();

int x_inkey(KeySym* keysym);

#endif /* XVIDEO_H */
