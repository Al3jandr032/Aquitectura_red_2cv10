#include <iostream>
#include <cstring>
#include "transporte.h"
using namespace std;
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
/*******************      ACUSES       *****************************/
/********************************************************************/
/*******************************************************************/

void enviarAck(char *trama){
	//byte para numerar los paquetes
	char Bloque=0x01;
	//instaancie del paquete datos
	Ack acuse;
	//instancia de direccion
	Adr dir(0x01,0x02);
	// agregar direcciones a la trama
	trama[0]=dir.dest;
	trama[1]=dir.orig;
	trama[2]=acuse.getTipo();
	do{
			acuse.setBloque(Bloque);
			trama[3]=acuse.getBloque();
			cout << unostrama(trama)<<'\n';
			tx(trama,4);
		Bloque++;
	}while(Bloque >= 10);
		
}


int waitforAck(char bloque){
	char bufer[1500];
	int tam=sizeof(bufer);
	do{
		rx(bufer,&tam);
		if(bufer[0] == 0x02 && bufer[1] == 0x01 
				&& bufer[2]== 0x08 && bufer[3]== bloque){
			imprimir(bufer,tam);
			continue;
		}
		
	}while(1);
	return 0;
}
//------------------------------------------------------------------------------

/********************************************************************/
/*******************      DATOS       *****************************/
/********************************************************************/
/********************************************************************/
void enviarData(char *trama,char *nombre){
	int con,length;
	//buffer para leer del archivo
	char buffer[5];
	//byte para numerar los paquetes
	char Bloque=0x01;
	//instaancie del paquete datos
	Data d;
	//instancia de direccion
	Adr dir(0x01,0x02);
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
		if(con <= 5){
			myFile.read(buffer, con);
			d.setBloque(Bloque);
			trama[3]=d.getBloque();
			memcpy(trama+4,buffer,con);
			if(unostrama(trama)%2==0){
			trama[4+con]=0x00;	
			}else{
			trama[4+con]=0x01;	
			}
			tx(trama,con+5);
		}
		else{
			myFile.read(buffer, 5);
			d.setBloque(Bloque);
			trama[3]=d.getBloque();
			memcpy(trama+4,buffer,5);
			if(unostrama(trama)%2==0){
			trama[9]=0x00;	
			}else{
			trama[9]=0x01;	
			}
			tx(trama,10);
		}
		system("PAUSE");
		//waitforAck(Bloque);
		Bloque++;
		con=con-5;
	}while(con > 0);
	
}

void recibirData(char *nombre){
	char trama[10];
	//byte para numerar los paquetes
	char Bloque=0x01;
	ofstream myFile;
	myFile.open("file.dat", ios::out);
	do{
		rx(trama,10);
		if(trama[2] == 0x04 && trama[2]==Bloque){
		myFile.write(trama+4,5);
		Bloque++;
		}
		
	}while(sizeof(trama) < 10);
	myFile.close();
}
//------------------------------------------------------------------------------
/********************************************************************/
/*******************      PETICIONES       *****************************/
/********************************************************************/
/********************************************************************/
void enviarPeticion(int tipo, char *nombre,int size){
	char trama[50];
	Solicitud request(tipo);
	//instancia de direccion
	Adr dir(0x01,0x02);
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

/********************************************************************/
