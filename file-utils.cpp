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
        cout << "File not opened. Might be not found or not have the permissions." << endl;
        return 0;
    }
    cout << "File found. Reading content..." << endl;

    char current_char;
    string parsedChars;
    string fileContent;

    while (file.good())
    {
        current_char = file.get();
        fileContent += current_char;
    }

    cout << "File content reading complete." << endl
         << endl;

    return fileContent;
};