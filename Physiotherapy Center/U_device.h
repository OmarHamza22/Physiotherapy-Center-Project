#pragma once
#include "Resource.h"
#include <iostream>
using namespace std;
class U_device : public Resource {
public:
    U_device(int id);
    bool IsAvailable() override;
    void Assign(Patient* p) override;
    Patient* Release() override;
    void print()override;
};

