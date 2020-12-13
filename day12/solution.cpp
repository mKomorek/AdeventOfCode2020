#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include <cmath>

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

std::pair<char, int> decode_line(const std::string& line)
{
    char action = *line.begin();
    int value = std::stoi(std::string(line.begin()+1, line.end()));
    return std::make_pair(action, value);
}

long int start_end_manhattan_distance_p1(std::vector<std::string>& dataAsLines)
{
    std::vector<int> directions{1,0,-1,0};
    int currentDirection = 1;
    long int x_pos=0, y_pos=0;
    for(auto& line : dataAsLines)
    {
        auto decodedLine = decode_line(line);
        switch (decodedLine.first) {
            case 'N': x_pos += decodedLine.second; break;
            case 'S': x_pos -= decodedLine.second; break;
            case 'E': y_pos += decodedLine.second; break;
            case 'W': y_pos -= decodedLine.second; break;
            case 'L': currentDirection -= decodedLine.second/90; break;
            case 'R': currentDirection += decodedLine.second/90; break;
            case 'F': {
                x_pos += directions[std::abs((currentDirection))%4]*decodedLine.second;
                y_pos += directions[std::abs((currentDirection)-1)%4]*decodedLine.second;
                break;
            }
        }
    }
    return std::abs(x_pos) + std::abs(y_pos);
}

long int start_end_manhattan_distance_p2(std::vector<std::string>& dataAsLines)
{
    std::vector<int> waypoint{1, 10, 0, 0};
    long int x_pos=0, y_pos=0;
    for(auto& line : dataAsLines)
    {
        auto decodedLine = decode_line(line);
        switch (decodedLine.first) {
            case 'N': waypoint[0] += decodedLine.second; break;
            case 'S': waypoint[2] += decodedLine.second; break;
            case 'E': waypoint[1] += decodedLine.second; break;
            case 'W': waypoint[3] += decodedLine.second; break;
            case 'L': {
                std::rotate(
                    waypoint.begin(),
                    waypoint.begin()+decodedLine.second/90,
                    waypoint.end()
                );
                break;
            }
            case 'R': {
                std::rotate(
                    waypoint.rbegin(),
                    waypoint.rbegin()+decodedLine.second/90,
                    waypoint.rend()
                );
                break;
            }
            case 'F': {
                x_pos += (waypoint[0]-waypoint[2]) * decodedLine.second;
                y_pos += (waypoint[1]-waypoint[3]) * decodedLine.second;
                break;
            }
        }
    }
    return std::abs(x_pos) + std::abs(y_pos);
}

int main()
{
    std::vector<std::string> dataAsLines = readFileAsLines("data.txt");
    std::cout << "Part 1: " << start_end_manhattan_distance_p1(dataAsLines) << std::endl;
    std::cout << "Part 2: " << start_end_manhattan_distance_p2(dataAsLines) << std::endl;
}
