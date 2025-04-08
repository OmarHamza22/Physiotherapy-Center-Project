#include "U_therapy.h"
#include "Center.h"

bool U_therapy::CanAssign(Resource* Rec)
{
	if (Rec && Rec->IsAvailable() )//&& Rec->GetType() == 'U'
	{
		SetResources(Rec);
		return true;
	}
	else
	{
		return false;
	}
}



bool U_therapy::MovetoWait(Patient* P) {
    if (center != nullptr) {
        center->AddToUWait(P);
        return true;
    }
    return false;
}
