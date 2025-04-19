#include "E_therapy.h"
#include "Center.h"

bool E_therapy::CanAssign(Resource* Rec)
{
	if (Rec && Rec->IsAvailable() ) //Rec == 'E')
	{
        E_device* eDevice = dynamic_cast<E_device*>(Rec);
        if (eDevice) 
        {
            SetResources(eDevice);
            return true;
        }
	}
	else
	{
		return false;
	}
}

bool E_therapy::MovetoWait(Patient* P) {
    if (center != nullptr) {
        center->AddToEWait(P);
        return true;
    }
    return false;
}



