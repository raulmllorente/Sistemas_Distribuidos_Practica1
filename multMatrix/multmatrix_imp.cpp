//Raul Martinez Llorente

#include "multmatrix_imp.h"


#define OP_LEEMAT         'L'
#define OP_MULTMAT        'M'
#define OP_ESCRIBEMAT     'W'
#define OP_CREAMATID 	   'I'
#define OP_CREAMATALE     'A'

#define OP_EXIT           'E'
#define OP_OK             'O'

multmatrix_imp::multmatrix_imp(int clientID){

	matop = new multMatrix();
	//inicializar estados, extra... 
	salir=false;
	this->clientID=clientID;

}

multmatrix_imp::~multmatrix_imp(){

	delete matop;
	closeConnection(clientID);
	//cierre estados, etc...
}


void multmatrix_imp::exec(){

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
				case OP_LEEMAT:
				{
					char* fileName = nullptr;
					matrix_t* datosLeidos = new matrix_t;
					
					//recibir nombre archivo
					recvMSG(clientID,(void**)&fileName,&dataLen);
					
					//operar leer matriz
					datosLeidos = matop->readMatrix(fileName);		
					
					//devolver parametros matriz leida
					sendMSG(clientID,(void*)&datosLeidos->rows,sizeof(int));
					sendMSG(clientID,(void*)&datosLeidos->cols,sizeof(int));
					sendMSG(clientID,(void*)datosLeidos->data,sizeof(int)*datosLeidos->rows*datosLeidos->cols);
					
					//borrar memoria
					delete fileName;
					delete datosLeidos;

				}break;
				
				case OP_MULTMAT:
				{
					matrix_t* a = new matrix_t;
					matrix_t* b = new matrix_t;
					matrix_t* res = new matrix_t;
					char* buffA = nullptr;
					char* buffB = nullptr;
					
					//recibir parametros matrices "a" y "b"
					recvMSG(clientID,(void**)&buffA,&dataLen);
					memcpy(&a->rows,buffA,sizeof(int));
					delete buffA;
					recvMSG(clientID,(void**)&buffA,&dataLen);
					memcpy(&a->cols,buffA,sizeof(int));
					delete buffA;
					recvMSG(clientID,(void**)&buffA,&dataLen);
					a->data = (int*)buffA;
					
					recvMSG(clientID,(void**)&buffB,&dataLen);
					memcpy(&b->rows,buffB,sizeof(int));
					delete buffB;
					recvMSG(clientID,(void**)&buffB,&dataLen);
					memcpy(&b->cols,buffB,sizeof(int));
					delete buffB;
					recvMSG(clientID,(void**)&buffB,&dataLen);
					b->data = (int*)buffB;
					
					//operar multiplicacion matrices
					res = matop->multMatrices(a, b);
					
					//devolver parametros matriz resultado
					sendMSG(clientID,(void*)&res->rows,sizeof(int));
					sendMSG(clientID,(void*)&res->cols,sizeof(int));
					sendMSG(clientID,(void*)res->data,sizeof(int)*res->rows*res->cols);
					
					delete a;
					delete b;
					delete res;
					
				}break;
				
				case OP_ESCRIBEMAT:
				{
					char* fileName = nullptr;
					matrix_t* matrixentrada = new matrix_t;
					char* buff = nullptr;
					
					//recibir nombre fichero
					recvMSG(clientID,(void**)&fileName,&dataLen);
					
					//recibir parametros matriz entrada
					recvMSG(clientID,(void**)&buff,&dataLen);
					memcpy(&matrixentrada->rows,buff,sizeof(int));
					delete buff;
					recvMSG(clientID,(void**)&buff,&dataLen);
					memcpy(&matrixentrada->cols,buff,sizeof(int));
					delete buff;
					recvMSG(clientID,(void**)&buff,&dataLen);
					matrixentrada->data = (int*)buff;
					
					//escribir matriz en fichero
					matop->writeMatrix(matrixentrada, fileName);			
					
					//borrar memoria
					delete fileName;
					delete matrixentrada;
					
				}break;
				
				case OP_CREAMATID:
				{
					int a = 0, b = 0;
					matrix_t* res = new matrix_t;
					char* buff = nullptr;
					
					//recibir filas y columnas para crear matriz identidad
					recvMSG(clientID,(void**)&buff,&dataLen);
					memcpy(&a,buff,sizeof(int));
					delete buff;
					recvMSG(clientID,(void**)&buff,&dataLen);
					memcpy(&b,buff,sizeof(int));
					delete buff;
					
					//operar matriz identidad
					res = matop->createIdentity(a, b);
					
					//devolver parametros matriz identidad
					sendMSG(clientID,(void*)&res->rows,sizeof(int));
					sendMSG(clientID,(void*)&res->cols,sizeof(int));
					sendMSG(clientID,(void*)res->data,sizeof(int)*res->rows*res->cols);
					
					delete res;
					
				}break;
				case OP_CREAMATALE:
				{
					int a = 0, b = 0;
					matrix_t* res = new matrix_t;
					char* buff = nullptr;
					
					//recibir filas y columnas para crear matriz aleatoria
					recvMSG(clientID,(void**)&buff,&dataLen);
					memcpy(&a,buff,sizeof(int));
					delete buff;
					recvMSG(clientID,(void**)&buff,&dataLen);
					memcpy(&b,buff,sizeof(int));
					delete buff;
					
					//operar matriz aleatoria
					res = matop->createRandMatrix(a, b);
					
					//devolver parametros matriz aleatoria
					sendMSG(clientID,(void*)&res->rows,sizeof(int));
					sendMSG(clientID,(void*)&res->cols,sizeof(int));
					sendMSG(clientID,(void*)res->data,sizeof(int)*res->rows*res->cols);
					
					delete res;
				
					
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







