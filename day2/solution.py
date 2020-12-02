def read_data_as_lines(fileName):
    with open("data.txt") as dataFile:
        data = dataFile.readlines()
    return data

def preproces_input(lineOfData):
    minNumberOfAppearances = lineOfData[ : lineOfData.find('-')]
    maxNumberOfAppearances = lineOfData[lineOfData.find('-')+1 : lineOfData.find(' ')]
    mark = lineOfData[lineOfData.find(' ')+1 : lineOfData.find(':')]
    password = lineOfData[lineOfData.find(': ')+2 : ]
    return int(minNumberOfAppearances), int(maxNumberOfAppearances), mark, password

def check_password_correctness(
        minNumberOfAppearances, maxNumberOfAppearances, mark, password
    ):
    counter = int()
    for letter in password:
        if letter == mark:
            counter += 1
    if counter in range(minNumberOfAppearances, maxNumberOfAppearances+1):
        return True
    else:
        return False

def number_of_correctness_passwords_1(data):
    number_of_correctness_passwords = int()
    for line in data:
        min, max, mark, password = preproces_input(line)
        if check_password_correctness(min, max, mark, password):
            number_of_correctness_passwords += 1
    return number_of_correctness_passwords

def number_of_correctness_passwords_2(data):
    number_of_correctness_passwords = int()
    for line in data:
        min, max, mark, password = preproces_input(line)
        if password[min-1]==mark and password[max-1]!=mark:
            number_of_correctness_passwords+=1
        if password[min-1]!=mark and password[max-1]==mark:
            number_of_correctness_passwords+=1
    return number_of_correctness_passwords

if __name__ == "__main__":
    data = read_data_as_lines("data.txt")
    print(number_of_correctness_passwords_1(data))
    print(number_of_correctness_passwords_2(data))
