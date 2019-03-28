#include "Menu.h"
#include "Joc.h"
#include "GestioResultats.h"
#include <conio.h>      /* getch */

const char JUGAR = '1';
const char CONFIGURAR = '2';
const char PUNTUACIO = '3';
const char SORTIR = '4';


int main()
{
	TipusJugador tMillorsJugadors[MAX_MILLORS_JUGADORS];



    char opcio;
    char nivell = '1';

	do{
		menuPrincipal();
		opcio = _getch();

        int posicio = -1;
		int punts;

		switch(opcio)
		{
			case JUGAR:
			    punts = joc(nivell-'0');



                if (posicio>=0)
				{
					system("cls");

				}
				break;

			case CONFIGURAR:
				do{
                    menuNivellDificultat();
					nivell =_getch();
					if ((nivell != '1') && (nivell != '2') && (nivell != '3'))
					{
						printf("Opcio incorrecta.\n");
					}
				} while((nivell != '1') && (nivell != '2') && (nivell != '3'));
				break;
			case PUNTUACIO:

				printf("Prem una tecla per tornar al menu principal");
				_getch();
				break;
		}
	}while(opcio != SORTIR);

	return 0;
}
