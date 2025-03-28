#pragma once
#include "LinkedQueue.h"
#include "Resource.h"

class Center
{
private:
    LinkedQueue<Resource*> E_Devices;
    LinkedQueue<Resource*> U_Devices;
    LinkedQueue<Resource*> X_Rooms;

public:
    Center();
    ~Center();

    void AddResource(Resource* res, char type);
    Resource* GetNextResource(char type);
};