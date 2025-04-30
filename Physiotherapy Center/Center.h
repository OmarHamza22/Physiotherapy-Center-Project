#pragma once
#include "E_device.h"
#include "U_device.h"
#include "X_room.h"
#include "LinkedQueue.h"
#include "EU_WaitList.h"
#include "X_WaitList.h"
#include "priQueue.h"
#include "Patient.h"
#include <iostream>
#include <fstream>
#include "Treatment.h"
#include "U_therapy.h"
#include "E_therapy.h"
#include "X_therapy.h"
#include "EarlyPList.h"
#include "ArrayStack.h"
class UI;

class Center
{
private:
	LinkedQueue<E_device*> E_Devices;
	LinkedQueue<U_device*> U_Devices;
	LinkedQueue<X_room*> X_Rooms;

	EU_WaitList eWaitList;
	EU_WaitList uWaitList;
	X_WaitList xWaitList;
	X_WaitList DumbbellsList;
	X_WaitList FoamRollersList;
	X_WaitList TreadmillsList;

	LinkedQueue<Patient*> AllPatient;
	EarlyPList Early;
	priQueue<Patient*> Late;
    priQueue<Patient*> InTreatment;


	ArrayStack<Patient*> finishedPatients;


	E_therapy* eTherapy=new E_therapy(this);
    U_therapy* uTherapy=new U_therapy(this);
    X_therapy* xTherapy=new X_therapy(this);

	int TimeStep;
	int Pcancel;
	int Presc;
public:
	Center();
	~Center();

	bool LoadALL(string filename);
	
	void IncTime();
	int getTime();

	void AddEDevice(int id);
	void AddUDevice(int id);
	//void AddXRoom(int id, int capacity);
	void AddXRoom(X_room* room);//for testingggggg

	E_device* GetAvailableEDevice();
	U_device* GetAvailableUDevice();
	X_room* GetAvailableXRoom();
	Dumbbell* GetAvailableDumbbels();
	FoamRoller* GetAvailableFoamRollers();
	Treadmill* GetAvailableTreadmills();

	void AddToEWait(Patient* newPatient);
	void AddToUWait(Patient* newPatient);
	void AddToXWait(Patient* newPatient);
	void AddToDumbbellWait(Patient* newPatient);
	void AddToFoamRollerWait(Patient* newPatient);
	void AddToTreadmillWait(Patient* newPatient);

	void AddPatients(Patient* newpatient);
	void ComeEarly(Patient* newpatient);
	void ComeLate(Patient* newpatient);
        void AddToTreatmentList(Patient* newPatient);

	int CheckEarlyPatientTime();
	int CheckLatePatientTime();

        Patient* FinishedTreatment();
	Patient* getNextEarlyPatient();
	Patient* getNextLatePatient();

	bool PatientListIsEmpty();
	bool EarlyListIsEmpty();
	bool LateListIsEmpty();

	void Simulate();

	void addToFinishedPatientslist(Patient* patient);
	Patient* getFinishedPatient();
	bool removeFinishedPatient(Patient* patient);
	void printFinishedPatient() const;
	void clearFinishedPatients();

	void RandomWaiting(Patient* patient);
	
	//New 
	E_device* GetAvailable_E();
	U_device* GetAvailable_U();
	X_room* GetAvailable_X();

	void From_INtreatment();

	void Assign_E();
	void Assign_U();
	void Assign_X();
	void Assign_Dumbbell();
	void Assign_FoamRoller();
	void Assign_Treadmill();
	/*void Release_E(E_device* device);
	void Release_U(U_device* device);
	void Release_X(X_room* room);
	void ReleaseDumbbell(Dumbbell* dumbbell);
	void ReleaseFoamRoller(FoamRoller* foamRoller);
	void ReleaseTreadmill(Treadmill* treadmill);*/
	void ReleaseResource(Resource* resource);
	void printDeviceAndRoomLists();
	void printWaitingList();

};
