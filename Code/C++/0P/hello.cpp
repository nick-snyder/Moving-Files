/* CS515 Assignment 0
File: hello.cpp
Name: Nick Snyder
Section: 2
Collaboration Declaration: none 
*/  

#include <iostream> // for cin and cout
#include <string> // for string type

int main(int argc, char ** argv) 
{
	std::string name = "";
	while (name == "") 
	{
		std::cout << "What is your name?" << std::endl;
		getline(std::cin, name);
	}
	std::cout << "Hello World!" << std::endl;
	std::cout << "Welcome to CS515, " << name << "!" << std::endl;
}

