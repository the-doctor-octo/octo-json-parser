
#include <gtest/gtest.h>
#include "include/json-parser.hpp"
#include "include/file-utils.hpp"

class SimpleJsonParserFixture : protected testing::Test
{
protected:
    void SetUp() override
    {
        std::string content = FileUtils::readFileContent("../simpleTest.json");
        parser->setContent(content);
    };

    JSONParser *parser = new JSONParser();
};