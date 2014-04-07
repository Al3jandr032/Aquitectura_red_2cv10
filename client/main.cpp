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
void printgen(){
	cout<< "enviar peticion" << '\n';
	cout<< "esperar peticion" << '\n';
	cout<< "salir	3" << '\n';
}
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
	//byte para numerar los paquetes
	char Bloque;
	//instancia de direccion
	Adr dir(0x01,0x02);
	char orgin[]={0x01};
	//opcion del menu
	int op,ch,tam=sizeof(trama);
	inicializar();
	do{
		printgen();
		cin >> ch;
		switch (ch)
		{
		case 1:
		   		do{
		
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
							cout<< "recibiendo ..."<< nombre << '\n';
							recibirData(nombre);
						   break;
						case 3:
						   continue;
						   break;
						default:
						   cout<< "valor invalido"<< '\n';
						}
					}while(op != 3);
		   break;
		case 2:
			do{                 
				rx(trama,&tam);
				impr((unsigned char*)trama);
			}while(memcmp(trama,orgin,1));
			if(trama[3] == 0x01 ){
				printf("hiol");
				impr((unsigned char*)trama);
				//recibirData(nombre);
			}else if(trama[3] == 0x02){
				printf("hiol");
				//enviarData(trama,nombre);
				impr((unsigned char*)trama);
			}
			
		   break;
		case 3:
		   return EXIT_SUCCESS;
		   break;
		default:
		   cout<< "valor invalido"<< '\n';
		}
	}while(ch != 3);
	
	terminar();
	//enviar data
	//enviarData(trama,nombre);
	
	
    system("PAUSE");
    return EXIT_SUCCESS;
}


