#pragma once

#include <string>
#include <vector>

// Create a random grid with dimensions in [40, 60] x [40, 60].
std::vector<int> rSeed(int &rows, int &cols);

// Read a grid from a PBM file (P1 format). Sets rows/cols based on the file.
std::vector<int> sSeed(const std::string &filename, int &rows, int &cols);

// Compute the next generation of the Game of Life based on the current grid.
std::vector<int> advance(std::vector<int> &board, int Nrows, int Ncols);

// Write the grid to a PBM file (P1 format).
void writePBM(const std::string &filename, std::vector<int> &board, int Nrows, int Ncols);