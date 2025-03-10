#include "Elevator.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

Elevator::Elevator()
{
    
}

Elevator::Elevator(const Elevator& _other)
{

}

Elevator& Elevator::operator=(const Elevator& _other)
{

    return *this;
}

Elevator::~Elevator()
{
    // cleanup Route
    CleanRoute();
}

void Elevator::CleanRoute()
{
    RouteNode* rn = Route;
    while(rn)
    {
        RouteNode* next = rn->Next;
        delete rn;
        rn = next;
    }
}

void Elevator::CallElevator(const int _nFloor)
{

}

void Elevator::SetRoute(const int _nFloorStart, std::vector<int> _FloorList)
{
    CleanRoute();

    std::sort(_FloorList.begin(), _FloorList.end());

    // find split based on floor
    auto iter = _FloorList.begin();
    while(*iter < _nFloorStart) iter++;

    std::vector<int> higherList(iter, _FloorList.end());
    std::vector<int> lowerList(_FloorList.begin(), iter);

    // find distance between lowest and highest floors relative to start
    const int nLowerDiff = abs(_nFloorStart - *lowerList.begin());
    const int nHigherDiff = abs(_nFloorStart - *(higherList.end()));

    // determine start direction based on distance
    std::vector<int> finalRouteList;
    const bool bLowerStart = nLowerDiff < nHigherDiff;
    std::vector<int>& startingList = bLowerStart ? lowerList : higherList;
    std::sort(startingList.begin(), startingList.end(), [bLowerStart](int l, int r){ return bLowerStart ? (l > r) : (r > l);});
    std::vector<int>& endingList = bLowerStart ? higherList : lowerList;
    
    // generate the final route
    finalRouteList = std::vector<int>(startingList.begin(), startingList.end());
    finalRouteList.insert(finalRouteList.end(), endingList.begin(), endingList.end());

    Route = new RouteNode(_nFloorStart);
    RouteNode* rn = Route;
    for(const int& floor : finalRouteList)
    {
        RouteNode* next = new RouteNode(floor);
        rn->SetNextNode(next);
        rn = next;
    }
    CurrentNode = Route;
}

void Elevator::StartElevator()
{
    MoveElevator();
}

void Elevator::MoveElevator(float _fTravelTimeTotal)
{
    if(!CurrentNode || !CurrentNode->Next)
    {
        std::cout << _fTravelTimeTotal << " ";
        RouteNode* rn = Route;
        while(rn)
        {
            std::cout << rn->Floor;
            rn = rn->Next;
            if(rn) std::cout << ", ";
        }
        std::cout << std::endl;
        return;
    }

    const int nStartingFloor = CurrentNode->Floor;
    const int nTargetFloor = CurrentNode->Next->Floor;
    const int nFloorDiff = abs(nTargetFloor - nStartingFloor);
    const float fTimeToMove = nFloorDiff * TravelTimeBetweenFloors;

    CurrentNode = CurrentNode->Next;

    MoveElevator(_fTravelTimeTotal + fTimeToMove);
}