#pragma once
#ifndef IMPL_H
#define IMPL_H
//#include "strcasecmp.h"
#include <string.h>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "getopt.h"
#include <deque>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
using namespace std;



struct entries {
	uint32_t entryID = 0;
	string timeStamp;
	int64_t timeStampInt;
	string category;
	string message;
};





#ifdef _MSC_VER
	inline int strcasecmp(const char* s1, const char* s2) {
		return _stricmp(s1, s2);
	}
#endif

struct comp {
	bool operator()(const entries& a, const entries& b)  {
		if (a.timeStampInt == b.timeStampInt) {
			
			int result = strcasecmp(a.category.c_str(), b.category.c_str());
			if (result == 0) {//same
				return a.entryID < b.entryID;
			}
			else if (result < 0) {
				return true;
			}
			else if (result > 0) {
				return false;
			}
		}
		return a.timeStampInt < b.timeStampInt;//increasing
	}

		
	
};


class logMan {
private:
	unordered_map<std::string, std::vector<uint32_t>> category;//c
	unordered_map<std::string, std::vector<uint32_t>> keyMap;//k

	std::unordered_map<uint32_t, uint32_t> copy;

	std::vector<entries> masterLog;
	
	vector<entries>::iterator  rt1 , rt2 ;
	std::vector<uint32_t> prevSearch;
	std::string prev;
	
	
	std::deque<uint32_t> excerpt;

	bool prevSearchExists = false;
	bool t, m, c, k;
	uint16_t indexOfFile = 1;
	string fileName;
public:
	void getMode(int, char*argv[]);
	void readingCommand();
	void readingInput();
	void processEverything(char&);
};




#endif // !1
