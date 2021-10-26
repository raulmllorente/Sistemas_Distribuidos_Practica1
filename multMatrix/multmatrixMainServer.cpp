//Raul Martinez Llorente

#include "multmatrix_imp.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <thread>

void threadClient(int clientID){
	multmatrix_imp* matop = new multmatrix_imp(clientID);
	matop->exec();
	delete matop;
	
}

int main(int argc,char** argv){

	int idSocket=0;
	idSocket=initServer(3301);


	while(true){
		if(checkNewConnections()){
			int clientID=getNewConnection();
			std::thread* newThread=new std::thread(threadClient,clientID);
			newThread->detach();
		}
	}

	return 0;
}
