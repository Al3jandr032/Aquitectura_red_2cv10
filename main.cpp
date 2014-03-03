#include <iostream>
#include <fstream>
#include <string>       
#include <bitset>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "canal.h"
#include "protocolo.h"

using namespace std;

int main(int argc, char *argv[])
{
	//Trama a transmitir
	char trama[7];
	//contador
	int cont=0;
	//buffer para leer del archivo
	char buffer[5];
	//byte para numerar los paquetes
	char Bloque=0x01;
	//instaancie del paquete datos
	Data d;
	// abrir el archivo en modo binario
	ifstream myFile ("laravel.txt", ios::in | ios::binary);
	
	inicializar();
	
		do{
		myFile.read (buffer, 5);
		d.setBloque(Bloque);
		trama[0]=d.getTipo();
		trama[1]=d.getBloque();
		trama[2]='\0';
		strncat(trama,buffer, 5);
		tx(trama,sizeof(trama));

		Bloque++;
	}while(1);
		terminar();
 
    system("PAUSE");
    return EXIT_SUCCESS;
}
