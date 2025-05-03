#include "X_room.h"

X_room::X_room(int id, int capacity) : Resource(id), Capacity(capacity), CurrentOccupancy(0) {}

bool X_room::IsAvailable() {
	/*if (CurrentOccupancy < Capacity)
	{
		return true;
	}*/
	if (GetAvalibleDummbells() == nullptr)
	{
		return false;
	}
	else if (GetAvalibleFoamRollers() == nullptr)
	{
		return false;
	}
	else if (GetAvalibleTreadmills() == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void X_room::Assign(Patient* p) {
    if (IsAvailable()) {
        roomQueue.enqueue(p, p->getarrivalTime() + p->getXtt());
        CurrentOccupancy++;
    }
}
//
Patient* X_room::Release() {
    Patient* releasedPatient = nullptr;
    int priority;
    if (roomQueue.dequeue(releasedPatient, priority)) {
        CurrentOccupancy--;
    }
    return releasedPatient;
}

int X_room::GetCapacity() {
    return Capacity;
}

int X_room::GetCurrentOccupancy() {
    return CurrentOccupancy;
}

void X_room::print()
{
    cout<<"R" << ID << "[" << CurrentOccupancy <<"," << Capacity << "]"; 
}

void X_room::AddDumbbell(Dumbbell* dumbbell)
{
    Dumbbells.enqueue(dumbbell);
}

void X_room::AddTreadmill(Treadmill* treadmill)
{
	Treadmills.enqueue(treadmill);
}

void X_room::AddFoamRoller(FoamRoller* foamRoller)
{
	FoamRollers.enqueue(foamRoller);
}

//void X_room::ReleaseDumbbell(Dumbbell* dumbbell)
//{
//	if (dumbbell != nullptr) 
//	{
//		dumbbell->Release();
//	}
//}
//
//void X_room::ReleaseTreadmill(Treadmill* treadmill)
//{
//	if (treadmill != nullptr)
//	{
//		treadmill->Release();
//	}
//}
//
//void X_room::ReleaseFoamRoller(FoamRoller* foamRoller)
//{
//	if (foamRoller != nullptr)
//	{
//		foamRoller->Release();
//	}
//}

Dumbbell* X_room::GetAvalibleDummbells()
{
	LinkedQueue<Dumbbell*> tempQueue;
	Dumbbell* dumbbell = nullptr;
    while (!Dumbbells.isEmpty())
    {
        Dumbbells.dequeue(dumbbell);
        tempQueue.enqueue(dumbbell);
        if (dumbbell->IsAvailable())
        {
            while (!tempQueue.isEmpty())
            {
                Dumbbell* tempDumbbell;
                tempQueue.dequeue(tempDumbbell);
                Dumbbells.enqueue(tempDumbbell);
            }
            return dumbbell;
        }
    }
	while (!tempQueue.isEmpty())
	{
		Dumbbell* tempDumbbell;
		tempQueue.dequeue(tempDumbbell);
		Dumbbells.enqueue(tempDumbbell);
	}
	return nullptr;

}

Treadmill* X_room::GetAvalibleTreadmills()
{
	LinkedQueue<Treadmill*> tempQueue;
	Treadmill* treadmill = nullptr;
	while (!Treadmills.isEmpty())
	{
		Treadmills.dequeue(treadmill);
		tempQueue.enqueue(treadmill);
		if (treadmill->IsAvailable())
		{
			while (!tempQueue.isEmpty())
			{
				Treadmill* tempTreadmill;
				tempQueue.dequeue(tempTreadmill);
				Treadmills.enqueue(tempTreadmill);
			}
			return treadmill;
		}
	}
	while (!tempQueue.isEmpty())
	{
		Treadmill* tempTreadmill;
		tempQueue.dequeue(tempTreadmill);
		Treadmills.enqueue(tempTreadmill);
	}
	return nullptr;
}

FoamRoller* X_room::GetAvalibleFoamRollers()
{
	LinkedQueue<FoamRoller*> tempQueue;
	FoamRoller* foamRoller = nullptr;
	while (!FoamRollers.isEmpty())
	{
		FoamRollers.dequeue(foamRoller);
		tempQueue.enqueue(foamRoller);
		if (foamRoller->IsAvailable())
		{
			while (!tempQueue.isEmpty())
			{
				FoamRoller* tempFoamRoller;
				tempQueue.dequeue(tempFoamRoller);
				FoamRollers.enqueue(tempFoamRoller);
			}
			return foamRoller;
		}
	}
	while (!tempQueue.isEmpty())
	{
		FoamRoller* tempFoamRoller;
		tempQueue.dequeue(tempFoamRoller);
		FoamRollers.enqueue(tempFoamRoller);
	}
	return nullptr;
}

int X_room::GetDumNum()
{
	return Dumbbells.getSize();
}

int X_room::GetTreadNum()
{
	return Treadmills.getSize();
}

int X_room::GetFoamNum()
{
	return FoamRollers.getSize();
}

