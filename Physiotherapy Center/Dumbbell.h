#pragma once
#include "Resource.h"
#include <iostream>
using namespace std;

class Dumbbell :
    public Resource
{
public:
    Dumbbell(int id);
    bool IsAvailable() override;
    void Assign(Patient* p) override;
    Patient* Release() override;
    void print()override;
};

