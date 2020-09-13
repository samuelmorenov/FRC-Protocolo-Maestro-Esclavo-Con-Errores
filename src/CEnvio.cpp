/**
 * Implementacion de los metodos de la clase CEnvio.
 *
 * @version 2.1
 * @author
 * Samuel Moreno Vincent<br/>
 * Santiago Rangel Colon
 *
 * Asignatura Fundamentos de Redes y Comunicaciones<br/>
 * Curso 16/17
 */

#include "CEnvio.h"
#include "Trama.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include "PuertoSerie.h"

CEnvio::CEnvio() {
	contadorCadena = 0;
	Esc = 0;
}
void CEnvio::setPuerto(HANDLE puerto_) {
	puerto = puerto_;
}
void CEnvio::pulsarTecla(char &car, bool &enviando) {
	if (!enviando) {
		if (car == '\0') {
			car = getch();
			if (car == 59)
				F1();
			if (car == 60)
				F2(car);
			if (car == 61)
				F3(enviando);
			if (car == 62)
				F4();
		} else
			noEsF(car);
	}
}
void CEnvio::F1_sinTrama() {
	cadena[contadorCadena] = '\n';
	contadorCadena++;
	cadena[contadorCadena] = '\0';
	EnviarCadena(puerto, cadena, contadorCadena);
	printf("\n ->Cadena enviada\n");
	contadorCadena = 0;
}
void CEnvio::F1() {
	cadena[contadorCadena] = '\n';
	contadorCadena++;
	int contadorInc = 0;
	char cadenaAux[255];
	while (contadorCadena > 255) {
		for (int i = 0; i < 255; i++) {
			while (escape())
				return;
			cadenaAux[i] = cadena[i+contadorInc];
		}
		cadenaAux[255] = '\0';
		trama.crearTramaD(255, cadenaAux);
		trama.enviarTramaD(puerto);


		contadorCadena = contadorCadena - 255;
		contadorInc = contadorInc + 255;

	}
	for (int i = 0; i < contadorCadena; i++) {
		while (escape())
			return;
		cadenaAux[i] = cadena[i+contadorInc];
		//cout << "i = " << i << ", cadenaAux[i] = " << cadenaAux[i] << "." << endl;

	}

	cadenaAux[contadorCadena] = '\0';
	trama.crearTramaD(contadorCadena, cadenaAux);
	trama.enviarTramaD(puerto);

//		trama.crearTramaD(contadorCadena, cadena);
//		trama.enviarTramaD(puerto);


	contadorCadena = 0;

}
void CEnvio::F2(char &car) {

	cout << "Trama de control a enviar:" << endl;
	cout << "1: Trama ENQ" << endl;
	cout << "2: Trama EOT" << endl;
	cout << "3: Trama ACK" << endl;
	cout << "4: Trama NACK" << endl;
	car = getch();
	cout << "Tecla " << car << " Pulsada" << endl;
	switch (car) {
	case 49: //Tecla pulsada 1 en caracter ascii
		trama.crearENQ();
		cout << "Creada trama control tipo ENQ" << endl;
		break;

	case 50: //Tecla pulsada 2 en caracter ascii
		trama.crearEOT();
		cout << "Creada trama control tipo EOT" << endl;
		break;

	case 51: //Tecla pulsada 3 en caracter ascii
		trama.crearACK();
		cout << "Creada trama control tipo ACK" << endl;
		break;

	case 52: //Tecla pulasada 4 en caracter ascii
		trama.crearNACK();
		cout << "Creada trama control tipo NACK" << endl;
		break;
	}
	if ((car == 49) || (car == 50) || (car == 51) || (car == 52)){ //si alguno de los caracteres pulsados el correcto
		//entonces es cuando enviamos la trama
		trama.enviarTramaC(puerto);
		cout << " ->Trama de control enviada" << endl;
	}

	else {	     //en caso contrario, mostramos por pantalla un mensaje de error
		cout << "Tecla no admitida" << endl;
	}

	//se reinicia car para que no escriba como si fuera una cadena
	if (kbhit())
		car = getch();
}
void CEnvio::F3(bool &enviando) {
	lectura.open("Frc-E.txt");
	if (lectura.is_open()) {
		cout << "Enviando fichero..." << endl;
		EnviarCaracter(puerto, '#');
		enviando = true;
	} else
		cout << "ERROR: Al abrir el archivo";
}
void CEnvio::F4(){
	CMaestroEsclavo cMaEs;
	cMaEs.setPuerto(puerto);
	cMaEs.Protocolo();
}
void CEnvio::enviarLinea(bool &enviando) {
	char linea[255];

	if (lectura.eof())
		cerrarEnvio(enviando);
	else {
		if (lectura.is_open()) {
			if ((!lectura.eof()) && !escape()) {
				lectura.read(linea, 254);
				int aux = lectura.gcount();
				if (aux > 0){
					linea[aux] = '\0';
					trama.crearTramaD(strlen(linea), linea);
					trama.enviarTramaD(puerto);
				}
			}
		} else
			cout << "ERROR: Intentando enviar archivo no abierto";
	}
}
void CEnvio::cerrarEnvio(bool &enviando) {
	lectura.close();
	EnviarCaracter(puerto, '@');
	cout << "Enviado fichero correctamente" << endl;
	enviando = false;
}
void CEnvio::noEsF(char &car) {
	if (car == 8) {	        //retroceso
		printf("\b");
		printf(" ");
		printf("\b");
		contadorCadena--;
		return;
	}
	if (car == 13) {	        //enter
		printf("\n");
		char aux = 13;
		cadena[contadorCadena] = aux;
		contadorCadena++;
		return;
	}
	if (contadorCadena < 800) {	        //cualquier tecla
		printf("%c", car); //añadido para ver que escribimos
		// if (contadorCadena == 254) cout << endl << "contador = 254" << endl;
		cadena[contadorCadena] = car;
		contadorCadena++;
	} else {
		printf("\nERROR: se ha llegado al maximo de caracteres\n");
	}

	return;
}
bool CEnvio::escape() {
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
