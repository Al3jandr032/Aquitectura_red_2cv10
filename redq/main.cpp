#include <stdio.h>
#include <stdlib.h>
#include "canal.h"
#include <windows.h>

unsigned char IDorigen[2]={0x00,0x01}, IDdestino[2]={0x00,0x02};

void estructuraTrama(unsigned char *bufer)
{
memcpy(bufer, IDdestino,2);     
memcpy(bufer+2, IDorigen,2);
memcpy(bufer+4,"Gilberto\0",9);
}

void imp(unsigned char *paq,int tam)
{
int i;
for(i=0;i<tam;i++)
{
if(i%16==0)
   printf("\n");
 printf("%.2x ",paq[i]);  
}
    
}

int main(int argc, char *argv[])
{
char trama[]="Hola mundo";
char bufer[1500];
int tam;

inicializar();
estructuraTrama((unsigned char *)trama);
tx(trama,60);//sizeof(trama));
tam=60;//sizeof(bufer);
do
{
rx(bufer,&tam);
imp((unsigned char *)bufer,60);
}
while(memcmp(bufer,IDorigen,2));

imp((unsigned char *)bufer,60);
printf("\n%s",bufer+4);
terminar();    
    system("PAUSE");
    return EXIT_SUCCESS;
}
