
#include <iostream>
#include "GlobalData.h"
#include "Cell.h"
#include "CellsTab.h"

using namespace std;


int main(int argc, char** argv)
{
	CellsTab cellsTab(argv[1]);
	
	cellsTab.calculations();

	return 0;
}

