#include "HuffTree.h" 
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <ctype.h>

int main(int argc, char ** argv) {
    std::ifstream f(argv[1]);
    if (f.is_open()) {
        // read input file text to a string
        std::string copiedFileText = "";
        std::string temp;
        while (f.peek() != EOF) {
            getline(f, temp);
            copiedFileText += temp;
            copiedFileText += "\n";
        }

        char alphabet[26];
        for (int i = 0; i < 26; i++) {
            alphabet[i] = 'a' + i;
        }

        double uncompressedBits = copiedFileText.length() * 8;
        
        int frequencies[26];
        std::string s = "";

        // for every char in the text
        for (int i = 0; i < copiedFileText.length(); i++) {

            // convert to lower case
            copiedFileText[i] = tolower(copiedFileText[i]);

            // if char is in the alphabet
            if (isalpha(copiedFileText[i])) {

                // increment frequency at the specified char
                frequencies[copiedFileText[i] - 'a']++;
            } else {

                s += copiedFileText[i];
            }
        }
        
        // compress file with HuffTree.cpp
        HuffTree ht;
        ht.buildTree(alphabet, frequencies, 26);

        // get the code for each letter in the alphabet
        // std::string s = "";
        for (int i = 0; i < 26; i++) {
            s += ht.getCode(alphabet[i]);
        }

        double compressedBits = s.length() * 8;

        // calculate compression
        double compressionRate = 100 * (uncompressedBits - compressedBits) / uncompressedBits;

        // output
        std::cout << "original bits: " << uncompressedBits << std::endl;
        std::cout << "bits after compression: " << compressedBits << std::endl;
        std::cout << "compression rate: " << std::setprecision(4) << compressionRate << "%" << std::endl;
    }
}