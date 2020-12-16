#include <iostream>
#include <list>
#include <map>

std::map<long long int, long long int> read_numbers(std::list<long long int>& inputNumbers)
{
    std::map<long long int, long long int> seenNumbers;
    int i = 0;
    for(auto& number : inputNumbers)
    {
        seenNumbers.insert(std::make_pair(number, i));
        ++i;
    }
    return seenNumbers;
}

long long int part_1(
    std::list<long long int>& inputNumbers,
    const long long int& numberOfSpokenNumbers)
{
    auto seenNumbers = read_numbers(inputNumbers);
    while(inputNumbers.size() < static_cast<long unsigned int>(numberOfSpokenNumbers))
    {
        auto search = seenNumbers.find(inputNumbers.back());
        if(search == seenNumbers.end())
        {
            inputNumbers.push_back(0);
            auto it = inputNumbers.end();
            std::advance(it, -2);
            seenNumbers.insert_or_assign(*it, inputNumbers.size()-2);
        }
        else
        {
            long long int temp = inputNumbers.size()-1;
            inputNumbers.push_back(temp - search->second);
            auto it = inputNumbers.end();
            std::advance(it, -2);
            seenNumbers.insert_or_assign(*it, temp);
        }
    }
    return inputNumbers.back();
}

int main()
{
    auto inputNumbers = std::list<long long int>{13,0,10,12,1,5,8};
    std::cout << "Part 1: " << part_1(inputNumbers, 2020) << std::endl;
    std::cout << "Part 2: " << part_1(inputNumbers, 30000000) << std::endl;
}
