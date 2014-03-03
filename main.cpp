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
	char trama[100];
	char a=0x01;
	
	Ack d;
	d.setBloque(0x01);
	trama[0]=d.getTipo();
	trama[1]=d.getBloque();
	cout <<trama<< '\n';

	return 0;
}
