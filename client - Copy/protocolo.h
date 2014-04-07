#include <iostream>
#include <cstring>
#include "transporte.h"
using namespace std;

#define Bloq_size 512
/********************************************************************/
/********************************************************************/
/*******************      TRAMAS       *****************************/
/********************************************************************/
/********************************************************************/
class Solicitud
{
	private:
		char tipo;
		char* nombre;
	public:
		Solicitud(int tipo){
			if(tipo == 1){
				this->tipo = 0x01;
				//strcpy(this->nombre, name);
			}else if(tipo == 2){
				this->tipo = 0x02;
				//strcpy(this->nombre, name);
			}
		}
		char getTipo(){
			return this->tipo;
		}
		char* getName(){
			return this->nombre;
		}
		void imprimir(){
			cout<< hex<< static_cast<int>(this->tipo) << '\n' << this->nombre <<'\n';
		}

};

class Data
{
	public:
		Data(){
			this->tipo = 0x04;	
		}
		char getTipo(){
			return this->tipo;
		}
		void setBloque(char i){
			this->bloque=i;
		}
		char getBloque(){
			return this->bloque;
		}
	private:
		char tipo;
		char bloque;
		char datos;
};

class Ack
{
	public:
		Ack(){
			this->tipo = 0x08;	
		}
		char getTipo(){
			return this->tipo;
		}
		void setBloque(char i){
			this->numero=i;
		}
		char getBloque(){
			return this->numero;
		}
	private:
		char tipo;
		char numero;
};

class error
{
	public:
		error(){
			this->tipo = 0x16;	
		}
		char getTipo(){
			return this->tipo;
		}
	private:
		char tipo;
		char codigo;
		char mensaje;
};
//------------------------------------------------------------------------------

/********************************************************************/
/*******************    DIRECCIONES     *****************************/
/********************************************************************/
class Adr
{
	public:
		char dest;
		char orig;
		Adr(char orig,char dest){
			this->orig=orig;
			this->dest=dest;
		}
		char getOrig(){
			return this->orig;
		}
		char getDest(){
			return this->dest;
		}
};	
//------------------------------------------------------------------------------

/***************************************************************************/
/*******************      BIT DE PARIDAD       *****************************/
/***************************************************************************/

int contarunos(char entrada){
	 int i,nunos=0;
	 //char temp = entrada;
	for(i = 0; i < sizeof(char)*8;i++) {
		if (entrada & 0x01) 
		nunos++;
	 
		entrada=entrada >> 1;
	}
	return nunos;
}

int unostrama(char *trama){
	int i , cont=0;
	for(i = 0; i <sizeof(trama);i++){
		cont = cont + contarunos(trama[i]);
	}
	return cont;
}
//------------------------------------------------------------------------------

/********************************************************************/
void impr(unsigned char *bufer){
   for(int i=0; i<60;i++)
	{     
		if(i%16==0)
    	 printf("\n");
     printf("%.2x ",bufer[i]);
   }
}
/********************************************************************/
/*******************      ACUSES       *****************************/
/********************************************************************/
/*******************************************************************/

void enviarAck(char *trama,char Bloque,Adr dir){
	
	//instaancie del paquete datos
	Ack acuse;
	
	// agregar direcciones a la trama
	trama[0]=dir.dest;
	trama[1]=dir.orig;
	trama[2]=acuse.getTipo();
	acuse.setBloque(Bloque);
	trama[3]=acuse.getBloque();
	if(unostrama(trama)%2==0){
		trama[4]=0x00;	
	}else{
		trama[4]=0x01;	
	}
		tx(trama,5);
		
}

/*
int waitforAck(char bloque,const char *dir){
	char bufer[1500];
	int tam=sizeof(bufer);
	
	return 0;
}*/
//------------------------------------------------------------------------------

/********************************************************************/
/*******************      DATOS       *****************************/
/********************************************************************/
/********************************************************************/
void enviarData(char *trama,char *nombre,Adr dir){
	int con,length,tam;
	char bufer[1500];
	//buffer para leer del archivo
	char buffer[Bloq_size];
	//byte para numerar los paquetes
	char Bloque=0x01;
	//instaancie del paquete datos
	Data d;
	//instancia de direccion
	char dirorig[1];
	char dirdest[1];
	dirorig[0] = dir.orig;
	dirdest[0]=dir.dest;
	// agregar direcciones a la trama
	trama[0]=dir.dest;
	trama[1]=dir.orig;
	trama[2]=d.getTipo();
	// abrir el archivo en modo binario
	ifstream myFile (nombre, ios::in | ios::binary);
	//longitud del archivo
		myFile.seekg (0, myFile.end);
    	length = myFile.tellg();
    	myFile.seekg (0, myFile.beg);
    	con=length;
	do{
		
		if(con <= Bloq_size){
			myFile.read(buffer, con);
			d.setBloque(Bloque);
			trama[3]=d.getBloque();
			memcpy(trama+4,buffer,con);
			if(unostrama(trama)%2==0){
			trama[4+con]=0x00;	
			}else{
			trama[4+con]=0x01;	
			}
			tx(trama,con+Bloq_size);
		}
		else{
			myFile.read(buffer, Bloq_size);
			d.setBloque(Bloque);
			trama[3]=d.getBloque();
			memcpy(trama+4,buffer,Bloq_size);
			if(unostrama(trama)%2==0){
			trama[9]=0x00;	
			}else{
			trama[9]=0x01;	
			}
			tx(trama,Bloq_size+5);
		}
		//system("PAUSE");
		leer:
			printf("esperando acuse\n");
			do{
				tam=sizeof(bufer);                  
				rx(bufer,&tam);
				impr((unsigned char*)bufer);
			}while(memcmp(bufer,dirorig,1));
			printf("recv\n");
			impr((unsigned char*)bufer);
			
		if(Bloque != 0xff){
		Bloque++;
		}else{
		Bloque = 0x00;
		}
		con=con-Bloq_size;
	}while(con > 0);
	
}

void recibirData(char *nombre,Adr dir){
	char trama[520];
	char dirorig[1];
	dirorig[0] = dir.orig;
	//byte para numerar los paquetes
	char Bloque=0x01;
	int tam=sizeof(trama);
	ofstream myFile;
	myFile.open(nombre, ios::out| ios::binary);
	do{
		do{                 
			rx(trama,&tam);
			impr((unsigned char*)trama);
		}while(memcmp(trama,dirorig,1));
		if(trama[2] == 0x04 && trama[2]==Bloque){
		myFile.write(trama+4,512);
		Bloque++;
		}
		
	}while(sizeof(trama) < 512);
	myFile.close();
}
//------------------------------------------------------------------------------
/********************************************************************/
/*******************      PETICIONES       *****************************/
/********************************************************************/
/********************************************************************/
void enviarPeticion(int tipo, char *nombre,int size,Adr dir){
	char trama[50];
	Solicitud request(tipo);
	//instancia de direccion
	
	// agregar direcciones a la trama
	trama[0]=dir.dest;
	trama[1]=dir.orig;
	trama[2]=request.getTipo();
	memcpy(trama+3,nombre,size); 
	if(unostrama(trama)%2==0){
			trama[15]=0x00;	
	}else{
			trama[15]=0x01;	
	}
	tx(trama,15);
}


