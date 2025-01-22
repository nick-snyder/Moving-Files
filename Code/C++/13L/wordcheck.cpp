#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype> 
#include <set>

std::set<std::string> convertDataToDataStructure(std::ifstream &file)
{
    // convert * to set ADT

    std::set<std::string> dictionary;
    std::string word;

    // while line of 'file' can be assigned to 'word'
    while (getline(file, word))
    {
        std::stringstream ss(word);

        ss >> word;

        if (ss.fail())
        {
            break;
        }

        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        dictionary.insert(word);
    }
    return dictionary;
}

std::set<std::string> checkWord(std::string word, std::set<std::string> dictionary)
{
    std::set<std::string> likeWords;
    std::set<std::string>::iterator it;

    std::string check;

    std::transform(word.begin(), word.end(), word.begin(), ::tolower);

    // for every letter in 'word'
    for (int i = 0; i < 4; i++)
    {
        check = word;
        for (int j = 0; j < 26; j++) 
        {
            it = dictionary.begin();

            // change the char to the next in the alphabet
            check[i] = 'a' + j;

            // if new 'word' is found in the dictionary
            if (dictionary.find(check) != dictionary.end())
            {
                likeWords.insert(check);
            }
            // char changes from 'a' to 'b'
        }
    }
    likeWords.erase(word);
    return likeWords;
}

void displayLikeWords(std::set<std::string> likeWords)
{
    std::set<std::string>::iterator it = likeWords.begin();
    while (it != likeWords.end())
    {
        std::cout << *it << " ";
        it++;
    }
    std::cout << "\nTotal: " << likeWords.size() << " words. " << std::endl;
}

int main(int argc, char *argv[])
{
    // i choose a set
    std::set<std::string> dictionary;
    std::set<std::string> likeWords;

    std::string word;

    std::ifstream file;
    file.open("words");

    // pretty self-explanatory
    dictionary = convertDataToDataStructure(file);

    // while input is not Ctrl-D
    while (std::cin)
    {


        std::cout << "Please input a 4 letter word:";

        // read input
        std::cin >> word;

        // check input again
        if (std::cin) 
        {
            // if word is correct length
            while (word.size() != 4)
            {
                std::cout << "wrong length!";// << std::endl;

                // read input
                std::cin >> word;

                if (!std::cin) 
                { 
                    break;
                }
            }
            if (word.size() == 4)
            {
                likeWords = checkWord(word, dictionary);
                displayLikeWords(likeWords);
            }
            
        }
        else
        {
            break;
        }
    }
    std::cout << std::endl;
}