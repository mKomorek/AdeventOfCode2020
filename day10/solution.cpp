#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> readFileAsLines(const std::string& fileName)
{
    auto dataAsLines = std::vector<int>{};
    std::string buffer;
    std::ifstream dataFile(fileName);
    if(dataFile.is_open())
    {
        while(getline(dataFile, buffer))
            dataAsLines.push_back(std::stoi(buffer));
    }
    dataFile.close();
    return dataAsLines;
}

void increment_jolts_counter(
    const int& value, int& jolts_1_counter, int& jolts_2_counter, int& jolts_3_counter)
{
    switch (value) {
        case 1: jolts_1_counter += 1; break;
        case 2: jolts_2_counter += 1; break;
        case 3: jolts_3_counter += 1; break;
    }
}

long long int compute_part_1(std::vector<int>& dataAsLines)
{
    std::sort(dataAsLines.begin(), dataAsLines.end());
    int jolts_1_counter = 0, jolts_2_counter = 0, jolts_3_counter = 0;
    increment_jolts_counter(
        dataAsLines[0], jolts_1_counter, jolts_2_counter, jolts_3_counter
    );
    for(size_t i=1; i<dataAsLines.size(); ++i)
        increment_jolts_counter(
            dataAsLines[i]-dataAsLines[i-1],
            jolts_1_counter, jolts_2_counter, jolts_3_counter
        );

    return jolts_1_counter * (jolts_3_counter+1);
}

long long int compute_part_2(std::vector<int>& dataAsLines)
{
    dataAsLines.push_back(0);
    std::sort(dataAsLines.begin(), dataAsLines.end());
    dataAsLines.push_back(dataAsLines[dataAsLines.size()-1]+3);
    std::vector<long long int> possibleCombination(dataAsLines.size(), 0);
    possibleCombination[0] = 1;
    for(int i = 1; i<=dataAsLines.size(); ++i)
    {
        for(int j=i; j>=0; --j)
        {
            if(dataAsLines[i] - dataAsLines[j] <= 3)
                possibleCombination[i] += possibleCombination[j];
            else
                break;
        }
    }
    return possibleCombination[dataAsLines.size()-1];
}

int main()
{
    auto dataAsLines = readFileAsLines("data.txt");
    std::cout << "Part 1: " << compute_part_1(dataAsLines) << std::endl;
    std::cout << "Part 2: \n" << compute_part_2(dataAsLines) << std::endl;
}
