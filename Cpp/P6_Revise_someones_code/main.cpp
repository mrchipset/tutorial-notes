#include <iostream>
#include <regex>

using namespace std;

std::string GetTitle(const char *line)
{
    std::string title;  // const char * title;
    std::regex pattern("(TITLE|Title|title)\\s*\"(.*)\"");
    std::cmatch result;
    if (std::regex_search(line, result, pattern))
    {
        title = result[2].str();
        // The original code
        // title = result[2].str().c_str();
    }
    return title;
}

char * GetTitle2(const char *line)
{
    char * title;  // const char * title;
    std::regex pattern("(TITLE|Title|title)\\s*\"(.*)\"");
    std::cmatch result;
    if (std::regex_search(line, result, pattern))
    {
        title = new char[result[2].str().length()+1];
        strcpy(title, result[2].str().c_str());
        // The original code
        // title = result[2].str().c_str();
    }
    return title;
}


int main()
{
    std::string title;
    title = GetTitle2("TITLE \"Hello, world! (1)\"");
    std::cout << title << std::endl;
    title = GetTitle2("TITLE \"Hello, world! (2)\"");
    std::cout << title << std::endl;
    return 1;
}