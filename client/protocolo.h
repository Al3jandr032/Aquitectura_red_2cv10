#include <iostream>
#include <cstring>
#include "transporte.h"
using namespace std;

class Solicitud
{
	private:
		char tipo;
		char* nombre;
	public:
		Solicitud(int tipo,const char name[]){
			if(tipo == 1){
				this->tipo = 0x01;
				strcpy(this->nombre, name);
			}else if(tipo == 2){
				this->tipo = 0x02;
				strcpy(this->nombre, name);
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
/*
char nombre[15]="hola";
Solicitud Rqe(1,nombre);
*/


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


/*
	Solicitud request(1);
	Solicitud req(2);
	char tipoRequest=request.getTipo();
	cout << "valor "<< hex<< static_cast<int>(tipoRequest) << '\n';
	tipoRequest=req.getTipo();
	cout << "valor "<< hex<< static_cast<int>(tipoRequest) << '\n';
	//DAtos
	Data datos;
	tipoRequest = datos.getTipo();
	cout << "valor "<< hex<< static_cast<int>(tipoRequest) << '\n';
	//Acuse
	Ack acuse;
	tipoRequest=acuse.getTipo();
	cout << "valor "<< hex<< static_cast<int>(tipoRequest) << '\n';
	//Error
	error err;
	tipoRequest=err.getTipo();
	cout << "valor "<< hex<< static_cast<int>(tipoRequest) << '\n';
	*/
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
	
/******************************************************************************/

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
			tx(trama,4);
		Bloque++;
	}while(Bloque >= 10);
		
}

void enviarData(char *trama){
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
	ifstream myFile ("laravel.txt", ios::in | ios::binary);
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
			tx(trama,con+4);
		}
		else{
			myFile.read(buffer, 5);
			d.setBloque(Bloque);
			trama[3]=d.getBloque();
			memcpy(trama+4,buffer,5);
			tx(trama,9);
		}
		Bloque++;
		con=con-5;
	}while(con > 0);
	
}
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

