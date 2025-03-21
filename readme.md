# Json Parser 🐙

A simple json parser that includes methods to recursively traverse a json file, generating a Map where the key of an element is the dotted property name version of a json property, as in:

`propertyA[0].someNestedProperty`

## Usage

Instantiate a new JSONParser object, optionally giving the JSON content in the constructor parameter. You can also change the content later through setContent

```c++
// Assign Json content through the constructor
JSONParser *parser = new JSONParser("{/"JSON CONTENT/": /"value/"}");

// Or assign through set content
JSONParser *parser = new JSONParser();
parser->setContent(std::string content);
```

> 💡 You could later retrive the current content of the JSONParser through getContent

Start the recursive parsing algorithm by callingthe parse method.

```c++
parser->parse();
```

This method will populate an inner private member 'm' of type Map that will host a Key that contains the dotted property name and a value of type JSONValue which is a pair that contains the type and the actual value of that JSON property.

> 💡 You can call
>
> ```c++
> printer->setLogEnabled(bool value)
> ```
>
> to enable verbose logging during the parsing task. IT will print a list of properties and values parsed, including type information

Get the property value with getProperty(std::string property);

```c++
parser->getProperty('JSON CONTENT')
```

### Build & Run

Run `cmake --build .` in the `build` folder to build all targets in CMAkeLists.txt.
`cmake --build . --config Release` to build the release version

Navigate to ./build/test/<debug|Release> and run json-parser_test.exe
