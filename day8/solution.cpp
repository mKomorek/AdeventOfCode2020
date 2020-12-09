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

std::pair<std::string, int> parse_instruction(const std::string& instruction)
{
    const std::string instructionName = std::string(
        std::begin(instruction), std::begin(instruction)+3
    );
    const int instructionValue = std::stoi(
        std::string(std::begin(instruction)+4, std::end(instruction))
    );
    return std::make_pair(instructionName, instructionValue);
}

std::pair<int, bool> accumulator_value(const std::vector<std::string>& instructions)
{
    int accumulatorValue = 0;
    std::set<int> seenLines;
    for(int i=0; i<instructions.size(); ++i)
    {
        auto instruction = parse_instruction(instructions[i]);
        if(seenLines.find(i) != seenLines.end())
            return std::make_pair(accumulatorValue, false);
        seenLines.insert(i);

        if(instruction.first == "acc")
            accumulatorValue += instruction.second;
        if(instruction.first == "jmp")
            i += instruction.second - 1;
    }
    return std::make_pair(accumulatorValue, true);
}

int accumulator_value_part2(const std::vector<std::string>& instructions)
{
    for(int i=0; i<instructions.size(); ++i)
    {
        auto copyOfInstrctions(instructions);
        auto instruction = parse_instruction(instructions[i]);

        if(instruction.first == "jmp")
        {
            copyOfInstrctions[i] = "nop +0";
            auto result = accumulator_value(copyOfInstrctions);
            if(result.second == true)
                return result.first;
        }
    }
    return -1;
}

int main()
{
    std::vector<std::string> dataAsLines = readFileAsLines("data.txt");
    std::cout << "Part 1: " << accumulator_value(dataAsLines).first << std::endl;
    std::cout << "Part 2: " << accumulator_value_part2(dataAsLines) << std::endl;
}
