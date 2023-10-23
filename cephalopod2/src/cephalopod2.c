/*
 ============================================================================
 Name        : cephalopod2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cabecera2.h"

int main(void) {
	struct posicion tablero[TAM][TAM];
	int contador[3]; // contador de espacios vacios y dados
	srand(time(NULL));
	mensajeBienvenida ();
	if (rand() % 2)
		partidaA (tablero, contador);
	else
		partidaB (tablero, contador);
	return EXIT_SUCCESS;
}
