/**
 * Implementacion de los metodos de la clase CRecibo.
 *
 * @version 2.1
 * @author
 * Samuel Moreno Vincent
 * Santiago Rangel Colon
 *
 * Asignatura Fundamentos de Redes y Comunicaciones<br/>
 * Curso 16/17
 */

#include "CRecibo.h"
#include "Trama.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include "PuertoSerie.h"

CRecibo::CRecibo() {
	nCampo = 1;
	recibiendoTrama = false;
	recibiendoTramaDatos = false;
	contadorTramaDatos = 0;
	Esc = 0;
}

void CRecibo::setPuerto(HANDLE puerto_) {
	puerto = puerto_;

}
void CRecibo::recibir(char car) {
	if (recibiendoTrama || car == 22) {
		recibirTrama(car);
	} else {
		if (!recibiendoFichero) { //NO recibiendo fichero:
			if (car == '#') {
				abrirArchivo();
			} else imprimirCaracter(car);

		} else { //Recibiendo fichero:
			if (car == '@')
				cerrarArchivo();
			else imprimirCaracter(car);
		}
	}
}
void CRecibo::imprimirCaracter(char car) {
	if (car == 13)
		printf("\n");
	else
		printf("%c", car);
}
void CRecibo::recibirTrama(char car) {

	switch (this->nCampo) {
	case 1: //Sincronismo:	Valor = 22
		if (car == 22) {
			recibiendoTrama = true;
			trama.setS(car);
			nCampo++;
		}
		break;
	case 2: //Direccion:	T o R
		trama.setD(car);
		nCampo++;
		break;
	case 3: //Control: ENQ = 05; EOT = 04; ACK = 06; NACK = 21; Datos = 02
		trama.setC(car);
		if (car == 02) {
			recibiendoTramaDatos = true;
		}
		nCampo++;
		break;
	case 4: //Numero de trama
		trama.setN(car);
		if (!recibiendoTramaDatos) {
			procesarTramaControl();
			nCampo = 1;
			recibiendoTrama = false;
			recibiendoTramaDatos = false;
		} else
			nCampo++;
		break;

	case 5: //Longitud de la trama
		unsigned char auxCar;
		auxCar = car;
		trama.setL(auxCar);
		contadorTramaDatos = 0;
		nCampo++;
		break;
	case 6: //Cadena de caracteres
		trama.setDato(car, contadorTramaDatos);
		contadorTramaDatos++;
		if (contadorTramaDatos == trama.getL()) {
			trama.setDato('\0', contadorTramaDatos);
			contadorTramaDatos=0;
			nCampo++;
		}
		break;

	case 7: //Control de errores	Valor = 1
		//cout << "Entramos en el bce" << endl;
		trama.setBCE(car);
		procesarTramaDatos();
		nCampo = 1;
		recibiendoTrama = false;
		recibiendoTramaDatos = false;
	}
}

void CRecibo::procesarTramaControl() {
	cout << " <-Recibida ";
	trama.imprimirTramaC();
	cout << endl;
	nCampo = 1;
	recibiendoTrama = false;
}
void CRecibo::procesarTramaDatos() {
	if (!recibiendoFichero)
		trama.imprimirTramaD();
	else {
		if (escritura.is_open()) {
			for (int i = 0; i < trama.getL(); i++) {
				char aux = trama.getDato(i);
				escritura.put(aux);
			}
		} else
			cout << "ERROR en escritura." << endl;

	}
}
void CRecibo::abrirArchivo() {
	cout << "Recibiendo fichero..." << endl;
	recibiendoFichero = true;
	escritura.open("Frc-R.txt"); //TODO
}
void CRecibo::cerrarArchivo() {
	cout << "Fichero recibido." << endl;
	recibiendoFichero = false;
	escritura.close();
}
bool CRecibo::escape() {
	if (kbhit()) {
		char escape = getch();
		if (escape == 27) {
			cout << endl
					<< "Detectada interrupcion escape, finalizado el envio de mensajes"
					<< endl;
			return true;
		}
	}
	return false;
}
