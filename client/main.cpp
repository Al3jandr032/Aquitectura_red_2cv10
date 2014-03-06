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
	char trama[9];
	//contador
	/*	    
	inicializar();
	enviarAck(trama);
	enviarData(trama);
	terminar();
 */
 int i,nunos=0;
char a = 0xA7;
char temp = a;
for(i = 0; i < sizeof(char)*8;i++) {
if (temp & 0x01) 
nunos++;
 
temp=temp >> 1;
}

cout << nunos;
    system("PAUSE");
    return EXIT_SUCCESS;
}
