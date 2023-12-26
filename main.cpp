#include "./include/main.hpp"
#include "./stack.cpp"
#include "./json-object.cpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace octo_data;

vector<char> TOKENS[8];
vector<char> BLACK_LIST_TOKENS[1];
char new_line = '\n';

int main(int argc, char *argv[])
{
    TOKENS->push_back('{');
    TOKENS->push_back('}');
    TOKENS->push_back('[');
    TOKENS->push_back(']');
    TOKENS->push_back('\"');
    TOKENS->push_back('\\');
    TOKENS->push_back(',');
    TOKENS->push_back(':');
    BLACK_LIST_TOKENS->push_back(' ');

    cout << "Octo JSON parser \n";

    ifstream myFile;
    myFile.open("test.json");

    if (!myFile.is_open())
    {
        return 0;
    }

    // file is open, start reading form file
    readFile(&myFile);
    return 0;
}

void parseFileContent(string fileContent, char *current_char)
{
    StackNode<string> *stack = new StackNode<string>();
    cout << current_char;
    string curr_char(current_char);

    //
    // parsedChars += current_char;

    // is parsedChars a token ?
    bool found = false;
    if (stack->data != "\"" && (current_char == new_line || current_char == ' '))
    {
        // continue;
    }
    // for (int i = 0; i < BLACK_LIST_TOKENS->size() && found == false; i++)
    // {
    //     if (current_char == BLACK_LIST_TOKENS->at(i))
    //     {
    //         continue;
    //     }
    // }

    found = false;
    for (int i = 0; i < TOKENS->size() && found == false; i++)
    {
        if (current_char == TOKENS->at(i))
        {
            found = true;
            // Read top element in the stack
            if (&current_char == '\"' && stack->data == "\"")
            {
                // We read a vlaue between quotes!
                JSONObject *value = new JSONObject(DataType::String);
            }

            push<string>(&stack, curr_char);
        }
    }
}

void readFile(ifstream *file)
{
    char current_char;
    string parsedChars;
    string fileContent;
    JSONObject *json_object = new JSONObject(DataType::Object);

    while (file->good())
    {
        current_char = file->get();
        fileContent += current_char;
    }

    parseFileContent(fileContent, &current_char);
}

void stack_test_code()
{
    StackNode<string> *top = newNode<string>("just kidding");

    push<string>(&top, "rust is the greatest of all");

    cout << "Are we alone in the universe? What the alien will say to us? Maybe he will say... " << endl;

    while (isEmpty<string>(top) == false)
    {
        cout << pop<string>(&top) << endl;
    }
}