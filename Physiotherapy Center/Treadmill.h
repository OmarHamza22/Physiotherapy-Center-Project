#pragma once
#include "Resource.h"
#include <iostream>
using namespace std;

class Treadmill :
    public Resource
{
public:
    Treadmill(int id);
    bool IsAvailable() override;
    void Assign(Patient* p) override;
    Patient* Release() override;
    void print()override;
};

