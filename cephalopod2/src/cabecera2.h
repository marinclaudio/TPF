/*
 * cabecera2.h
 *
 *  Created on: 10 oct. 2023
 *      Author: lp1-2023
 */

#ifndef CABECERA2_H_
#define CABECERA2_H_

#define TAM 5		//tamaño tablero
#define VACIO 0
#define ROJO 1
#define VERDE 2
#define SI 1
#define NO 0

struct posicion {
	int tipoDado;
	char valor;
};

//---------------....entradasalida-------------------------
void inicializar (struct posicion t[TAM][TAM], int *colorUsu, int *colorMaq, int *cont);
void mensajeBienvenida ();
void mostrarTab (struct posicion t[TAM][TAM], int *cont);
void jugadaUsuario (int color, struct posicion t[TAM][TAM], int *cont);
void mensajeFinJuego (int usuario, int ganador);

//--------------........jugada-----------------------------
int verificarSeleccion (int f, int c, struct posicion t[TAM][TAM]);
int existenciaCaptura (int f, int c, struct posicion t[TAM][TAM]);
int verificarCaptura (int f, int c, int izq, int der, int arriba, int abajo, struct posicion t[TAM][TAM]);
void jugadaMaquina (int color, struct posicion t[TAM][TAM], int *f, int *c, int *totalCap, int *cont);
void realizarJugada (int color, int f,int c, int realizarCap, int izq, int der, int arriba, int abajo, struct posicion t[TAM][TAM], int *cont);
int finJuego (int *cont);
void partidaA (struct posicion t[TAM][TAM], int *cont);
void partidaB (struct posicion t[TAM][TAM], int *cont);

#endif /* CABECERA2_H_ */
