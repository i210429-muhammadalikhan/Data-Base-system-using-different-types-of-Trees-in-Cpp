#include <iostream>

#include "DSDB.h"

using namespace std;

int main() {

	DSDB dsdb;
	dsdb.run();

	return 0;
}


//int writeOnfile (char* filetext) {
//       ofstream myfile;
//       myfile.open ("checkSellExit_file_output.csv", fstream::app);
//       myfile << filetext;
//       myfile.close();
//       return 0;
//    }