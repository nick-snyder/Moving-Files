/*
 * CS515 Assignment 1
 * File: calSpan.cpp
 * Name: Nick Snyder
 * Section: 2
 * Date: 9 February 2022
 * Collaboration Declaration: none
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <string.h>
#include <cstdlib>
#include <ctype.h>
#include <algorithm>

bool isint(std::string s) {
	for (char c : s) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}

int main(int argc, char ** argv) {

	// data input from the command line
	if (argc == 2) {
		std::ifstream f(argv[1]);
		if (f.is_open()) {

			std::vector<double> values;
			std::string str;
			

			while (f.good()) {

				f >> str;

				double num = 0;

				// counts bad characters. Resets before every iteration
				int badchar = 0;

				// for each character in the string ...
				for (char c : str) {

					// if the character is not a digit, period, or minus ...
					if (!std::isdigit(c) && c != '.' && c != '-') {

						// increment bad character count
						badchar++;
					}
				}

				// new code
				//std::cout << str << std::endl;

				// if any bad characters are found in the file...
				if (badchar > 0) {
					
					// out of bounds data is appended instead
					
					//if (num < -100 || num > 100) {
						num = -999;
						//values.push_back(-999);	
					//}
					//std::cout << "Pushing " << num << "(bad) to vector" << std::endl;
				}
				
				// if no bad characters are found in the file...
				else {

					num = atof(str.c_str());
					if (num < -100 || num > 100) {
						num = -999;
					} 

					// number is appended to vector as is
					//num = atof(str.c_str());
					
					
				}
				values.push_back(num);
				//std::cout << "Pushing " << num << " to vector" << std::endl;
			}

			// last value (duplicate) is removed
			values.pop_back();

			// query starts as empty string to ensure while loop runs once
			std::string query = "";
			while (true) {
				
				// read line from user input
				std::cout << "Which minute to query? \n";
				//getline (std::cin, query);
				std::cin >> query;

				// check exit condition first
				transform(query.begin(), query.end(), query.begin(), ::tolower);
				if (query == "exit") {
					break;
				}

				// if invalid query (sdasfvjosuf*%#@$%@$)
				else if (!isint(query)) {
					std::cout << "Wrong query input." << std::endl;
				}

				// if out of range 0 < (int) query < values.size()
				else if (stoi(query) >= values.size() || stoi(query) < 0) {
					std::cout << "Query minute out of range" << std::endl;
				}

				// if queried value is bad
				else if (values.at(stoi(query)) == -999) {
					std::cout << "Data at minute " << query << " is corrupted." << std::endl;
				}

				// else ... valid
				else {

					// start of counter
					int high = 0;

					// starts at the query and will decrement while 'input' >= 0 
					for (int input = stoi(query); input >= 0; input--) {

						// if the value at the query is >= the previous value ...
						if (values.at(stoi(query)) >= values.at(input)) {
							
							// counter increments
							high++;
						}
						else {
							break;
						}
					}
					// display to terminal
					std::cout << "Data at minute " << query << " is a " << high << "-minute(s) high." << std::endl;
				}	

			}
		} else {
			std::cout << "Error opening file" << std::endl;
		}
	} else {
		std::cout << "Wrong number of arguments" << std::endl;
	}
	return 0;
}		
