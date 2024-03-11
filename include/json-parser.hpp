#pragma once
#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <string>
#include <map>
#include <vector>
#include <functional>
#include <utility>

typedef std::pair<std::string, std::string> JSONValue;

class JSONParser
{
private:
    void parseObject();
    void parsePair();
    void parseArray();
    JSONValue parsePrimitive();
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
    std::map<std::string, JSONValue> m;
    std::vector<std::string> properties;
    bool log_enabled = false;

public:
    JSONParser();
    JSONParser(std::string content);
    ~JSONParser();

    void parse();
    std::string getContent();
    void setContent(std::string &content);
    JSONValue getProperty(std::string property);
    void setLogEnabled(bool value);
};

#endif