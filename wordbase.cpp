#include "wordbase.hh"
#include <fstream>
#include <vector>
#include <iostream>

WordBase::WordBase(QObject *parent) : QObject(parent)
{
    initialized_ = false;
    colors_ = {0, 1, 0, 1, 0};
}

WordBase::~WordBase()
{

}

/*
WordBase::WordBase(std::string const& filename)
{
    WordBase();
    readWords(filename);
}
*/

void WordBase::readWords(std::string const& filename)
{
    std::ifstream file;
    std::string line;

    file.open(filename);

    while (std::getline(file, line)) {
        std::vector<std::string> splitted = splitLine(line);
        wordBase_.push_back(splitted);
    }

    file.close();
    initialized_ = true;
}

size_t WordBase::size() const
{
    return wordBase_.size();
}

QVector<int> WordBase::currentColors() const
{
    return colors_;
}

void WordBase::changeColors()
{

}

std::vector<std::string> WordBase::splitLine(std::string& line)
{
    std::vector<std::string> ret;
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;

    trimLine(line); // Remove whitespace from beginning and end

    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        ret.push_back(token);
        line.erase(0, pos + delimiter.length());
    }
    ret.push_back(line);
    if (ret.size() != CARD_COUNT) {
        throw;
    }
    return ret;
}

void WordBase::trimLine(std::string &line)
{
    size_t first_not_ws = line.find_first_not_of(' ');
    line.erase(0, first_not_ws);
    size_t last_not_ws = line.find_last_not_of(' ');
    line.erase(last_not_ws+1, line.size()-last_not_ws);

}
