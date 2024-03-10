#pragma once
#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <string>
#include <map>
#include <vector>
#include <functional>

class JSONParser
{
private:
    void parseObject();
    void parsePair();
    void parseArray();
    std::string parsePrimitive();
    void parseValue();
    std::string parseString();
    std::string parseNumber();
    std::string parseBooleanOrNull();

    // Helpers
    char getCurrentChar();
    void skipWhitespaces();
    char getCharAndAdvance();
    void advanceCharIndex();
    std::string buildPropertyKey();
    std::string parseUntil(const std::function<bool(char)> &condition);
    void printLog();

    std::string content;
    size_t curr_char_index = 0;
    std::map<std::string, std::string> m;
    std::vector<std::string> properties;

public:
    JSONParser();
    JSONParser(std::string content);
    ~JSONParser();

    void parse();
    std::string getContent();
    void setContent(std::string content);
    std::string getProperty(std::string property);
};

#endif