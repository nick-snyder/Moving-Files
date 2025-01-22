/**
* CS515 Assignment 3
* File: imagestack.cpp
* Name: Nick Snyder
* Section: 2
* Date: 19 February 2022
* Collaboration Declaration: online resources
* Issue: core dump
*/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <bits/stdc++.h>
#include <algorithm>

int main (int argc, char ** argv) {
    std::string version;
    int columns;
    int rows;
    int darkness;
    int numberOfInputImages = argc - 2;

    int *** images;
    images = new int**[numberOfInputImages];
    for (int n = 0; n < numberOfInputImages; n++) {
        std::ifstream f(argv[n+1]);
        if (f.is_open()) {
            f >> version;
            f >> rows;
            f >> columns;
            f >> darkness;
            images[n] = new int*[rows];
            for (int r = 0; r < rows; r++) {
                images[n][r] = new int[columns];
                for (int c = 0; c < columns; c++)
                    f >> images[n][r][c];
            }
        }
    }

    // allocates memory for 2d array
    int ** correctedimage;
    correctedimage = new int*[rows];
    for (int r = 0; r < rows; r++)
        correctedimage[r] = new int[columns];

    // allocates memory for 1d array
    int *comparebits;
    comparebits = new int[numberOfInputImages];

    // std::cout << "Corrected image:" << std::endl;
    // std::cout << "rows = " << rows << std::endl;
    // std::cout << "columns = " << columns << std::endl;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            for (int n = 0; n < numberOfInputImages; n++)
                comparebits[n] = images[n][r][c];
            std::sort(comparebits, comparebits+numberOfInputImages);
            correctedimage[r][c] = comparebits[numberOfInputImages / 2];
        }
    }

    std::string corrected(argv[argc-1]);
    std::fstream corrected_out;
    corrected_out.open(corrected, std::ios_base::out);
    if (corrected_out.is_open()) {
        corrected_out << version << "\n" << rows << " " << columns << "\n" << darkness << std::endl;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++)
                corrected_out << correctedimage[r][c] << " ";
            corrected_out << std::endl;
        }
    } else
        std::cout << "failed to open " << corrected << '\n';


    // unallocates memory for 3d array
    for (int n = 0; n < numberOfInputImages; n++) {
        for (int r = 0; r < rows; r++)
            delete[] images[n][r];
        delete[] images[n];
    }
    delete[] images;

    // unallocates memory for 2d array
    for (int r = 0; r < rows; r++)
        delete[] correctedimage[r];
    delete[] correctedimage;

    // unallocates memory for 1d array
    delete[] comparebits;
}
