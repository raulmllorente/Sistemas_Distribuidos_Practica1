//Raul Martinez Llorente

#include "filemanager_stub.h"

#define OP_LISTARCH          'L'
#define OP_LEERARCH          'R'
#define OP_ESCRIBARCH        'W'

#define OP_EXIT              'E'
#define OP_OK                'O'

filemanager_stub::filemanager_stub(){
	char* ip=NULL;
	ip=new char[strlen(IP_SERVER)+1];
	memcpy(ip,IP_SERVER,strlen(IP_SERVER)+1);
	
	std::cout<<"INICIANDO CLIENTE\n";
	
	serverID=initClient(ip,PORT_SERVER);
	if(serverID==-1)
	{
		std::cout<<"ERROR CLIENTE Fichero: "<<__FILE__<<" Línea: "<<__LINE__<<" Conexión no válida\n";
	}
	
	delete ip;
}

filemanager_stub::~filemanager_stub(){
	char msg=OP_EXIT;
	sendMSG(serverID,(void*)&msg,sizeof(char));
	//recibir resultado
	char* buff=nullptr;
	int dataLen=0;
	char state=0;
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&state,buff,sizeof(char));
	delete buff;
	
	if(state!=OP_OK){
		std::cout<<"ERROR cerrando conexion\n";
	}
}

vector<string*>* filemanager_stub::listFiles(){

	char msg = OP_LISTARCH;
	char* buff = nullptr;
	int dataLen = 0;
	int tamVec = 0;
	vector<string*>* vecFich = new vector<string*>();
	
	//enviar mensaje de listFiles
	sendMSG(serverID,(void*)&msg,sizeof(char));
	
	//recibir el tamaño del vector
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&tamVec,buff,dataLen);
	delete buff;
	
	//se van introduciendo los archivos en el vector creado anteriormente, para ello se crea una variable de tipo string que almacenara los datos del buffer y despues se
	//añadira esa variable string al vector y asi sucesivamente
	for(unsigned int i = 0; i < tamVec; i++){
		recvMSG(serverID,(void**)&buff,&dataLen);
		
   		string* fich = new string;
   		fich->append(buff);
   		
		vecFich->push_back(fich);
		delete buff;
   	}
   	
	return vecFich;
}

void filemanager_stub::readFile(char* fileName, char* &data, unsigned long int & dataLength){

	char msg = OP_LEERARCH;
	char* buff = nullptr;
	int dataLen = 0;
	
	//enviar mensaje de readFile
	sendMSG(serverID,(void*)&msg,sizeof(char));
	
	//se envia el nombre del fichero a leer
	sendMSG(serverID,(void*)fileName, strlen(fileName)+1);
	
	//se recibe el tamaño del fichero
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&dataLength, buff, sizeof(unsigned long int));
	delete buff;
	
	//se recibe el contenido del fichero
	recvMSG(serverID,(void**)&data,&dataLen);
}

void filemanager_stub::writeFile(char* fileName, char* data, unsigned long int dataLength){

	char msg = OP_ESCRIBARCH;
	
	//enviar mensaje de writeFile
	sendMSG(serverID,(void*)&msg,sizeof(char));
	
	//se envian tanto el nombre, como los datos, como el tamaño del fichero a escribir
	sendMSG(serverID,(void*)fileName, strlen(fileName)+1);
	sendMSG(serverID,(void*)data,sizeof(char*)*sizeof(dataLength));
	sendMSG(serverID,(void*)&dataLength,sizeof(unsigned long int));
}

void filemanager_stub::freeListedFiles(vector<string*>* fileList){

	//esta funcion es auxiliar local por lo que no requiere de mensajes de llamada entre cliente y servidor
	
	//se itera sobre el vector recibido para eliminar todo su contenido de principio a fin, para ello se emplean las funciones begin() y end() que pertenecen a la libreria de los vectores
	for(vector<string*>::iterator i = fileList->begin(); i != fileList->end(); i++){
		delete *i;
	}
	
	//se elimina la lista ya vacia
	delete fileList;
}

