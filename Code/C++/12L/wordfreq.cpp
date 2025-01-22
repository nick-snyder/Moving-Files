#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

std::map<std::string, std::map<int, int>> convertDataToDataStructure(std::ifstream &file)
{
    // convert *.csv to map ADT
    // key: "airport"
    // value: "1900, 443"

    std::map<std::string, std::map<int, int>> outerMap;
    std::map<int, int> innerMap;
    std::string line;

    while (getline(file, line))
    {
        std::stringstream ss(line);

        std::string word;
        int year;
        int frequency;
        int publications;

        ss >> word;
        ss >> year;
        ss >> frequency;
        ss >> publications;

        if (ss.fail())
        {
            break;
        }

        outerMap[word][year] = frequency;
    }

    return outerMap;
}

void displayInnerMap(std::string word, int year, std::map<int, int> innerMap)
{

    // starting from year, list out innerMap
    std::map<int, int>::iterator it = innerMap.begin();
    while (it->first != year)
    {
        it++;
    }

    while (it != innerMap.end())
    {
        // display every key/value pair
        std::cout << it->first << " " << it->second << std::endl;
        it++;
    }
}

int main(int argc, char ** argv) 
{    
    // outer map is every word and an inner map of its year and frequency
    std::map<std::string, std::map<int, int>> outerMap;

    std::ifstream file;
    file.open(argv[1]);

    outerMap = convertDataToDataStructure(file);

    while (std::cin)
    {
        std::cout << "Which word starting which year? ";

        std::string word;
        int year;
        std::cin >> word;
        std::cin >> year;

        if (std::cin) 
        {
            if (outerMap.find(word) != outerMap.end())
            {
                displayInnerMap(word, year, outerMap[word]);
            }
            else 
            {
                std::cout << "That is not found.\n";
            }
        }   
    }

    return 0;
}