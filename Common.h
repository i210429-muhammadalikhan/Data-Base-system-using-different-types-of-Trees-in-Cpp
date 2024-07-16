#pragma once
// contains utility functions

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

//#include <filesystem>
#include "AVL.h"
#include "Btree.h"
#include "RBtree.h"
#include "RecordLinkedList.h"

using namespace std;

class Common {

public:
	Common() {
	}

	static int convertStringToInt(string s) {
		stringstream d(s);
		int x = 0;
		d >> x;
		return x;
	}

	// static string convertIntToString(int i) {
	// 	std::ostringstream ss;
	//     ss << i;
	//     return ss.str();
	// }

	// get AVL index based records with respect to user input
	RecordLinkedList<string> getAVLIndexBasedRecordsWrtUserInput(int indexField, int treeType, string userInput) {

		// Record r("1","2016","Accidents (unintentional injuries) (V01-X59,Y85-Y86)","Unintentional injuries","Alabama","2755","55.5");
		// RecordLinkedList<string> list;
		// list.insert("", r);
		// list.print();

		// Load Node Data from Index File
		string fileName = "";
		if (treeType == 1) {
			fileName = "data/indexes/AVLIndex.csv";
		}
		else if (treeType == 2) {
			fileName = "data/indexes/BtreeIndex.csv";
		}
		else if (treeType == 3) {
			fileName = "data/indexes/RBtreeIndex.csv";
		}

		RecordLinkedList<string> list;
		fstream file;
		file.open(fileName, ios::in);
		if (file.is_open()) {

			string line, key, dataFileName, lineNo;
			while (getline(file, line)) {
				stringstream ss(line);
				getline(ss, key, ',');
				getline(ss, dataFileName, ',');
				getline(ss, lineNo, ',');

				//	key == indexField
				if (key != "" && indexField == 1 && key == userInput)
				{
					//cout << "going to get data from file: " << dataFileName << " - " << lineNo << endl;
					// Porceed futher with search, search in data files
					Record r = getRecordFromDataFile(dataFileName, convertStringToInt(lineNo));

					// cout << "found record" << endl;
					// cout << r.getId()<< endl;
					// cout << r.getYear() << endl;
					// cout << r.getCauseName113() << endl;
					// cout << r.getCauseName() << endl;
					// cout << r.getState() << endl;
					// cout << r.getDeaths() << endl;
					// cout << r.getRate() << endl;

					if (r.getId() != "" && r.getYear() != "" && r.getCauseName113() != "") {
						list.insert("", r);
						break;
					}
				}
				else if (key == userInput) {
					// Porceed futher with search, search in data files
					Record r = getRecordFromDataFile(dataFileName, convertStringToInt(lineNo));
					if (r.getId() != "" && r.getYear() != "" && r.getCauseName113() != "")
						list.insert("", r);
				}
			}
		}
		file.close();
		return list;
	}

	// get AVL index based records with respect to user input
	RecordLinkedList<string> getAVLIndexBasedRecordsWrtUserInputRange(int treeType, int startingRange, int endingRange) {

		string fileName = "";
		if (treeType == 1) {
			fileName = "data/indexes/AVLIndex.csv";
		}
		else if (treeType == 2) {
			fileName = "data/indexes/BtreeIndex.csv";
		}
		else if (treeType == 3) {
			fileName = "data/indexes/RBtreeIndex.csv";
		}

		RecordLinkedList<string> list;
		fstream file;
		file.open(fileName, ios::in);
		if (file.is_open()) {

			string line, key, dataFileName, lineNo;
			while (getline(file, line)) {
				stringstream ss(line);
				getline(ss, key, ',');
				getline(ss, dataFileName, ',');
				getline(ss, lineNo, ',');
				int k = convertStringToInt(key);
				if (key != "" && (k >= startingRange && k <= endingRange))
				{
					//cout << k << endl;
					Record r = getRecordFromDataFile(dataFileName, convertStringToInt(lineNo));
					if (r.getId() != "" && r.getYear() != "" && r.getCauseName113() != "")
						list.insert("", r);
				}
			}
		}
		file.close();
		return list;
	}
	// lineNo means required row from excel
	Record getRecordFromDataFile(string dataFileName, int lineNo) {
		Record r;
		int excelLine = 2;
		fstream file;
		file.open(dataFileName, ios::in);
		if (file.is_open()) {

			string line, skip;
			string id;
			string year;
			string causeName113;
			string causeName;
			string state;
			string deaths;
			string rate;

			//cout << "requried line: " << lineNo << ", excelLine " << excelLine << endl;

			// if (dataFileName.find("1.csv") != std::string::npos || dataFileName.find("6.csv") != std::string::npos || dataFileName.find("8.csv") != std::string::npos || dataFileName.find("10.csv") != std::string::npos)
			// {
			getline(file, line);		 					// SKIP First Line in csv it has headings
			while (getline(file, line)) {
				stringstream ss(line);
				//cout << line << endl;
				//cout << "requried line: " << lineNo << ", excelLine " << excelLine << endl;

				if (excelLine == lineNo) {

					getline(ss, id, ',');
					getline(ss, year, ',');

					if (ss.peek() == '"') {
						string csvElement;
						ss >> std::quoted(csvElement);
						causeName113 = csvElement;
						getline(ss, skip, ',');
					}
					else {
						getline(ss, causeName113, ',');
					}
					getline(ss, causeName, ',');
					getline(ss, state, ',');
					getline(ss, deaths, ',');
					getline(ss, rate);

					// cout << id << "id"<< "\n";				
					// cout << year << "year"<<"\n";				
					// cout << causeName113 << "causeName113"<<"\n";				
					// cout << causeName << "causeName" << "\n";				
					// cout << state << "state"<<"\n";				
					// cout << deaths << "deaths"<<"\n";				
					// cout << rate << "rate"<< "\n";				

					r.setId(id);
					r.setYear(year);
					r.setCauseName113(causeName113);
					r.setCauseName(causeName);
					r.setState(state);
					r.setDeaths(deaths);
					r.setRate(rate);

					break;
				}
				excelLine++;
			}
			// } else
			// {
			// 	getline(file, line);		 					// SKIP First Line in csv it has headings
			// 	while (getline(file, line)) {
			// 		stringstream ss(line);

			// 		if(excelLine == lineNo) {
			// 			getline(ss, id, ',');
			// 			getline(ss, year, ',');
			// 			getline(ss, causeName113, ',');
			// 			getline(ss, causeName, ',');	
			// 			getline(ss, state, ',');	
			// 			getline(ss, deaths, ',');	
			// 			getline(ss, rate);	

			// 			r.setId(id);
			// 			r.setYear(year);
			// 			r.setCauseName113(causeName113);
			// 			r.setCauseName(causeName);
			// 			r.setState(state);
			// 			r.setDeaths(deaths);
			// 			r.setRate(rate);
			// 			break;
			// 		} else {
			// 			getline(ss, id, ',');
			// 			getline(ss, year, ',');
			// 			getline(ss, causeName113, ',');
			// 			getline(ss, causeName, ',');	
			// 			getline(ss, state, ',');	
			// 			getline(ss, deaths, ',');	
			// 			getline(ss, rate);		
			// 		}
			// 		excelLine++;
			// 	}
			// }
		}
		file.close();
		return r;
	}

	bool update(int key, string keyValue, int field, string oldValue, string newValue) {

		string dfileName; // = "data/NCHS_-_Leading_Causes_of_Death__United_States_1.csv";	
		Record oldRecord;
		Record newRecord;
		for (int i = 1; i < 11; i++)
		{
			dfileName = "data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(i) + ".csv";
			fstream dfile;

			string fileName = "data/temp.csv";
			try {
				std::filesystem::remove(fileName);
			}
			catch (const std::exception& e) {
				cout << "File already deleted" << endl;
			}

			ofstream file;

			dfile.open(dfileName, fstream::in);
			if (dfile.is_open()) {
				string line, id, year, causeName113, skip, causeName, state, deaths, rate;
				getline(dfile, line);
				while (getline(dfile, line)) {
					stringstream ss(line);

					getline(ss, id, ',');
					getline(ss, year, ',');

					if (ss.peek() == '"') {
						string csvElement;
						ss >> std::quoted(csvElement);
						causeName113 = csvElement;
						// add quotes back
						causeName113 = '"' + causeName113 + '"';
						getline(ss, skip, ',');
					}
					else {
						getline(ss, causeName113, ',');
					}

					getline(ss, causeName, ',');
					getline(ss, state, ',');
					getline(ss, deaths, ',');
					getline(ss, rate);


					if (key == 1 && keyValue == id) {
						oldRecord.setId(id);
						oldRecord.setYear(year);
						oldRecord.setCauseName113(causeName113);
						oldRecord.setCauseName(causeName);
						oldRecord.setState(state);
						oldRecord.setDeaths(deaths);
						oldRecord.setRate(rate);
						newRecord = updateRecord(field, oldValue, newValue, oldRecord);

						id = newRecord.getId();
						year = newRecord.getYear();
						causeName = newRecord.getCauseName();
						state = newRecord.getState();
						deaths = newRecord.getDeaths();
						rate = newRecord.getRate();

					}
					else if (key == 2 && keyValue == year) {
						oldRecord.setId(id);
						oldRecord.setYear(year);
						oldRecord.setCauseName113(causeName113);
						oldRecord.setCauseName(causeName);
						oldRecord.setState(state);
						oldRecord.setDeaths(deaths);
						oldRecord.setRate(rate);
						newRecord = updateRecord(field, oldValue, newValue, oldRecord);

						id = newRecord.getId();
						year = newRecord.getYear();
						causeName = newRecord.getCauseName();
						state = newRecord.getState();
						deaths = newRecord.getDeaths();
						rate = newRecord.getRate();

					}
					else if (key == 3 && keyValue == causeName) {
						oldRecord.setId(id);
						oldRecord.setYear(year);
						oldRecord.setCauseName113(causeName113);
						oldRecord.setCauseName(causeName);
						oldRecord.setState(state);
						oldRecord.setDeaths(deaths);
						oldRecord.setRate(rate);
						newRecord = updateRecord(field, oldValue, newValue, oldRecord);

						id = newRecord.getId();
						year = newRecord.getYear();
						causeName = newRecord.getCauseName();
						state = newRecord.getState();
						deaths = newRecord.getDeaths();
						rate = newRecord.getRate();

					}
					else if (key == 4 && keyValue == state) {
						oldRecord.setId(id);
						oldRecord.setYear(year);
						oldRecord.setCauseName113(causeName113);
						oldRecord.setCauseName(causeName);
						oldRecord.setState(state);
						oldRecord.setDeaths(deaths);
						oldRecord.setRate(rate);
						newRecord = updateRecord(field, oldValue, newValue, oldRecord);

						id = newRecord.getId();
						year = newRecord.getYear();
						causeName = newRecord.getCauseName();
						state = newRecord.getState();
						deaths = newRecord.getDeaths();
						rate = newRecord.getRate();

					}
					else if (key == 5 && keyValue == deaths) {
						oldRecord.setId(id);
						oldRecord.setYear(year);
						oldRecord.setCauseName113(causeName113);
						oldRecord.setCauseName(causeName);
						oldRecord.setState(state);
						oldRecord.setDeaths(deaths);
						oldRecord.setRate(rate);
						newRecord = updateRecord(field, oldValue, newValue, oldRecord);

						id = newRecord.getId();
						year = newRecord.getYear();
						causeName = newRecord.getCauseName();
						state = newRecord.getState();
						deaths = newRecord.getDeaths();
						rate = newRecord.getRate();

					}
					else if (key == 6 && keyValue == rate) {
						oldRecord.setId(id);
						oldRecord.setYear(year);
						oldRecord.setCauseName113(causeName113);
						oldRecord.setCauseName(causeName);
						oldRecord.setState(state);
						oldRecord.setDeaths(deaths);
						oldRecord.setRate(rate);
						newRecord = updateRecord(field, oldValue, newValue, oldRecord);

						id = newRecord.getId();
						year = newRecord.getYear();
						causeName = newRecord.getCauseName();
						state = newRecord.getState();
						deaths = newRecord.getDeaths();
						rate = newRecord.getRate();
					}

					// WRITES TO BE DONE OUTSIDE SWITCH

					// FOR UPDATE
					/*
					if(key == "ID") {}
					else if(key == "CAUSENAME113") {}
					else if(key == "CAUSENAME") {}
					else if(key == "STATE") {
						if (state == oldValue) {
							state = newValue;
						}
					}
					*/

					if (!file.is_open()) {
						file.open(fileName, fstream::app);
						file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
						file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
					}
					else {
						file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
					}
				}

				file.close();
				dfile.close();
				try {
					std::filesystem::remove(dfileName);
				}
				catch (const std::exception& e) {
					cout << "File already deleted" << endl;
				}
				rename(fileName.c_str(), dfileName.c_str()); 	// using c_str() to convert string to char*
			}
		}
		return true;
	}

	Record updateRecord(int field, string oldValue, string newValue, Record r) {
		switch (field) {
		case 1: {
			if (r.getId() == oldValue) {
				r.setId(newValue);
			}
			break;
		}
		case 2: {
			if (r.getYear() == oldValue) {
				r.setYear(newValue);
			}
			break;
		}
		case 3: {
			if (r.getCauseName() == oldValue) {
				r.setCauseName(newValue);
			}
			break;
		}
		case 4: {
			if (r.getState() == oldValue) {
				r.setState(newValue);
			}
			break;
		}
		case 5: {
			if (r.getDeaths() == oldValue) {
				r.setDeaths(newValue);
			}
			break;
		}
		case 6: {
			if (r.getRate() == oldValue) {
				r.setRate(newValue);
			}
			break;
		}
		}
		return r;
	}

	bool deleteKey(int key, string keyVal) {

		string dfileName; // = "data/NCHS_-_Leading_Causes_of_Death__United_States_1.csv";	

		for (int i = 1; i < 11; i++)
		{
			dfileName = "data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(i) + ".csv";
			fstream dfile;

			string fileName = "data/temp.csv";
			try {
				std::filesystem::remove(fileName);
			}
			catch (const std::exception& e) {
				cout << "File already deleted" << endl;
			}

			ofstream file;

			dfile.open(dfileName, fstream::in);
			if (dfile.is_open()) {
				string line, id, year, causeName113, skip, causeName, state, deaths, rate;
				getline(dfile, line);
				while (getline(dfile, line)) {
					stringstream ss(line);

					getline(ss, id, ',');
					getline(ss, year, ',');

					if (ss.peek() == '"') {
						string csvElement;
						ss >> std::quoted(csvElement);
						causeName113 = csvElement;
						// add quotes back
						causeName113 = '"' + causeName113 + '"';
						getline(ss, skip, ',');
					}
					else {
						getline(ss, causeName113, ',');
					}

					getline(ss, causeName, ',');
					getline(ss, state, ',');
					getline(ss, deaths, ',');
					getline(ss, rate);


					// FOR UPDATE
					/*
					if(key == "ID") {}
					else if(key == "CAUSENAME113") {}
					else if(key == "CAUSENAME") {}
					else if(key == "STATE") {
						if (state == oldValue) {
							state = newValue;
						}
					}
					*/

					// FOR DELETE
					if ((key == 1 && keyVal != id) ||
						(key == 2 && keyVal != year) ||
						//(key == "CAUSENAME113" && keyVal != causeName113) ||
						(key == 3 && keyVal != causeName) ||
						(key == 4 && keyVal != state) ||
						(key == 5 && keyVal != deaths) ||
						(key == 6 && keyVal != rate)
						) {
						if (!file.is_open()) {
							file.open(fileName, fstream::app);
							file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
							file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
						}
						else {
							file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
						}
					}
				}

				file.close();
				dfile.close();
				try {
					std::filesystem::remove(dfileName);
				}
				catch (const std::exception& e) {
					cout << "File already deleted" << endl;
				}
				rename(fileName.c_str(), dfileName.c_str()); 	// using c_str() to convert string to char*
			}
		}
		return true;
	}

	/*
	bool searchWrtWhereClause(int key, string query) {
		string str = query;

		unsigned first = str.find("DELETE");
		unsigned last = str.find("WHERE");

		first = str.find("=");
		last = str.find(";");
		string strNew = str.substr (first, last - first);
		strNew = strNew.substr(1);
		string fieldValue = regex_replace(strNew, std::regex("^ +| +$|( ) +"), "$1");
		cout << fieldValue << endl;
	}
	*/

	bool deleteWrtWhereClause(int key, string query) {
		string str = query;
		string where = "WHERE";
		string del = "DELETE";

		unsigned first = str.find("DELETE");
		unsigned last = str.find("WHERE");

		string strNew = str.substr(first, last);
		strNew = strNew.substr(del.size());
		string keyValue = regex_replace(strNew, std::regex("^ +| +$|( ) +"), "$1");
		cout << keyValue << endl;

		first = str.find("WHERE");
		last = str.find("=");

		strNew = str.substr(first, last - first);
		strNew = strNew.substr(where.size());
		string field = regex_replace(strNew, std::regex("^ +| +$|( ) +"), "$1");
		cout << field << endl;


		first = str.find("=");
		last = str.find(";");
		strNew = str.substr(first, last - first);
		strNew = strNew.substr(1);
		string fieldValue = regex_replace(strNew, std::regex("^ +| +$|( ) +"), "$1");
		cout << fieldValue << endl;


		deleteWrtKeyAndField(key, keyValue, getField(field), fieldValue);

		return true;
	}

	bool deleteWrtKeyAndField(int key, string keyVal, int field, string fieldValue) {
		string dfileName; // = "data/NCHS_-_Leading_Causes_of_Death__United_States_1.csv";	
		cout << "field: " << field << endl;
		cout << "key: " << key << endl;
		for (int i = 1; i < 11; i++)
		{
			dfileName = "data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(i) + ".csv";
			fstream dfile;

			string fileName = "data/temp.csv";
			try {
				std::filesystem::remove(fileName);
			}
			catch (const std::exception& e) {
				cout << "File already deleted" << endl;
			}

			ofstream file;

			dfile.open(dfileName, fstream::in);
			if (dfile.is_open()) {
				string line, id, year, causeName113, skip, causeName, state, deaths, rate;
				getline(dfile, line);
				while (getline(dfile, line)) {
					stringstream ss(line);

					getline(ss, id, ',');
					getline(ss, year, ',');

					if (ss.peek() == '"') {
						string csvElement;
						ss >> std::quoted(csvElement);
						causeName113 = csvElement;
						// add quotes back
						causeName113 = '"' + causeName113 + '"';
						getline(ss, skip, ',');
					}
					else {
						getline(ss, causeName113, ',');
					}

					getline(ss, causeName, ',');
					getline(ss, state, ',');
					getline(ss, deaths, ',');
					getline(ss, rate);


					// FOR UPDATE
					/*
					if(key == "ID") {}
					else if(key == "CAUSENAME113") {}
					else if(key == "CAUSENAME") {}
					else if(key == "STATE") {
						if (state == oldValue) {
							state = newValue;
						}
					}
					*/

					// FOR DELETE
					/*
					if((key == 1 && keyVal != id) ||
						(key == 2 && keyVal != year) ||
						//(key == "CAUSENAME113" && keyVal != causeName113) ||
						(key == 3 && keyVal != causeName) ||
						(key == 4 && keyVal != state) ||
						(key == 5 && keyVal != deaths) ||
						(key == 6 && keyVal != rate)
					) {
						switch (field)
						{
							case 1:
								if (fieldValue != id) {
									if(!file.is_open()) {
										file.open(fileName, fstream::app);
										file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
										file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
									} else {
										file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
									}
								}
								break;
							case 2:
								if (fieldValue != year) {
									if(!file.is_open()) {
										file.open(fileName, fstream::app);
										file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
										file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
									} else {
										file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
									}
								}
								break;
							case 3:
								if (fieldValue != causeName) {
									if(!file.is_open()) {
										file.open(fileName, fstream::app);
										file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
										file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
									} else {
										file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
									}
								}
								break;
							case 4:
								if (fieldValue != state) {
									if(!file.is_open()) {
										file.open(fileName, fstream::app);
										file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
										file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
									} else {
										file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
									}
								}
								break;
							case 5:
								if (fieldValue != deaths) {
									if(!file.is_open()) {
										file.open(fileName, fstream::app);
										file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
										file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
									} else {
										file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
									}
								}
								break;
							case 6:
								if (fieldValue != rate) {
									if(!file.is_open()) {
										file.open(fileName, fstream::app);
										file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
										file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
									} else {
										file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
									}
								}
								break;
						}
					}
					*/


					switch (key)
					{
					case 1: {
						switch (field)
						{
						case 1:
							if (keyVal == id && fieldValue == id) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 2:
							if (keyVal == id && fieldValue == year) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 3:
							if (keyVal == id && fieldValue == causeName) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 4:
							if (keyVal == id && fieldValue == state) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 5:
							if (keyVal == id && fieldValue == deaths) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 6:
							if (keyVal == id && fieldValue == rate) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						}
						break;
					}
					case 2: {
						switch (field)
						{
						case 1:
							if (keyVal == year && fieldValue == id) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 2:
							if (keyVal == year && fieldValue == year) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 3:
							if (keyVal == year && fieldValue == causeName) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 4:
							if (keyVal == year && fieldValue == state) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 5:
							if (keyVal == year && fieldValue == deaths) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 6:
							if (keyVal == year && fieldValue == rate) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						}
						break;
					}
					case 3: {
						switch (field)
						{
						case 1:
							if (keyVal == causeName && fieldValue == id) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 2:
							if (keyVal == causeName && fieldValue == year) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 3:
							if (keyVal == causeName && fieldValue == causeName) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 4:
							if (keyVal == causeName && fieldValue == state) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 5:
							if (keyVal == causeName && fieldValue == deaths) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 6:
							if (keyVal == causeName && fieldValue == rate) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						}
						break;
					}
					case 4: {
						switch (field)
						{
						case 1:
							if (keyVal == state && fieldValue == id) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 2:
							if (keyVal == state && fieldValue == year) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 3:
							if (keyVal == state && fieldValue == causeName) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 4:
							if (keyVal == state && fieldValue == state) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 5:
							if (keyVal == state && fieldValue == deaths) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 6:
							if (keyVal == state && fieldValue == rate) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						}
						break;
					}
					case 5: {
						switch (field)
						{
						case 1:
							if (keyVal == deaths && fieldValue == id) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 2:
							if (keyVal == deaths && fieldValue == year) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 3:
							if (keyVal == deaths && fieldValue == causeName) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 4:
							if (keyVal == deaths && fieldValue == state) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 5:
							if (keyVal == deaths && fieldValue == deaths) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 6:
							if (keyVal == deaths && fieldValue == rate) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						}
						break;
					}
					case 6: {
						switch (field)
						{
						case 1:
							if (keyVal == rate && fieldValue == id) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 2:
							if (keyVal == rate && fieldValue == year) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 3:
							if (keyVal == rate && fieldValue == causeName) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 4:
							if (keyVal == rate && fieldValue == state) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 5:
							if (keyVal == rate && fieldValue == deaths) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						case 6:
							if (keyVal == rate && fieldValue == rate) { continue; }
							else {
								if (!file.is_open()) {
									file.open(fileName, fstream::app);
									file << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate";
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
								else {
									file << "\n" << id << "," << year << "," << causeName113 << "," << causeName << "," << state << "," << deaths << "," << rate;
								}
							}
							break;
						}
						break;
					}
					}
				}

				file.close();
				dfile.close();
				try {
					std::filesystem::remove(dfileName);
				}
				catch (const std::exception& e) {
					cout << "File already deleted" << endl;
				}
				rename(fileName.c_str(), dfileName.c_str()); 	// using c_str() to convert string to char*
			}
		}
		return true;
	}

	bst<int> loadIntDataInAvlTree(int key) {

		bst<int> obj;	// AVL

		string fileName;
		for (int i = 1; i < 11; i++)
		{
			fileName = "data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(i) + ".csv";

			fstream dataFile;
			dataFile.open(fileName, ios::in);
			if (dataFile.is_open()) {

				string id;
				string year;
				string causeName113;
				string causeName;
				string state;
				string deaths;
				string rate;
				string skip;

				int count = 0;
				string line;
				//cout << key;

				if (key == 1 || key == 2 || key == 5 || key == 6) {

					int lineNo = 2;
					getline(dataFile, line);		 // SKIP First Line in csv it has headings
					while (getline(dataFile, line)) {
						stringstream ss(line);
						// getline(ss, id, ',');
						// getline(ss, year, ',');
						//cout << id << "\n";	


						getline(ss, id, ',');
						getline(ss, year, ',');

						if (ss.peek() == '"') {
							string csvElement;
							ss >> std::quoted(csvElement);
							causeName113 = csvElement;
							getline(ss, skip, ',');
						}
						else {
							getline(ss, causeName113, ',');
						}

						getline(ss, causeName, ',');
						getline(ss, state, ',');
						getline(ss, deaths, ',');
						getline(ss, rate);

						switch (key)
						{
						case 1: {
							obj.insert(convertStringToInt(id), fileName, to_string(lineNo));
							break;
						}
						case 2: {
							obj.insert(convertStringToInt(year), fileName, to_string(lineNo));
							break;
						}
						case 5: {
							obj.insert(convertStringToInt(deaths), fileName, to_string(lineNo));
							break;
						}
						case 6: {
							obj.insert(convertStringToInt(rate), fileName, to_string(lineNo));
							break;
						}
						}
						lineNo++;
					}
				}
			}
			dataFile.close();
		}
		return obj;
	}

	BTree<int> loadIntDataInBTree(int key, int d) {

		BTree<int> obj(d);	// Btree

		string fileName;
		for (int i = 1; i < 11; i++)
		{
			fileName = "data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(i) + ".csv";

			fstream dataFile;
			dataFile.open(fileName, ios::in);
			if (dataFile.is_open()) {

				string id;
				string year;
				string causeName113;
				string causeName;
				string state;
				string deaths;
				string rate;
				string skip;

				int count = 0;
				string line;
				//cout << key;

				if (key == 1 || key == 2 || key == 5 || key == 6) {

					int lineNo = 2;
					getline(dataFile, line);		 // SKIP First Line in csv it has headings
					while (getline(dataFile, line)) {
						stringstream ss(line);
						getline(ss, id, ',');
						getline(ss, year, ',');

						if (ss.peek() == '"') {
							string csvElement;
							ss >> std::quoted(csvElement);
							causeName113 = csvElement;
							getline(ss, skip, ',');
						}
						else {
							getline(ss, causeName113, ',');
						}

						getline(ss, causeName, ',');
						getline(ss, state, ',');
						getline(ss, deaths, ',');
						getline(ss, rate);

						switch (key)
						{
						case 1: {
							obj.insert(fileName, to_string(lineNo), convertStringToInt(id));
							break;
						}
						case 2: {
							obj.insert(fileName, to_string(lineNo), convertStringToInt(year));
							break;
						}
						case 5: {
							obj.insert(fileName, to_string(lineNo), convertStringToInt(deaths));
							break;
						}
						case 6: {
							obj.insert(fileName, to_string(lineNo), convertStringToInt(rate));
							break;
						}
						}

						// cout << id << "\n";	
						//obj.insert(fileName, to_string(lineNo), convertStringToInt(id));

						lineNo++;
					}
				}
			}
			dataFile.close();
		}
		return obj;
	}

	RBTree<int> loadIntDataInRBTree(int key) {

		RBTree<int> obj;	// Btree

		string fileName;
		for (int i = 1; i < 11; i++)
		{
			fileName = "data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(i) + ".csv";

			fstream dataFile;
			dataFile.open(fileName, ios::in);
			if (dataFile.is_open()) {

				string id;
				string year;
				string causeName113;
				string causeName;
				string state;
				string deaths;
				string rate;
				string skip;

				int count = 0;
				string line;
				//cout << key;

				if (key == 1 || key == 2 || key == 5 || key == 6) {

					int lineNo = 2;
					getline(dataFile, line);		 // SKIP First Line in csv it has headings
					while (getline(dataFile, line)) {
						stringstream ss(line);
						getline(ss, id, ',');
						getline(ss, year, ',');

						if (ss.peek() == '"') {
							string csvElement;
							ss >> std::quoted(csvElement);
							causeName113 = csvElement;
							getline(ss, skip, ',');
						}
						else {
							getline(ss, causeName113, ',');
						}

						getline(ss, causeName, ',');
						getline(ss, state, ',');
						getline(ss, deaths, ',');
						getline(ss, rate);

						switch (key)
						{
						case 1: {
							obj.insert(convertStringToInt(id), fileName, to_string(lineNo));
							break;
						}
						case 2: {
							obj.insert(convertStringToInt(year), fileName, to_string(lineNo));
							break;
						}
						case 5: {
							obj.insert(convertStringToInt(deaths), fileName, to_string(lineNo));
							break;
						}
						case 6: {
							obj.insert(convertStringToInt(rate), fileName, to_string(lineNo));
							break;
						}
						}
						lineNo++;
					}
				}
			}
			dataFile.close();
		}
		return obj;
	}

	RBTree<string> loadStringDataInRBTree(int key) {

		// string fileName = "data/NCHS_-_Leading_Causes_of_Death__United_States_10.csv";
		RBTree<string> obj;
		fstream file;

		string fileName;
		for (int i = 1; i < 11; i++)
		{
			fileName = "data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(i) + ".csv";
			file.open(fileName, ios::in);
			if (file.is_open()) {

				string id;
				string year;
				string causeName113;
				string causeName;
				string state;
				string deaths;
				string rate;
				string skip;

				int count = 0;
				string line;

				int lineNo = 2;
				// -------------------------------------------------------------

				getline(file, line);		 					// SKIP First Line in csv it has headings
				while (getline(file, line)) {
					stringstream ss(line);

					getline(ss, id, ',');
					getline(ss, year, ',');

					if (ss.peek() == '"') {
						string csvElement;
						ss >> std::quoted(csvElement);
						causeName113 = csvElement;
						getline(ss, skip, ',');
					}
					else {
						getline(ss, causeName113, ',');
					}
					getline(ss, causeName, ',');
					getline(ss, state, ',');
					getline(ss, deaths, ',');
					getline(ss, rate);

					switch (key)
					{
					case 3: {
						obj.insert(causeName, fileName, to_string(lineNo));
						break;
					}
					case 4: {
						obj.insert(state, fileName, to_string(lineNo));
						break;
					}
					}
					lineNo++;
				}
				file.close();
			}
		}
		return obj;
	}

	bst<string> loadStringDataInAvlTree(int key) {

		// string fileName = "data/NCHS_-_Leading_Causes_of_Death__United_States_10.csv";
		bst<string> obj;
		fstream file;

		string fileName;
		for (int i = 1; i < 11; i++)
		{
			fileName = "data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(i) + ".csv";
			file.open(fileName, ios::in);
			if (file.is_open()) {

				string id;
				string year;
				string causeName113;
				string causeName;
				string state;
				string deaths;
				string rate;
				string skip;

				int count = 0;
				string line;

				int lineNo = 2;
				// -------------------------------------------------------------

				getline(file, line);		 					// SKIP First Line in csv it has headings
				while (getline(file, line)) {
					stringstream ss(line);

					getline(ss, id, ',');
					getline(ss, year, ',');

					if (ss.peek() == '"') {
						string csvElement;
						ss >> std::quoted(csvElement);
						causeName113 = csvElement;
						getline(ss, skip, ',');
					}
					else {
						getline(ss, causeName113, ',');
					}
					getline(ss, causeName, ',');
					getline(ss, state, ',');
					getline(ss, deaths, ',');
					getline(ss, rate);

					switch (key)
					{
					case 3: {
						obj.insert(causeName, fileName, to_string(lineNo));
						break;
					}
					case 4: {
						obj.insert(state, fileName, to_string(lineNo));
						break;
					}
					}
					lineNo++;
				}
				file.close();
			}
		}
		return obj;
	}

	BTree<string> loadStringDataInBTree(int key, int d) {

		// string fileName = "data/NCHS_-_Leading_Causes_of_Death__United_States_10.csv";
		BTree<string> obj(d);	// Btree
		fstream file;

		string fileName;
		for (int i = 1; i < 11; i++)
		{
			fileName = "data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(i) + ".csv";
			file.open(fileName, ios::in);
			if (file.is_open()) {

				string id;
				string year;
				string causeName113;
				string causeName;
				string state;
				string deaths;
				string rate;
				string skip;

				int count = 0;
				string line;

				int lineNo = 2;

				getline(file, line);		 					// SKIP First Line in csv it has headings
				while (getline(file, line)) {
					stringstream ss(line);

					getline(ss, id, ',');
					getline(ss, year, ',');

					if (ss.peek() == '"') {
						string csvElement;
						ss >> std::quoted(csvElement);
						causeName113 = csvElement;
						getline(ss, skip, ',');
					}
					else {
						getline(ss, causeName113, ',');
					}

					getline(ss, causeName, ',');
					getline(ss, state, ',');
					getline(ss, deaths, ',');
					getline(ss, rate);


					switch (key)
					{
					case 3: {
						obj.insert(fileName, to_string(lineNo), causeName);
						break;
					}
					case 4: {
						obj.insert(fileName, to_string(lineNo), state);
						break;
					}
					}

					//obj.insert(fileName, to_string(lineNo), state);
					lineNo++;
				}
				file.close();
			}
		}
		return obj;
	}

	int getField(string field) {
		transform(field.begin(), field.end(), field.begin(), ::toupper);
		if (field == "ID") {
			return 1;
		}
		else if (field == "YEAR")
		{
			return 2;
		}
		else if (field == "CAUSE NAME")
		{
			return 3;
		}
		else if (field == "STATE")
		{
			return 4;
		}
		else if (field == "DEATHS")
		{
			return 5;
		}
		else if (field == "RATE")
		{
			return 6;
		}
	}


};