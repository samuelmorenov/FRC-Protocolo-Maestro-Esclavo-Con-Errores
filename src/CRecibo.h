/**
 * Definicion de los metodos de la clase CRecibo.
 *
 * @version 2.1
 * @author
 * Samuel Moreno Vincent<br/>
 * Santiago Rangel Colon
 *
 * Asignatura Fundamentos de Redes y Comunicaciones<br/>
 * Curso 16/17
 */

#ifndef CRECIBO_H_
#define CRECIBO_H_
#include "Trama.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include "PuertoSerie.h"

class CRecibo {
private:
	int nCampo;
	HANDLE puerto;
	Trama trama;
	bool recibiendoTrama;
	bool recibiendoTramaDatos;
	bool recibiendoFichero;
	int contadorTramaDatos;
	//char DatosAux[255];
	bool Esc;
	ofstream escritura;
public:
	CRecibo();
	void setPuerto(HANDLE puerto_);
	void recibir(char car);
	void recibirCaracter(char car);
	void imprimirCaracter(char car);
	void recibirTrama(char car);
	void procesarTramaControl();
	void procesarTramaDatos();
	void abrirArchivo();
	void cerrarArchivo();
	bool escape();
};

#endif /* CRECIBO_H_ */
