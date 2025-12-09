# Conway’s Game of Life (C++)








A C++ implementation of Conway’s Game of Life.
The simulation evolves a 2D grid over time and writes each generation
as a PBM image. The program uses simple file-based I/O (no interactive input).

---

## Files
`life_main.cpp` – program entry point  
`life_functions.cpp` – Game of Life logic and PBM I/O  
`life_functions.h` – function declarations  
`life_input.txt` – input configuration file  
`life_output.txt` – run log (generated)  
`pbm_frames/` – directory containing PBM output frames (generated)  

---

## Build (Standard C++)

This project uses standard C++ and should compile on any system
with a modern compiler.

### Recommended build command

`g++ -std=c++17 life_main.cpp life_functions.cpp -o life`

Notes:
- On Windows, the output may be `life.exe`  
- On Linux / macOS, the output is `life`  
- No third-party libraries are required  

---

## Input Configuration

The program reads from a file named `life_input.txt`.

### Random initial grid

`1`

Creates a random grid (size between 40×40 and 60×60).

### Example PBM-based initial grid

`2`  
`glider.pbm`

Loads the initial state from a PBM (P1 format) file.  
(*Any `.pbm` file will work*)

---

## Running the Program

From the build directory:

`./life` (Linux / macOS)  
`life.exe` (Windows)

The program will:
- Read `life_input.txt`  
- Create a folder called `pbm_frames`  
- Write one PBM file per generation for 1000 generations  
- Write run details to `life_output.txt`  

No terminal interaction is required.

---

## Viewing PBM Output

Each PBM file represents one generation of the simulation.

You can:
- Open PBM files directly with viewers such as GIMP or IrfanView  
- Convert PBM files to common formats using ImageMagick  

Multiple frames can also be combined into animations using external tools
such as ImageMagick or ffmpeg.