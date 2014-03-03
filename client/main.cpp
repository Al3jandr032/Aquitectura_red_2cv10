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
	int con,length;
	//buffer para leer del archivo
	char buffer[5];
	//byte para numerar los paquetes
	char Bloque=0x01;
	//instaancie del paquete datos
	Data d;
	// abrir el archivo en modo binario
	ifstream myFile ("laravel.txt", ios::in | ios::binary);
	myFile.seekg (0, myFile.end);
    length = myFile.tellg();
    myFile.seekg (0, myFile.beg);
    con=length;
	inicializar();
	do{
		if(con <= 5){
			myFile.read(buffer, con);
			d.setBloque(Bloque);
			trama[0]=d.getTipo();
			trama[1]=d.getBloque();
			trama[2]='\0';
			strncat(trama,buffer, con);
			tx(trama,con+2);
		}
		else{
			myFile.read(buffer, 5);
			d.setBloque(Bloque);
			trama[0]=d.getTipo();
			trama[1]=d.getBloque();
			trama[2]='\0';
			strncat(trama,buffer, 5);
			tx(trama,sizeof(trama));
		}
		Bloque++;
		con=con-5;
	}while(con > 0);
		terminar();
 
    system("PAUSE");
    return EXIT_SUCCESS;
}
