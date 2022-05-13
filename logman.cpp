//01BD41C3BF016AD7E8B6F837DF18926EC3E83350
#include <iostream>
#include "impl.h"
using namespace std;


int main(int argc, char *argv[]) {
	ios_base::sync_with_stdio(false);
	logMan logs;
	logs.getMode(argc, argv);
	logs.readingInput();
	logs.readingCommand();
	return 0;
}