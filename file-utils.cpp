#include "./include/file-utils.hpp"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

string FileUtils::readFileContent(string filePath)
{
    ifstream file;
    file.open(filePath);

    if (!file.is_open())
    {
        return 0;
    }

    char current_char;
    string parsedChars;
    string fileContent;

    while (file.good())
    {
        current_char = file.get();
        fileContent += current_char;
    }

    return fileContent;
};