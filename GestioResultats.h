
typedef struct
{
  char Nom[15];
  int puntuacio;
}TipusJugador;

const int MAX_MILLORS_JUGADORS = 5;

void inicialitzarTaulaMillorJugadors(TipusJugador
	                                 tMillorsJugadors[]);
int  esMillorPuntuacio(TipusJugador tMillorsJugadors[],
	                   int punts);
void desplacarArray(TipusJugador tMillorsJugadors[],
	                int posicio);
void emplenarPosicioArray(TipusJugador& tMillorsJugadors,
	                      int punts);
void escriuRanking(TipusJugador tMillorsJugadors[]);
