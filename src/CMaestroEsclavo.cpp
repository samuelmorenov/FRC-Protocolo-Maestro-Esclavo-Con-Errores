/*
 * Implementacion de los metodos de la clase  Control Maestro Esclavo
 *
 * @version 2.1
 * @author
 * Samuel Moreno Vincent<br/>
 * Santiago Rangel Colon
 *
 * Asignatura Fundamentos de Redes y Comunicaciones<br/>
 * Curso 16/17
 */

#include "CMaestroEsclavo.h"

CMaestroEsclavo::CMaestroEsclavo() {

}
void CMaestroEsclavo::setPuerto(HANDLE puerto_) {
	puerto = puerto_;
}
bool CMaestroEsclavo::Protocolo() {
	iniciarProtocolo();
	return false;
}
void CMaestroEsclavo::iniciarProtocolo() {
	numtrama = 0;
	maestro = false;
	esclavo = false;
	sondeo = false;
	seleccion = false;
	escapePulsado = false;
	pulsadoF5 = false;
	cout << "Elija una de las posibles opciones: " << endl;
	cout << "1: Estacion Maestra" << endl;
	cout << "2: Estacion esclava" << endl;
	int car = getch();
	switch (car) {
	case 49: //Pulsada tecla 1
		cout << "Elegida estacion como maestra" << endl;
		maestro = true;
		cout << "Elija una de las posibles opciones: " << endl;
		cout << "1: Seleccion" << endl;
		cout << "2: Sondeo" << endl;
		car = getch();
		switch (car) {
		case 49: //Pulsada tecla 1
			cout << "Elegido envio por seleccion" << endl << endl;
			seleccion = true;
			maestroSeleccion();
			break;
		case 50: //Pulsada tecla 2
			cout << "Elegido envio por sondeo" << endl << endl;
			sondeo = true;
			maestroSondeo();
			break;
		}
		if ((car != 49) && (car != 50)) {
			cout << "tecla incorrecta pulsada" << endl << endl;
		}
		break;

	case 50: //Pulsada tecla 2
		cout << "Elegida estacion como esclava" << endl << endl;
		esclavo = true;
		recibirTrama();
		char ToR = trama.getD();
		if (ToR == 'T')
			esclavoSondeo();
		if (ToR == 'R')
			esclavoSeleccion();
		break;
	}
	if ((car != 49) && (car != 50)) {
		cout << "tecla incorrecta pulsada" << endl;
	}
}
void CMaestroEsclavo::maestroSeleccion() {

	/*ESTABLECIMIENTO:
	 E: R ENQ 0
	 R:	R ACK 0
	 */
	numtrama = '0';
	trama.crearENQ('R', numtrama);
	trama.enviarTramaC(puerto);
	trama.imprimirEnvio();
	recibirTrama();
	if(!trama.esACK()){
		cout << "Error, la Trama recibida no es ACK" << endl;
		return;
	}

	//TRANSFERENCIA:
	cout << endl;
	enviarArchivo('R');
	cout << endl;

	/*LIBERACION:
	 E: R EOT 0
	 R:	R ACK 0
	 */
	numtrama = '0';
	trama.crearEOT('R', numtrama);
	trama.enviarTramaC(puerto);
	trama.imprimirEnvio();
	recibirTrama();
	if(!trama.esACK()){
		cout << "Error, la Trama recibida no es ACK" << endl;
		return;
	}
}
void CMaestroEsclavo::maestroSondeo() {
	/*ESTABLECIMIENTO:
	 E: T ENQ 0
	 R: T ACK 0
	 */
	numtrama = '0';
	trama.crearENQ('T', numtrama);
	trama.enviarTramaC(puerto);
	trama.imprimirEnvio();
	recibirTrama();
	if(!trama.esACK()){
		cout << "Error, la Trama recibida no es ACK" << endl;
		return;
	}

	//TRANSFERENCIA:
	cout << endl;
	recibirArchivo('T');
	cout << endl;

	//LIBERACION:
	recibirTrama();
	if(!trama.esEOT()){
		cout << "Error, la Trama recibida no es EOT" << endl;
		return;
	}

	numtrama = trama.getN();

	bool finConexion = false;
	while (!finConexion && !escape()) {
		cout << "Desea terminar la transmision? 1: Si, 2: No" << endl;
		car = getch();
		switch (car) {
		case 49: //Pulsada tecla 1
			finConexion = true;
			trama.crearACK('T', numtrama);
			trama.enviarTramaC(puerto);
			trama.imprimirEnvio();
			return;
			break;
		case 50: //Pulsada tecla 2
			trama.crearNACK('T', numtrama);
			trama.enviarTramaC(puerto);
			trama.imprimirEnvio();
			break;

		}
		if ((car != 49) && (car != 50)) {
			cout << "Tecla incorrecta pulsada" << endl << endl;
		} else {
			recibirTrama();
			if(!trama.esEOT()){
				cout << "Error, la Trama recibida no es EOT" << endl;
				return;
			}
			numtrama = trama.getN();
		}
	}
}

void CMaestroEsclavo::esclavoSeleccion() {
	/*ESTABLECIMIENTO:
	 Recibo: 	R, ENQ, 0
	 Envio:		R, ACK, 0
	 */
	numtrama = trama.getN();
	trama.crearACK('R', numtrama);
	trama.enviarTramaC(puerto);
	trama.imprimirEnvio();

	//TRANSFERENCIA:
	cout << endl;
	recibirArchivo('R');
	cout << endl;

	/*LIBERACION:
	 R: R EOT 0
	 E:	R ACK 0
	 */
	numtrama = '0';
	recibirTrama();
	if(!trama.esEOT()){
		cout << "Error, la Trama recibida no es EOT" << endl;
		return;
	}
	numtrama = trama.getN();
	trama.crearACK('R', numtrama);
	trama.enviarTramaC(puerto);
	trama.imprimirEnvio();
}

void CMaestroEsclavo::esclavoSondeo() {
	/*ESTABLECIMIENTO:
	 R: T ENQ 0
	 E: T ACK 0
	 */
	numtrama = trama.getN();
	trama.crearACK('T', numtrama);
	trama.enviarTramaC(puerto);
	trama.imprimirEnvio();

	//TRANSFERENCIA:
	cout << endl;
	enviarArchivo('T');
	cout << endl;

	//LIBERACION:
	numtrama = '0';
	bool finConexion = false;
	while (!finConexion && !escape()) {
		trama.crearEOT('T', numtrama);
		trama.enviarTramaC(puerto);
		trama.imprimirEnvio();

		recibirTrama();
		if (trama.esACK()){
			finConexion = true;
		} else 	if(!trama.esNACK()){
			cout << "Error, la Trama recibida no es NACK ni ACK" << endl;
			return;
		}
		cambiarNumTrama();
	}

}

void CMaestroEsclavo::enviarCar(char envioCar){
	EnviarCaracter(puerto, envioCar);
	//cout << "Enviado: " << envioCar << endl;
		bool carRecibido = false;
		while(!carRecibido && !escape()){
			char auxCar = RecibirCaracter(puerto);
			if(!auxCar){
				EnviarCaracter(puerto, envioCar);
			}
			if (auxCar == '#'){
				carRecibido = true;
			}
		}
}
void CMaestroEsclavo::enviarArchivo(char ToR) {
	//Abre fichero
	//Envia '#'
	/* Bucle:
	 Si fichero no vacio: Enviar trama datos
	 Recibe trama y la imprime
	 */
	//envia '@'
	/*
	 E: R STX 0 1 1
	 R: R ACK 0
	 E: R STX 1 1 1
	 R: R ACK 1
	 E: R STX 0 1 1
	 R: R ACK 0
	 */
	numtrama = '0';
	lectura.open("Frc-E.txt");
	if (!lectura.is_open()) {
		cout << "ERROR: Al abrir el archivo" << endl;
		enviarCar('@');
		return;
	}
	enviarCar('#');
	bool finEnvio = false;
	while (!finEnvio && !escape()) {
		//ENVIO:
		if (!lectura.eof()) {
			char linea[255];
			lectura.read(linea, 254);
			int aux = lectura.gcount();
			if (aux > 0){
				linea[aux] = '\0';
				trama.crearTramaDCompleta(ToR, numtrama, strlen(linea), linea);
				if (pulsarF5()) {
					trama.setDato('ç', 0);
					cout << "Error introducido" << endl;
					pulsadoF5 = false;
				}
				trama.enviarTramaD(puerto);
				trama.imprimirEnvio();

				//CONFIRMACION:
				recibirTrama();
				if (trama.esNACK()) {
					trama.crearTramaDCompleta(ToR, numtrama, strlen(linea), linea);
					trama.enviarTramaD(puerto);
					trama.imprimirEnvio();
					recibirTrama();
					if(!trama.esACK()){
						cout << "Error, la Trama recibida no es ACK" << endl;
						return;
					}
				} else if(!trama.esACK()){
					cout << "Error, no es ACK" << endl;
					finEnvio = true;
				}
			}
			if (lectura.eof()) {
				lectura.close();
				finEnvio = true;
				EnviarCaracter(puerto, '@');
			} else {
				cambiarNumTrama();
			}
		}
		else finEnvio=true;

	}
}
void CMaestroEsclavo::recibirArchivo(char ToR) {
	//Recibe '#'
	//Abre fichero
	/*BUCLE:
	 Llama a recibir
	 Si no es trama de datos, cierra fichero y devuelve true
	 Copia el contenido de la trama en el fichero
	 Envioa una ACK
	 */
	//Recibe '@'
	/*
	 R: R STX 0 1 1
	 E: R ACK 0
	 R: R STX 1 1 1
	 E: R ACK 1
	 R: R STX 0 1 1
	 E: R ACK 0
	 */
	bool dolarRecibido = false;
	bool arrobaRecibida = false;
	//Recibir #
	while (!dolarRecibido && !escape()) {
		char car = RecibirCaracter(puerto);
		if (car == '#'){
			dolarRecibido = true;
			EnviarCaracter(puerto, '#');
		}
		if (car == '@'){
			dolarRecibido = true;
			escritura.close();
			return;
		}
	}
	escritura.open("Frc-R.txt");
	if (escritura.is_open()) {
		while (!arrobaRecibida && !escape()) {
			//RECEPCION:
			while (!car && !escape()){
				car = RecibirCaracter(puerto);
			}
			if (car == '@') {
				dolarRecibido = true;
				escritura.close();
				return;
			}

			recibirTrama();

			//CONFIRMACION/NEGACION
			numtrama = trama.getN();
			if (trama.esCorrecta() && !trama.esControl()) {
				for (int i = 0; i < trama.getL(); i++) {
					char aux = trama.getDato(i);
					escritura.put(aux);
				}
				trama.crearACK(ToR, numtrama);
				trama.enviarTramaC(puerto);
				trama.imprimirEnvio();

				//FIN?
				while (!car && !escape()){
					car = RecibirCaracter(puerto);
				}
				if (car == '@') {
					dolarRecibido = true;
					escritura.close();
					return;
				}
			} else {
				if(!trama.esControl()){
				cout << "BCE recibido: " << int(trama.getBCE())
						<< ", BCE calculado: " << int(trama.calcularBCE())
						<< endl;
				trama.crearNACK(ToR, numtrama);
				trama.enviarTramaC(puerto);
				trama.imprimirEnvio();
				}
			}


		}
	} else {
		cout << "ERROR en escritura." << endl;
		return;
	}
	escritura.close();
}
void CMaestroEsclavo::recibirTrama() {
	//Espera hasta recibir una trama completa
	//Imprime trama obtenida
	//Devuelve true si no es NACK
	bool recibiendoTrama = true;
	int nCampo = 1;
	bool recibiendoTramaDatos = false;
	int contadorTramaDatos;
	while (recibiendoTrama == true && !escape()) {
		if (car) {
			switch (nCampo) {
			case 1: //Sincronismo:	Valor = 22
				if (car == 22) {
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
					contadorTramaDatos = 0;
					nCampo++;
				}
				break;

			case 7: //Control de errores	Valor = 1
				trama.setBCE(car);
				nCampo = 1;
				recibiendoTrama = false;
				recibiendoTramaDatos = false;
			}
		}
		car = RecibirCaracter(puerto); //libreria puerto serie
	}
	trama.imprimirRecibo();
}
void CMaestroEsclavo::cambiarNumTrama() {
	if (this->numtrama == '0') {
		this->numtrama = '1';
	} else
		this->numtrama = '0';
}
bool CMaestroEsclavo::pulsarF5() {
	if (kbhit()) {
		char carAux = getch();
		if (carAux == '\0') {
			carAux = getch();
			if (carAux == 63) {
				cout << "F5 Pulsado" << endl;
				pulsadoF5 = true;
			}
		}
		if (carAux == 63) {
			pulsadoF5 = true;
		}
	}
	return pulsadoF5;
}
bool CMaestroEsclavo::escape() {
	if (escapePulsado) {
		cout << "Saliendo por escape" << endl;
		return true;
	}
	if (kbhit()) {
		char escape = getch();
		if (escape == 27) {
			cout << endl
					<< "Detectada interrupcion escape, finalizado el envio de mensajes"
					<< endl;
			escapePulsado = true;
			return true;
		}
	}
	pulsarF5();
	return false;
}


