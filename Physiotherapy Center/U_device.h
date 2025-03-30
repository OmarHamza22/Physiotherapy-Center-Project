#pragma once
#include "Resource.h"
class Resource;
class Patient;

class U_device : public Resource {
public:
    U_device(int id);
    bool IsAvailable() override;
    void Assign(Patient* p) override;
    Patient* Release() override;
};

