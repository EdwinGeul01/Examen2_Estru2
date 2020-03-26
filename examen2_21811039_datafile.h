#ifndef DATAFILE_H
#define DATAFILE_H

#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <limits>
#include <string>

#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <limits>
#include <string>



using namespace std;


class Empleado
{
	public:
	char Codigo[11];
    char Nombres[51];
    char Apellidos[51];
    char Departamento[4];
    char Edad[4];
    char Sueldo[10];

};	

class RecData{
	public:	
		void Pack();
		void UnPack();
		Empleado Registro;
		void GetOne();
		//TODO agregar resto de las funciones
		//TODO agregar resto de las funciones
};



class DataFile{
	private:
		RecData recData;
    public:
        void PrintAll();
		int  Add();
		int Find(char*);
		void Find2(char*);

		void Remove(char*);
		void Compact();
		DataFile();
};

#endif /* DATAFILE_H */