#include <iostream>
#include <fstream>
#include <string>       
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
	char nombre[14]="tramas1.pdf";
	char bufer[1500];
	char dirorig = {0x01};
	char dirdest = {0x02};
	int tam;
	inicializar();
	enviarPeticion(1,nombre,sizeof(nombre));
			printf("esperando acuse\n");
			do{
				tam=sizeof(bufer);                  
				rx(bufer,&tam);
				//impr((unsigned char*)bufer);
			}while(memcmp(bufer,&dirorig,1));
			printf("recibido\n");
	enviarData(trama,nombre,Bloque,dirorig,dirdest);
	terminar();
   
    return EXIT_SUCCESS;
}


