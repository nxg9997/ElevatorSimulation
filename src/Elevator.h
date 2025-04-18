#pragma once
#include <queue>

struct RouteNode
{
public:
    RouteNode(const int _floor)
    {
        Floor = _floor;
    }

    void SetNextNode(RouteNode* _next)
    {
        Next = _next;
    }

    RouteNode* Next = nullptr;
    int Floor = 0;
};

class Elevator
{
public:
    Elevator();
    Elevator(const Elevator& _other);
    Elevator& operator=(const Elevator& _other);
    ~Elevator();

    void SetRoute(const int _nFloorStart, std::vector<int> _FloorList);
    void StartElevator();

private:
    void MoveElevator(float _fTravelTimeTotal = 0);
    void CleanRoute();
    void InternalCopy(const Elevator& _other);

    RouteNode* Route = nullptr;
    RouteNode* CurrentNode = nullptr;

    const float TRAVEL_TIME = 10.f;
};