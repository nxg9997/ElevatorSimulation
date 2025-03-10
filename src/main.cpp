#include <iostream>
#include <vector>
#include <string>
#include "Elevator.h"

int main()
{
    std::cout << "=== Welcome to the Elevator ===" << std::endl;

    std::cout << "Enter the Elevator Instructions: ";
    std::string inputFull;
    std::getline(std::cin, inputFull);

    char inputFloorNum[256];
    char* charFloorNumCurrent = inputFloorNum;
    char const* inputFullCurrent = inputFull.c_str();
    char const* inputFullListStart = inputFull.c_str();

    int nEqualCount = 0;
    bool bSetStart = false;
    while(nEqualCount < 2)
    {
        if(nEqualCount == 1 && !bSetStart)
        {
            if(*inputFullCurrent == ' ')
            {
                *charFloorNumCurrent = '\0';
                bSetStart = true;
            }
            else
            {
                *charFloorNumCurrent = *inputFullCurrent;
                charFloorNumCurrent++;
            }
        }
        if(*inputFullCurrent == '=')
        {
            nEqualCount++;
            if(nEqualCount == 2)
            {
                inputFullListStart = inputFullCurrent + 1;
                break;
            }
        }
        inputFullCurrent++;
    }

    const int nStartingFloor = atoi(inputFloorNum);

    // parse list of floors to visit
    char const* charInputCurrent = inputFullListStart;
    char parseString[4096];
    char* charParseCurrent = parseString;
    std::vector<int> inputFloorList;
    do
    {
        if(*charInputCurrent == ',' || *charInputCurrent == '\0')
        {
            *charParseCurrent = '\0';
            inputFloorList.push_back(atoi(parseString));
            charParseCurrent = parseString;
        }
        else if(*charInputCurrent < 48 || *charInputCurrent > 57)
        {
            std::cout << "invalid character input; skipping." << std::endl;
        }
        else
        {
            *charParseCurrent = *charInputCurrent;
            charParseCurrent++;
        }
        charInputCurrent++;
    } while(*(charInputCurrent - 1) != '\0');

    Elevator elevator;
    elevator.SetRoute(nStartingFloor, inputFloorList);
    elevator.StartElevator();

    return 0;
}