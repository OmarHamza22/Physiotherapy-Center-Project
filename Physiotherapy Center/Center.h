#pragma once
#include "E_device.h"
#include "U_device.h"
#include "X_room.h"
#include "LinkedQueue.h"
class E_device;
class U_device;
class X_room;

class Center
{
private:
    LinkedQueue<E_device*> E_Devices;
    LinkedQueue<U_device*> U_Devices;
    LinkedQueue<X_room*> X_Rooms;

public:
    Center();
    ~Center();

    void AddEDevice(int id);
    void AddUDevice(int id);
    void AddXRoom(int id, int capacity);

    E_device* GetAvailableEDevice();
    U_device* GetAvailableUDevice();
    X_room* GetAvailableXRoom();
};