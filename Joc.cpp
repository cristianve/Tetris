
#include "Joc.h"
#include "lib/libreria.h"
#include <cstdlib>

void escriuDigit(int n, int posX, int posY)
{
    Sprite uno("data/numeros/numero0001.png");
    Sprite dos("data/numeros/numero0002.png");
    Sprite tres("data/numeros/numero0003.png");
    Sprite quatre("data/numeros/numero0004.png");
    Sprite cinc("data/numeros/numero0005.png");
    Sprite sis("data/numeros/numero0006.png");
    Sprite siete("data/numeros/numero0007.png");
    Sprite vuit("data/numeros/numero0008.png");
    Sprite nou("data/numeros/numero0009.png");
    Sprite zero("data/numeros/numero0000.png");

    switch(n)
    {
        case 1: {
                    uno.Draw(posX,posY);
                    break;
        }
        case 2: {
                    dos.Draw(posX,posY);
                    break;
        }
        case 3: {
                    tres.Draw(posX,posY);
                    break;
        }
        case 4: {
                    quatre.Draw(posX,posY);
                    break;
        }
        case 5: {
                    cinc.Draw(posX,posY);
                    break;
        }
        case 6: {
                    sis.Draw(posX,posY);
                    break;
        }
        case 7: {
                    siete.Draw(posX,posY);
                    break;
        }
        case 8: {
                    vuit.Draw(posX,posY);
                    break;
        }
        case 9: {
                    nou.Draw(posX,posY);
                    break;
        }
        case 0: {
                    zero.Draw(posX,posY);
                    break;
        }
    }
}


void escriuNumero(int n,int posX,int posY,int pasDigit)
{
    int divisor = 100;
    int posXActual = posX;
    int nActual =n;
    bool primerDigit = true;

    while (divisor > 0)
    {
        int d = nActual / divisor;
        nActual = nActual % divisor;
        divisor = divisor / 10;

        if ( (d > 0) || !primerDigit )
        {
            escriuDigit( d , posXActual, posY);
            primerDigit = false;
        }

        posXActual += pasDigit;
    }
}


int llegirEvent()
{

    int codi;

    if (Keyboard_GetKeyTrg(KEYBOARD_LEFT)) codi = KEYBOARD_LEFT;
    else if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT)) codi = KEYBOARD_RIGHT;
    else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN)) codi = KEYBOARD_DOWN;
    else if (Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)) codi = KEYBOARD_ESCAPE;

    return codi;
    //OK?
}

// Funció que retorna un valor aleatori entre min i max
// No cal modificar-la
int aleatori(int min, int max)
{
	int aleatori = rand() % (max - min + 1) + min; //
	return aleatori;
}


// Funció que retorna el nº de columnes que ocupa una peça
// No cal modificar-la
int llargPeca(int obj)
{
    int llarg = 0;
    switch (obj)
    {
        case I:
            llarg = 4;
            break;
        case O:
            llarg = 2;
            break;
        case T:
        case L:
            llarg = 3;
            break;
    }
    return llarg;
}

int altPeca(int obj)
{

    int alt = 0;
    switch (obj)
    {
        case I:
            alt = 1;
            break;
        case O:
        case T:
        case L:
            alt = 2;
            break;
    }
    return alt;

}


int limitiDretX(int obj)
{

    return (FI_X - (llargPeca(obj)* MIDA_Q));
    //OK
}


void inicialitzarMeta(int meta[])
{
	for(int i = 0; i < COL_X; i++)
	    meta[i] = 1;
}



void arribadaMeta(int obj, int x, int meta[])
{
    // ***
    // Aquesta funció actualitza l'array que controla les posiccions de l'última fila ocupades
    // Cal modificar només el càlcul de la columna (pos) a partir de la coordinada x de la peça
    // La resta de la funció no cal modificar-la
    // Aquí us donem el codi del projecte de FI on cada columna ocupava només 1 posició
    // Ara cal tenir en compte que cada columna ocupa una amplada en píxels equivalent a MIDA_Q

	int pos = x - INICI_X*MIDA_Q - MIDA_Q;

	for(int i = pos; i <= pos + 1; i++)
    {
        switch (obj)
        {
            case I:
                meta[i] = 0;
			    meta[i + 2] = 0;
                break;
            case O:
                meta[i] = 0;
                break;
            case T:
            case L:
                meta[i]   = 0;
                meta[i + 1] = 0;
                break;
        }
    }
}


void mourePeca(int& x, int& y, int dirX, int dirY, int& obj, int meta[])
{
    // ***
    // Aquesta funció mou una peça segons els valors dels paràmetres dirX i dirY
    // Si la peça arriba al final del taulell es torna a generar una nova peça que apareix a
    // la part de dalt del taulell.
    // Cal modificar tot el que té a veure amb el càlcul i control de les coordinades de la peça
    // per tenir en compte que cada columna i fila ocupen una amplada i alçada en píxels equivalent a MIDA_Q
    // Aquí us donem el codi del projecte de FI on cada columna i fila ocupaven només 1 posició
	if( y < (FI_Y - MIDA_Q))
    {
        x += dirX*MIDA_Q;
        y += dirY*MIDA_Q;
    }
    else
    {
		arribadaMeta(obj, x, meta);

		obj  = aleatori(I, L);
        x = aleatori(INICI_X + MIDA_Q,  limitiDretX(obj));
        y = INICI_Y;
    }
    //OK?
}


void tractarEvent(int tecla, int& x, int& y, int& obj, int meta[])
{
    // ***mourePeca
    // Aquesta funció decideix quin moviment s'ha de fer a la peça en funció de la tecla que s'hagi pressionat
    // Abans de fer el moviment de la peça es comprova que no superi els límits del taulell
    // Cal modificar tot el que té a veure amb el control de les coordinades de la peça
    // per tenir en compte que cada columna i fila ocupen una amplada i alçada en píxels equivalent a MIDA_Q
    // Aquí us donem el codi del projecte de FI on cada columna i fila ocupaven només 1 posició
	switch(tecla)
	{
		case KEYBOARD_LEFT:
			if ( x > (INICI_X + MIDA_Q) ) //+1
				mourePeca(x, y, -1, 0, obj, meta);
			break;
		case KEYBOARD_RIGHT:
			if ( x < limitiDretX(obj))
				mourePeca(x, y, 1, 0, obj, meta);
			break;
		case KEYBOARD_DOWN:
			if ( y < (FI_Y - 2*MIDA_Q))
				mourePeca(x, y, 0, 2, obj, meta);
			break;
		default: break;
	}
	//OK?
}

// Funció que retorna un 0 si totes les posicions de l'última fila estan ocpuades.
// En cas contrari, retorna un valor diferent de 0
// No cal modificar-la
int guanyar(int meta[])
{
	int sum = 0;

	for(int i = 0; i < COL_X; i++)
		sum += meta[i];

	return sum;
}


void pintarMeta(int meta[])
{

    int i;
    Sprite tetris("data/Graficstetris/q1roig.png");

    for (i = 0; i < COL_X; i++)
    {
        if(meta[i]== 0)tetris.Draw((i+1)*MIDA_Q, FI_Y - MIDA_Q);
    }
}


int joc(int nivell)
{

    Game joc;
    // ***
    // En aquest punt hauren de cridar a les funcions d'inicialització de la llibreria gràfica
    joc.Init();

    // igual que està fet al projecte TestGrafics



	int peca, pecaX, pecaY;
    int tecla = 0;

    int meta[COL_X];
    int metaAconseguida;

	int velocitatJoc = 50;
	int contVPeca;

	int vides = 3;
	int punts = 0;
	int diffT = 0;
	time_t now;

	srand((unsigned)time(NULL));

    // ***
    // En aquest punt haureu de crear els gràfics de les 4 peces, el gràfic del fons del taulel i el gràfic
    // que permet mostrar els resultats. Per les peces necessitareu 4 variables de tipus Sprite, una per cada peça
    // Preneu com a referència el codi de creació dels gràfics al projecte TestGrafics
    // Els gràfics que heu d'utilitzar per les peces, el fons i el resultat són:
    // "data/Graficstetris/palblaucel2.png"
    // "data/Graficstetris/pblaufosc4.png"
    // "data/Graficstetris/tmagenta2.png"
    // "data/Graficstetris/q4groc1.png"
    // "data/GraficsTetris/fons.png"
    // "data/GraficsTetris/Resultats.png"
    // També haureu de mostrar la pantalla gràfica cridant a la funció Video_ShowWindow() igual que al projecte TestGrafics

    //Sprite tetrisPBC1("data/Graficstetris/palblaucel1.png");
    Sprite tetrisPBC2("data/Graficstetris/palblaucel2.png");
    //Sprite tetrisLT1("data/Graficstetris/ltaronja1.png");
    //Sprite tetrisLT2("data/Graficstetris/ltaronja2.png");
    //Sprite tetrisLT3("data/Graficstetris/ltaronja3.png");
    //Sprite tetrisLT4("data/Graficstetris/ltaronja4.png");
    //Sprite tetrisPBF1("data/Graficstetris/pblaufosc1.png");
    //Sprite tetrisPBF2("data/Graficstetris/pblaufosc2.png");
    //Sprite tetrisPBF3("data/Graficstetris/pblaufosc3.png");
    Sprite tetrisPBF4("data/Graficstetris/pblaufosc4.png");
    //Sprite tetrisSV1("data/Graficstetris/sverd1.png");
    //Sprite tetrisSV2("data/Graficstetris/sverd2.png");
    //Sprite tetrisZR1("data/Graficstetris/zroig1.png");
    //Sprite tetrisZR2("data/Graficstetris/zroig2.png");
    //Sprite tetrisTM1("data/Graficstetris/tmagenta1.png");
    Sprite tetrisTM2("data/Graficstetris/tmagenta2.png");
    //Sprite tetrisTM3("data/Graficstetris/tmagenta3.png");
    //Sprite tetrisTM4("data/Graficstetris/tmagenta4.png");
    Sprite tetrisQ4G("data/Graficstetris/q4groc1.png");
    //Sprite tetrisQBC("data/Graficstetris/q1blaucel.png");
    //Sprite tetrisQBF("data/Graficstetris/q1blaufosc.png");

    //Sprite tetrisQV("data/Graficstetris/q1verd.png");
    //Sprite tetrisQT("data/Graficstetris/q1taronja.png");
    //Sprite tetrisQM("data/Graficstetris/q1magenta.png");
    //Sprite tetrisQ1G("data/Graficstetris/q1groc.png");

    Sprite fons("data/GraficsTetris/fons.png");
    Sprite resultats("data/GraficsTetris/Resultats.png");

    joc.Video_ShowWindow();

	do
    {

        // Inicialització de la posició de la peça
        peca  = aleatori(I, L);

        // ***
        // En aquest punt heu de modificar la inicialització de la coordinada X de la peça perquè
        // es correspongui amb el valor en píxels d'alguna columna vàlida del taulell
        // Podeu prendre com a referència la inicialització de la posició de la peça que es fa al projecte TestGrafics

        pecaX = aleatori(INICI_X + MIDA_Q,  limitiDretX(peca));
        //pecaX = aleatori(INICI_X + 1, limitiDretX(peca)); antiguo
        pecaY = INICI_Y;

        metaAconseguida = 1;
        inicialitzarMeta(meta);
        contVPeca = velocitatJoc / nivell;
        now = time(NULL);

        // ***
        // En aquest punt haureu de dibuixar el fons, les peces, el fons dels resultats, la puntuació i el nivell actual
        // Per dibuixar les peces tingueu en compte que haureu de dibuixar un gràfic diferent segons el valor
        // de la peça actual que determina la variable peca
        // Podeu prendre com a referència el codi que dibuixa fons, resultats i peça al projecte TestGrafics
        // Podeu copiar i utilitzar les funcions del projecte TestGrafics que s'utilitzen per escriure números
        // Finalment heu de cridar a la funció VideoUpdate() per refrescar la pantalla de forma similar a com
        // es fa al projecte TestGrafics

        fons.Draw(0, 0);

        switch (peca)
        {
            case I:
                tetrisPBC2.Draw(pecaX, pecaY);
                break;
            case O:
                tetrisQ4G.Draw(pecaX, pecaY);
                break;
            case T:
                tetrisTM2.Draw(pecaX, pecaY);
                break;
            case L:
                tetrisPBF4.Draw(pecaX, pecaY);
                break;
        }

        //Pinta resultats
        resultats.Draw(POS_RESX,POS_RESY);
        escriuNumero(nivell, POS_NIV_RESX, POS_NIV_RESY, PAS_DIGIT_X);
        escriuNumero(punts, POS_CENT_RESX, POS_NUM_RESY, PAS_DIGIT_X);

        //OK?


        do
        {
            // ***
            // En aquest punt haureu de cridar a la funció ProcessEvents de forma similar a com es fa al projecte
            // TestGrafics. Després es crida a les versions modificades de llegirEvent i tractarEvent (no cal modificar
            // aquestes crides)
            joc.ProcessEvents();

            tecla = llegirEvent();
            tractarEvent(tecla, pecaX, pecaY, peca, meta);

            // Moviment de la peça
            contVPeca--;
            if(!contVPeca)
            {
                mourePeca(pecaX, pecaY, 0, 1, peca, meta);
                contVPeca = velocitatJoc / nivell;
            }

            // ***
            // En aquest punt haureu de tornar a dibuixar el fons, les peces, el fons dels resultats, la puntuació
            // i el nivell actual exactament igual que heu fet més amunt
            // A més a més, aquí haureu de dibuixar també l'ocupació de l'última fila cridant a la funció pintarMeta

            fons.Draw(0, 0);

            switch (peca)
            {
                case I:
                    tetrisPBC2.Draw(pecaX, pecaY);
                    break;
                case O:
                    tetrisQ4G.Draw(pecaX, pecaY);
                    break;
                case T:
                    tetrisTM2.Draw(pecaX, pecaY);
                    break;
                case L:
                    tetrisPBF4.Draw(pecaX, pecaY);
                    break;
            }

            //Pinta resultats
            resultats.Draw(POS_RESX,POS_RESY);
            escriuNumero(nivell, POS_NIV_RESX, POS_NIV_RESY, PAS_DIGIT_X);
            escriuNumero(punts, POS_CENT_RESX, POS_NUM_RESY, PAS_DIGIT_X);

            pintarMeta(meta);

            //OK?


            diffT = difftime(time(NULL),  now);

            if(diffT > (TEMPS_PERDUA / nivell))
            {
                metaAconseguida = 0;
                vides--;
            }


            if(!guanyar(meta))
            {
                metaAconseguida = 0;
                punts += nivell;
                nivell++;
            }

        joc.VideoUpdate();

        }while(tecla != KEYBOARD_ESCAPE && metaAconseguida);

	}while((nivell<4) && (vides>0) && (tecla != KEYBOARD_ESCAPE));


	return punts;
}
