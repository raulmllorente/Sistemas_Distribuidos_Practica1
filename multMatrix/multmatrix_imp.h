//Raul Martinez Llorente

#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "multmatrix.h"


class multmatrix_imp {
private:
	multMatrix* matop = nullptr;
	bool salir=false;
	int clientID=0;
public:
	multmatrix_imp(int clientID);
	~multmatrix_imp();
	void exec();
};
