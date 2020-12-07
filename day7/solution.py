from collections import defaultdict

def read_data_as_lines(fileName):
    with open("data.txt") as dataFile:
        data = dataFile.readlines()
    return data

def preprocess_data(dataAsLines):
    containDict = defaultdict(list)
    parentDict = defaultdict(list)

    for line in dataAsLines:
        if "other" in line:
            continue
        parent, children = parse_child_and_parent(line)
        for child in children.split(", "):
            number, color1, color2, _ = child.split()
            color = color1 + " " + color2
            containDict[parent].append((int(number), color))
            parentDict[color].append(parent)
    return containDict, parentDict

def parse_child_and_parent(line):
    parent, children = line.replace(" bags", "", 1).split(" contain ")
    return parent, children

def compute_part_1(dataAsLines, color):
    containDict, parentDict = preprocess_data(dataAsLines)

    setOfParents = set()
    listOfParents = [color]
    for color in listOfParents:
        for key in parentDict:
            if key == color:
                for child in parentDict[key]:
                    if child not in setOfParents:
                        setOfParents.add(child)
                        listOfParents.append(child)
    return len(setOfParents)

def compute_part_2(dataAsLines, color):
    containDict, parentDict = preprocess_data(dataAsLines)
    def compute_recursively(color):
        return 1 + sum(
            number * compute_recursively(nextColor)
            for number, nextColor in containDict[color]
        )
    return compute_recursively(color) - 1

if __name__ == "__main__":
    color = "shiny gold"
    dataAsLines = read_data_as_lines("data.txt")
    print(f"PART 1: {compute_part_1(dataAsLines, color)}")
    print(f"PART 2: {compute_part_2(dataAsLines, color)}")
