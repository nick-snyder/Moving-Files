/**
 * CS515 Assignment 3
 * File: image.cpp
 * Name: Nick Snyder
 * Section: 2
 * Date: 19 February 2022
 * Collaboration Declaration: online resources
 */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>



int main (int argc, char ** argv) {
    if (argv[4] == nullptr) {
        std::ifstream f(argv[1]);
        if (f.is_open()) {

            std::string version;
            int columns;
            int rows;
            int darkness;

            f >> version;
            f >> columns;
            f >> rows;
            f >> darkness;

            int ** image;
            image = new int*[rows];
            for (int i = 0; i < rows; i++)
                image[i] = new int[columns];

            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < columns; c++)
                    f >> image[r][c];
            }

            std::string inverted(argv[2]);
            std::fstream inverted_out;
            inverted_out.open(inverted, std::ios_base::out);
            if (!inverted_out.is_open())
                std::cout << "failed to open " << inverted << '\n';
            else {
                inverted_out << version << "\n" << columns << " " << rows << "\n" << darkness << std::endl;
                for (int r = 0; r < rows; r++) {
                    for (int c = 0; c < columns; c++)
                        inverted_out << abs(darkness - image[r][c]) << " ";
                    inverted_out << std::endl;
                }
            }

            std::string rotated(argv[3]);
            std::fstream rotated_out;
            rotated_out.open(rotated, std::ios_base::out);
            if (!rotated_out.is_open())
                std::cout << "failed to open " << rotated << '\n';
            else {
                rotated_out << version << "\n" << rows << " " << columns << "\n" << darkness << std::endl;
                for (int c = 0; c < columns; c++) {
                    for (int r = rows - 1; r >= 0; r--)
                        rotated_out << image[r][c] << " ";
                        //std::cout << image[r][c] << " ";
                    rotated_out << std::endl;
                    //std::cout << std::endl;
                }
            }

            for(int i = 0; i < rows; i++)
                delete[] image[i];
            delete[] image;

        } else
            std::cout << "Can not open " << argv[1] << " for input." << std::endl;
    } else
        std::cout << "Usage: ./image <input image> <neg image> <rotate image>" << std::endl;
}
