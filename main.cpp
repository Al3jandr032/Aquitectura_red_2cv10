#include <iostream>
#include <string>       
#include <bitset>
#include <string.h>
#include "protocolo.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
//char prueba = 0x23;
	/*
	Armar la trama instanciando el tipo de trama a enviar y  configurandola
	*/
	int i;
	char trama[100];
	char nombre[15]="hola";
	Solicitud Rqe(1,nombre);
	trama[0]=Rqe.getTipo();
	trama[1]='\0';
	strncat(trama, Rqe.getName(), 4);
	cout << trama << '\n';

	return 0;
}
