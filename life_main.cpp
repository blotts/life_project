#include "Life_functions.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <cstdio>
#include <filesystem>

int main () {
    // Seed the random number generator once for the whole program
    srand(time(NULL));

    int type, nRows, nCols;
    std::string myFile;
    std::vector<int> grid;

    std::ifstream fin("life_input.txt");
    if (!fin.is_open()) {
        std::cerr << "Error: could not open life_input.txt for reading.\n";
        return 1;
    }

    fin >> type;  // read 1 (random) or 2 (file)
    if (type == 2) {
        fin >> myFile;  // read PBM filename if needed
    }
    fin.close();

    // Choose initial grid based on type
    if(type == 1) {
        // Type 1: random seed in a 40–60 by 40–60 grid
        grid = rSeed(nRows, nCols);
    }
    else if(type == 2) {
        // Type 2: read grid from a PBM file
        grid = sSeed(myFile, nRows, nCols);
    }
    else {
        // Invalid type in the input file
        std::cerr << "Error: invalid type in life_input.txt (must be 1 or 2).\n";
        return 1;
    }

    // Output log
    std::ofstream log("life_output.txt");
    if (!log.is_open()) {
        std::cerr << "Error: could not open life_output.txt for writing.\n";
        return 1;
    }

    log << "Conway's Game of Life simulation\n";
    log << "Seed type: " << (type == 1 ? "random" : "file") << "\n";
    if (type == 2) {
        log << "Input PBM file: " << myFile << "\n";
    }
    log << "Grid size: " << nRows << " x " << nCols << "\n";
    log << "Simulating 1000 generations...\n";

    // Create directory for PBM output frames
    const std::string outputDir = "pbm_frames";
    std::filesystem::create_directories(outputDir);

    // Simulation loop
    for(int generation = 0; generation < 1000; generation++) { 
        // Build a filename like "output0000.pbm", "output0001.pbm", ...
        char filename[32];
        sprintf(filename, "%s/output%04d.pbm", outputDir.c_str(), generation);

        // Write the current grid to a PBM image
        writePBM(std::string(filename), grid, nRows, nCols); 

        // Advance to the next generation
        grid = advance(grid, nRows, nCols); 
    }

    // Final message goes into the log file
    log << "Done! 1000 generations of Life simulated.\n";
    log.close();

    return 0;
}