//Raul Martinez Llorente

#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "filemanager.h"

using namespace std;

class filemanager_imp {

private:

    FileManager* fmImp = nullptr;
    bool salir = false;
    int clientID = 0;
    
public:

    filemanager_imp(int clientID, string path);
    ~filemanager_imp();
    void exec();
};
