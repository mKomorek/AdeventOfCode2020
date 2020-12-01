def read_data_as_lines(fileName):
    with open("data.txt") as dataFile:
        numbers = dataFile.readlines()
    return numbers

def computed_value_part_1(numbers):
    for number in numbers:
        for number2 in numbers:
            if int(number) + int(number2) == 2020:
                return int(number)*int(number2)

def computed_value_part_2(numbers):
    for number in numbers:
        for number2 in numbers:
            if int(number) + int(number2) > 2020:
                continue
            for number3 in numbers:
                if int(number) + int(number2) + int(number3) == 2020:
                    return int(number)*int(number2)*int(number3)

if __name__ == "__main__":
    numbers = read_data_as_lines("data.txt")
    print(computed_value_part_1(numbers))
    print(computed_value_part_2(numbers))
