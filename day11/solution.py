import copy

def read_data_as_lines(fileName):
    with open("data.txt") as dataFile:
        data = dataFile.readlines()
        data = [line.replace("\n", "") for line in data]
        data = [list(line) for line in data]
    return data

def preprocess_data(dataAsLines):
    for line in dataAsLines:
        line.append(".")
        line.insert(0, ".")
    dataAsLines.append(['.']*len(dataAsLines[0]))
    dataAsLines.insert(0, ['.']*len(dataAsLines[0]))

def number_of_occupied_seats(dataAsLines):
    dataAsLinesCP = list()
    counterrr = 0
    while dataAsLines != dataAsLinesCP:
        counterrr += 1
        dataAsLinesCP = copy.deepcopy(dataAsLines)
        for rowNumber in range(1, len(dataAsLines)-1):
            for columnNumber in range(1, len(dataAsLines[rowNumber])-1):
                if dataAsLines[rowNumber][columnNumber] == "#":
                    if count_occupied_around(
                            dataAsLinesCP[rowNumber-1:rowNumber+2],
                            columnNumber
                        )-1 >= 4:
                        dataAsLines[rowNumber][columnNumber] = "L"
                if dataAsLines[rowNumber][columnNumber] == "L":
                    if count_occupied_around(
                            dataAsLinesCP[rowNumber-1:rowNumber+2],
                            columnNumber
                        ) == 0:
                        dataAsLines[rowNumber][columnNumber] = "#"
    return sum(i.count("#") for i in dataAsLines)

def count_occupied_around(lines, columnBaseValue):
    count = 0;
    for rowCounter in range(0, 3):
        for columnCounter in range(columnBaseValue-1, columnBaseValue+2):
            if columnCounter >= len(lines[rowCounter]):
                break
            if lines[rowCounter][columnCounter] == "#":
                count +=  1
    return count

if __name__ == "__main__":
    dataAsLines = read_data_as_lines("data.txt")
    preprocess_data(dataAsLines)
    print(f"PART 1: {number_of_occupied_seats(dataAsLines)}")
    #print(f"PART 2: {}")
