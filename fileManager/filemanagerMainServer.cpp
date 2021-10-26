//Raul Martinez Llorente

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include "filemanager_imp.h"

using namespace std;

void threadClient(int clientID){
	filemanager_imp* fmImp = new filemanager_imp(clientID, "./dirpruebaserv/");
	fmImp->exec();
	delete fmImp;
}

int main (int argc, char** argv){

	int idSocket = 0;
	idSocket = initServer(3301);

	while(true){
		if(checkNewConnections()){
			int clientID=getNewConnection();	
			thread* newThread=new thread(threadClient,clientID);
			newThread->detach();
		}
	}

	return 0;
}
