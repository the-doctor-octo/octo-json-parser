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
        JSONValue primitive = JSONParser::parsePrimitive();
        // traverse properties items to build the key name for the new map entry
        std::string key = JSONParser::buildPropertyKey();
        if (key != "")
        {
            m.emplace(key, primitive);
            if (log_enabled)
            {
                printLog();
            }

            // pop the last property from properties
            if (properties.size() != 0)
            {
                properties.pop_back();
            }
        }
    }
};

// primitive -> string | number | 'true' | 'false' | 'null'
JSONValue JSONParser::parsePrimitive()
{
    const char curr_char = JSONParser::getCurrentChar();
    JSONValue jsonValue;

    if (curr_char == '"')
    {
        jsonValue.first = JSONParser::parseString();
        jsonValue.second = "string";
    }
    else if (std::isdigit(curr_char) || curr_char == '-' || curr_char == '+' || curr_char == '.')
    {
        jsonValue.first = JSONParser::parseNumber();
        jsonValue.second = "number";
    }
    else if (std::isalpha(curr_char))
    {
        if (curr_char == 't' || curr_char == 'f' || curr_char == 'n')
        {
            jsonValue.second = "bool";
            if (curr_char == 'n')
            {
                jsonValue.second = "null";
            }
            jsonValue.first = JSONParser::parseBooleanOrNull();
        }
    }
    return jsonValue;
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
                                  { return !isspace(c) && c != ','; });
}
string JSONParser::parseBooleanOrNull()
{
    return JSONParser::parseUntil([](char c)
                                  { return !isspace(c) && isalpha(c); });
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
    while (condition(curr_char))
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
        cout << "No content loaded, use setContent" << endl;
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

void JSONParser::setContent(std::string &cnt)
{
    content = cnt;
}

JSONValue JSONParser::getProperty(std::string property)
{
    JSONValue result;
    if (property != "" && m.count(property))
    {
        result = m[property];
    }
    return result;
}

void JSONParser::printLog()
{
    string conc_prop = JSONParser::buildPropertyKey();
    JSONValue prop = m.find(conc_prop)->second;
    cout << conc_prop << "<" << prop.second << ">"
         << ": " << prop.first << endl;
}

void JSONParser::setLogEnabled(bool value)
{
    log_enabled = value;
}