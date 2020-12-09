#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

std::vector<long long int> readFileAsLines(const std::string& fileName)
{
    auto dataAsLines = std::vector<long long int>{};
    std::string buffer;
    std::ifstream dataFile(fileName);
    if(dataFile.is_open())
    {
        while(getline(dataFile, buffer))
            dataAsLines.push_back(std::stoll(buffer));
    }
    dataFile.close();
    return dataAsLines;
}

bool check_number(
    std::vector<long long int>::iterator L_iter,
    std::vector<long long int>::iterator R_iter,
    const long long int& number)
{
    while(L_iter < R_iter)
    {
        if(*L_iter + *R_iter == number)
            return true;
        else if(*L_iter + *R_iter < number)
            ++L_iter;
        else
            --R_iter;
    }
    return false;
}

long long int number_with_no_property(const std::vector<long long int>& dataAsLines)
{
    for(size_t i=0; i<dataAsLines.size()-25; ++i)
    {
        std::vector<long long int> preamble(dataAsLines.begin()+i, dataAsLines.begin()+i+25);
        std::sort(preamble.begin(), preamble.end());
        std::vector<long long int> dataToFind(dataAsLines.begin()+i+25, dataAsLines.end());

        if(!check_number(preamble.begin(), preamble.end()-1, dataAsLines[i+25]))
            return dataAsLines[i+25];
    }
    return -1;
}

long long int min_max_part_2(
    const std::vector<long long int>& dataAsLines,
    const long long int& number)
{
    for(size_t i=0; i<dataAsLines.size(); ++i)
    {
        long long int sum = 0;
        long long int min = std::numeric_limits<long long int>::max();
        long long int max = 0;
        int j = i;
        while(sum < number)
        {
            if(dataAsLines[j]>max)
                max = dataAsLines[j];
            if(dataAsLines[j]<min)
                min = dataAsLines[j];
            sum += dataAsLines[j];
            ++j;
        }
        if(sum == number)
            return min + max;
    }
    return -1;
}

int main()
{
    auto dataAsLines = readFileAsLines("data.txt");
    auto part1 = number_with_no_property(dataAsLines);
    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << min_max_part_2(dataAsLines, part1) << std::endl;
}
