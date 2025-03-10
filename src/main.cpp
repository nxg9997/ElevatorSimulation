#include <iostream>
#include <vector>
#include <string>
#include "Elevator.h"

int main()
{
    std::cout << "=== Welcome to the Elevator Simulation ===" << std::endl;

    // get input instructions from the user
    std::cout << "Enter the Elevator Instructions (ex. start=x floor=x,y,z): ";
    std::string strInputFull;
    std::getline(std::cin, strInputFull);

    char cstrInputFloorNum[256];
    char* charFloorNumCurrent = cstrInputFloorNum;
    char const* charInputFullCurrent = strInputFull.c_str();
    char const* charInputFullListStart = strInputFull.c_str();

    int nEqualCount = 0;
    bool bSetStart = false;
    while(nEqualCount < 2)
    {
        if(nEqualCount == 1 && !bSetStart)
        {
            if(*charInputFullCurrent == ' ')
            {
                *charFloorNumCurrent = '\0';
                bSetStart = true;
            }
            else if(*charInputFullCurrent < 48 || *charInputFullCurrent > 57)
            {
                std::cout << "invalid character input; skipping." << std::endl;
            }
            else
            {
                *charFloorNumCurrent = *charInputFullCurrent;
                charFloorNumCurrent++;
            }
        }
        if(*charInputFullCurrent == '=')
        {
            nEqualCount++;
            if(nEqualCount == 2)
            {
                charInputFullListStart = charInputFullCurrent + 1;
                break;
            }
        }
        charInputFullCurrent++;
    }

    // parse starting floor
    const int nStartingFloor = atoi(cstrInputFloorNum);

    // parse list of floors to visit
    char const* charInputCurrent = charInputFullListStart;
    char cstrParseString[4096];
    char* charParseCurrent = cstrParseString;
    std::vector<int> inputFloorList;
    do
    {
        if(*charInputCurrent == ',' || *charInputCurrent == '\0')
        {
            *charParseCurrent = '\0';
            inputFloorList.push_back(atoi(cstrParseString));
            charParseCurrent = cstrParseString;
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

    // run the elevator
    Elevator elevator;
    elevator.SetRoute(nStartingFloor, inputFloorList);
    elevator.StartElevator();

    return 0;
}