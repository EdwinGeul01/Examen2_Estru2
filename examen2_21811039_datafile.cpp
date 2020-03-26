#include <limits>
#include <fstream>
#include <inttypes.h>
#include <string>
#include <iostream>
#include <sstream>

#include "examen2_21811039_datafile.h"


using namespace std;

char Buffer_I[125];


/***************************************** RecData ********************************************/


void RecData::UnPack(){

	
    string temp_data = Buffer_I;

    strcpy(Registro.Codigo,temp_data.substr(0,temp_data.find(",")).c_str());
    Registro.Codigo[10] = '\0';
    temp_data = temp_data.substr(temp_data.find(",")+1);
    
    strcpy(Registro.Nombres,temp_data.substr(0,temp_data.find(",")).c_str());
    Registro.Nombres[50] = '\0';
    temp_data = temp_data.substr(temp_data.find(",")+1);
    
    strcpy(Registro.Apellidos,temp_data.substr(0,temp_data.find(",")).c_str());
    Registro.Apellidos[50] = '\0';
    temp_data = temp_data.substr(temp_data.find(",")+1);
    
    strcpy(Registro.Departamento,temp_data.substr(0,temp_data.find(",")).c_str());
    Registro.Departamento[3] = '\0';
    temp_data = temp_data.substr(temp_data.find(",")+1);
    
    strcpy(Registro.Edad,temp_data.substr(0,temp_data.find(",")).c_str());
    Registro.Edad[3] = '\0';
    temp_data = temp_data.substr(temp_data.find(",")+1);
    
    strcpy(Registro.Sueldo,temp_data.substr(0,temp_data.find("*")).c_str());
    Registro.Sueldo[9] = '\0';



}

void RecData::Pack(){

    strcpy(Buffer_I,Registro.Codigo);

    strcat(Buffer_I,",");
    strcat(Buffer_I,Registro.Nombres);

    strcat(Buffer_I,",");
    strcat(Buffer_I,Registro.Apellidos);

    strcat(Buffer_I,",");
    strcat(Buffer_I,Registro.Departamento);
    
    strcat(Buffer_I,",");
    strcat(Buffer_I,Registro.Edad);
    
    strcat(Buffer_I,",");
    strcat(Buffer_I,Registro.Sueldo);

    int totalsize  = strlen(Buffer_I);

    if (totalsize != 124)
    {
        while (strlen(Buffer_I) != 124)
        {
            strcat(Buffer_I,"*");
        }
        


    }
    strcat(Buffer_I,"\n");
    

    return;




}
void RecData::GetOne(){

	
	char temp[10];
	cout << "Ingrese codigo : ";
    cin.getline(Registro.Codigo,11);



	if (strlen(Registro.Codigo) != 10)
	{
		strcpy(temp,Registro.Codigo);
		Registro.Codigo[0] = 0;
	
	while ((strlen(Registro.Codigo)+strlen(temp))!=10)
	{
		strcat(Registro.Codigo,"0");

	}

		strcat(Registro.Codigo,temp);
		cout << Registro.Codigo << endl;
	
	}
	Registro.Codigo[10] = '\0';



    cout << "Ingrese nombre : ";
    cin.getline(Registro.Nombres,51);
	Registro.Nombres[50]= '\0';
    cout << "Ingrese Apellidos : ";
    cin.getline(Registro.Apellidos,51);
	Registro.Apellidos[50]= '\0';

    cout << "Ingrese Departamentos : ";
    cin.getline(Registro.Departamento,4);
	Registro.Departamento[3]= '\0';
    
	cout << "Ingrese Edad :";
    cin.getline(Registro.Edad,4);
	Registro.Edad[3]= '\0';

    cout << "Ingrese Sueldo : ";
    cin.getline(Registro.Sueldo,10);
	Registro.Sueldo[9]= '\0';


	string temp_sueldo = Registro.Sueldo;

	Registro.Sueldo[0] = 0;

	if (temp_sueldo.find(".") != -1)
	{
		if (temp_sueldo.size()-3 == temp_sueldo.find("."))
		{
			while (strlen(Registro.Sueldo) + (temp_sueldo.size()-3) != 6)
			{
				
				strcat(Registro.Sueldo,"0");
			}
			

		}else
		{
			temp_sueldo = temp_sueldo.substr(0,temp_sueldo.find(".")) + temp_sueldo.substr(temp_sueldo.find("."),2);
			while (strlen(Registro.Sueldo) + (temp_sueldo.size()-3) != 6)
			{
				strcat(Registro.Sueldo,"0");
			}

		}
		
		strcat(Registro.Sueldo,temp_sueldo.c_str());

	}else
	{
		temp_sueldo += ".00";

		while (strlen(Registro.Sueldo) + (temp_sueldo.size()-3) != 6)
			{
				strcat(Registro.Sueldo,"0");
			}
		strcat(Registro.Sueldo,temp_sueldo.c_str());

	}
	
		Registro.Sueldo[10]= '\0';

    
	Pack();


    
	
}

/*********************************************************************************************/



/***************************************** DataFile ********************************************/
DataFile::DataFile(){

}

void DataFile::PrintAll(){

 	ifstream fr;
    fr.open("Registros.txt",ios::in);
    fr.seekg(0,ios::end);
    int size = fr.tellg();
    fr.seekg(0);

    int position ;

    if (size == 0 || size == -1)
    {
        return;
    }
    

    while (true)
    {
        position = fr.tellg();
        fr.read(Buffer_I,125);
        Buffer_I[125] = '\0';
    	recData.UnPack();

	
		
        cout << "CODIGO - " << recData.Registro.Codigo << " NOMBRE - " << recData.Registro.Nombres << ":: APELLIDO - " << recData.Registro.Apellidos << ":: DEPARTAMENTO - " << recData.Registro.Departamento << " EDAD - " << recData.Registro.Edad << ":: ZIPCODE - " << recData.Registro.Sueldo << endl;
        

        if (fr.tellg() == size)
        {
            break;
        }

        
    }

}

int DataFile::Add(){
	recData.GetOne();


	ofstream fw;

    fw.open("Registros.txt",ios::out|ios::app);
    fw.write(Buffer_I,125);
    fw.close();


}


void DataFile::Find2(char* key)
{
	char codigo_temp[19];
    cout << "ingrese codigo del archivo a buscar : ";
    
    cin.getline(codigo_temp,11);

	char temp[10];


	if (strlen(codigo_temp) != 10)
	{
		strcpy(temp,codigo_temp);
		codigo_temp[0] = 0;
	
	while ((strlen(codigo_temp)+strlen(temp))!=10)
	{
		strcat(codigo_temp,"0");

	}

		strcat(codigo_temp,temp);
	
	}
	codigo_temp[10] = '\0';


	key =codigo_temp;

	ifstream fr;
    fr.open("Registros.txt",ios::in);
    fr.seekg(0,ios::end);
    int size = fr.tellg();
    fr.seekg(0);

    int position ;

    if (size == 0 || size == -1)
    {
        return ;
    }
    

    while (true)
    {
        position = fr.tellg();
        fr.read(Buffer_I,125);
        Buffer_I[125] = '\0';
    	recData.UnPack();

		if (strcmp(recData.Registro.Codigo,key) == 0)
		{
        	cout << "CODIGO - " << recData.Registro.Codigo << " NOMBRE - " << recData.Registro.Nombres << ":: APELLIDO - " << recData.Registro.Apellidos << ":: DEPARTAMENTO - " << recData.Registro.Departamento << " EDAD - " << recData.Registro.Edad << ":: ZIPCODE - " << recData.Registro.Sueldo << endl;
			break;
		}
		
		
        

        if (fr.tellg() == size)
        {
			cout << "registro no encontrado";
            break;
        }

        
    }


}

int DataFile::Find(char* key){

	ifstream fr;
    fr.open("Registros.txt",ios::in);
    fr.seekg(0,ios::end);
    int size = fr.tellg();
    fr.seekg(0);

    int position ;

    if (size == 0 || size == -1)
    {
        return -1;
    }
    

    while (true)
    {
        position = fr.tellg();
        fr.read(Buffer_I,125);
        Buffer_I[125] = '\0';
    	recData.UnPack();

		if (strcmp(recData.Registro.Codigo,key) == 0)
		{
			return position;
			
		}
		
		
        

        if (fr.tellg() == size)
        {
            break;
        }

        
    }


}

void DataFile::Remove(char* key){

	char codigo_temp[19];
    cout << "ingrese codigo del archivo a eliminar : ";
    
    cin.getline(codigo_temp,11);

	char temp[10];


	if (strlen(codigo_temp) != 10)
	{
		strcpy(temp,codigo_temp);
		codigo_temp[0] = 0;
	
	while ((strlen(codigo_temp)+strlen(temp))!=10)
	{
		strcat(codigo_temp,"0");

	}

		strcat(codigo_temp,temp);
		cout << codigo_temp << endl;
	
	}
	codigo_temp[10] = '\0';

    int position  =  Find(codigo_temp);

    // FILE* filew = fopen(filename.c_str(),"rb+");

    // fseek(filew,position,0);
    // fwrite("A",1,1,filew);

    // fflush(filew);
    // fclose(filew);

    if (position == -1)
    {
        cout << "registro no encontrado!!";
        return;
    }
    

    fstream fw("Registros.txt",ios::in |ios::ate | ios::out);
    fw.seekp(position);
    fw << "D";

    fw.close();

}


void DataFile::Compact(){


	
    //ifstream to read the original file   
    ifstream fr;
    fr.open("Registros.txt",ios::in);
    fr.seekg(0,ios::end);
    int size = fr.tellg();
    fr.seekg(0);

    //new registre file
    ofstream fw;
    fw.open("./temp.txt",ios::out | ios::app);




    int position ;

    while (true)
    {
       position = fr.tellg();
        fr.read(Buffer_I,125);
        Buffer_I[125] = '\0';

        if (Buffer_I[0] != 'D')
        {
            fw.write(Buffer_I,125);
            fw.flush();
        }
        



        if (fr.tellg() == size)
        {
            break;

        }

    }
    
    fr.close();
    fw.close();

    remove("Registros.txt");
    rename("./temp.txt","Registros.txt");






}
/*********************************************************************************************/

	
