#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* openFile(char* fileName)
{
    FILE* filePtr;
    filePtr = fopen(fileName, "r");
    if(filePtr == NULL)
    {
        perror("Error while opening file");
        exit(-1);
    }
    return filePtr;
}

int numberOfDataInFile()
{
    FILE* filePtr = openFile("data.txt");
    char buffer[8];
    int counter = 0;
    while(fgets(buffer, sizeof(buffer), filePtr) != NULL)
        ++counter;
    return counter;
}

char** readFile()
{
    int dataAmount = numberOfDataInFile();
    char** arrayOfStrings;
    arrayOfStrings = malloc(dataAmount * sizeof(char*));

    FILE* filePtr = openFile("data.txt");
    char buffer[8];
    int i = 0;
    while(fgets(buffer, sizeof(buffer), filePtr) != NULL)
    {
        arrayOfStrings[i] = malloc(sizeof(buffer) * sizeof(char));
        strcpy(arrayOfStrings[i], buffer);
        ++i;
    }
    fclose(filePtr);
    return arrayOfStrings;
}

int computeValuePart1()
{
    char** arrayOfInputStrings = readFile();
    for(int i=0; i<200; ++i)
    {
        for(int j=0; j<200; ++j)
        {
            if(atoi(arrayOfInputStrings[i]) + atoi(arrayOfInputStrings[j]) == 2020)
                return atoi(arrayOfInputStrings[i]) * atoi(arrayOfInputStrings[j]);
        }
    }
    return 0;
}

int main()
{
    int result = computeValuePart1();
    printf("%d\n", result);
    return 0;
}
