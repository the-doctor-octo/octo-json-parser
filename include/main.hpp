#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

std::ifstream *openFile(std::string path);
void readFile(std::ifstream *file);
