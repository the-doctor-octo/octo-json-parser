#include <stdio.h>
#include <string>
#include <map>

using namespace std;

class JSONParser
{
public:
    JSONParser(string content) : content(content){};

    void parse()
    {
        parseObject();
    }

    void getToNextChar()
    {
        if (index + 1 <= content.size())
        {
            index += 1;
        }
        else
        {
            index = -1;
        }
    }

private:
    // object -> '{' pair-list '}'
    void parseObject()
    {
        skipWhitespaces();
        if (getCurrentChar() == '{')
        {
            skipWhitespaces();
            if (getCurrentChar() == '\"')
            {
                parsePair();
            }
        }
    };

    // pair->string ':' value
    void parsePair()
    {
        getToNextChar(); // skip " and parse the property name
        string json_prop_name = parseString();

        // Check the right-hand side of the pair
        // if is a primitive value, as in string | number | boolean | null => store in map
        skipWhitespaces();
        if (getCurrentChar() == ':')
        {
            skipWhitespaces();
            if (getCurrentChar() == '{')
            {
                parseObject();
            }
            else if (getCurrentChar() == '[')
            {
                parseArray();
            }
            else
            {
                parsePrimitive();
            }
        }
    }
    void parsePrimitive(){

    };
    void parseArray(){

    };
    string parseString()
    {
        string string_value;
        while (getCurrentChar() != '\"')
        {
            string_value += getCurrentChar();
            getToNextChar();
        }
        return string_value;
    }

    // Helpers
    char getCurrentChar()
    {
        return content.at(index);
    }

    void skipWhitespaces()
    {
        while (isspace(getCurrentChar()))
        {
            getToNextChar();
        }
    }

    const string content;
    size_t index;

    map<string, string> m;
};