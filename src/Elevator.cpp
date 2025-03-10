#include "Elevator.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

Elevator::Elevator()
{
    Route = nullptr;
    CurrentNode = nullptr;
}

Elevator::Elevator(const Elevator& _other)
{
    InternalCopy(_other);
}

Elevator& Elevator::operator=(const Elevator& _other)
{
    InternalCopy(_other);
    return *this;
}

void Elevator::InternalCopy(const Elevator& _other)
{
    Route = _other.Route;
    CurrentNode = _other.CurrentNode;
}

Elevator::~Elevator()
{
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

void Elevator::SetRoute(const int _nFloorStart, std::vector<int> _FloorList)
{
    CleanRoute();
    std::sort(_FloorList.begin(), _FloorList.end());

    std::vector<int> finalRouteList;

    // determine if a full sort is required
    const bool bLessThanMin = *_FloorList.begin() > _nFloorStart;
    const bool bGreaterThanMax = *(_FloorList.end() - 1) < _nFloorStart;
    const bool bNeedToSort = !bLessThanMin && !bGreaterThanMax;

    if(bNeedToSort)
    {
        // find split based on floor
        auto iter = _FloorList.begin();
        while(*iter < _nFloorStart) iter++;

        std::vector<int> higherList(iter, _FloorList.end());
        std::vector<int> lowerList(_FloorList.begin(), iter);

        // find distance between lowest and highest floors relative to start
        const int nLowerDiff = abs(_nFloorStart - *lowerList.begin());
        const int nHigherDiff = abs(_nFloorStart - *(higherList.end() - 1));

        // determine start direction based on distance
        const bool bLowerStart = nLowerDiff < nHigherDiff;
        std::vector<int>& startingList = bLowerStart ? lowerList : higherList;
        std::sort(startingList.begin(), startingList.end(), [bLowerStart](int l, int r){ return bLowerStart ? (l > r) : (r > l);});
        std::vector<int>& endingList = bLowerStart ? higherList : lowerList;
        std::sort(endingList.begin(), endingList.end(), [bLowerStart](int l, int r){ return bLowerStart ? (l < r) : (r < l);});

        // generate the final route
        finalRouteList = std::vector<int>(startingList.begin(), startingList.end());
        finalRouteList.insert(finalRouteList.end(), endingList.begin(), endingList.end());
    }
    else
    {
        if(bLessThanMin)
        {
            finalRouteList = _FloorList;
        }
        else if(bGreaterThanMax)
        {
            std::sort(_FloorList.begin(), _FloorList.end(), [](int l, int r){return r < l;});
            finalRouteList = _FloorList;
        }
    }

    // generate the route linked list
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
    // exit if we reacht he end of the route, output result
    if(!CurrentNode || !CurrentNode->Next)
    {
        std::cout << "Result: " << _fTravelTimeTotal << " ";
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

    // determine travel time and move to next floor node
    const int nStartingFloor = CurrentNode->Floor;
    const int nTargetFloor = CurrentNode->Next->Floor;
    const int nFloorDiff = abs(nTargetFloor - nStartingFloor);
    const float fTimeToMove = nFloorDiff * TRAVEL_TIME;

    CurrentNode = CurrentNode->Next;

    MoveElevator(_fTravelTimeTotal + fTimeToMove);
}