import re

def read_data_as_lines(fileName):
    with open("data.txt") as dataFile:
        data = dataFile.readlines()
    return data

def create_passports_list(data):
    listOfPassports = list()
    passportProperties = list()
    for line in data:
        if line == '\n':
            create_passport_dictionary(line, passportProperties, listOfPassports)
            passportProperties.clear()
        else:
            tempList = line.split(' ')
            for element in tempList:
                passportProperties.append(element)

    create_passport_dictionary(line, passportProperties, listOfPassports)
    return listOfPassports

def create_passport_dictionary(line, passportProperties, listOfPassports):
    passportsDict = dict()
    for line in passportProperties:
        separatorPosition = line.find(':')
        passportsDict[line[ : separatorPosition]] = (
            line[separatorPosition+1 : ].replace('\n', '')
        )
    listOfPassports.append(passportsDict)

def computed_valid_passports_1(passportsDicts):
    numberOfValidPassports = 0
    validPassports = list()
    for passport in passportsDicts:
        if len(passport) == 8:
            numberOfValidPassports += 1
            validPassports.append(passport)
        elif len(passport) < 7:
            continue
        else:
            if ("ecl" in passport and
                "eyr" in passport and
                "hcl" in passport and
                "pid" in passport and
                "iyr" in passport and
                "byr" in passport and
                "hgt" in passport):
                numberOfValidPassports += 1
                validPassports.append(passport)
    return numberOfValidPassports, validPassports

def computed_valid_passports_2(passportsDicts):
    numberOfValidPassports = 0
    for passport in passportsDicts:
        if len(passport) < 7:
            continue
        else:
            if (four_digit_validator(passport['byr'], 1920, 2002) and
                four_digit_validator(passport['iyr'], 2010, 2020) and
                four_digit_validator(passport['eyr'], 2020, 2030) and
                hgt_validator(passport['hgt']) and
                hcl_validator(passport['hcl']) and
                ecl_validator(passport['ecl']) and
                pid_validator(passport['pid'])):
                numberOfValidPassports += 1
    return numberOfValidPassports

def four_digit_validator(value, least, most):
    if len(value) != 4:
        return False
    if int(value) < least:
        return False
    if int(value) > most:
        return False
    return True

def hgt_validator(value):
    if value.find('cm') > 0:
        if int(value[ : value.find('cm')]) < 150:
            return False
        if int(value[ : value.find('cm')]) > 193:
            return False
    else:
        if int(value[ : value.find('in')]) < 59:
            return False
        if int(value[ : value.find('in')]) > 76:
            return False
    return True

def hcl_validator(value):
    if value[0] != '#':
        return False
    else:
        pattern = '[a-f\d]{6}'
        if re.match(pattern, value[1:]):
            return True
        else:
            return False

def ecl_validator(value):
    if (value == 'amb' or
        value == 'blu' or
        value == 'brn' or
        value == 'gry' or
        value == 'grn' or
        value == 'hzl' or
        value == 'oth'):
        return True
    return False

def pid_validator(value):
    pattern = '^(\d{9})$'
    if re.match(pattern, value):
        return True
    else:
        return False

if __name__ == "__main__":
    data = read_data_as_lines("data.txt")
    listOfPassports = create_passports_list(data)
    numberOfValidPassports, validPassports = computed_valid_passports_1(listOfPassports)
    print(f"PART 1: {numberOfValidPassports}")
    print(f"PART 2: {computed_valid_passports_2(validPassports)}")
