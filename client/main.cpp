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
void printm(){
		cout<< "peticion de escritura	1" << '\n';
		cout<< "peticion de lectura	2" << '\n';
		cout<< "salir	3" << '\n';
}
int main(int argc, char *argv[])
{
	//Trama a transmitir
	char trama[512];
	//Nombre del archivo
	char nombre[14]="song.mp3";
	const char *empty="";
	//byte para numerar los paquetes
	char Bloque;
	//instancia de direccion
	Adr dir(0x01,0x02);
	//opcion del menu
	int op;
	inicializar();
	do{
		//memset(nombre, 0, 25);
		//strcpy(nombre,empty);
		printm();
		cin >> op;
		switch (op)
		{
		case 1:
		   //cin >> nombre;
			//peticion de escritura
			enviarPeticion(1,nombre,sizeof(nombre));
			//waitforAck(0x00);
			cout<< "enviando ..."<< nombre << '\n';
			enviarData(trama,nombre);
		   break;
		case 2:
			cin >> nombre;
			//peticion de escritura
			enviarPeticion(2,nombre,sizeof(nombre));
			//waitforAck(0x00);
			recibirData(nombre);
		   break;
		case 3:
		   return EXIT_SUCCESS;
		   break;
		default:
		   cout<< "valor invalido"<< '\n';
		}
	}while(op != 3);
	terminar();
	//enviar data
	//enviarData(trama,nombre);
	
	
    system("PAUSE");
    return EXIT_SUCCESS;
}


