#include <iostream>

using namespace std;
class solicitud
{
	private:
		char tipo;
		char nombre;
};

class data
{
	private:
		char tipo;
		char bloque;
		char datos;
};

class acuse
{
	private:
		char tipo;
		char numero;
};

class error
{
	private:
		char tipo;
		char codigo;
		char mensaje;
};

/******************************************************************************/
class Transfer
{
   public:
      char tipo[];   
      char archivo[];  
      char modo[];   
	private:
		solicitud trama;
};

class Datagram
{
	public:
		char ndato[];
		char bit;
};

class internet
{
	public:
		char dest[];
		char orig[];
};
