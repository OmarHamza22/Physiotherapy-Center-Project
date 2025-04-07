#pragma once
#include "E_device.h"
#include "U_device.h"
#include "X_room.h"
#include "LinkedQueue.h"
#include "EU_WaitList.h"
#include "X_WaitList.h"
#include "priQueue.h"
#include "Patient.h"

class Center
{
private:
	LinkedQueue<E_device*> E_Devices;
	LinkedQueue<U_device*> U_Devices;
	LinkedQueue<X_room*> X_Rooms;

	EU_WaitList eWaitList;
	EU_WaitList uWaitList;
	X_WaitList xWaitList;

	LinkedQueue<Patient*> AllPatient;
	priQueue<Patient*> Early;
	priQueue<Patient*> Late;
        priQueue<Patient*> InTreatment;
		stack<Patient*> finishedPatients;

public:
	Center();
	~Center();

	void AddEDevice(int id);
	void AddUDevice(int id);
	void AddXRoom(int id, int capacity);

	E_device* GetAvailableEDevice();
	U_device* GetAvailableUDevice();
	X_room* GetAvailableXRoom();

	void AddToEWait(Patient* newPatient);
	void AddToUWait(Patient* newPatient);
	void AddToXWait(Patient* newPatient);

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

	

	void addToFinishedPatientslist(Patient* patient);
	Patient* getFinishedPatient();
	bool removeFinishedPatient(Patient* patient);
	void printFinishedPatient() const;
	void clearFinishedPatients();
};
