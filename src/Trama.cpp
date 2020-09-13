/**
 * Implementacion de los metodos de la clase Trama.
 *
 * @version 2.1
 * @author
 * Samuel Moreno Vincent<br/>
 * Santiago Rangel Colon
 *
 * Asignatura Fundamentos de Redes y Comunicaciones<br/>
 * Curso 16/17
 */

#include "Trama.h"
Trama::Trama() {
	this->S = 22;	//Por defecto
	this->D = 'T';	//Por defecto
	this->C = 05;
	this->N = '0';	//Por defecto
	this->L = 0;	//Por defecto
	this->BCE = 1;	//Por defecto
}
void Trama::setS(char S_) {
	S = S_;
}
void Trama::setD(char D_) {
	D = D_;
}
void Trama::setC(char C_) {
	C = C_;
}
void Trama::setN(char N_) {
	N = N_;
}
void Trama::setL(char L_) {
	L = L_;
}
void Trama::setDatos(char* Datos_) {
	for (int i = 0; i < L; i++)
		Datos[i] = Datos_[i];
	//char * strcpy ( char * Datos, const char * Datos_);
}
void Trama::setDato(char Dato_, int posicion){
	Datos[posicion] = Dato_;
}
void Trama::setBCE(char BCE_) {
	BCE = BCE_;
}
unsigned char Trama::getS() {
	return this->S;
}
unsigned char Trama::getD() {
	return this->D;
}
unsigned char Trama::getC() {
	return this->C;
}
unsigned char Trama::getN() {
	return this->N;
}
int Trama::getL() {
	return this->L;
}
char Trama::getDato(int posicion) {
	return this->Datos[posicion];
}
void Trama::crearENQ() {
	this->S = 22;	//Por defecto
	this->D = 'T';	//Por defecto
	this->C = 05;
	this->N = '0';	//Por defecto
}
void Trama::crearEOT() {
	this->S = 22;	//Por defecto
	this->D = 'T';	//Por defecto
	this->C = 04;
	this->N = '0';	//Por defecto
}
void Trama::crearACK() {
	this->S = 22;	//Por defecto
	this->D = 'T';	//Por defecto
	this->C = 06;
	this->N = '0';	//Por defecto
}
void Trama::crearNACK() {
	this->S = 22;	//Por defecto
	this->D = 'T';	//Por defecto
	this->C = 21;
	this->N = '0';	//Por defecto
}
void Trama::crearTramaD(char L_, char* cadenaAux) {
	this->S = 22;	//Por defecto
	this->D = 'T';	//Por defecto
	this->C = 02;
	this->N = '0';	//Por defecto
	this->L = L_;
	for (int i = 0; i < L; i++)
		Datos[i] = cadenaAux[i];
	BCE = calcularBCE();
}
void Trama::enviarTramaC(HANDLE puerto) {
	EnviarCaracter(puerto, S);
	EnviarCaracter(puerto, D);
	EnviarCaracter(puerto, C);
	EnviarCaracter(puerto, N);
	//cout << " ->Trama de control enviada" << endl;
}
void Trama::enviarTramaD(HANDLE puerto) {
	EnviarCaracter(puerto, S);
	EnviarCaracter(puerto, D);
	EnviarCaracter(puerto, C);
	EnviarCaracter(puerto, N);
	EnviarCaracter(puerto, L);
	EnviarCadena(puerto, Datos, L);
	EnviarCaracter(puerto, BCE);
	//imprimirTramaD();	//TODO
	//cout << endl << " ->Trama de datos enviada" << endl;

}
void Trama::imprimirTramaC() {
	cout << "trama de tipo ";
	switch (this->C) {
	case 05:
		cout << "ENQ";
		break;
	case 04:
		cout << "EOT";
		break;
	case 06:
		cout << "ACK";
		break;
	case 21:
		cout << "NACK";
		break;
	}
}
void Trama::imprimirTramaD() {
	//imprimirTramaDatosCompleta();	//TODO
	for (int i = 0; i < this->L; i++) {
		char car = Datos[i];
		if (car == 13)
			printf("\n");
		else
			printf("%c", car);
	}

	//cout << endl << "----------------------------" << endl;
}
void Trama::imprimirTramaDatosCompleta() {
	cout << endl << "----------------------------" << endl
			<< "Datos de la trama: " << endl;

	cout << "S: " << int(S) << endl;
	cout << "C: " << int(C) << endl;
	cout << "N: " << int(N) << endl;
	cout << "L: " << int(L) << endl;
	cout << "BCE: " << int(BCE) << endl;
	cout << "Datos: " << endl;
}
bool Trama::esControl() {
	if (this->C == 02) {
		return false;
	}
	return true;
}
unsigned char Trama::calcularBCE() {
	unsigned char xorxor = this->Datos[0];
	int longitud = int(this->L);
	for (int i = 1; i < longitud - 1; ++i) {
		xorxor = xorxor ^ this->Datos[i];
	}
	if (xorxor == unsigned(0) || xorxor == unsigned(35) || xorxor == unsigned(36) || xorxor == unsigned(27)) {
		xorxor = unsigned(1); // si la xor es /0, % o # pone un 1
	}
	return xorxor;
}
bool Trama::esCorrecta() {
	char car1 = calcularBCE();
	char car2 = this->BCE;
	if (car1 == car2)
		return true;
	else
		return false;
}
unsigned char Trama::getBCE() {
	return this->BCE;
}
void Trama::crearENQ(char ToR, char NumeroTrama) {
	this->S = 22;	//Por defecto
	this->D = ToR;
	this->C = 05;
	this->N = NumeroTrama;
}
void Trama::crearEOT(char ToR, char NumeroTrama) {
	this->S = 22;	//Por defecto
	this->D = ToR;
	this->C = 04;
	this->N = NumeroTrama;
}
void Trama::crearACK(char ToR, char NumeroTrama) {
	this->S = 22;	//Por defecto
	this->D = ToR;
	this->C = 06;
	this->N = NumeroTrama;
}
void Trama::crearNACK(char ToR, char NumeroTrama) {
	this->S = 22;	//Por defecto
	this->D = ToR;
	this->C = 21;
	this->N = NumeroTrama;
}
void Trama::crearTramaDCompleta(char ToR, char NumeroTrama, char L_,
		char* cadenaAux) {
	this->S = 22;
	this->D = ToR;
	this->C = 02;
	this->N = NumeroTrama;
	this->L = L_;
	for (int i = 0; i < L; i++)
		Datos[i] = cadenaAux[i];
	this->BCE = calcularBCE();
}
void Trama::imprimirEnvio() {
	//R: R ACK 0
	cout << "E: " << this->D << " ";
	imprimirC();
	cout << " " << this->N;
	if (!esControl()) {
		cout << " " << int(BCE);
	}
	cout << endl;
}
void Trama::imprimirRecibo() {
	//R: R ACK 0 0
	cout << "R: " << this->D << " ";
	imprimirC();
	cout << " " << this->N;
	if (!esControl()) {
		cout << " " << int(BCE) << " " << int(calcularBCE());
	}
	cout << endl;
}
void Trama::imprimirC() {
	switch (this->C) {
	case 05:
		cout << "ENQ";
		break;
	case 04:
		cout << "EOT";
		break;
	case 06:
		cout << "ACK";
		break;
	case 21:
		cout << "NACK";
		break;
	case 02:
		cout << "STX";
		break;
	}
}
bool Trama::esACK() {
	if (this->C == 06)
		return true;
	else
		return false;
}
bool Trama::esNACK() {
	if (this->C == 21)
		return true;
	else
		return false;
}
bool Trama::esEOT() {
	if (this->C == 04)
		return true;
	else
		return false;
}
bool Trama::esENQ() {
	if (this->C == 05)
		return true;
	else
		return false;
}

