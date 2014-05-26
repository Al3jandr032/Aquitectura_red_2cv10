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
	char trama[512];
	char Bloque=0x01;
	char nombre[14]="laravel.txt";
	char dirorig = {0x02};
	char dirdest ={0x01};
	int tam,con=0,recv;
	char bufer[519];
	Adr dir(dirorig,dirdest);
	ofstream myFile;
	
	inicializar();
	leer:
	con++;
	memset(&bufer, 0x03 , sizeof(bufer));
	do{
		tam=sizeof(bufer);                  
		rx(bufer,&tam);
		//impr((unsigned char*)bufer);
	}while(memcmp(bufer,&dirorig,1));
	//impr((unsigned char*)bufer);
	if( bufer[517] == 0x03 && bufer[2] == 0x04 ){
		recv=impr((unsigned char*)bufer);
		printf("\n %d",recv);
		recv= recv -5;
		printf("\n %d",recv);		
		enviarAck(trama,Bloque,dir);
		myFile.write(bufer+ 4,recv);
		terminar();
		goto reel;
	}
	if(bufer[2] == 0x01  ){
		enviarAck(trama,0x00,dir);
		myFile.open(nombre, ios::out| ios::binary);
		printf("reciviendo \n");
		goto leer;
	}
	if(bufer[2] == 0x04){
		impr((unsigned char*)bufer);
		enviarAck(bufer,Bloque,dir);
		myFile.write(trama+4,512);
		Bloque++;
		//printf("\n%X\n ",bufer[517]);
		goto leer;
	}
	
	reel:
		myFile.close();
		printf("\n done ..");
	   return EXIT_SUCCESS;
}


