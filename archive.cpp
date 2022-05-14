#include "archive.h"
#include <getopt.h>
using namespace std;

void logMan::getMode(int argc, char* argv[]) {
    opterr = false; // Let us handle all error output for command line options
    int choice=0, option_index = 0;//options_index is options index, choice is valueof commandLine

    option long_options[] = {//commands
            {"help", no_argument,       nullptr, 'h'},
			{ nullptr,  0 ,            nullptr, '\0'}
    };

	while((choice = getopt_long(argc, argv, "h", long_options, &option_index)) != -1){
        // colon means required argument
        switch (choice) {
        case 'h':
			cout << "No other cmd Lines!" << "\n";
			indexOfFile++;
			exit(0);
			break;
		default:
			break;
		} // switch
    } // while
	
	fileName = argv[indexOfFile];
}




void logMan::readingCommand() {
	char cmd;
	std::sort(masterLog.begin(), masterLog.end(), comp());
	for (size_t i = 0; i < masterLog.size(); i++) {
		string word;
		string extra = masterLog.at(i).category;
		for (char& c : extra) { c = static_cast<char>(tolower(c)); }
		category[extra].emplace_back(i); //index
		
		string val = masterLog.at(i).category + " " + masterLog.at(i).message;
		
		for (size_t i = 0; i < val.length(); ++i) {
			if (isalnum(val[i])) {
				val[i] = static_cast<char>(tolower(val[i]));
			}
			else {
				val[i] = ' ';
			}
		}

		stringstream ss(val);

		while (ss >> word) {
			//for (char& c : word) { c = static_cast<char>(tolower(c)); }
			//transform(word.begin(), word.end(), word.begin(), [&] (char c) {return ::tolower(c);});
			if (keyMap[word].empty() || keyMap[word].back() != i) {
				keyMap[word].emplace_back(static_cast<uint32_t>(i));
			}
		}
		copy[masterLog.at(i).entryID] = static_cast<uint32_t>(i);
	}
		
	do {
		cout << "% ";
		cin >> cmd;//m db mgr
		processEverything(cmd);
	} while (cmd != 'q');
}



void logMan::processEverything(char& cmd) {
	string t1;//t
	string matchingTimeStamp;//m
	string categories; //c
	string keyword;//k
	int append;//a
	int deletion;//d
	int begin;//b
	int end;//e
	string comment;//#
	switch(cmd) {
	case 't':
	{
		cin >> ws;
		cin >> t1; 
		prevSearch.clear();
		prevSearchExists = true;

		t1.erase(t1.begin() + 2);
		t1.erase(t1.begin() + 4);
		t1.erase(t1.begin() + 6);
		t1.erase(t1.begin() + 8);
		string timeStamp1String = t1.substr(0, 10);
		t1.erase(t1.begin() + 13);
		t1.erase(t1.begin() + 15);
		t1.erase(t1.begin() + 17);
		t1.erase(t1.begin() + 19);

		string timeStamp2String = t1.substr(11, 10);
	
		int64_t  timeStamp1 = stoll(timeStamp1String);

		int64_t timeStamp2 = stoll(timeStamp2String);

		auto temp = [](const entries& a, const int64_t b) { return a.timeStampInt < b; };//lower
		auto temp2 = [](const int64_t  b, const entries& a) { return b < a.timeStampInt; };//upper
		auto low = lower_bound(masterLog.begin(), masterLog.end(), timeStamp1, temp);
		auto up = upper_bound(low, masterLog.end(), timeStamp2, temp2);
		//prevSearch.push_back(timeStamp1);
		rt1 = low;
		//prevSearch.push_back(timeStamp2);
		rt2 = up;

		t = true;
		m = false;
		c = false;
		k = false;

		cout << "Timestamps search: " << up - low << " entries found" << "\n";
		break;
	}
	case 'm':
	{
		cin >> ws;
		getline(cin, matchingTimeStamp);
		
		prevSearch.clear();
		prevSearchExists = true;

		matchingTimeStamp.erase(matchingTimeStamp.begin() + 2);
		matchingTimeStamp.erase(matchingTimeStamp.begin() + 4);
		matchingTimeStamp.erase(matchingTimeStamp.begin() + 6);
		matchingTimeStamp.erase(matchingTimeStamp.begin() + 8);
		int64_t timeStamp1 = stoll(matchingTimeStamp);
	
		
		auto temp = [](const entries& a, const int64_t b) { return a.timeStampInt < b; };
		auto temp2 = [](const int64_t b, const entries& a) { return b < a.timeStampInt; };
		auto low = lower_bound(masterLog.begin(), masterLog.end(), timeStamp1, temp);
		auto up = upper_bound(low, masterLog.end(), timeStamp1, temp2);
		
		rt1 = low;
		rt2 = up;
		

		m = true;
		t = false;
		c = false;
		k = false;
		
		cout << "Timestamp search: " << up - low	 << " entries found" << "\n";
		break;
	}
	case 'c':
	{
		cin >> ws;
		getline(cin, categories);

		for (auto& c : categories) c = static_cast<char>(tolower(c));
	
		prevSearch.clear();
		prevSearchExists = true;
		c = true;
		m = false;
		t = false;
		k = false;
		

		auto it = category.find(categories);
		prev = categories;
		if (it != category.end()) {
			cout << "Category search: " << it->second.size() << " entries found" << "\n";
		}
		else {
			cout << "Category search: 0 entries found" << "\n";
		}
		break;
	}
	case 'k'://no square brackets, append to excerpt
	{
		prevSearchExists = true;
		prevSearch.clear();
		k = true;
		c = false;
		m = false;
		t = false;
		cin >> ws;
		getline(cin, keyword);
		vector<string> word;
		for (size_t i = 0; i < keyword.length(); ++i) {
			if (isalnum(keyword[i])) {
				keyword[i] = static_cast<char>(tolower(keyword[i]));
			}
			else {
				keyword[i] = ' ';
			}
		}
		stringstream ss(keyword);
		while (ss >> keyword) {
			word.emplace_back(keyword);
		}
		
		if (word[0].empty()) { cout << "Key	word search: 0 entries found" << "\n"; break; }
		
		//prevSearch has size 0
		uint32_t i = 0;
		if (i == 0) {
			if (keyMap.find(word[i]) != keyMap.end()) {
				prevSearch = keyMap[word[0]];
			}
		}
		for (i=1; i < word.size(); i++) {
			vector<uint32_t> temp;
			if (keyMap.find(word[i]) == keyMap.end()) {
				prevSearch.clear();
				break;
			}
			
			set_intersection(keyMap.find(word[i])->second.begin(), keyMap.find(word[i])->second.end(), prevSearch.begin(), prevSearch.end(), back_inserter(temp));
			swap(temp, prevSearch);
			//temp.resize(it - temp.begin());
		}
			//auto entries = keyMap.find(keyword.begin());

		cout << "Keyword search: " << prevSearch.size() << " entries found" << "\n";

		break;
		
	}
	case 'a':
	{
		cin >> ws;
		cin >> append;//append refers to origianl vector entryID position

		auto it = copy.find(append);
		if (it == copy.end()) {
			break;
		}

		
		if (static_cast<size_t>(it->second) < masterLog.size()) {
			excerpt.emplace_back(it->second);
			cout << "log entry " << append << " appended" << "\n";
		}
		else {
			//do nothing
		}
		break;
	}
	case 'r'://append to excerpt 
	{

		if (!prevSearchExists) {
			cerr << "Prev Search does not exist!" << "\n";
			break;
		}
		else {
			if (t == true) {
				auto it = rt2 - rt1;
				auto temp = rt1;
				while (temp  != rt2) {
					excerpt.emplace_back(temp - masterLog.begin());
					temp++;
				}
				cout << it << " log entries appended" << "\n";
				
			}
			else if (m == true) {
				auto it = rt2 - rt1;
				auto temp = rt1;
				while (temp != rt2) {
					excerpt.emplace_back(temp - masterLog.begin());
					temp++;
				}
				cout << it << " log entries appended" << "\n";
			}
			else if (c == true) {			
				auto it = category.find(prev);
				if (it != category.end()) {
					for (size_t i = 0; i < it->second.size(); i++) {
						excerpt.emplace_back(it->second[i]);
					}
					cout << it->second.size() << " log entries appended" << "\n";
				}
				else {
					cout << "0 log entries appended" << "\n";

				}
			}
			else if (k == true) {
				for (size_t i = 0; i < prevSearch.size(); i++) {
					excerpt.emplace_back(prevSearch[i]);
				}
				cout << prevSearch.size() << " log entries appended" << "\n";
			}
			
		}

		break;
	}
	case 'd'://d,e,b,s, r only taking recent?
	{
		cin >> ws;
		cin >> deletion;
		if (static_cast<size_t>(deletion) < excerpt.size()) {
			excerpt.erase(excerpt.begin() + deletion);
			cout << "Deleted excerpt list entry " << deletion << "\n";
		}
		else {
			//out of bounds
		}
		break;
	}
	case 'b'://moved to beginning?
	{
		cin >> ws;
		cin >> begin;//refers to masterLog entry?
		if (static_cast<size_t>(begin) < excerpt.size()) {
			rotate(excerpt.begin(), excerpt.begin()+begin, excerpt.begin()+begin+1);
			cout << "Moved excerpt list entry " << begin << "\n";
		}
		else {
			//out of bounds
		}
		break;
	}
	case 'e':
	{
		cin >> ws;
		cin >> end;
		if (static_cast<size_t>(end) < excerpt.size()) {
			int temp = excerpt[end];
			excerpt.erase(excerpt.begin() + end);
			excerpt.emplace_back(temp);
			//rotate(excerpt.rbegin()+end, excerpt.rbegin()+end+1, excerpt.rend());
			cout << "Moved excerpt list entry " << end << "\n";
		}
		else {
			//out of size
		}
		break;
	}
	case 's':
		if (excerpt.size() == 0) {
			cout << "excerpt list sorted\n(previously empty)" << "\n"; 
			break;
		}
		
		cout << "excerpt list sorted\nprevious ordering:\n";
		
		cout << 0 << "|" << masterLog[excerpt[0]].entryID << "|" << masterLog[excerpt[0]].timeStamp <<
			"|" << masterLog[excerpt[0]].category << "|" << masterLog[excerpt[0]].message << "\n";
		cout << "..." << "\n";
		cout << excerpt.size() - 1 << "|" << masterLog[excerpt[excerpt.size() - 1]].entryID << "|" << masterLog[excerpt[excerpt.size() - 1]].timeStamp <<
			"|" << masterLog[excerpt[excerpt.size() - 1]].category << "|" << masterLog[excerpt[excerpt.size() - 1]].message << "\n";

		
		std::sort(excerpt.begin(), excerpt.end());
		
		cout << "new ordering:\n";
		
		cout << 0 << "|" << masterLog[excerpt[0]].entryID << "|" << masterLog[excerpt[0]].timeStamp <<
			"|" << masterLog[excerpt[0]].category << "|" << masterLog[excerpt[0]].message << "\n";
		cout << "..." << "\n";
		cout << excerpt.size() - 1 << "|" << masterLog[excerpt[excerpt.size() - 1]].entryID << "|" << masterLog[excerpt[excerpt.size() - 1]].timeStamp <<
			"|" << masterLog[excerpt[excerpt.size() - 1]].category << "|" << masterLog[excerpt[excerpt.size() - 1]].message << "\n";
		break;
	case 'l':
		if (excerpt.empty()) {
			cout << "excerpt list cleared\n(previously empty)\n";
		}
		else {
			cout << "excerpt list cleared\nprevious contents:\n";
			
				cout << 0 << "|" << masterLog[excerpt[0]].entryID << "|" << masterLog[excerpt[0]].timeStamp <<
					"|" << masterLog[excerpt[0]].category << "|" << masterLog[excerpt[0]].message << "\n";
				cout << "..." << "\n";
				cout << excerpt.size()-1 << "|" << masterLog[excerpt[excerpt.size()-1]].entryID << "|" << masterLog[excerpt[excerpt.size() - 1]].timeStamp <<
					"|" << masterLog[excerpt[excerpt.size() - 1]].category << "|" << masterLog[excerpt[excerpt.size() - 1]].message << "\n";

				// 0|10|07:02:10:12:43|PGM|Beginning master election.
			excerpt.clear();
		}
		break;
	case 'g':
		if (!prevSearchExists) {
			cerr << "Prev Search does not exist!" << "\n";
			break;
		}
		else {
			if (t == true) {
				auto temp = rt1;
				while (temp != rt2) {
					cout << masterLog[temp - masterLog.begin()].entryID << "|" << masterLog[temp - masterLog.begin()].timeStamp <<
						"|" << masterLog[temp - masterLog.begin()].category << "|" << masterLog[temp - masterLog.begin()].message << "\n";
					temp++;
				}
			}
			else if (m == true) {
				auto temp = rt1;
				while (rt1 != rt2) {
					cout << masterLog[temp - masterLog.begin()].entryID << "|" << masterLog[temp - masterLog.begin()].timeStamp <<
						"|" << masterLog[temp - masterLog.begin()].category << "|" << masterLog[temp - masterLog.begin()].message << "\n";
					temp++;
				}
			}
			else if (c == true) {
				auto it = category.find(prev);
				if (it != category.end()) {
					for (size_t i = 0; i < it->second.size(); i++) {
						cout << masterLog[it->second[i]].entryID << "|" << masterLog[it->second[i]].timeStamp <<
							"|" << masterLog[it->second[i]].category << "|" << masterLog[it->second[i]].message << "\n";
					}
				}
			}
			else if (k == true) {
				for (size_t i = 0; i < prevSearch.size(); i++) {
					cout << masterLog[prevSearch[i]].entryID << "|" << masterLog[prevSearch[i]].timeStamp <<
						"|" << masterLog[prevSearch[i]].category << "|" << masterLog[prevSearch[i]].message << "\n";
				}
			}
		}
		break;
	case 'p':
	{
		for (size_t i = 0; i < excerpt.size(); i++) {
			cout << i << "|" << masterLog[excerpt[i]].entryID << "|" << masterLog[excerpt[i]].timeStamp <<
				"|" << masterLog[excerpt[i]].category << "|" << masterLog[excerpt[i]].message << "\n";
		}
		break;
	}
	case '#':
		getline(cin, comment);
		break;
	case 'q':
		break;
	default:
		cerr << "Command not recognized" << "\n";
		break;
	}
}



void logMan::readingInput() {
	string line; int id = 0; int index = 0;
	uint32_t numEntries = 0;
	ifstream ifz{fileName};

	string ts, cat, msg;
	while (getline(ifz, ts, '|')) {
		numEntries++;
		entries entry;
		entry.entryID = id++;
		if (ts.size() != 14) {
			ts.clear();
			continue;
		}


		entry.timeStamp = ts;
		ts.erase(ts.begin() + 2);
		ts.erase(ts.begin() + 4);
		ts.erase(ts.begin() + 6);
		ts.erase(ts.begin() + 8);

		entry.timeStampInt = stoll(ts);

		getline(ifz, cat, '|');
		entry.category = cat;


		getline(ifz, msg);
		entry.message = msg;

		masterLog.emplace_back(entry);
		++index;
	}

	cout << numEntries << " entries read" << "\n";
	ifz.close();
}
