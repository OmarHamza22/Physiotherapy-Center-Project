#pragma once
#include "Resource.h"
#include "priQueue.h"
#include "Patient.h"
#include"Dumbbell.h"
#include"Treadmill.h"
#include"FoamRoller.h"
#include <istream>

class X_room : public Resource {
private:
    int Capacity;
    int CurrentOccupancy;
    priQueue<Patient*> roomQueue;
    LinkedQueue< Dumbbell*> Dumbbells;
    LinkedQueue< Treadmill*> Treadmills;
    LinkedQueue< FoamRoller*> FoamRollers;

public:
    X_room(int id, int capacity);
    bool IsAvailable() override;
    void Assign(Patient* p) override;
    Patient* Release() override;
    int GetCapacity();
    int GetCurrentOccupancy();
    void print()override;
	//TOOLS Mangement
	void AddDumbbell(Dumbbell* dumbbell);
	void AddTreadmill(Treadmill* treadmill);
	void AddFoamRoller(FoamRoller* foamRoller);
	/*void ReleaseDumbbell(Dumbbell* dumbbell);
	void ReleaseTreadmill(Treadmill* treadmill);
	void ReleaseFoamRoller(FoamRoller* foamRoller);*/
    Dumbbell* GetAvalibleDummbells();
	Treadmill* GetAvalibleTreadmills();
	FoamRoller* GetAvalibleFoamRollers();

    int GetDumNum();
    int GetTreadNum();
    int GetFoamNum();
};

