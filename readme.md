# Advent Code 2023
Collection of my participation to  [Advent Code 2023](https://adventofcode.com/2023/) puzzles.
Made with C++.


## Requirements
- CMake >= 3.22
- GNU Make >= 4.3
- GCC >= 11.4.0


## Getting started

Here are the commands to build executables:
```
git clone git@github.com:SalaheddineSTA/Advent-Of-Code-2023.git
cd Advent-Of-Code-2023 
mkdir build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cd build && make -j8
```

Run day <dd>
```
./Day<dd>/solveDay<dd> ../Day<dd>/Data/input.txt 
```