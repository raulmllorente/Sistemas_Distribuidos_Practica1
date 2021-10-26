//Raul Martinez Llorente

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "filemanager_stub.h"

using namespace std;

int main(){
    FileManager* fmCli = new FileManager("./dirpruebacli/");
    filemanager_stub* fmRem = new filemanager_stub();
    
    vector<string*>* cliFich = fmCli->listFiles();
    vector<string*>* remFich = fmRem->listFiles();
    bool seguir = true;
    int opc;
    bool isFound = false;
    char* upArchivo = new char;
    char* dwlArchivo = new char;
    char* datosFich = nullptr;
    unsigned long int longFich = 0;
    
    while(seguir == true){
    
    	cout<<"\n";
    	cout<<"Menu opciones del sistema de ficheros\n\n";
    	cout<<"1 - Listar ficheros del directorio remoto y local\n";
    	cout<<"2 - Subir archivos al directorio remoto desde el directorio local\n";
    	cout<<"3 - Descargar archivos desde el directorio remoto al directorio local\n";
    	cout<<"4 - Salir\n";
    	cout<<"Introduce la opcion deseada: ";
    	
    	cin>>opc;
    	cout<<"\n";
    	
	    switch(opc){
	    
		case 1:
		{
		    cout<<"Lista de ficheros en el directorio remoto:\n";
		    
		    for(unsigned int i = 0; i < remFich->size(); i++){
			cout<<"Fichero: "<<remFich->at(i)->c_str()<<endl;
		    }
		    
		    cout<<"\n";
		    cout<<"Lista de ficheros en el directorio local:\n";
		    
		    for(unsigned int i = 0; i < cliFich->size(); i++){
			cout<<"Fichero: "<<cliFich->at(i)->c_str()<<endl;
		    }
		} break;
		
		
		case 2:
		{
		    while(isFound == false){
		    	cout<<"Nombre del archivo a subir: ";
		    	cin>>upArchivo;
		    	
		    	for(unsigned int i = 0; i < cliFich->size(); i++){
				if(strcmp(upArchivo, cliFich->at(i)->c_str()) == 0){
					cout<<"Inicio de subida de archivo\n";
					
		       		fmCli->readFile(upArchivo,datosFich,longFich);
		       		fmRem->writeFile(upArchivo,datosFich,longFich);
		       		
		       		cout<<"El archivo se subio correctamente\n";
		       		isFound = true;
		       	 }
		       }
		       
		       if(isFound == false){
		       	cout<<"Error. Archivo no encontrado. Volviendo al menu\n";
		       	isFound = true;
		       }
		    }
		} break;
		
		
		case 3:
		{
		    while(isFound == false){
		    	cout<<"Nombre del archivo a descargar: ";
		    	cin>>dwlArchivo;
		    	
		    	for(unsigned int i = 0; i < remFich->size(); i++){
				if(strcmp(dwlArchivo, remFich->at(i)->c_str()) == 0){
					cout<<"Inicio de descarga de archivo\n";
					
		       		fmRem->readFile(dwlArchivo,datosFich,longFich);
		       		fmCli->writeFile(dwlArchivo,datosFich,longFich);
		       		
		       		cout<<"El archivo se descargo correctamente\n";
		       		isFound = true;
		       	 }
		       }
		       
		       if(isFound == false){
		       	cout<<"Error. Archivo no encontrado. Volviendo al menu\n";
		       	isFound = true;
		       }
		    }
		} break;
		
		
		case 4:
		{
			cout<<"Saliendo\n";
			seguir = false;
		} break;
		
		default:
		{
			cout<<"Comando incorrecto. Introduzca uno nuevo\n";
		} break;
	     }
	     
	     //hace falta relistar todos los archivos en cada iteracion del bucle while, ademas de restablecer la variable de si se ha encontrado el fichero a false
	     //para que se cumplan las condiciones en las siguientes iteraciones
	     isFound = false;
	     cliFich = fmCli->listFiles();
	     remFich = fmRem->listFiles();
    }
    
    delete upArchivo;
    delete dwlArchivo;
    delete datosFich;
    delete cliFich;
    delete remFich;
    delete fmCli;
    delete fmRem;
    
    return 0;
}
