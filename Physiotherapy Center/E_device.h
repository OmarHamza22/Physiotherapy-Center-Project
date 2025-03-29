#pragma once
#include "Resource.h"

class E_device : public Resource {
public:
    E_device(int id);
    bool IsAvailable() override;
    void Assign(Patient* p) override;
    Patient* Release() override;
};
