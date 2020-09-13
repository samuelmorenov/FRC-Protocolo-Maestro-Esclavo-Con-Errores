/*
 * Definicion de los metodos de la clase Control Maestro Esclavo
 *
 * @version 2.1
 * @author
 * Samuel Moreno Vincent<br/>
 * Santiago Rangel Colon
 *
 * Asignatura Fundamentos de Redes y Comunicaciones<br/>
 * Curso 16/17
 */

#ifndef CMAESTROESCLAVO_H_
#define CMAESTROESCLAVO_H_
#include "Trama.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include "PuertoSerie.h"
#include "CRecibo.h"
using namespace std;


class CMaestroEsclavo {
private:
	HANDLE puerto;
	bool maestro;
	bool esclavo;
	bool sondeo;
	bool seleccion;
	char numtrama;
	Trama trama;
	ifstream lectura;
	ofstream escritura;
	bool escapePulsado;
	char car;
	bool pulsadoF5;

public:
	CMaestroEsclavo();
	void setPuerto(HANDLE puerto_);
	bool Protocolo();
	void iniciarProtocolo();
	void maestroSeleccion();
	void maestroSondeo();
	void esclavoSeleccion();
	void esclavoSondeo();
	void enviarArchivo(char ToR);
	void enviarCar(char envioCar);
	void recibirArchivo(char ToR);
	void recibirTrama();
	char calcularBCE();
	void cambiarNumTrama();
	bool pulsarF5();
	bool escape();



};

#endif /* CMAESTROESCLAVO_H_ */
