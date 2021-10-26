//Raul Martinez Llorente

#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "filemanager.h"

using namespace std;

#define IP_SERVER "127.0.0.1"
#define PORT_SERVER 3301

class filemanager_stub {
private:

    int serverID = 0;
    
public:

    filemanager_stub();
    ~filemanager_stub();
    vector<string*>* listFiles();
    void readFile(char* fileName, char* &data, unsigned long int & dataLength);
    void writeFile(char* fileName, char* data, unsigned long int dataLength);
    void freeListedFiles(vector<string*>* fileList);
};
