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
	char trama[512];
	
	
	char nombre[14]="laravel.txt";
	
	inicializar();
	//peticion de escritura
	enviarPeticion(1,nombre,sizeof(nombre));
	//peticion de lectura
	enviarPeticion(2,nombre,sizeof(nombre));
	//enviar data
	enviarData(trama,nombre);
	terminar();
	
    system("PAUSE");
    return EXIT_SUCCESS;
}



