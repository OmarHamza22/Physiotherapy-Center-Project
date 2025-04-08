#include "X_therapy.h"
#include "Center.h"
bool X_therapy::CanAssign(Resource* Rec)
{
	if (Rec && Rec->IsAvailable())//checks for capacity Rec->HasCapacity()  && Rec->GetType() == 'X'
	{
		SetResources(Rec);
		return true;
	}
	else
	{
		return false;
	}
}

bool X_therapy::MovetoWait(Patient* P) {
    if (center != nullptr) {
        center->AddToXWait(P);
        return true;
    }
    return false;
}


