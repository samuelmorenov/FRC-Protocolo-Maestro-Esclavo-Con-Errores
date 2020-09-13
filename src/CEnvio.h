/**
 * Definicion de los metodos de la clase CEnvio.
 *
 * @version 2.1
 * @author
 * Samuel Moreno Vincent<br/>
 * Santiago Rangel Colon
 *
 * Asignatura Fundamentos de Redes y Comunicaciones<br/>
 * Curso 16/17
 */

#ifndef CENVIO_H_
#define CENVIO_H_
#include "Trama.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include "PuertoSerie.h"
#include "CMaestroEsclavo.h"

using namespace std;


class CEnvio {
	private:
	int contadorCadena;
	char cadena [802]; // /n /0
	HANDLE puerto;
	Trama trama;
	bool Esc;
	ifstream lectura;
public:
	CEnvio();
	void setPuerto(HANDLE puerto_);
	void pulsarTecla(char &car, bool &enviando);
	void pulsarTecla(char &car);
	void F1_sinTrama();
	void F1();
	void F2(char &car);
	void F3(bool &enviando);
	void F4();
	void enviarLinea(bool &enviando);
	void cerrarEnvio(bool &enviando);
	void noEsF(char &car);
	bool escape();
};

#endif /* CENVIO_H_ */
