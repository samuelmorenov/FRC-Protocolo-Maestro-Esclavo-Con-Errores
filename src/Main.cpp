/**
 * Definicion de la clase Main.
 *
 * @version 2.1
 * @author
 * Samuel Moreno Vincent<br/>
 * Santiago Rangel Colon
 *
 * Asignatura Fundamentos de Redes y Comunicaciones<br/>
 * Curso 16/17
 */

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include "PuertoSerie.h"
#include "Trama.h"
#include "CEnvio.h"
#include "CRecibo.h"

using namespace std;

HANDLE PuertoCOM; //esta declarado en windows.h

bool abrirConfig() {
	// Parámetros necesarios al llamar a AbrirPuerto:
	// - Nombre del puerto a abrir ("COM1", "COM2", "COM3", ...).
	// - Velocidad (1200, 1400, 4800, 9600, 19200, 38400, 57600, 115200).
	// - Número de bits en cada byte enviado o recibido (4, 5, 6, 7, 8).
	// - Paridad (0=sin paridad, 1=impar, 2=par, 3=marca, 4=espacio).
	// - Bits de stop (0=1 bit, 1=1.5 bits, 2=2 bits)

	printf("Seleccionar el puerto a utilizar:\n");
	printf("1. COM1\n");
	printf("2. COM2\n");
	printf("3. COM3\n");
	printf("4. COM4\n> ");
	char car = 0;
	LPCSTR NombrePuerto = "COM1";
	DWORD Velocidad = 9600;
	BYTE NumBitsXByte = 8;
	BYTE Paridad = 0;
	BYTE BitsParada = 0;
	string mostrartipoParidad="sin paridad";
	string mostrarBitsParada="1";
	string mostrarPuerto="";

	bool leido = false;
	while (car != 27 && !leido) { //NombrePuerto
		if (kbhit()) {
			car = getch();
			if (car != 27) {
				printf("%c", car);
				printf("\n");
				switch (car) {
				case '1':
					NombrePuerto = "COM1";
					mostrarPuerto = "COM1";
					leido = true;
					break;
				case '2':
					NombrePuerto = "COM2";
					mostrarPuerto = "COM2";
					leido = true;
					break;
				case '3':
					NombrePuerto = "COM3";
					mostrarPuerto = "COM3";
					leido = true;
					break;
				case '4':
					NombrePuerto = "COM4";
					mostrarPuerto = "COM4";
					leido = true;
					break;
				default:
					printf("Numero incorrecto\n> ");

				}
			}
		}
	}

	printf(
			"Seleccionar los parametros de configuracion:\n1. Configuracion por defecto (9600, 8, sin paridad, 1 bit parada)\n2. Configuracion personalizada\n> ");

	bool porDefecto = true;
	leido = false;
	while (car != 27 && !leido) { //parametros de configuracion
		if (kbhit()) {
			car = getch();
			if (car != 27) {
				printf("%c", car);
				printf("\n");
				switch (car) {
				case '1':
					leido = true;
					break;
				case '2':
					porDefecto = false;
					leido = true;
					break;
				default:
					printf("Numero incorrecto\n> ");

				}
			}
		}
	}

	if (car == 27)
		return false;
	if (!porDefecto) {
		leido = false;
		printf("Bits por segundo:\n1. 1400\n2. 4800\n3. 9600\n4. 19200\n> ");
		while (car != 27 && !leido) { //Velocidad
			if (kbhit()) {
				car = getch();
				if (car != 27) {
					printf("%c", car);
					printf("\n");
					switch (car) {
					case '1':
						Velocidad = 1400;
						leido = true;
						break;
					case '2':
						Velocidad = 4800;
						leido = true;
						break;
					case '3':
						Velocidad = 9600;
						leido = true;
						break;
					case '4':
						Velocidad = 19200;
						leido = true;
						break;
					default:
						printf("Numero incorrecto\n> ");
					}
				}
			}
		}

		leido = false;
		printf("Bits de datos:\n1. 5\n2. 6\n3. 7\n4. 8\n>");
		while (car != 27 && !leido) { //NumBitsXByte
			if (kbhit()) {
				car = getch();
				if (car != 27) {
					printf("%c", car);
					printf("\n");
					switch (car) {
					case '1':
						NumBitsXByte = 5;
						leido = true;
						break;
					case '2':
						NumBitsXByte = 6;
						leido = true;
						break;
					case '3':
						NumBitsXByte = 7;
						leido = true;
						break;
					case '4':
						NumBitsXByte = 8;
						leido = true;
						break;
					default:
						printf("Numero incorrecto\n> ");
					}
				}
			}
		}

		leido = false;
		printf("Paridad:\n1. Sin paridad\n2. Impar\n3. Par\n4. Marca\n5. Espacio\n> ");
		while (car != 27 && !leido) { //Paridad
			if (kbhit()) {
				car = getch();
				if (car != 27) {
					printf("%c", car);
					printf("\n");
					switch (car) {
					case '1':
						Paridad = 0;
						mostrartipoParidad = "Sin Paridad";
						leido = true;
						break;
					case '2':
						Paridad = 1;
						mostrartipoParidad = "Impar";
						leido = true;
						break;
					case '3':
						Paridad = 2;
						mostrartipoParidad = "Par";
						leido = true;
						break;
					case '4':
						Paridad = 3;
						mostrartipoParidad = "Marca";
						leido = true;
						break;
					case '5':
						Paridad = 4;
						mostrartipoParidad = "Espacio";
						leido = true;
						break;
					default:
						printf("Numero incorrecto\n> ");
					}
				}
			}
		}

		leido = false;
		printf("Bits de parada:\n1. 1\n2. 1,5\n3. 2\n> ");
		while (car != 27 && !leido) {
			if (kbhit()) {
				car = getch();
				if (car != 27) {
					printf("%c", car);
					printf("\n");
					switch (car) {
					case '1':
						BitsParada = 0;
						mostrarBitsParada="1";
						leido = true;
						break;
					case '2':
						BitsParada = 1;
						mostrarBitsParada="1.5";
						leido = true;
						break;
					case '3':
						BitsParada = 2;
						mostrarBitsParada="2";
						leido = true;
						break;
					default:
						printf("Numero incorrecto\n> ");
					}
				}
			}
		}
	}
	cout << "Se configurara el puerto con: " + mostrarPuerto;
	printf(" - %d - %d - ",Velocidad,NumBitsXByte);
	cout << mostrartipoParidad + " - " + mostrarBitsParada + " bits de parada" << endl;

	PuertoCOM = AbrirPuerto(NombrePuerto, Velocidad, NumBitsXByte, Paridad, BitsParada);
	if (PuertoCOM == NULL) {
		printf("Error al abrir el puerto\n");
		getch();
		return (false);
	} else { //añadido
		printf("Puerto abierto\n");
		return (true);
	}
	return (false);

}

int main() {
	char car = 0;
	bool eFichero = false;

	if (!abrirConfig())
		return (1);

    CRecibo Recibo;// = new CRecibo();
    Recibo.setPuerto(PuertoCOM);
    CEnvio Envio;//  = new CEnvio();
    Envio.setPuerto(PuertoCOM);


// Lectura y escritura simultánea de caracteres:

	while (car != 27) {

			car = RecibirCaracter(PuertoCOM); //libreria puerto serie
			if (eFichero)
				Envio.enviarLinea(eFichero);
			if (car)
				Recibo.recibir(car);
			if (kbhit()) { //es una funcion que nos detecta la pulsacion de una tecla
				car = getch(); //leer tecla pulsada
				if (car != 27)
					Envio.pulsarTecla(car, eFichero);
			}

	}

// Para cerrar el puerto:
	CerrarPuerto(PuertoCOM);
	printf("Puerto cerrado\n");
	//while (true);

	return 0;
}
