#include <stdio.h>
#include <stdlib.h>
#include "canal.h"
#include <string.h>
#include <windows.h>
unsigned char IDdest[2]={0,1},IDori[2]={0,2};

void EstructuraTrama(unsigned char *pac)
{
memcpy(pac,IDdest,2 );
memcpy(pac+2,IDori,2 );
memcpy(pac+4,"ACK\0",4 );
     }




void impr(unsigned char *bufer){
     for(int i=0; i<60;i++)
{     if(i%16==0)
     printf("\n");
     printf("%.2x ",bufer[i]);
     }
     }

int main(int argc, char *argv[])
{
char trama[1000];

char bufer[1500];
int tam;
int i=0;

//EstructuraTrama((unsigned char*)trama);
inicializar();
/*
tx(trama,sizeof(trama));
tam=sizeof(bufer);}
*/

leer:
//Sleep(980);     
do{
tam=sizeof(bufer);                  
rx(bufer,&tam);
impr((unsigned char*)bufer);
//printf("Recibi %d",i++);
}while(memcmp(bufer,IDori,2));

printf("recv\n");
impr((unsigned char*)bufer);
if(!memcmp(bufer,IDori,2))
{
                          printf("%s\n",bufer+4);

EstructuraTrama((unsigned char*)trama);
imprimir(trama,strlen(trama));
tx(trama,60);

}

                                                    
else
goto leer;




terminar();    
    system("PAUSE");
    return EXIT_SUCCESS;
}


