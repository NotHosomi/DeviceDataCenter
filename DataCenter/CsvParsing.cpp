#include "CsvParsing.h"

std::ifstream CSV::openFileR(std::string name)
{
    std::ifstream file;
    file.open(name, std::ios::in);
    if (!file.is_open())
        throw std::runtime_error("File \"" + name + "\" failed to open");
    return file;
}
std::ofstream CSV::openFileW(std::string name)
{
    std::ofstream file;
    file.open(name, std::ios::out);
    if (!file.is_open())
        throw std::runtime_error("File \"" + name + "\" failed to open");
    return file;
}

std::vector<std::string> CSV::delimit(std::string s, std::string delimiter)
{
    std::vector<std::string> tokens;
    size_t pos = s.find(delimiter);
    while (pos != std::string::npos)
    {
        if (pos == std::string::npos)
            break;
        tokens.emplace_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
        pos = s.find(delimiter);
    }
    if (s != "")
        tokens.emplace_back(s);
    return tokens;
}

std::pair<std::string, std::string> CSV::delimitOnce(std::string s, std::string delimiter)
{
    std::pair<std::string, std::string> tokens;
    size_t pos = s.find(delimiter);
    if (pos == std::string::npos)
    {
        std::cout << "Bad delimit: " << s << std::endl;
        throw std::runtime_error("Bad split on \"" + s + "\" with delimiter \"" + delimiter + "\"");
    }
    tokens.first = s.substr(0, pos);
    tokens.second = s.substr(pos + delimiter.length(), s.length());
    return tokens;
}