#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
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

int decode_number(std::string& code)
{
    for(int i=0; i<code.size(); ++i)
    {
        if(code[i] == 'F' || code[i] == 'L')
            code[i] = '0';
        else
            code[i] = '1';
    }
    std::bitset<8> bits(code);
    return bits.to_ulong();
}

int compute_id(const int &row, const int& column)
{
    return 8*row + column;
}

int max_id(const std::vector<std::string>& dataAsLines)
{
    int maxId = 0;
    for(auto& line : dataAsLines)
    {
        std::string rowCode(std::begin(line), std::begin(line)+7);
        std::string columnCode(std::begin(line)+7, std::begin(line)+10);
        maxId = std::max(
            maxId, compute_id(decode_number(rowCode), decode_number(columnCode))
        );
    }
    return maxId;
}

std::vector<int> compute_all_ids(const std::vector<std::string>& dataAsLines)
{
    std::vector<int> ids{};
    for(auto& line : dataAsLines)
    {
        std::string rowCode(std::begin(line), std::begin(line)+7);
        std::string columnCode(std::begin(line)+7, std::begin(line)+10);
        ids.push_back(compute_id(decode_number(rowCode), decode_number(columnCode)));
    }
    std::sort(ids.begin(), ids.end());
    return ids;
}

int my_seat_id(const std::vector<std::string>& dataAsLines)
{
    auto ids = compute_all_ids(dataAsLines);
    auto iterator = std::adjacent_find(
        ids.begin(), ids.end(),
        [](const int& a, const int& b){ return a + 1 != b; }
    );
    return *iterator + 1;
}

int main()
{
    std::vector<std::string> dataAsLines = readFileAsLines("data.txt");
    std::cout << "Part 1: " << max_id(dataAsLines) << std::endl;
    std::cout << "Part 2: " << my_seat_id(dataAsLines) << std::endl;
}
