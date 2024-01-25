#include <gtest/gtest.h>
#include "../include/json-parser.hpp"
#include <string>
#include <iostream>
#include <string>

TEST(JsonParserTest, setContent_does_not_throw)
{
    JSONParser *parser = new JSONParser();
    EXPECT_NO_THROW(parser->setContent("test"));
}

TEST(JsonParserTest, getContent)
{
    JSONParser *parser = new JSONParser();
    parser->setContent("test");

    std::string content = parser->getContent();

    // Expect equality.
    EXPECT_EQ(content, "test");
}

TEST(JsonParserTest, parse_does_not_throw)
{
    JSONParser *parser = new JSONParser();
    parser->setContent("{\"propertyA\":\"test\"}");

    EXPECT_NO_THROW(parser->parse());
}

TEST(JsonParserTest, parse_then_getProperty)
{
    JSONParser *parser = new JSONParser();
    parser->setContent("{\"propertyA\":\"test\"}");

    EXPECT_NO_THROW(parser->parse());

    std::cout << "\n reading propertyA \n";
    std::string prop_value = parser->getProperty("propertyA");

    std::cout << "\n propertyA: " << prop_value << "; \n";
    EXPECT_EQ(prop_value, "test");
}