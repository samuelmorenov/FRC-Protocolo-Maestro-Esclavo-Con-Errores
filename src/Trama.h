/**
 * Definicion de los metodos de la clase Trama.
 *
 * @version 2.1
 * @author
 * Samuel Moreno Vincent<br/>
 * Santiago Rangel Colon
 *
 * Asignatura Fundamentos de Redes y Comunicaciones<br/>
 * Curso 16/17
 */

#ifndef TRAMA_H_
#define TRAMA_H_
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include "PuertoSerie.h"

class Trama {
private:
    unsigned char S;	//Sincronismo:	Valor = 22
    unsigned char D;	//Direccion:	T o R
    unsigned char C;	//Control:		//ENQ = 05
										//EOT = 04
										//ACK = 06
										//NACK = 21
    									//Datos = 02
    unsigned char N;	//Numero de trama
    unsigned char L;	//Longitud de la trama
    char Datos[255];	//Cadena de caracteres
    unsigned char BCE;	//Control de errores

public:
    Trama();
	void setS(char S);
	void setD(char D);
	void setC(char C);
	void setN(char N);
	void setL(char L);
	void setDatos(char* Datos);
	void setDato(char Dato_, int posicion);
	void setBCE(char BCE);
	unsigned char getS();
	unsigned char getD();
	unsigned char getC();
	unsigned char getN();
	int getL();
	char getDato(int posicion);
	unsigned char getBCE();
	void crearENQ();
    void crearEOT();
    void crearACK();
    void crearNACK();
    void crearTramaD(char L_, char* cadenaAux);
    void enviarTramaC(HANDLE puerto);
    void enviarTramaD(HANDLE puerto);
    void imprimirTramaC();
    void imprimirTramaD();
    void imprimirTramaDatosCompleta();
    bool esControl();
    unsigned char calcularBCE();
    bool esCorrecta();


	void crearENQ(char ToR, char NumeroTrama);
    void crearEOT(char ToR, char NumeroTrama);
    void crearACK(char ToR, char NumeroTrama);
    void crearNACK(char ToR, char NumeroTrama);
//    void crearTramaD(char L_, char* cadenaAux);
    void crearTramaDCompleta(char ToR, char NumeroTrama,char L_, char* cadenaAux);
//    unsigned char calcularBCE();
//    void enviarTramaC(HANDLE puerto);
//    void enviarTramaD(HANDLE puerto);
//    void imprimirTramaC();
//    void imprimirTramaD();
//    void imprimirTramaDatosCompleta();
    void imprimirEnvio();
    void imprimirRecibo();
    void imprimirC();
//    bool esControl();
    bool esACK();
    bool esNACK();
    bool esEOT();
    bool esENQ();


//    bool esCorrecta();
};

#endif /* TRAMA_H_ */
