#include "./include/json-parser.hpp"
#include "./include/file-utils.hpp"
#include "./build/ParserConfig.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<char> TOKENS[8];
vector<char> BLACK_LIST_TOKENS[1];
char new_line = '\n';

int main(int argc, char *argv[])
{
    // report version
    std::cout << argv[0] << " Version " << OctoJsonParser_VERSION_MAJOR << "."
              << OctoJsonParser_VERSION_MINOR << std::endl;
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " jsonfile" << std::endl;
        return 0;
    }
    std::string fileContent = FileUtils::readFileContent(argv[1]);

    JSONParser *parser = new JSONParser(fileContent);
    parser->setLogEnabled(true);

    parser->parse();

    return 0;
}
