/*
============================================================
  Fichero: spectrum.h
  Creado: 01-10-2025
  Ultima Modificacion: lun 13 oct 2025 13:50:08
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

//CONSTANTES

//MEMORY

//dimension de pantalla

#define SCRBW 32
#define SCRBH 24
#define SCRPW (SCRBW*8)
#define SCRPH (SCRBH*8)

//gdu

#define GDUS 256

//key

#define KEYS 5

//colores 

#define COLORS 16

//memoria

#define ODCL 0 //inicio de la definicion de colores (4 bytes por colores)
#define DDCL (COLORS*4) //dimension de los colores guardados
#define OPIX (ODCL+DDCL) //inicio de la pantalla de pixels
#define DPIX (SCRPW*SCRPH/8)  //dimension de la pantalla de pixeles
#define OCOL (OPIX+DPIX) //origen de los colores
#define DCOL (SCRBW*SCRBH) //dimension de los colores
#define OMEM (OCOL+DCOL) //origen de la memoria de GDU
#define DMEM (GDUS*8) //dimension de la memoria de GDU
#define OKEY (OMEM+DMEM) //inicio de la direccion donde se guardan las teclas
#define DKEY KEYS //guarda el keysym de KEYS teclas
#define OROM (OKEY+DKEY) //origen de la memoria rom (no a disposicion de usuario)
#define DROM 8 //dimension de la memoria rom
#define ORAM (OROM+DROM) //origen de la ram
#define DRAM 1024 //dimension de la ram

#define MEMORY (DDCL + DPIX + DCOL + DMEM + DKEY + DROM + DRAM) //memoria total

//memoria colores

#define RINK 1
#define GINK 2
#define BINK 4
#define UINK 8
#define RBKG 16
#define GBKG 32
#define BBKG 64
#define UBKG 128

//SPECTRUM

// direcciones auxiliares (en la memoria rom)

#define ATF OROM //posicion del cursor fila
#define ATC (ATF+1) //posicion del cursor columna
#define CLF (ATC+1) //color guardado (background y foreground)
#define CLC (CLF+1) //color guardado del cursor (una vez usado en impresion, desaparece por el valor de CLF)
#define MOI (CLC+1) //guarda el modo de impresion

// constante 0 (para todos los valores)

#define NORMAL 0

// colores

#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7

#define BRIGHT 8

// tipos de impresion

#define FLIPX 1 //simetria respecto eje de las x's
#define FLIPY 2 //simetria respecto eje de las y's
#define INVERSE 4 //inversion gdu (ocupado es abierto y al reves)

// lugar del color

#define PINK 0 //color de los bits conectados
#define PPAPER 1 //color de los bits desconectados

// cabecera funciones

#define poke(D,V) if ((D)<MEMORY) memory[D]=(V)  //asignar valor a posicion de memoria
#define peek(D) ((D)<MEMORY)?memory[D]:0 //conseguir el valor de la posicion de memoria
#define move(O,D) poke((D),peek((O))) //mover de una a otra posicion el valor
#define listen input() //se produce la entrada del teclado
#define show output() //se produce la salida por pantalla
#define background(A) s_attrsetall(PPAPER,A) //fondo de toda la pantalla
#define foreground(A) s_attrsetall(PINK,A) //tinta de toda la pantalla
#define paper(A) s_attrset(PPAPER,A) //paper de la proxima impresion
#define ink(A) s_attrset(PINK,A) //tinta de la proxima impresion
#define attri s_attrget(PINK) //se consigue donde los atributos de tinta
#define attrp s_attrget(PPAPER) //se consigue donde los atributos de paper
#define mode(M) s_mode((M)) //almacena el modo de impresion
#define locate(F,C) s_at((F),(C)) //coloca en la posicion dicha el cursor
#define printc(B) s_print_c((B)) //impresion de un caracter (0 a 255), M es el modo de impresion (FLIPX,FLIPY,INVERSE)
#define printn(N) s_print_n((N)) //impresion de cualquier numero
#define prints(S) s_print_s(S) //impresion de una cadena
#define cls s_clear(); //limpia la pantalla (ver s_clear())
#define inkey(A) s_inkey(A) //devuelve si se ha tecleado cierta tecla (a-z,0-9,espacio)
#define unkey(A) s_unkey(A) //desconexion de una tecla
#define gdu(N,A,B,C,D,E,F,G,H) s_gdu((N),(A),(B),(C),(D),(E),(F),(G),(H)) //definicion de un grafico definido por el usuario
#define randomize(A) s_randomize((A)) //introduce la semilla
#define rnd(A,B) s_rnd((A),(B)) //da numero aleatorio del intervalo [A,B]
#define pause(A) s_pause((A)) //pausa de un determinado tiempo

//TIPOS

//MEMORY

typedef unsigned char byte;
typedef unsigned short direction;

//VARIABLES

//MEMORY

extern byte memory[MEMORY];

//FUNCIONES

//MEMORY

void output();
//se produce muestra de la pantalla

void input();
//se produce lectura del teclado

void program();
//en su interior se mete todo el programa que se ejecutara. Solo parara la ejecucion en el momento que haya la señal de END_SIGN

//SPECTRUM

void s_attrsetall(byte place,byte a);
//definicion de todo el fondo o tinta de la pantalla (a=color|bright)

void s_attrset(byte place,byte a);
//definicion de fondo o tinta del siguiente sector de impresion

byte s_attrget(byte place);
//consigue color|bright segun el valor de place de attribute

void s_at(byte f,byte c);
//pone la posicion del cursor en la fila y columna especificada

void s_clear();
//quita todos los pixeles de pantalla, y restablece los colores de fondo y de tinta originales
//la posicion del cursor la situa en 0,0

//todas las funciones print implican que las posiciones de at varian hasta detras de la
//impresion

void s_mode(byte m);
//modo de impresion de caracter, numero o secuencia

void s_print_c(byte c);
//impresion de un caracter

void s_print_n(double n);
//impresion de cualquier tipo de numero

void s_print_s(char* s);
//impresion de una cadena de caracteres

byte s_inkey(char k);
//comprueba si se esta pulsada una tecla.

void s_unkey(char k);
//desconecta una tecla

void s_gdu(byte code,byte a,byte b,byte c,byte d,byte e,byte f,byte g,byte h);
//definicion de un gdu en el caracter c

void s_randomize(int a);
//establecimiento de la semilla del numero aleatorio, si a negativa, en funcion del tiempo

int s_rnd(int a,int b);
//nuemero aleatorio entre dos valores dados

void s_pause(double seconds);
//hacer una pausa de un determinado numero de segundos
