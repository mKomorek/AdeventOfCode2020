#include <iostream>
#include <fstream>
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

std::string pathExtension(const int& multiplyTime, const std::string& path)
{
    std::string extendedPath = path;
    for(int i=1; i<multiplyTime; ++i)
        extendedPath += path;
    return extendedPath;
}

int countTreesAtSlope(std::vector<std::string>& dataAsLines, const int& right, const int& down=1)
{
    int baseWidth = dataAsLines[0].length();
    int widthCounter = 0;
    int treeCounter = 0;
    int multiplyTime = 1;

    for(int i=1; i<dataAsLines.size(); i+=down)
    {
        widthCounter += right;

        if(widthCounter >=   baseWidth)
        {
            ++multiplyTime;
            baseWidth = dataAsLines[i].length();
        }

        dataAsLines[i] = pathExtension(multiplyTime, dataAsLines[i]);
        if(dataAsLines[i].at(widthCounter) == '#')
            ++treeCounter;
    }
    return treeCounter;
}

int main()
{
    std::vector<std::string> dataAsLines = readFileAsLines("data.txt");
    std::cout << static_cast<unsigned long long>(countTreesAtSlope(dataAsLines, 1)) *
        countTreesAtSlope(dataAsLines, 3) *
        countTreesAtSlope(dataAsLines, 5) *
        countTreesAtSlope(dataAsLines, 7) *
        countTreesAtSlope(dataAsLines, 1, 2)
        << std::endl;

    return 0;
}
