#include <iostream>
#include <string>       
#include <bitset>
#include "protocolo.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
//char prueba = 0x23;
	/*
	Armar la trama instanciando el tipo de trama a enviar y  configurandola
	*/
	char trama[100];
	char nombre[15]="hola";
	Solicitud Rqe(1,nombre);
	trama[0]=Rqe.getTipo();
	//trama[1]=Rqe.getName();
	cout << trama << '\n';
	
	return 0;
}
