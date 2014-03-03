#include <stdio.h>
#include <stdlib.h>
#include "canal.h"
#include <iostream>
#include <string>       
#include <bitset>
#include <string.h>
#include <cstring>
#include "protocolo.h"

using namespace std;

int main(int argc, char *argv[])
{
	char trama[2];
	char Bloque=0x01;
	Ack d;
	inicializar();
	do{
		
		d.setBloque(Bloque);
		trama[0]=d.getTipo();
		trama[1]=d.getBloque();
		
		
		tx(trama,sizeof(trama));
		
		Bloque++;
	}while(1);
	terminar();
	  
    system("PAUSE");
    return EXIT_SUCCESS;
}
