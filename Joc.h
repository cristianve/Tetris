
#include <conio.h>      /* getch */
#include <stdio.h>      /* printf */
#include <time.h>       /* time */

//========================================================================
// Inici del taulell respecte la cantonada superior esquerre
const int INICI_X = 26;
const int INICI_Y = 1;

//========================================================================
// Fi del taulell respecte la cantonada inferior dreta
const int FI_X = 312;
const int FI_Y = 547;

//========================================================================
// nº de píxels que ocupa un quadre dels que formen les figures del tetris
const int MIDA_Q = 26;

// Posició de la graella per nostrar puntuacio i nivell;
const int POS_RESX = 350;
const int POS_RESY = 350;

// Posicio de les centenes dels punts i del pas d'una unitat a una altre.
const int POS_CENT_RESX = 530;
const int POS_NUM_RESY = 485;
const int PAS_DIGIT_X = 20;

// Posicio del nivell
const int POS_NIV_RESX = 550;
const int POS_NIV_RESY = 430;


//===================================================================================
// Codis tecles
const int KEYBOARD_ESCAPE = 27;
const int  KEYBOARD_RIGHT = 77;
const int  KEYBOARD_LEFT = 75;
const int  KEYBOARD_DOWN = 80;

//========================================================================
// Codis peces
const int  I = 1;
const int  O = 2;
const int  T = 3;
const int  L = 4;

// Longitud meta
const int COL_X = ((FI_X-INICI_X) / MIDA_Q);

const int TEMPS_PERDUA = 30;


int llegirEvent();
int aleatori(int min, int max);
int llargPeca(int obj);
int altPeca(int obj);

int  limitiDretX(int obj);

void inicialitzarMeta(int meta[]);
void arribadaMeta(int obj, int x, int meta[]);

void mourePeca(int& x, int& y, int dirX, int dirY, int& obj, int meta[]);
void tractarEvent(int tecla, int& x, int& y, int& obj, int meta[]);

void pintarMeta(int meta[]);
int guanyar(int meta[]);

int joc(int nivell);

/*----- END --------------*/

