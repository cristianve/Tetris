#include "GestioResultats.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>     /* system */

void inicialitzarTaulaMillorJugadors(TipusJugador tMillorsJugadors[])
{
	for(int i = 0; i < MAX_MILLORS_JUGADORS; i++)
	{
		strcpy(tMillorsJugadors[i].Nom,"--------------");
		tMillorsJugadors[i].puntuacio = 0;
	}
}



int esMillorPuntuacio(TipusJugador tMillorsJugadors[], int punts)
{
	int i=0;
	int trobat=0;

	do
	{
		if(tMillorsJugadors[i].puntuacio < punts)
		{
			trobat = 1;
		}
		i++;

	}while ((i < MAX_MILLORS_JUGADORS) && (!trobat));

	if (trobat)
	{
		return (i - 1);
	}
	else
	{
		return - 1;
	}
}

void desplacarArray(TipusJugador tMillorsJugadors[], int posicio)
{
	for (int i = MAX_MILLORS_JUGADORS - 1; i > posicio; i--)
	{
		strcpy(tMillorsJugadors[i].Nom, tMillorsJugadors[i - 1].Nom);
		tMillorsJugadors[i].puntuacio = tMillorsJugadors[i - 1].puntuacio;
	}
}

void emplenarPosicioArray(TipusJugador& tMillorsJugadors,int punts)
{
	system("cls");
	printf("Entra el teu nom\n");
	scanf("%s",&(tMillorsJugadors.Nom));
	(tMillorsJugadors).puntuacio = punts;
}

void escriuRanking(TipusJugador tMillorsJugadors[])
{
	system("cls");
	for(int i = 0; i < MAX_MILLORS_JUGADORS; i++)
	{
		printf("%d.- %s %d\n", i + 1, tMillorsJugadors[i].Nom, tMillorsJugadors[i].puntuacio);
	}

}
