#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> readFileAsLines(const std::string& fileName)
{
    auto dataAsLines = std::vector<std::string>{};
    std::string buffer;
    std::ifstream dataFile(fileName);
    if(dataFile.is_open())
    {
        while(getline(dataFile, buffer))
            dataAsLines.push_back(buffer);
    }
    dataFile.close();
    return dataAsLines;
}

std::vector<std::pair<int, std::string>> preprocessData(const std::vector<std::string>& dataAsLines)
{
    auto preprocessData = std::vector<std::pair<int, std::string>>{};
    int groupCount = 0;
    std::string groupData;
    for(auto& line : dataAsLines)
    {
        if(line.empty())
        {
            auto pair = std::make_pair(groupCount, groupData);
            preprocessData.push_back(pair);
            groupCount = 0;
            groupData.clear();
        }
        else
        {
            ++groupCount;
            groupData.append(line);
        }
    }
    auto pair = std::make_pair(groupCount, groupData);
    preprocessData.push_back(pair);
    return preprocessData;
}

int countYesAnswers_1(const std::vector<std::string>& dataAsLines)
{
    auto preprocessedData = preprocessData(dataAsLines);
    int counter = 0;
    for(auto &line : preprocessedData)
    {
        std::set<char> setOfAnswers(std::begin(line.second), std::end(line.second));
        counter += setOfAnswers.size();
    }
    return counter;
}

int countYesAnswers_2(const std::vector<std::string>& dataAsLines)
{
    auto preprocessedData = preprocessData(dataAsLines);
    int counter = 0;
    for(auto &line : preprocessedData)
    {
        std::set<char> setOfAnswers(std::begin(line.second), std::end(line.second));
        for(auto& mark : setOfAnswers)
            if(line.first == std::count(line.second.begin(), line.second.end(), mark))
                ++counter;
    }
    return counter;
}

int main()
{
    std::vector<std::string> dataAsLines = readFileAsLines("data.txt");
    std::cout << "Part 1: " << countYesAnswers_1(dataAsLines) << std::endl;
    std::cout << "Part 2: " << countYesAnswers_2(dataAsLines) << std::endl;
}
