#include "Life_functions.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

//
// rSeed
// ------
// Initializes a Game of Life grid with random live (1) and dead (0) cells.
// The grid dimensions are randomly chosen between 40 and 60 in both
// directions. The resulting grid is returned as a 1D vector.
//

std::vector<int> rSeed(int &Nrows, int &Ncols) {
    double n;
    Nrows = rand() % 21 + 40;
    Ncols = rand() % 21 + 40;
    std::vector<int> ret(Nrows * Ncols);

    for (int i = 0; i < Nrows; i++) {
        for (int j = 0; j < Ncols; j++) {
            n = (double) rand() / (double) RAND_MAX;
            if (n > 0.5) ret[Ncols * i + j] = 1;
            else ret[Ncols * i + j] = 0;
        }
    }
    return ret;
}

//
// sSeed
// ------
// Reads an initial Game of Life grid from a PBM (P1) file.
// The PBM file specifies the grid dimensions and binary cell values.
// The grid is returned as a 1D vector with row-major ordering.
//

std::vector<int> sSeed(const std::string &filename, int &Nrows, int &Ncols) {
    std::ifstream file;
    file.open(filename);
    if (!file) {
        std::cout << " Error reading input file. Program aborted.\n";
        exit(-1);
    }

    char num;
    std::vector<int> ret;

    // Skip PBM header and comment lines
    std::string line;
    while (std::getline(file, line)) {
        if (line.size() == 0) continue;
        if (line[0] == '#') continue;
        if (line[0] == 'P') continue;
        break;
    }

    // The first non-header line contains the grid dimensions
    std::istringstream sin(line);
    sin >> Ncols;
    sin >> Nrows;

    // Read cell values (0 = dead, 1 = alive)
    while (!file.eof()) {
        file >> num;
        ret.push_back((int) num - 48);
    }
    return ret;
}

//
// neighbors
// ---------
// Counts the number of live neighbors surrounding a given cell.
// Neighbors are the 8 surrounding cells
// with bounds checking to avoid invalid memory access.
//

int neighbors(std::vector<int> &board, int row, int col, int Nrows, int Ncols) {
    int ret = 0;
    for(int i = row - 1; i <= row + 1; i++) {
        for(int j = col - 1; j <= col + 1; j++) {
            if (i == row && j == col) continue;
            if (i >= 0 && j >= 0 && i < Nrows && j < Ncols) {
                ret += board[Ncols * i + j];
            }
        }
    }
    return ret;
}

//
// advance
// -------
// Computes the next generation of the Game of Life grid using the standard
// Conway rules:
//
//  - A live cell with 2 or 3 neighbors survives
//  - A dead cell with exactly 3 neighbors becomes alive
//  - All other cells die or remain dead
//
// A new grid is returned; the original grid is not modified.
//

std::vector<int> advance(std::vector<int> &board, int Nrows, int Ncols) {
    std::vector<int> ret(Ncols * Nrows);

    for(int i = 0; i < Nrows; i++) {
        for(int j = 0; j < Ncols; j++) {
            int neigh = neighbors(board, i, j, Nrows, Ncols);
            if (neigh == 2) ret[Ncols * i + j] = board[Ncols * i + j];
            else if (neigh == 3) ret[Ncols * i + j] = 1;
            else ret[Ncols * i + j] = 0;
        }
    }
    return ret;
}

//
// writePBM
// --------
// Writes the current grid state to a PBM (P1) image file.
// Each call produces a snapshot that can be viewed or animated
// externally to visualize the evolution of the system.
//

void writePBM(const std::string &filename, std::vector<int> &board, int Nrows, int Ncols) {
    std::ofstream file;
    file.open(filename);
    if(!file) {
        std::cout << " Error writing to output file. Program aborted.\n";
        exit(-1);
    }

    file << "P1\n";
    file << Ncols << ' ' << Nrows << '\n';

    int lengthCounter = 0;
    for (int i = 0; i < Nrows; i++) {
        for (int j = 0; j < Ncols; j++) {
            file << ' ' << board[Ncols * i + j];
            lengthCounter++;
            if (lengthCounter == 30) {
                file << '\n';
                lengthCounter = 0;
            }
        }
    }
    file << '\n';
}