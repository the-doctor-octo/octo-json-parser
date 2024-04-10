#include <gtest/gtest.h>
#include "../include/json-parser.hpp"
#include <string>
#include <iostream>
#include <string>

TEST(JsonParserTest, setContent_does_not_throw)
{
    JSONParser *parser = new JSONParser();
    std::string content = "test";
    EXPECT_NO_THROW(parser->setContent(content));
}

TEST(JsonParserTest, getContent)
{
    JSONParser *parser = new JSONParser();
    std::string content = "test";
    parser->setContent(content);

    std::string result = parser->getContent();

    // Expect equality.
    EXPECT_EQ(result, "test");
}

TEST(JsonParserTest, parse_does_not_throw)
{
    JSONParser *parser = new JSONParser();
    std::string content = "{\"propertyA\":\"test\"}";
    parser->setContent(content);

    EXPECT_NO_THROW(parser->parse());
}

TEST(JsonParserTest, parse_then_getProperty)
{
    JSONParser *parser = new JSONParser();
    std::string content = "{\"propertyA\":\"test\"}";
    parser->setContent(content);

    EXPECT_NO_THROW(parser->parse());

    std::cout << "\n reading propertyA \n";
    JSONValue prop_value = parser->getProperty("propertyA");

    std::cout << "\n propertyA: " << prop_value.second << "; \n";
    EXPECT_EQ(prop_value.second, "test");
}