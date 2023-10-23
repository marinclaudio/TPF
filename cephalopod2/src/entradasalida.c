/*
 * entradasalida.c
 *
 *  Created on: 10 oct. 2023
 *      Author: lp1-2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cabecera2.h"

void inicializar (struct posicion t[TAM][TAM], int *colorUsu, int *colorMaq, int *cont)
/*
 * inicializa el tablero el color de usuario, el color de la maquina y el contador
 * Argumentos:
 * -> t: tablero
 * -> colorUsu: color del usuario
 * -> colorMaq: color maquina
 * -> cont: contador dados y espacios vacios
 */
{
	srand(time(NULL));
	int i, j;
	//inicializacion del tablero
	for (i = 0; i < TAM; i++)
	{
		for (j = 0; j < TAM; j++){
			t[i][j].tipoDado = VACIO;
			t[i][j].valor = ' ';
		}
	}
	// se inicializa colorUsu y colorMaq
	*colorUsu = rand() % 2 + 1;
	if (*colorUsu == ROJO)
		*colorMaq = VERDE;
	else *colorMaq = ROJO;
	// inicializacion del contador
	*(cont + VACIO)= 25;	//espacios vacios
	*(cont + ROJO) = 0;		//dados rojos
	*(cont + VERDE) = 0;	//dados verdes
}

void mensajeBienvenida ()
/*
 * Muestra un mensaje de bienvenida y algunas idicaciones de como ingresar las jugadas
 */
{
	printf ("\n\t      Bienvenido al juego:\n\n");
	printf ("\t    ╔═════════════════════╗\n\t    ║                     ║\n\t    ║ C - P H A L O P O D ║\n\t    ║                     ║\n\t    ╚═════════════════════╝\n");
	printf ("\n   -----------|Como jugar?|-----------\n");
	printf ("   1) Para seleccionar una casilla debes ingresar el numero de\n");
	printf ("   fila seguido de la letra de la columna, en ese orden y sin\n");
	printf ("   espacios, correspondiente a la casilla.\n\n");
	printf ("   2) En caso de que existan capturas para la posicion seleccionada\n");
	printf ("   se te preguntara si deseas realizarlas.\n\n");
	printf ("   3) Para ingresar las capturas, las mismas se indican como:\n");
	printf ("    I o i: para capturar el dado de la izquierda de la posicion seleccionada.\n");
	printf ("    D o d: para capturar el dado de la derecha.\n");
	printf ("    A o a: para capturar el dado de arriba.\n");
	printf ("    B o b: para capturar el dado de abajo.\n");
	printf ("   Para realizar varias capturas se ingresan las posiciones relativas de los dados\n");
	printf ("   a capturar en cualquier orden y sin espacios. Por ejemplo: para capturar los dados\n");
	printf ("   de arriba y de la izquierda se podria ingresar como: \"ai\".\n\n");
	printf ("   Para iniciar la partida presione ENTER:\n");
	while (getchar() != '\n');
	return;
}

void mostrarTab (struct posicion t[TAM][TAM], int *cont)
/*
 * imprime el tablero y la cantidad de dados en el
 * Argumentos:
 * -> t: tablero
 * -> c: contador de vacios, dados rojos y dados verdes
 */

{
	int i, j;
	// se imprime el tablero
	printf("\t    A   B   C   D   E\n\t  ╔═══╦═══╦═══╦═══╦═══╗\n");
	for (i = 0; i < TAM; i++){
		printf("\t %d║", i + 1);
		for(j = 0; j < TAM; j++){
			switch (t[i][j].tipoDado)
			{
			case ROJO:
				printf("\x1b[31m %c \x1b[0m║", t[i][j].valor);
				break;
			case VERDE:
				printf("\x1b[32m %c \x1b[0m║", t[i][j].valor);
				break;
			default:
				printf(" %c ║", t[i][j].valor);
				break;
			}
		}
		if (i < TAM - 1)
			printf("\n\t  ╠═══╬═══╬═══╬═══╬═══╣\n");
		else
			printf("\n\t  ╚═══╩═══╩═══╩═══╩═══╝\n");
	}
	// se imprime la cantidad de dados rojos y verdes
	printf("\t\t  Dados\n\t\x1b[31mRojos\x1b[0m: %d\t\x1b[32mVerdes\x1b[0m: %d\n\n", *(cont + ROJO), *(cont + VERDE));
}

void jugadaUsuario (int color, struct posicion t[TAM][TAM], int *cont)
/*
 * Pide al usuario ingresar una jugada y la realiza
 * Argumentos:
 * -> color: color del usuario
 * -> t: tablero
 * -> cont: contador de espacios vacios y dados
 */
{
	int i;
	int band1, band2, realizarCap;
	int f;	// fila
	int c;	// columna
	int izq, der, arriba, abajo;
	char posi[3];
	char capturas[5];
	do
	{
		band1 = 1;
		do
		{
			printf("   Ingrese la posicion de destino: ");
			band2 = scanf("%2s", posi);
			while (getchar() != '\n');
		} while (band2 != 1);
		f = *posi - '1';		//se determina el valor entero de la coord. fila
		// se determina el valor entero de la coord. columna
		if (*(posi + 1) >= 'A' && *(posi + 1) <= 'E')
			c = *(posi + 1) - 'A';	// si es mayuscula
		else
			c = *(posi + 1) - 'a';	//si es minuscula
		switch (verificarSeleccion(f, c, t))
		{
		case 1:
			printf("   La posicion ingresada esta ocupada. Intente de nuevo.\n");
			band1 = 0;
			break;
		case 2:
			printf("   La posicion ingresada no es valida. Intente de nuevo.\n");
			band1 = 0;
			break;
		}
		if (band1 == 1)
		{
			// se verifica si existe capturas para la posicion ingreada
			if (existenciaCaptura(f, c, t) == SI)
			{
				do
				{
					printf("   Desea realizar capturas? (Ingrese 1 para si o 2 para no): ");
					band2 = scanf("%d", &realizarCap);
					while (getchar() != '\n');
				} while (band2 != 1);
				if (realizarCap == SI)
				{
					do
					{
						printf("   Ingrese las capturas a realizar (i: izquierda, d: derecha, a: arriba, b: abajo).");
						band2 = scanf("%4s", capturas);
						while (getchar() != '\n');
					} while (band2 != 1);
					izq = der = arriba = abajo = NO;
					for (i = 0; *(capturas + i) != '\0' && band1 == 1; i++)
					{
						switch (*(capturas + i))
						{
						case 'I': case 'i':
							// se verifica si I o i no se hayan metido mas de una vez
							if (izq == NO)
								izq = SI;
							else band1 = 0;
							break;
						case 'D': case 'd':
							// se verifica si D o d no se hayan metido mas de una vez
							if (der == NO)
								der = SI;
							else band1 = 0;
							break;
						case 'A': case 'a':
							// se verifica si A o a no se hayan metido mas de una vez
							if (arriba == NO)
								arriba = SI;
							else band1 = 0;
							break;
						case 'B': case 'b':
							// se verifica si B o b no se hayan metido mas de una vez
							if (abajo == NO)
								abajo = SI;
							else band1 = 0;
							break;
						default:
							// caracter no valido
							band1 = 0;
							break;
						}
					}
					if (band1 == 1)
					{
						if (verificarCaptura (f, c, izq, der, arriba, abajo, t) == NO)
						{
							printf("   No es posible realizar las capturas ingresadas.\n");
							band1 = 0;
						}
					} else
						printf("   Las capturas ingresadas no son validas.\n");
				} else realizarCap = NO;
			}
		}
	}while (band1 == 0);
	realizarJugada (color, f, c, realizarCap, izq, der, arriba, abajo, t, cont);
}

void mensajeFinJuego (int usuario, int ganador)
/*
 * Imprime un mensaje al final del juego
 * Argumentos:
 * -> usuario: color del usuario
 * -> ganador: color del ganador
 */
{
	if(usuario == ganador)
		printf("\t    ╔═══════════════════╗\n\t    ║ ¡¡¡Felicidades!!! ║\n\t    ║    Has ganado.    ║\n\t    ╚═══════════════════╝\n");
	else
		printf("\t    ╔═══════════════════╗\n\t    ║     Perdiste.     ║\n\t    ╚═══════════════════╝\n");
}
