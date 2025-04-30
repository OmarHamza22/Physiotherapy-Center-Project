#include "Center.h"
#include "UI.h"

Center::Center() {}

Center::~Center() {
	E_device* e;
	while (E_Devices.dequeue(e)) delete e;

	U_device* u;
	while (U_Devices.dequeue(u)) delete u;

	X_room* r;
	while (X_Rooms.dequeue(r)) delete r;
}

bool Center::LoadALL(string Filename)
{
	string filename = Filename + ".txt";

	std::ifstream INfile(filename, ios::in);
	if (!INfile) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return false;
	}

	int Pt, Vt, XT, ET, UT, NumU, NumX, NumE, NumP, Numteratments;
	char pType, tType;
	int presc, pcancel;
	//E_device* Edev;
	//U_device* Udev;
	//X_room* Xroom;

	Patient* newP;
	U_therapy* Uther;
	E_therapy* Ether;
	X_therapy* Xther;


	INfile >> NumE >> NumU >> NumX;
	for (int i = 1; i <= NumE; i++)
	{
		AddEDevice(i);
	}

	for (int i = 1; i <= NumU; i++)
	{
		AddUDevice(i);
	}

	for (int i = 1; i <= NumX; i++)
	{
		int capacityX;
		INfile >> capacityX;
		X_room* newXRoom = new X_room(i, capacityX);
		AddXRoom(newXRoom);
	}

	INfile >> pcancel >> presc;
	Pcancel = pcancel;
	Presc = presc;
	INfile >> NumP;

	for (int i = 1; i <= NumP; i++)
	{
		INfile >> pType;
		INfile >> Pt >> Vt;
		newP = new Patient(i, Pt, Vt, pType);

		INfile >> Numteratments;
		if (Numteratments > 3 || Numteratments < 0)
		{
			return false;
		}

		for (int i = 1; i <= Numteratments; i++)
		{
			INfile >> tType;
			if (tType == 'E')
			{
				INfile >> ET;
				newP->setEtt(ET);
				//Ether = new E_therapy(1, ET, -1);
				newP->addTreatment(eTherapy);
			}
			else if (tType == 'U')
			{
				INfile >> UT;
				newP->setUtt(UT);
				//Uther = new U_therapy(1, UT, -1);
				newP->addTreatment(uTherapy);
			}
			else if (tType == 'X')
			{
				INfile >> XT;
				newP->setXtt(XT);
				//Xther = new X_therapy(1, XT, -1);
				newP->addTreatment(xTherapy);
			}

		}

		AllPatient.enqueue(newP);

	}
	return true;
}

void Center::IncTime()
{
	TimeStep++;
}

int Center::getTime()
{
	return TimeStep;
}


void Center::AddEDevice(int id) {
	E_Devices.enqueue(new E_device(id));
}

void Center::AddUDevice(int id) {
	U_Devices.enqueue(new U_device(id));
}

void Center::AddXRoom(X_room* room)
{
	X_Rooms.enqueue(room);
}



E_device* Center::GetAvailableEDevice() 
{
	LinkedQueue<E_device*> tempQueue;
	E_device* device = nullptr;
	while (!E_Devices.isEmpty()) 
	{
		E_Devices.dequeue(device);
		tempQueue.enqueue(device);
		if (device->IsAvailable()) 
		{
			while (!tempQueue.isEmpty()) 
			{
				E_device* tempDevice;
				tempQueue.dequeue(tempDevice);
				E_Devices.enqueue(tempDevice);
			}
			return device;
		}
	}
	while (!tempQueue.isEmpty()) 
	{
		E_device* tempDevice;
		tempQueue.dequeue(tempDevice);
		E_Devices.enqueue(tempDevice);
	}
	return nullptr;
}

U_device* Center::GetAvailableUDevice() 
{
	LinkedQueue<U_device*> tempQueue;
	U_device* device = nullptr;
	while (!U_Devices.isEmpty()) 
	{
		U_Devices.dequeue(device);
		tempQueue.enqueue(device);
		if (device->IsAvailable()) 
		{
			while (!tempQueue.isEmpty()) 
			{
				U_device* tempDevice;
				tempQueue.dequeue(tempDevice);
				U_Devices.enqueue(tempDevice);
			}
			return device;
		}
	}
	while (!tempQueue.isEmpty()) 
	{
		U_device* tempDevice;
		tempQueue.dequeue(tempDevice);
		U_Devices.enqueue(tempDevice);
	}
	return nullptr;
}

X_room* Center::GetAvailableXRoom() 
{
	LinkedQueue<X_room*> tempQueue;
	X_room* room = nullptr;

	while (!X_Rooms.isEmpty()) 
	{
		X_Rooms.dequeue(room);
		tempQueue.enqueue(room);
		if (room->IsAvailable()) 
		{
			while (!tempQueue.isEmpty()) 
			{
				X_room* tempRoom;
				tempQueue.dequeue(tempRoom);
				X_Rooms.enqueue(tempRoom);
			}
			return room;
		}
	}
	while (!tempQueue.isEmpty())
	{
		X_room* tempRoom;
		tempQueue.dequeue(tempRoom);
		X_Rooms.enqueue(tempRoom);
	}
	return nullptr;
}

Dumbbell* Center::GetAvailableDumbbels()
{
	LinkedQueue<X_room*> tempQueue;
	X_room* room = nullptr;
	while (!X_Rooms.isEmpty())
	{
		X_Rooms.dequeue(room);
		tempQueue.enqueue(room);
		Dumbbell* dumbbell = room->GetAvalibleDummbells();
		if (dumbbell != nullptr)
		{
			while (!tempQueue.isEmpty())
			{
				X_room* tempRoom;
				tempQueue.dequeue(tempRoom);
				X_Rooms.enqueue(tempRoom);
			}
			return dumbbell;
		}
	}
	while (!tempQueue.isEmpty())
	{
		X_room* tempRoom;
		tempQueue.dequeue(tempRoom);
		X_Rooms.enqueue(tempRoom);
	}
	return nullptr;

}

FoamRoller* Center::GetAvailableFoamRollers()
{
	LinkedQueue<X_room*> tempQueue;
	X_room* room = nullptr;
	while (!X_Rooms.isEmpty())
	{
		X_Rooms.dequeue(room);
		tempQueue.enqueue(room);
		FoamRoller* foamRoller = room->GetAvalibleFoamRollers();
		if (foamRoller != nullptr)
		{
			while (!tempQueue.isEmpty())
			{
				X_room* tempRoom;
				tempQueue.dequeue(tempRoom);
				X_Rooms.enqueue(tempRoom);
			}
			return foamRoller;
		}
	}
	while (!tempQueue.isEmpty())
	{
		X_room* tempRoom;
		tempQueue.dequeue(tempRoom);
		X_Rooms.enqueue(tempRoom);
	}
	return nullptr;
}

Treadmill* Center::GetAvailableTreadmills()
{
	LinkedQueue<X_room*> tempQueue;
	X_room* room = nullptr;
	while (!X_Rooms.isEmpty())
	{
		X_Rooms.dequeue(room);
		tempQueue.enqueue(room);
		Treadmill* treadmill = room->GetAvalibleTreadmills();
		if (treadmill != nullptr)
		{
			while (!tempQueue.isEmpty())
			{
				X_room* tempRoom;
				tempQueue.dequeue(tempRoom);
				X_Rooms.enqueue(tempRoom);
			}
			return treadmill;
		}
	}
	while (!tempQueue.isEmpty())
	{
		X_room* tempRoom;
		tempQueue.dequeue(tempRoom);
		X_Rooms.enqueue(tempRoom);
	}
	return nullptr;
}

void Center::AddToEWait(Patient* newPatient) {
	eWaitList.insertSort(newPatient);
}

void Center::AddToUWait(Patient* newPatient) {
	uWaitList.insertSort(newPatient);
}

void Center::AddToXWait(Patient* newPatient) {
	xWaitList.insertSort(newPatient);
}

void Center::AddToDumbbellWait(Patient* newPatient)
{
	DumbbellsList.insertSort(newPatient);
}

void Center::AddToFoamRollerWait(Patient* newPatient)
{
	FoamRollersList.insertSort(newPatient);
}

void Center::AddToTreadmillWait(Patient* newPatient)
{

	TreadmillsList.insertSort(newPatient);
}

void Center::AddPatients(Patient* newpatient)
{
	AllPatient.enqueue(newpatient);
}

void Center::ComeEarly(Patient* newpatient)
{
	Early.enqueue(newpatient, -(newpatient->getappointmentTime()));
}

void Center::ComeLate(Patient* newpatient)
{
	int pri, vt, pt;

	vt = newpatient->getarrivalTime();
	pt = newpatient->getappointmentTime();

	if (vt > pt)
	{
		pri = -(vt + 0.5 * (vt - pt));
		Late.enqueue(newpatient, pri);
		newpatient->setappointmentTime(-pri);
	}

	if (vt < pt)
	{
		pri = -(vt + 0.5 * (vt + 24 - pt));
		Late.enqueue(newpatient, pri);
		newpatient->setappointmentTime(-pri);
	}

}

void Center::AddToTreatmentList(Patient* newPatient)
{
	int pri;

	pri = -(newPatient->getfinishTime());
	InTreatment.enqueue(newPatient, pri);
}

int Center::CheckEarlyPatientTime()
{
	Patient* p;
	int pp;
	Early.peek(p, pp);

	return p->getappointmentTime();
}

int Center::CheckLatePatientTime()
{
	Patient* p;
	int pp;
	Late.peek(p, pp);

	return p->getappointmentTime();
}

Patient* Center::FinishedTreatment()
{
	Patient* p;
	int pp;
	InTreatment.dequeue(p, pp);
	return p;
}

Patient* Center::getNextEarlyPatient()
{
	Patient* p;
	int pp;
	Late.dequeue(p, pp);

	return p;
}

Patient* Center::getNextLatePatient()
{
	Patient* p;
	int pp;
	Late.dequeue(p, pp);

	return p;
}

bool Center::PatientListIsEmpty()
{
	return AllPatient.isEmpty();
}

bool Center::EarlyListIsEmpty()
{
	return Early.isEmpty();
}

bool Center::LateListIsEmpty()
{
	return Late.isEmpty();
}



void Center::addToFinishedPatientslist(Patient* patient)
{
	if (patient && !patient->hasTreatmentsLeft()) {
		finishedPatients.push(patient);
	}
}

Patient* Center::getFinishedPatient()
{
	if (finishedPatients.isEmpty())
		return nullptr;

	Patient* finished = nullptr;
	finishedPatients.pop(finished);
	return finished;
}

bool Center::removeFinishedPatient(Patient* patient)
{
	ArrayStack<Patient*> tempStack;
	Patient* topPatient = nullptr;
	bool found = false;

	while (!finishedPatients.isEmpty()) {
		finishedPatients.pop(topPatient);
		if (topPatient == patient) {
			found = true;
			break; // Do not push this one back
		}
		tempStack.push(topPatient);
	}

	// Restore the other patients
	Patient* tempTop = nullptr;
	while (!tempStack.isEmpty()) {
		tempStack.pop(tempTop);
		finishedPatients.push(tempTop);
	}

	return found;
}

void Center::printFinishedPatient() const
{
	if (finishedPatients.isEmpty()) {
		cout << "No finished patients available." << endl;
		return;
	}

	// Create a copy of the stack (manually)
	ArrayStack<Patient*> tempStack = finishedPatients;
	Patient* topPatient = nullptr;

	cout << "Finished Patients List:\n";
	while (!tempStack.isEmpty()) {
		tempStack.pop(topPatient);
		cout << "Patient ID: " << topPatient->getID()
			<< ", Finish Time: " << topPatient->getfinishTime() << endl;
	}
}

void Center::clearFinishedPatients()
{
	Patient* p = nullptr;
	while (!finishedPatients.isEmpty()) {
		finishedPatients.pop(p);
		delete p;
	}
}


void Center::Simulate()
{
	string you = "Omar";
	LoadALL(you);
	while (!AllPatient.isEmpty())
	{
		Patient* P;
		AllPatient.peek(P);
		if (P->getarrivalTime() == TimeStep)
		{
			AllPatient.dequeue(P);

			if (P->getStatus() == "ERLY")
			{
				Early.enqueue(P, -(P->getappointmentTime()));
			}
			else if (P->getStatus() == "Late")
			{
				Late.enqueue(P, -(P->getsortValue()));
			}
			else if (P->getappointmentTime() == P->getarrivalTime())
			{
				RandomWaiting(P);
				// Step 5: Print current simulation state
			/*	cout << "Press Enter to continue...";
				cin.ignore();
				cin.get();*/

				UI::PrintTimes(TimeStep);
				UI::PrintAllList(AllPatient);
				UI::PrintEarlyList(Early);
				UI::PrintLateList(Late);
				UI::PrintWaitingLists(eWaitList, uWaitList, xWaitList);
				UI::PrintAvailableDevices(E_Devices, U_Devices);
				UI::PrintAvailableRooms(X_Rooms);
				UI::PrintInTreatmentList(InTreatment);
				UI::PrintFinishedPatients(finishedPatients);
				IncTime();

				continue;
			}
		}
		IncTime();

	}	//*//





	while (!Early.isEmpty() || !Late.isEmpty() || !InTreatment.isEmpty() || !eWaitList.isEmpty() || !uWaitList.isEmpty() || !xWaitList.isEmpty())
	{

		Patient* P;
		int pri;
		int X = rand() % 101;
		int N = rand() % 101;

		if (X < 10) {
			if (!(Early.isEmpty()))

			{
				Early.dequeue(P, pri);
				if (N < 33)
					eTherapy->MovetoWait(P);
				else if (N < 66)
					uTherapy->MovetoWait(P);
				else
					xTherapy->MovetoWait(P);
			}
		}
		else if (10 <= X && X < 20)
		{
			if (!(Late.isEmpty()))
			{
				Late.dequeue(P, pri);
				if (N < 33)
					eTherapy->MovetoWait(P);
				else if (N < 66)
					uTherapy->MovetoWait(P);
				else
					xTherapy->MovetoWait(P);
			}
		}
		else if (20 <= X && X < 40)
		{
			for (int i = 0; i < 2; i++)
			{
				if (N < 33)
				{
					if (!(eWaitList.isEmpty()))
					{
						eWaitList.dequeue(P);
						InTreatment.enqueue(P, P->gettreatmentTime());
					}
				}
				else if (N < 66)
				{
					if (!(uWaitList.isEmpty()))
					{
						uWaitList.dequeue(P);
						InTreatment.enqueue(P, P->gettreatmentTime());
					}
				}
				else
				{
					if (!(xWaitList.isEmpty()))
					{
						xWaitList.dequeue(P);
						InTreatment.enqueue(P, P->gettreatmentTime());
					}
				}
			}
		}
		else if (40 <= X && X < 50)
		{
			if (!(InTreatment.isEmpty()))

			{
				InTreatment.dequeue(P, pri);
				if (N < 33)
					eTherapy->MovetoWait(P);
				else if (N < 66)
					uTherapy->MovetoWait(P);
				else
					xTherapy->MovetoWait(P);
			}
		}
		else if (50 <= X && X < 60)
		{
			if (!(InTreatment.isEmpty()))
			{
				InTreatment.dequeue(P, pri);
				finishedPatients.push(P);
			}
		}
		else if (60 <= X && X < 70)
		{
			if (!(xWaitList.isEmpty()))
			{
				xWaitList.randCancelAppointment(Pcancel, finishedPatients);
			}

		}
		else if (70 <= X && X < 80)
		{
			if (!Early.isEmpty())
			{
				Early.randReschedule(Presc);
			}
		}
		// Step 5: Print current simulation state
		/*cout << "Press Enter to continue...";
		cin.ignore();
		cin.get();*/
		UI::PrintTimes(TimeStep);
		UI::PrintAllList(AllPatient);
		UI::PrintEarlyList(Early);
		UI::PrintLateList(Late);
		UI::PrintWaitingLists(eWaitList, uWaitList, xWaitList);
		UI::PrintAvailableDevices(E_Devices, U_Devices);
		UI::PrintAvailableRooms(X_Rooms);
		UI::PrintInTreatmentList(InTreatment);
		UI::PrintFinishedPatients(finishedPatients);
		IncTime();

	}


}


void Center::RandomWaiting(Patient* patient) {
	// Initialize random seed if not already done
	static bool initialized = false;
	if (!initialized) {
		srand(time(0));
		initialized = true;
	}

	// Generate random number between 0-100
	int randomNum = rand() % 101;

	if (randomNum < 33) {
		// Send to E-Waiting (0-32)
		eTherapy->MovetoWait(patient);
	}
	else if (randomNum < 66) {
		// Send to U-Waiting (33-65)
		uTherapy->MovetoWait(patient);
	}
	else {
		// Send to X-Waiting (66-100)
		xTherapy->MovetoWait(patient);
	}
}

E_device* Center::GetAvailable_E()
{
	int NumE = E_Devices.getSize();
	E_device* AvailableDev_E = nullptr;
	for (int i = 0; i < NumE; i++)
	{
		E_Devices.dequeue(AvailableDev_E);
		E_Devices.enqueue(AvailableDev_E);
		if (AvailableDev_E->IsAvailable())
		{
			return AvailableDev_E;
		}
	}
	return nullptr;
}

U_device* Center::GetAvailable_U()
{
	int NumU = U_Devices.getSize();
	U_device* AvailableDev_U = nullptr;
	for (int i = 0; i < NumU; i++)
	{
		U_Devices.dequeue(AvailableDev_U);
		U_Devices.enqueue(AvailableDev_U);
		if (AvailableDev_U->IsAvailable())
		{
			return AvailableDev_U;
		}
	}
	return nullptr;
}

X_room* Center::GetAvailable_X()
{
	int NumX = X_Rooms.getSize();
	X_room* AvailableDev_X = nullptr;
	for (int i = 0; i < NumX; i++)
	{
		X_Rooms.dequeue(AvailableDev_X);
		X_Rooms.enqueue(AvailableDev_X);
		if (AvailableDev_X->IsAvailable())
		{
			return AvailableDev_X;
		}
	}
	return nullptr;
}

void Center::From_INtreatment()
{
	Patient* dequeuedPatient = nullptr;
	int priority = 0;

	if (InTreatment.peek(dequeuedPatient, priority) && dequeuedPatient != nullptr) 
	{
		// Check if the current TimeStep matches the patient's finish time
		//if (TimeStep < -priority) 
		//{
		//	// The patient is not yet finished with their treatment
		//	return;
		//}

		InTreatment.dequeue(dequeuedPatient, priority);

		Resource* assignedResource = dequeuedPatient->getAssignedResource();
		if (assignedResource != nullptr) 
		{
			ReleaseResource(assignedResource); // Release the resource
		}

		if (dequeuedPatient->hasTreatmentsLeft()) 
		{
			LinkedQueue<Treatment*> treatments = dequeuedPatient->getRequiredTreatments();
			Treatment* nextTreatment = nullptr;
			treatments.dequeue(nextTreatment);

			if (nextTreatment != nullptr) {
				if (nextTreatment->GetTreType() == "E_therapy") 
				{
					AddToEWait(dequeuedPatient);
					dequeuedPatient->setStatus("EWaiting");
				}
				else if (nextTreatment->GetTreType() == "U_therapy") 
				{
					AddToUWait(dequeuedPatient);
					dequeuedPatient->setStatus("UWaiting");
				}
				else if (nextTreatment->GetTreType() == "X_therapy") 
				{
					// Handle tools for X-Therapy
					Resource* requiredTool = nullptr;
					LinkedQueue<Resource*> tools = dequeuedPatient->getRequiredTools();
					tools.dequeue(requiredTool);

					if (requiredTool != nullptr) 
					{
						if (dynamic_cast<Dumbbell*>(requiredTool)) 
						{
							AddToDumbbellWait(dequeuedPatient);
							dequeuedPatient->setStatus("DumbbellWaiting");
						}
						else if (dynamic_cast<FoamRoller*>(requiredTool)) 
						{
							AddToFoamRollerWait(dequeuedPatient);
							dequeuedPatient->setStatus("FoamRollerWaiting");
						}
						else if (dynamic_cast<Treadmill*>(requiredTool)) 
						{
							AddToTreadmillWait(dequeuedPatient);
							dequeuedPatient->setStatus("TreadmillWaiting");
						}
					}
				}
			}
		}
		else 
		{
			finishedPatients.push(dequeuedPatient);
			dequeuedPatient->setfinishTime(TimeStep); // Set the finish time to the current TimeStep
			dequeuedPatient->setStatus("Finished");
		}
	}
}


void Center::Assign_E()
{
	if (!eWaitList.isEmpty())
	{
		Patient* patient = nullptr;
		eWaitList.dequeue(patient);
		E_device* Available_E = GetAvailableEDevice();

		if (Available_E != nullptr)
		{
			Available_E->Assign(patient);
			patient->setAssignedResource(Available_E);
			InTreatment.enqueue(patient, -(TimeStep + patient->getEtt()));//check with mandoooooooooo
			patient->setStatus("InTreatment");
		}
		else
		{
			eWaitList.insertSort(patient);
			patient->setStatus("EWaiting");
		}
	}
}

void Center::Assign_U()
{
	if (!uWaitList.isEmpty())
	{
		Patient* patient = nullptr;
		uWaitList.dequeue(patient);

		U_device* Available_U = GetAvailableUDevice();

		if (Available_U != nullptr)
		{
			Available_U->Assign(patient);//avalibalty will be set automatic 
			patient->setAssignedResource(Available_U);
			InTreatment.enqueue(patient, -(TimeStep + patient->getUtt()));//check with mandoooooooooo
			patient->setStatus("InTreatment");
		}
		else
		{
			uWaitList.insertSort(patient);
			patient->setStatus("UWaiting");
		}
	}
}

void Center::Assign_X()
{

	if (!xWaitList.isEmpty())
	{
		Patient* patient = nullptr;
		xWaitList.dequeue(patient);

		X_room* Available_X = GetAvailableXRoom();

		if (Available_X != nullptr)
		{
			Available_X->Assign(patient);//avalibalty will be set automatic 
			patient->setAssignedResource(Available_X);
			InTreatment.enqueue(patient, -(TimeStep + patient->getXtt()));//check with mandoooooooooo
			patient->setStatus("InTreatment");
		}
		else
		{
			xWaitList.insertSort(patient);
			patient->setStatus("XWaiting");
		}
	}
}

void Center::Assign_Dumbbell()
{
	if (!DumbbellsList.isEmpty())
	{
		Patient* patient = nullptr;
		DumbbellsList.dequeue(patient);
		Dumbbell* Available_Dumbbell = GetAvailableDumbbels();
		if (Available_Dumbbell != nullptr)
		{
			Available_Dumbbell->Assign(patient);
			patient->setAssignedResource(Available_Dumbbell);
			InTreatment.enqueue(patient, -(TimeStep + patient->getDummbellTime()));//check with mandoooooooooo
			patient->setStatus("InTreatment");
		}
		else
		{
			DumbbellsList.insertSort(patient);
			patient->setStatus("DumbbellWaiting");
		}

	}
}

void Center::Assign_FoamRoller()
{
	if (!FoamRollersList.isEmpty())
	{
		Patient* patient = nullptr;
		FoamRollersList.dequeue(patient);
		FoamRoller* Available_FoamRoller = GetAvailableFoamRollers();
		if (Available_FoamRoller != nullptr)
		{
			Available_FoamRoller->Assign(patient);
			patient->setAssignedResource(Available_FoamRoller);
			InTreatment.enqueue(patient, -(TimeStep + patient->getFoamRollerTime()));//check with mandoooooooooo
			patient->setStatus("InTreatment");
		}
		else
		{
			FoamRollersList.insertSort(patient);
			patient->setStatus("FoamRollerWaiting");
		}
	}
}

void Center::Assign_Treadmill()
{
	if (!TreadmillsList.isEmpty())
	{
		Patient* patient = nullptr;
		TreadmillsList.dequeue(patient);
		Treadmill* Available_Treadmill = GetAvailableTreadmills();
		if (Available_Treadmill != nullptr)
		{
			Available_Treadmill->Assign(patient);
			patient->setAssignedResource(Available_Treadmill);
			InTreatment.enqueue(patient, -(TimeStep + patient->getTreadmillTime()));//check with mandoooooooooo
			patient->setStatus("InTreatment");
		}
		else
		{
			TreadmillsList.insertSort(patient);
			patient->setStatus("TreadmillWaiting");
		}
	}
}

//void Center::Release_E(E_device* device)
//{
//	if (device != nullptr)
//	{
//		Patient* patient = device->Release();
//		if (patient != nullptr)
//		{
//			//FromINtreatmentToWait or Finshsh Function
//		}
//	}
//}
//
//void Center::Release_U(U_device* device)
//{
//	if (device != nullptr)
//	{
//		Patient* patient = device->Release();
//		if (patient != nullptr)
//		{
//			//FromINtreatmentToWait or Finshsh Function
//		}
//	}
//}
//
//void Center::ReleaseDumbbell(Dumbbell* dumbbell)
//{
//	if (dumbbell != nullptr)
//	{
//		Patient* patient = dumbbell->Release();
//		if (patient != nullptr)
//		{
//			//FromINtreatmentToWait or Finshsh Function
//		}
//	}
//}
//
//void Center::ReleaseFoamRoller(FoamRoller* foamRoller)
//{
//	if (foamRoller != nullptr)
//	{
//		Patient* patient = foamRoller->Release();
//		if (patient != nullptr)
//		{
//			//FromINtreatmentToWait or Finshsh Function
//		}
//	}
//}
//
//void Center::ReleaseTreadmill(Treadmill* treadmill)
//{
//	if (treadmill != nullptr)
//	{
//		Patient* patient = treadmill->Release();
//		if (patient != nullptr)
//		{
//			//FromINtreatmentToWait or Finshsh Function
//		}
//	}
//}



void Center::ReleaseResource(Resource* resource) 
{
	if (resource == nullptr) 
	{
		return;
	}

	Patient* releasedPatient = resource->Release();

	if (releasedPatient != nullptr) 
	{
		releasedPatient->setAssignedResource(nullptr);


	}
}


void Center::printDeviceAndRoomLists()
{
		// Print all E devices
		std::cout << "Available E Devices: " << std::endl;
		E_device* eDevice;
		int sizeE = E_Devices.getSize();  // Assuming a method to get the size of the queue
		for (int i = 0; i < sizeE; i++) {
			E_Devices.dequeue(eDevice);  // Dequeue and then enqueue again to maintain order
			E_Devices.enqueue(eDevice);
			std::cout << "E Device ID: " << eDevice->GetID() << ", Available: "
				<< (eDevice->IsAvailable() ? "Yes" : "No") << std::endl;
		}

		// Print all U devices
		std::cout << "Available U Devices: " << std::endl;
		U_device* uDevice;
		int sizeU = U_Devices.getSize();  // Assuming a method to get the size of the queue
		for (int i = 0; i < sizeU; i++) {
			U_Devices.dequeue(uDevice);  // Dequeue and then enqueue again to maintain order
			U_Devices.enqueue(uDevice);
			std::cout << "U Device ID: " << uDevice->GetID() << ", Available: "
				<< (uDevice->IsAvailable() ? "Yes" : "No") << std::endl;
		}

		// Print all X rooms
		std::cout << "Available X Rooms: " << std::endl;
		X_room* xRoom;
		int sizeX = X_Rooms.getSize();  // Assuming a method to get the size of the queue
		for (int i = 0; i < sizeX; i++) {
			X_Rooms.dequeue(xRoom);  // Dequeue and then enqueue again to maintain order
			X_Rooms.enqueue(xRoom);
			std::cout << "X Room ID: " << xRoom->GetID() << ", Available: "
				<< (xRoom->IsAvailable() ? "Yes" : "No") << std::endl;
		}
		// Print all Dumbbells
		std::cout << "Available Dumbbells: " << std::endl;
		Dumbbell* dumbbell;
		int sizeD = X_Rooms.getSize();  // Assuming a method to get the size of the queue	
		for (int i = 0; i < sizeD; i++) {
			X_Rooms.dequeue(xRoom);  // Dequeue and then enqueue again to maintain order
			X_Rooms.enqueue(xRoom);
			dumbbell = xRoom->GetAvalibleDummbells();
			if (dumbbell != nullptr) {
				std::cout << "Dumbbell ID: " << dumbbell->GetID() << ", Available: "
					<< (dumbbell->IsAvailable() ? "Yes" : "No") << std::endl;
			}
		}
		// Print all Treadmills	
		std::cout << "Available Treadmills: " << std::endl;
		Treadmill* treadmill;
		int sizeT = X_Rooms.getSize();  // Assuming a method to get the size of the queue
		for (int i = 0; i < sizeT; i++) {
			X_Rooms.dequeue(xRoom);  // Dequeue and then enqueue again to maintain order
			X_Rooms.enqueue(xRoom);
			treadmill = xRoom->GetAvalibleTreadmills();
			if (treadmill != nullptr) {
				std::cout << "Treadmill ID: " << treadmill->GetID() << ", Available: "
					<< (treadmill->IsAvailable() ? "Yes" : "No") << std::endl;
			}
		}
		// Print all FoamRollers
		std::cout << "Available FoamRollers: " << std::endl;
		FoamRoller* foamRoller;
		int sizeF = X_Rooms.getSize();  // Assuming a method to get the size of the queue
		for (int i = 0; i < sizeF; i++) {
			X_Rooms.dequeue(xRoom);  // Dequeue and then enqueue again to maintain order
			X_Rooms.enqueue(xRoom);
			foamRoller = xRoom->GetAvalibleFoamRollers();
			if (foamRoller != nullptr) {
				std::cout << "FoamRoller ID: " << foamRoller->GetID() << ", Available: "
					<< (foamRoller->IsAvailable() ? "Yes" : "No") << std::endl;
			}
		}
}

void Center::printWaitingList()
{
	
		std::cout << "E-Device Wait List:" << std::endl;

		// Printing the E-device waitlist
		int sizeE = eWaitList.getSize();  // Assuming method to get the size of the waitlist
		for (int i = 0; i < sizeE; i++) {
			Patient* ePatient;
			eWaitList.dequeue(ePatient);  // Dequeue the patient temporarily
			eWaitList.enqueue(ePatient);  // Re-enqueue to preserve order

			std::cout << "Patient ID: " << ePatient->getID()
				//<< ", Name: " << ePatient->getName()
				<< ", Status: " << ePatient->getStatus() << std::endl;
		}

		std::cout << "\nU-Device Wait List:" << std::endl;

		// Printing the U-device waitlist
		int sizeU = uWaitList.getSize();  // Assuming method to get the size of the waitlist
		for (int i = 0; i < sizeU; i++) {
			Patient* uPatient;
			uWaitList.dequeue(uPatient);  // Dequeue the patient temporarily
			uWaitList.enqueue(uPatient);  // Re-enqueue to preserve order

			std::cout << "Patient ID: " << uPatient->getID()
				//<< ", Name: " << uPatient->getName()
				<< ", Status: " << uPatient->getStatus() << std::endl;
		}

		std::cout << "\nX-Room Wait List:" << std::endl;

		// Printing the X-room waitlist
		int sizeX = xWaitList.getSize();  // Assuming method to get the size of the waitlist
		for (int i = 0; i < sizeX; i++) {
			Patient* xPatient;
			xWaitList.dequeue(xPatient);  // Dequeue the patient temporarily
			xWaitList.enqueue(xPatient);  // Re-enqueue to preserve order

			std::cout << "Patient ID: " << xPatient->getID()
				//<< ", Name: " << xPatient->getName()
				<< ", Status: " << xPatient->getStatus() << std::endl;
		}
		std::cout << "\nDumbbell Wait List:" << std::endl;
		// Printing the Dumbbell waitlist
		int sizeD = DumbbellsList.getSize();  // Assuming method to get the size of the waitlist
		for (int i = 0; i < sizeD; i++) {
			Patient* dPatient;
			DumbbellsList.dequeue(dPatient);  // Dequeue the patient temporarily
			DumbbellsList.enqueue(dPatient);  // Re-enqueue to preserve order
			std::cout << "Patient ID: " << dPatient->getID()
				//<< ", Name: " << dPatient->getName()
				<< ", Status: " << dPatient->getStatus() << std::endl;
		}
		std::cout << "\nFoamRoller Wait List:" << std::endl;
		// Printing the FoamRoller waitlist
		int sizeF = FoamRollersList.getSize();  // Assuming method to get the size of the waitlist
		for (int i = 0; i < sizeF; i++) {
			Patient* fPatient;
			FoamRollersList.dequeue(fPatient);  // Dequeue the patient temporarily
			FoamRollersList.enqueue(fPatient);  // Re-enqueue to preserve order
			std::cout << "Patient ID: " << fPatient->getID()
				//<< ", Name: " << fPatient->getName()
				<< ", Status: " << fPatient->getStatus() << std::endl;
		}
		std::cout << "\nTreadmill Wait List:" << std::endl;
		// Printing the Treadmill waitlist
		int sizeT = TreadmillsList.getSize();  // Assuming method to get the size of the waitlist
		for (int i = 0; i < sizeT; i++) {
			Patient* tPatient;
			TreadmillsList.dequeue(tPatient);  // Dequeue the patient temporarily
			TreadmillsList.enqueue(tPatient);  // Re-enqueue to preserve order
			std::cout << "Patient ID: " << tPatient->getID()
				//<< ", Name: " << tPatient->getName()
				<< ", Status: " << tPatient->getStatus() << std::endl;
		}
	
}

void Center::fromAllPatientsList(Patient* patient)
{
	AllPatient.dequeue(patient);
	
	if (patient->getarrivalTime()>= TimeStep)
	{
		Early.enqueue(patient,55);/////////////change prio
	}
	else
	Late.enqueue(patient,55);/////////////change prio
}

void Center::toWaitList(Patient* patient)
{
	if (patient->getPatientType()=='N')
	{
		
		Treatment* nextT = patient->getNextTreatment();
		if (!nextT) return;
	
		string type = nextT->GetTreType();
	
		if (type == "E")
			AddToEWait(patient);
		else if (type == "U")
			AddToUWait(patient);
	
		// else if (type == "X1")
		//     AddToXWait1(patient);
		// else if (type == "X2")
		//     AddToXWait2(patient);
		// else    (type == "X3")
		//     AddToXWait3(patient);
	}
	else
	{
		int waitE = eWaitList.CalcTreatmentLatency('E');
		int waitU = eWaitList.CalcTreatmentLatency('U');
		int waitX = eWaitList.CalcTreatmentLatency('X');
		//
		if (waitE <= waitU && waitE <= waitX)
        	AddToEWait(patient);
    	else if (waitU <= waitX)
        	AddToUWait(patient);
    	else
		{
        	//AddToXWait(patient); /////////// 3 cases to be added depending on the device, 
			// revise it with Omar;;;;

		}
		

	}

}
// dummy

