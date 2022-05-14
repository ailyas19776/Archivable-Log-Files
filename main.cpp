#include <iostream>
#include "archive.h"
using namespace std;


int main(int argc, char *argv[]) {
	ios_base::sync_with_stdio(false);
	logMan logs;
	logs.getMode(argc, argv);
	logs.readingInput();
	logs.readingCommand();
	return 0;
}
