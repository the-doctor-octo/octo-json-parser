#include <stdio.h>
#include <string>
#include <map>
#include <ctype.h>
#include <cctype>
#include "include/json-parser.hpp"
#include <iostream>

using namespace std;

JSONParser::JSONParser(){};
JSONParser::JSONParser(string content) : content(content){};

// object -> '{' pair-list '}'
void JSONParser::parseObject()
{
    JSONParser::advanceCharIndex(); // Skip the opening curly bracket '{'

    char curr_char = JSONParser::getCurrentChar();
    while (curr_char != '}' || curr_char == ',')
    {
        JSONParser::skipWhitespaces();
        JSONParser::parsePair();
        curr_char = JSONParser::getCurrentChar();
    }
    if (curr_char == '}')
    {
        // pop the last property from properties
        if (properties.size() != 0)
        {
            properties.pop_back();
        }
    }
};

// pair-list -> pair | pair ',' pair-list
// pair -> string ':' value
void JSONParser::parsePair()
{
    char curr_char = JSONParser::getCurrentChar();
    if (curr_char == '"')
    {
        string json_prop_name = JSONParser::parseString();
        properties.push_back(json_prop_name);

        // Check the right-hand side of the pair
        // if is a primitive value, as in string | number | boolean | null => store in map
        JSONParser::skipWhitespaces();
        char curr_char = JSONParser::getCurrentChar();

        if (curr_char == ':')
        {
            JSONParser::skipWhitespaces();
            JSONParser::parseValue();
        }
    }
}

// value -> object | array | primitive
void JSONParser::parseValue()
{
    const char curr_char = JSONParser::getCurrentChar();
    if (curr_char == '{')
    {
        JSONParser::parseObject();
    }
    else if (curr_char == '[')
    {
        JSONParser::parseArray();
    }
    else
    {
        JSONParser::parsePrimitive();
    }
};

// primitive -> string | number | 'true' | 'false' | 'null'
std::string JSONParser::parsePrimitive()
{
    const char curr_char = JSONParser::getCurrentChar();
    std::string primitiveValue;

    if (curr_char == '"')
    {
        primitiveValue = JSONParser::parseString();
    }
    else if (std::isdigit(curr_char) || curr_char == '-' || curr_char == '+' || curr_char == '.')
    {
        primitiveValue = JSONParser::parseNumber();
    }
    else if (std::isalpha(curr_char))
    {
        if (curr_char == 't' || curr_char == 'f' || curr_char == 'n')
        {
            primitiveValue = JSONParser::parseBooleanOrNull();
        }
    }

    // traverse properties items to build the key name for the new map entry
    std::string key = JSONParser::buildPropertyKey();
    if (key != "")
    {
        m.emplace(key, primitiveValue);
        cout << "m =" << m[key];

        // pop the last property from properties
        if (properties.size() != 0)
        {
            properties.pop_back();
        }
    }
    return primitiveValue;
}

// array -> '[' value-list ']'
void JSONParser::parseArray()
{
    int array_index = 0;
    char curr_char = JSONParser::getCurrentChar();

    JSONParser::skipWhitespaces();
    if (curr_char == '[')
    {
        while (curr_char != ']')
        {
            if (curr_char == ',')
            {
                JSONParser::skipWhitespaces();
            }
            properties.push_back("[" + to_string(array_index) + "]");
            JSONParser::parseValue();
            array_index = ++array_index;
            JSONParser::skipWhitespaces();
            curr_char = JSONParser::getCurrentChar();
        }
        properties.pop_back();
    }
};

/** PRIMITIVES */

// string -> '"' characters '"'
// characters -> "" | character characters
// character -> any valid Unicode character except " and slash
string JSONParser::parseString()
{
    JSONParser::advanceCharIndex(); // skip " and parse the property name
    return JSONParser::parseUntil([](char c)
                                  { return c != '\"' && c != '\\'; });
}
string JSONParser::parseNumber()
{
    return JSONParser::parseUntil([](char c)
                                  { return c != ','; });
}
string JSONParser::parseBooleanOrNull()
{
    return JSONParser::parseUntil([](char c)
                                  { return isalpha(c); });
}

/** HELPERS */
char JSONParser::getCurrentChar()
{
    return content.at(curr_char_index);
}

void JSONParser::skipWhitespaces()
{
    JSONParser::advanceCharIndex();
    while (isspace(JSONParser::getCurrentChar()))
    {
        JSONParser::advanceCharIndex();
    }
}

char JSONParser::getCharAndAdvance()
{
    char char_value = JSONParser::getCurrentChar();
    JSONParser::advanceCharIndex();
    return char_value;
}

void JSONParser::advanceCharIndex()
{
    if (curr_char_index + 1 <= content.size())
    {
        curr_char_index += 1;
    }
    else
    {
        curr_char_index = -1;
    }
}

std::string JSONParser::buildPropertyKey()
{
    vector<string>::iterator it;
    std::string key = "";

    for (it = properties.begin(); it != properties.end(); it++)
    {
        if (it == properties.begin())
        {
            key += *it;
        }
        else
        {
            key += '.' + *it;
        }
    }
    return key;
}

std::string JSONParser::parseUntil(const std::function<bool(char)> &condition)
{
    string string_value;
    char curr_char = JSONParser::getCurrentChar();
    while (!isspace(curr_char) && condition(curr_char))
    {
        string_value += JSONParser::getCharAndAdvance();
        curr_char = JSONParser::getCurrentChar();
    }
    return string_value;
}

/** public: */
void JSONParser::parse()
{
    if (content == "")
    {
        throw new exception("No content to parse!");
    }
    char curr_char = JSONParser::getCurrentChar();
    if (curr_char == '{')
    {
        JSONParser::parseObject();
    }

    std::vector<string>().swap(properties);
}

std::string JSONParser::getContent()
{
    return content;
}

void JSONParser::setContent(std::string cnt)
{
    content = cnt;
}

std::string JSONParser::getProperty(std::string property)
{
    std::string result;
    if (property != "" && m.count(property))
    {
        result = m[property];
    }
    return result;
}
