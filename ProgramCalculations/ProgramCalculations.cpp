
#include <iostream>
#include "GlobalData.h"
#include "Cell.h"
#include "CellsTab.h"
#include "Calculations.h"

using namespace std;


int main(int argc, char** argv)
{	
	if (argc > 1) {
		Calculations c(argv[1]);
		c.calculate();
	}
		
	
		return 0;
}

