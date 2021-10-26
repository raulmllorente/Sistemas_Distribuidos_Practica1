//Raul Martinez Llorente

#include "multmatrix_stub.h"
#include <string.h>


#define OP_LEEMAT              'L'
#define OP_MULTMAT             'M'
#define OP_ESCRIBEMAT          'W'
#define OP_CREAMATID           'I'
#define OP_CREAMATALE          'A'

#define OP_EXIT                'E'
#define OP_OK                  'O'

multmatrix_stub::multmatrix_stub(){

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


multmatrix_stub::~multmatrix_stub(){
	char msg=OP_EXIT;
	sendMSG(serverID,(void*)&msg,sizeof(char));
	//recibir resultado
	char* buff=nullptr;
	int dataLen=0;
	char state=0;
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&state,buff,sizeof(char));
	delete buff;
	
	if(state!=OP_OK)
		std::cout<<"ERROR cerrando conexion\n";

}


matrix_t* multmatrix_stub::readMatrix(const char* fileName){

	char msg = OP_LEEMAT;
	char* buff = nullptr;
	int dataLen = 0;
	matrix_t* matriz = new matrix_t;
	
	//enviar mensaje de readMatrix
	sendMSG(serverID,(void*)&msg,sizeof(char));
	
	//enviar nombre fichero
	sendMSG(serverID,(void*)fileName,strlen(fileName)+1);
	
	//recibir parametros matriz
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&matriz->rows, buff, sizeof(int));
	delete buff;
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&matriz->cols, buff, sizeof(int));
	delete buff;
	recvMSG(serverID,(void**)&buff,&dataLen);
	matriz->data = (int*)buff;
	
	return matriz;
}


matrix_t* multmatrix_stub::multMatrices(matrix_t* m1, matrix_t *m2){

	char msg = OP_MULTMAT;
	char* buff = nullptr;
	int dataLen = 0;
	matrix_t* matriz = new matrix_t;
	
	//enviar mensaje de multMatrices
	sendMSG(serverID,(void*)&msg,sizeof(char));
	
	//envio parametros matrices "m1" y "m2"
	sendMSG(serverID,(void*)&m1->rows,sizeof(int));
	sendMSG(serverID,(void*)&m1->cols,sizeof(int));
	sendMSG(serverID,(void*)m1->data,sizeof(int)*m1->rows*m1->cols);
	
	sendMSG(serverID,(void*)&m2->rows,sizeof(int));
	sendMSG(serverID,(void*)&m2->cols,sizeof(int));
	sendMSG(serverID,(void*)m2->data,sizeof(int)*m2->rows*m2->cols);
	
	//recibir resultado
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&matriz->rows, buff, sizeof(int));
	delete buff;
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&matriz->cols, buff, sizeof(int));
	delete buff;
	recvMSG(serverID,(void**)&buff,&dataLen);
	matriz->data = (int*)buff;
	
	return matriz;
}


void multmatrix_stub::writeMatrix(matrix_t* m, const char *fileName){

	char msg = OP_ESCRIBEMAT;
	
	//enviar mensaje de writeMatrix
	sendMSG(serverID,(void*)&msg,sizeof(char));
	
	//enviar nombre fichero
	sendMSG(serverID,(void*)fileName,strlen(fileName)+1);
	
	//enviar parametros matriz a escribir
	sendMSG(serverID,(void*)&m->rows,sizeof(int));
	sendMSG(serverID,(void*)&m->cols,sizeof(int));
	sendMSG(serverID,(void*)m->data,sizeof(int)*m->rows*m->cols);
}


matrix_t* multmatrix_stub::createIdentity(int rows, int cols){

	char msg = OP_CREAMATID;
	char* buff = nullptr;
	int dataLen = 0;
	matrix_t* matriz = new matrix_t;
	
	//enviar mensaje de createIdentity
	sendMSG(serverID,(void*)&msg,sizeof(char));
	
	//enviar filas y columnas para generar matriz
	sendMSG(serverID,(void*)&rows,sizeof(int));
	sendMSG(serverID,(void*)&cols,sizeof(int));
	
	//recibir parametros de matriz identidad
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&matriz->rows, buff, sizeof(int));
	delete buff;
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&matriz->cols, buff, sizeof(int));
	delete buff;
	recvMSG(serverID,(void**)&buff,&dataLen);
	matriz->data = (int*)buff;
	
	return matriz;
	
	
}


matrix_t* multmatrix_stub::createRandMatrix(int rows, int cols){

	char msg = OP_CREAMATALE;
	char* buff = nullptr;
	int dataLen = 0;
	matrix_t* matriz = new matrix_t;
	
	//enviar mensaje de createRandMatrix
	sendMSG(serverID,(void*)&msg,sizeof(char));
	
	//enviar filas y columnas para generar matriz
	sendMSG(serverID,(void*)&rows,sizeof(int));
	sendMSG(serverID,(void*)&cols,sizeof(int));
	
	//enviar filas y columnas de matriz aleatoria
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&matriz->rows, buff, sizeof(int));
	delete buff;
	recvMSG(serverID,(void**)&buff,&dataLen);
	memcpy(&matriz->cols, buff, sizeof(int));
	delete buff;
	recvMSG(serverID,(void**)&buff,&dataLen);
	matriz->data = (int*)buff;
	
	return matriz;
	
}
