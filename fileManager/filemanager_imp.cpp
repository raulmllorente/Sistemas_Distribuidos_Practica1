//Raul Martinez Llorente

#include "filemanager_imp.h"


#define OP_LISTARCH          'L'
#define OP_LEERARCH          'R'
#define OP_ESCRIBARCH        'W'

#define OP_EXIT              'E'
#define OP_OK                'O'

filemanager_imp::filemanager_imp(int clientID, string path){

    fmImp = new FileManager(path);
    //inicializar estados, extra...
    salir = false;
    this->clientID = clientID;
}

filemanager_imp::~filemanager_imp(){

    delete fmImp;
    closeConnection(clientID);
    //cierre estados, etc...
}

void filemanager_imp::exec(){

    while(!salir)
    {
        //ejecutar
        //recibir tipo de operacion
        char* msg=NULL;
        int dataLen=0;
        char tipo_op=-1;

        recvMSG(clientID,(void**)&msg,&dataLen);
        if(dataLen!=1)
        {
            std::cout<<"Error, tipo operacion no valido\n";
        }else
        {
            tipo_op=msg[0];
            delete msg;
            
            switch(tipo_op)
            {
            
            	case OP_LISTARCH:
            	{
            		//creamos un vector de strings para almacenar los ficheros del directorio que se van a listar
            		vector<string*>* vecFich = new vector<string*>();
            		
            		//se llama a listFiles para realizar la operacion de listado del directorio
            		vecFich = fmImp->listFiles();
            		
            		//se almacena el tamaño del vector en una variable
            		int tamVec = vecFich->size();
            		
            		//se envia el tamaño del vector
            		sendMSG(clientID,(void*)&tamVec,sizeof(int));
            		
            		//se van enviando los nombres de los ficheros del directorio a medida que se recorre el bucle for
            		for(unsigned int i = 0; i < tamVec; i++) {
            			sendMSG(clientID, (void*)vecFich->at(i)->c_str(), strlen(vecFich->at(i)->c_str()));
            		}
            		
            		//se libera el vector ya que no es dinamico
            		fmImp->freeListedFiles(vecFich);
            		
            	}break;
            	
                case OP_LEERARCH:
                {
                	char* fileName = nullptr;
                	char* datosFich = nullptr;
                	unsigned long int longFich = 0;
                	
                	//se recibe el nombre del fichero a leer
                	recvMSG(clientID,(void**)&fileName,&dataLen);
                	
                	//se llama a readFile para realizar la operacion de lectura
                	fmImp->readFile(fileName, datosFich, longFich);
                	
                	//se envian tanto el tamaño del fichero como su contenido
                	sendMSG(clientID,(void*)&longFich,sizeof(unsigned long int));
                	sendMSG(clientID,(void*)datosFich, sizeof(char*)*sizeof(longFich));
                	
                	//limpiar memoria
                	delete datosFich;
                	delete fileName;
                	
                }break;
                
                case OP_ESCRIBARCH:
                {
                	char* fileName = nullptr;
                	char* datosFich = nullptr;
                	unsigned long int longFich = 0;
                	
                	//se reciben tanto el nombre, como los datos y el tamaño del fichero a escribir
                	recvMSG(clientID,(void**)&fileName,&dataLen);
                	recvMSG(clientID,(void**)&datosFich,&dataLen);
                	recvMSG(clientID,(void**)&longFich,&dataLen);
                	
                	//se llama a writeFile para realizar la funcion de escritura del fichero
                	fmImp->writeFile(fileName,datosFich,strlen(datosFich));
                	
                	//limpiar memoria
                	delete fileName;
                	delete datosFich;
                	
                }break;
                
                case OP_EXIT:
                {
                    salir=true;
                    char opOK=OP_OK;
                    sendMSG(clientID,(void*)&opOK,sizeof(char));
                }break;
                
                default:
                    std::cout<<"Error, tipo operacion no valido\n";
                break;
                
            }
        }
    }
}
