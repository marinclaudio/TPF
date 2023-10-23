/*
 * validaciones.c
 *
 *  Created on: 10 oct. 2023
 *      Author: lp1-2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cabecera2.h"

int verificarSeleccion (int f, int c, struct posicion t[TAM][TAM])
/*
 * Verifica que las coord. ingresadas son validas y si la posicion seleccionada esta vacia
 * Argumentos:
 * -> f: coord. fila
 * -> c: coord. columna
 * -> t: tablero
 * Retorno:
 * -> 0 si la posicion esta vacia
 * -> 1 si la posicion ingresada esta ocupada
 * -> 2 si la posicion ingresada no es valida
 */
{
	if (f < 0 || f > 4)
		return 2;
	else if (c < 0 || c > 4)
		return 2;
	else if(t[f][c].tipoDado != VACIO)
		return 1;
	else return 0;
}

int existenciaCaptura (int f, int c, struct posicion t[TAM][TAM])
/*
 * Verifica si existe capturas para una posicion seleccionada
 * Argumentos:
 * -> f: coord. fila de la posicion seleccionada
 * -> c: coord. columna de la posicion seleccionada
 * -> t: tablero
 * Retorno:
 * -> SI, si existen capturas
 * -> NO, si no existen capturas
 */
{
	if (c - 1 >= 0 && t[f][c - 1].tipoDado != VACIO) 		// verifica la posicion izq.
		return SI;
	else if (c + 1 <= 4 && t[f][c + 1].tipoDado != VACIO)	// verifica la posicion dere.
		return SI;
	else if (f - 1 >= 0 && t[f - 1][c].tipoDado != VACIO)	// verifica la posicion de arriba
		return SI;
	else if (f + 1 <= 4 && t[f + 1][c].tipoDado != VACIO)	// verifica la posicion de abajo
		return SI;
	else
		return NO;
}

int verificarCaptura (int f, int c, int izq, int der, int arriba, int abajo, struct posicion t[TAM][TAM])
/*
 * Verifica si las capturas ingresadas son validas
 * Argumentos:
 * -> f: coord. fila de la posicion seleccionada
 * -> c: coord. columna de la posicion seleccionada
 * -> izq: SI o NO, si se desea o no hacer una captura a la izquierda
 * -> der: SI o NO, si se desea o no hacer una captura a la derecha
 * -> arriba: SI o NO, si se desea o no hacer una captura arriba
 * -> abajo: SI o NO, si se desea hacer o no una captura a abajo
 * -> t: tablero
 * Retorno:
 * SI, si se puede realizar las capturas
 * NO, si no se puede realizar las capturas
 */

{
	int sumaCap = 0; 	//suma de dados a capturar
	if (izq == SI)
	{
		if (c - 1 < 0								// verifica si la casilla selec. tiene un elemento izq.
		|| t[f][c - 1].tipoDado == VACIO)			// verifica si la casilla izq. esta vacia
			return NO;
		else sumaCap += t[f][c - 1].valor - '0';	// se suma el numero del dado al contador
	}
	if (der == SI)
	{
		if (c + 1 > 4								// verifica si la casilla selec. tiene un elemento derecho
		|| t[f][c + 1].tipoDado == VACIO			// verifica si la casilla dere. esta vacia
		|| (sumaCap += t[f][c + 1].valor - '0') > 6)// verifica si la suma de dados es > 6
			return NO;
	}
	if (arriba == SI)
	{
		if (f - 1 < 0								// verifica si la casilla selec. tiene un elemento arriba
		|| t[f - 1][c].tipoDado == VACIO			// verifica si la casilla de arriba esta vacia
		|| (sumaCap += t[f - 1][c].valor - '0') > 6)// verifica si la suma de dados es > 6
			return NO;
	}
	if (abajo == SI)
	{
		if (f + 1 > 4								// verifica si la casilla selec. tiene un elemento abajo
		|| t[f + 1][c].tipoDado == VACIO			// verifica si la casilla de abajo esta vacia
		|| (sumaCap += t[f + 1][c].valor - '0') > 6)// verifica si la suma de dados es > 6
			return NO;
	}
	return SI;
}

void jugadaMaquina (int color, struct posicion t[TAM][TAM], int *f, int *c, int *totalCap, int *cont)
/*
 * selecciona una posicion alazar para colocar un dado y realiza capturas aleatorias si es posible
 * Argumentos:
 * -> color: color de la maquina
 * -> t: tablero
 * -> f: fila de la posicion de destino
 * -> c: columna de la posicion de destino
 * -> t: totalCap: total capturas
 * -> cont: contador de espacios vacios y dados
 */
{
	srand(time(NULL));
	int capturas;
	int izq, der, arriba, abajo;
	do
	{
		*f = rand() % 5;
		*c = rand() % 5;
	} while (verificarSeleccion (*f, *c, t) != 0);
	*totalCap = 0;
	if (existenciaCaptura (*f, *c, t) == SI)
	{
		do
		{
			izq = rand() % 2;
			der = rand() % 2;
			arriba = rand() % 2;
			abajo = rand() % 2;
			*totalCap = izq + der + arriba + abajo;
		} while (verificarCaptura (*f, *c, izq, der, arriba, abajo, t) == NO);
	}
	if (izq == SI || der == SI || arriba == SI || abajo == SI)
		capturas = SI;
	else capturas = NO;
	realizarJugada (color, *f, *c, capturas, izq, der, arriba, abajo, t, cont);
}

void realizarJugada (int color, int f,int c, int realizarCap, int izq, int der, int arriba, int abajo, struct posicion t[TAM][TAM], int *cont)
/*
 * realiza una jugada
 * Argumentos:
 * ->color: indica que color realiza la jugada
 * ->f: coord. fila de la posicion de destino
 * ->c: coord. columna de la posicion de destino
 * ->realizarCap: indica si se quiere o no realizar capturas
 * ->izq: SI, para realizar una captura a la izquierda, NO, si no
 * ->der: SI, para realizar una captura a la derecha, NO, si no
 * .>arriba: SI, para realizar una captura arriba, NO, si no
 * ->abajo: SI, para realizar una captura abajo, NO, si no
 * ->t: tablero
 * ->cont: contador de espacios vacios y dados
 */
{
	int sumaCap = 0;
	if (realizarCap == SI)
	{
		if (izq == SI)
		{
			sumaCap += t[f][c - 1].valor - '0';
			*(cont + t[f][c - 1].tipoDado) -= 1;
			t[f][c - 1].valor = ' ';
			t[f][c - 1].tipoDado = VACIO;
			*(cont + VACIO) += 1;
		}
		if (der == SI)
		{
			sumaCap += t[f][c + 1].valor - '0';
			*(cont + t[f][c + 1].tipoDado) -= 1;
			t[f][c + 1].valor = ' ';
			t[f][c + 1].tipoDado = VACIO;
			*(cont + VACIO) += 1;
		}
		if (arriba == SI)
		{
			sumaCap += t[f - 1][c].valor - '0';
			*(cont + t[f - 1][c].tipoDado) -= 1;
			t[f - 1][c].valor = ' ';
			t[f - 1][c].tipoDado = VACIO;
			*(cont + VACIO) += 1;
		}
		if (abajo == SI)
		{
			sumaCap += t[f + 1][c].valor - '0';
			*(cont + t[f + 1][c].tipoDado) -= 1;
			t[f + 1][c].valor = ' ';
			t[f + 1][c].tipoDado = VACIO;
			*(cont + VACIO) += 1;
		}
		t[f][c].valor = '0' + sumaCap;
	} else t[f][c].valor = '1';
	t[f][c].tipoDado = color;
	*(cont + color) += 1;
	*(cont + VACIO) -= 1;
}

int finJuego (int *cont)
/*
 * verifica si el juego acabo
 * Argumentos:
 * -> cont: contador de espacios vacios y dados
 */
{
	if (*cont == 0)		//verifica si no hay espacios vacios
		if (*(cont + ROJO) > *(cont + VERDE))
			return ROJO;
		else return VERDE;
	else return VACIO;
}

void partidaA (struct posicion t[TAM][TAM], int *cont)
/*
 * partida en la que el usuario empieza la jugada
 * Argumentos:
 * -> t: tablero
 * -> cont: contador de espacios vacios y dados
 */
{
	int colorUsu, colorMaq;	//color usuario y maquina
	int f, c;
	int capturas;
	int ganador;
	inicializar (t, &colorUsu, &colorMaq, cont);
	mostrarTab (t, cont);
	do
	{
		if(*(cont + VACIO) != 25)	// si ya se han hecho jugadas
			printf("   -------------|Su turno|------------\n");
		else						// si aun no se han hecho jugasas
		{
			if (colorUsu == ROJO)
				printf("   Eres el dado \x1b[31mrojo\x1b[0m.\n");
			else printf("   Eres el dado \x1b[32mverde\x1b[0m.\n");
			printf("   -------|Empiezas la partida|-------\n");
		}
		jugadaUsuario (colorUsu, t, cont);
		mostrarTab (t, cont);
		if ((ganador = finJuego (cont)) == VACIO)
		{
			printf("   -------|Turno de la maquina|-------\n");
			jugadaMaquina (colorMaq, t, &f, &c, &capturas, cont);
			mostrarTab (t, cont);
			if (capturas == 0)
				printf("La maquina ha colocado un dado en la posicion (%d, %c).\n\n", f + 1, c + 'A');
			else
				printf("La maquina ha colocado un dado en la posicion (%d, %c) y ha hecho %d captura%s.\n\n", f + 1, c + 'A', capturas, capturas == 1 ? "" : "s");
			ganador = finJuego (cont);
		}
	} while (ganador == VACIO);
	mensajeFinJuego (colorUsu, ganador);
}

void partidaB (struct posicion t[TAM][TAM], int *cont)
/*
 * partida en la que la maquina empieza la jugada
 * Argumentos:
 * -> t: tablero
 * -> cont: contador de espacios vacios y dados
 */
{
	int colorUsu, colorMaq;	//color usuario y maquina
	int f, c;
	int capturas;
	int ganador;
	inicializar (t, &colorUsu, &colorMaq, cont);
	mostrarTab (t, cont);
	do
	{
		if(*(cont + VACIO) != 25) 	// si ya se han hecho jugadas
			printf("   -------------|Turno de la maquina|------------\n");
		else						// si aun no se han hecho jugasas
		{
			if (colorUsu == ROJO)
				printf("   Eres el dado \x1b[31mrojo\x1b[0m.\n");
			else printf("   Eres el dado \x1b[32mverde\x1b[0m.\n");
			printf("   -------|La maquina empiza la partida|-------\n");
		}
		jugadaMaquina (colorMaq, t, &f, &c, &capturas, cont);
		mostrarTab (t, cont);
		if (capturas == 0)
			printf("La maquina ha colocado un dado en la posicion (%d, %c).\n\n", f + 1, c + 'A');
		else
			printf("La maquina ha colocado un dado en la posicion (%d, %c) y ha hecho %d captura%s.\n\n", f + 1, c + 'A', capturas, capturas == 1 ? "" : "s");
		if ((ganador = finJuego (cont)) == VACIO)
		{
			printf("   -------------|Su turno|------------\n");
			jugadaUsuario (colorUsu, t, cont);
			mostrarTab (t, cont);
			ganador = finJuego (cont);
		}
	} while (ganador == VACIO);
	mensajeFinJuego (colorUsu, ganador);
}
