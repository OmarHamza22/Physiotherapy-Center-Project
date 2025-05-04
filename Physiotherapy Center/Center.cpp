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

bool Center::Load(string Filename)
{
	string filename = Filename + ".txt";
	ifstream INfile(filename, ios::in);

	if (!INfile) {
		std::cerr << "Failed to open file: "  << std::endl;
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
	int Tcap, Fcap, Dcap,Ttime,Ftime,Dtime ;

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
	for (int i = 1; i <= NumX; i++)
	{
		X_room* xx;
		string tool;
		INfile >> tool >> Tcap >> tool >> Fcap >> tool >> Dcap;
		
		X_Rooms.dequeue(xx);
		for (int y = 1; y <= Tcap;y++)
		{
			Treadmill* tt=new Treadmill(y);
			
			xx->AddTreadmill(tt);
			
		
			
		}
		for (int y = 1; y <= Fcap; y++)
		{
			FoamRoller* ff=new FoamRoller(y);

			xx->AddFoamRoller(ff);

		}
		for (int y = 1; y <= Dcap; y++)
		{
			Dumbbell* dd=new Dumbbell(y);

			xx->AddDumbbell(dd);

		}
		X_Rooms.enqueue(xx);
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

		bool haveX = false;

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
				haveX = true;
			}

		}
		if (haveX == true)
		{
			string tool;
			INfile >> tool >> Ttime >> tool >> Ftime >> tool >> Dtime;
			newP->setTreadmillTime(Ttime);
			newP->setFoamRollerTime(Ftime);
			newP->setDubmbellTime(Dtime);
			if (Ttime > 0)
			{
				newP->addtool(t);
			}
			if (Ftime > 0)
			{
				newP->addtool(f);
			}
			if (Dtime > 0)
			{
				newP->addtool(d);
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

	if (E_Devices.isEmpty())
	{
		return nullptr;
	}
	E_device* device;
	E_Devices.dequeue(device);
	return device;
}

U_device* Center::GetAvailableUDevice() 
{
	if (U_Devices.isEmpty())
	{
		return nullptr;
	}
	U_device* device;
	U_Devices.dequeue(device);
	return device;
}

X_room* Center::GetAvailableXRoom() 
{
	if (X_Rooms.isEmpty())
	{
		return nullptr;
	}
	X_room* device;
	X_Rooms.dequeue(device);
	return device;
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
	Early.dequeue(p, pp);

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


//void Center::Simulate()
//{
//	string you = "Omar";
//	Load(you);
//	while (!AllPatient.isEmpty())
//	{
//		Patient* P;
//		AllPatient.peek(P);
//		if (P->getarrivalTime() == TimeStep)
//		{
//			AllPatient.dequeue(P);
//
//			if (P->getStatus() == "ERLY")
//			{
//				Early.enqueue(P, -(P->getappointmentTime()));
//			}
//			else if (P->getStatus() == "Late")
//			{
//				Late.enqueue(P, -(P->getsortValue()));
//			}
//			else if (P->getappointmentTime() == P->getarrivalTime())
//			{
//				RandomWaiting(P);
//				// Step 5: Print current simulation state
//			/*	cout << "Press Enter to continue...";
//				cin.ignore();
//				cin.get();*/
//
//				UI::PrintTimes(TimeStep);
//				UI::PrintAllList(AllPatient);
//				UI::PrintEarlyList(Early);
//				UI::PrintLateList(Late);
//				UI::PrintWaitingLists(eWaitList, uWaitList, xWaitList);
//				UI::PrintAvailableDevices(E_Devices, U_Devices);
//				UI::PrintAvailableRooms(X_Rooms);
//				UI::PrintInTreatmentList(InTreatment);
//				UI::PrintFinishedPatients(finishedPatients);
//				IncTime();
//
//				continue;
//			}
//		}
//		IncTime();
//
//	}	//*//
//
//
//
//
//
//	while (!Early.isEmpty() || !Late.isEmpty() || !InTreatment.isEmpty() || !eWaitList.isEmpty() || !uWaitList.isEmpty() || !xWaitList.isEmpty())
//	{
//
//		Patient* P;
//		int pri;
//		int X = rand() % 101;
//		int N = rand() % 101;
//
//		if (X < 10) {
//			if (!(Early.isEmpty()))
//
//			{
//				Early.dequeue(P, pri);
//				if (N < 33)
//					eTherapy->MovetoWait(P);
//				else if (N < 66)
//					uTherapy->MovetoWait(P);
//				else
//					xTherapy->MovetoWait(P);
//			}
//		}
//		else if (10 <= X && X < 20)
//		{
//			if (!(Late.isEmpty()))
//			{
//				Late.dequeue(P, pri);
//				if (N < 33)
//					eTherapy->MovetoWait(P);
//				else if (N < 66)
//					uTherapy->MovetoWait(P);
//				else
//					xTherapy->MovetoWait(P);
//			}
//		}
//		else if (20 <= X && X < 40)
//		{
//			for (int i = 0; i < 2; i++)
//			{
//				if (N < 33)
//				{
//					if (!(eWaitList.isEmpty()))
//					{
//						eWaitList.dequeue(P);
//						InTreatment.enqueue(P, P->gettreatmentTime());
//					}
//				}
//				else if (N < 66)
//				{
//					if (!(uWaitList.isEmpty()))
//					{
//						uWaitList.dequeue(P);
//						InTreatment.enqueue(P, P->gettreatmentTime());
//					}
//				}
//				else
//				{
//					if (!(xWaitList.isEmpty()))
//					{
//						xWaitList.dequeue(P);
//						InTreatment.enqueue(P, P->gettreatmentTime());
//					}
//				}
//			}
//		}
//		else if (40 <= X && X < 50)
//		{
//			if (!(InTreatment.isEmpty()))
//
//			{
//				InTreatment.dequeue(P, pri);
//				if (N < 33)
//					eTherapy->MovetoWait(P);
//				else if (N < 66)
//					uTherapy->MovetoWait(P);
//				else
//					xTherapy->MovetoWait(P);
//			}
//		}
//		else if (50 <= X && X < 60)
//		{
//			if (!(InTreatment.isEmpty()))
//			{
//				InTreatment.dequeue(P, pri);
//				finishedPatients.push(P);
//			}
//		}
//		else if (60 <= X && X < 70)
//		{
//			if (!(xWaitList.isEmpty()))
//			{
//				xWaitList.randCancelAppointment(Pcancel, finishedPatients,TimeStep);
//			}
//
//		}
//		else if (70 <= X && X < 80)
//		{
//			if (!Early.isEmpty())
//			{
//				Early.randReschedule(Presc);
//			}
//		}
//		// Step 5: Print current simulation state
//		/*cout << "Press Enter to continue...";
//		cin.ignore();
//		cin.get();*/
//		UI::PrintTimes(TimeStep);
//		UI::PrintAllList(AllPatient);
//		UI::PrintEarlyList(Early);
//		UI::PrintLateList(Late);
//		UI::PrintWaitingLists(eWaitList, uWaitList, xWaitList);
//		UI::PrintAvailableDevices(E_Devices, U_Devices);
//		UI::PrintAvailableRooms(X_Rooms);
//		UI::PrintInTreatmentList(InTreatment);
//		UI::PrintFinishedPatients(finishedPatients);
//		IncTime();
//
//	}
//
//
//}


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
		if (TimeStep < -priority) 
		{
			// The patient is not yet finished with their treatment
			return;
		}

		InTreatment.dequeue(dequeuedPatient, priority);

		



		Resource* assignedResource = dequeuedPatient->getAssignedResource();


		if ((dynamic_cast<Dumbbell*>(assignedResource)) || (dynamic_cast<FoamRoller*>(assignedResource)) || ((dynamic_cast<Treadmill*>(assignedResource))))
		{
			X_room* room;
			X_Rooms.peek(room);
			room->decOcupancy();

		}
			

		if (assignedResource != nullptr) 
		{
			ReleaseResource(assignedResource); // Release the resource
		}

		if (dequeuedPatient->hasTreatmentsLeft()) 
		{
			toWaitList(dequeuedPatient);

			Assign_E();
			Assign_U();
			Assign_X();
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
			patient->settreatmentTime(patient->getEtt());
			patient->getNextTreatment();
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
			patient->settreatmentTime(patient->getUtt());

			patient->getNextTreatment();
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

	X_room* room;
	X_Rooms.peek(room);

	if (room->GetCapacity() == room->GetCurrentOccupancy())
	{
		X_Rooms.dequeue(room);
	}
	




	Assign_Dumbbell();
	Assign_FoamRoller();
	Assign_Treadmill();

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
			patient->settreatmentTime(patient->getDummbellTime());

			patient->getNextTool();

			///////////////////////////////////////
			X_room* availRoom;
			X_Rooms.peek(availRoom);
			if (availRoom)
			{
				X_Rooms.peek(availRoom);
				availRoom->incOcupancy();

			}
			////////////////////////////////////////
			patient->removeXTreatment();
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
			patient->settreatmentTime(patient->getFoamRollerTime());

			patient->getNextTool();
			///////////////////////////////////////
			X_room* availRoom;
			X_Rooms.peek(availRoom);
			if (availRoom)
			{
				X_Rooms.peek(availRoom);
				availRoom->incOcupancy();

			}
			////////////////////////////////////////
			patient->removeXTreatment();

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
			patient->settreatmentTime(patient->getTreadmillTime());

			patient->getNextTool();
			///////////////////////////////////////
			X_room* availRoom;
			X_Rooms.peek(availRoom);
			if (availRoom)
			{
				X_Rooms.peek(availRoom);
				availRoom->incOcupancy();

			}
			////////////////////////////////////////
			patient->removeXTreatment();
		}
		else
		{
			TreadmillsList.insertSort(patient);
			patient->setStatus("TreadmillWaiting");

			patient->getNextTool();
		}
	}
}




void Center::ReleaseResource(Resource* resource) 
{
	if (resource == nullptr) 
	{
		return;
	}

	resource->Release();

	if (auto* u = dynamic_cast<U_device*>(resource))
		U_Devices.enqueue(u);
	else if (auto* e = dynamic_cast<E_device*>(resource))
		E_Devices.enqueue(e);

	else if (auto* x = dynamic_cast<X_room*>(resource))
	{
		X_room* room;
		X_Rooms.peek(room);
		room->decOcupancy();

		if (!FullRooms.isEmpty())
		{
			X_room* temproom;
			FullRooms.dequeue(temproom);
			X_Rooms.enqueue(temproom);
		}
	}
}


void Center::fromAllPatientsList(Patient* patient)
{
    if (patient->getappointmentTime() > TimeStep) {
       return;
    }

    AllPatient.dequeue(patient);

    if (patient->getStatus() == "ERLY") 
	{
        Early.enqueue(patient, -patient->getServingTime());
		NumE_Patinets++;
    } else 
	{
        Late.enqueue(patient, -patient->getServingTime());
		NumL_Patinets++;
    }
}

void Center::MainSimulation() {
    string you = "Omar";
    Load(you);

	int totalPnum = AllPatient.getSize();


    while (!AllPatient.isEmpty()|| !Early.isEmpty() || !Late.isEmpty() || !InTreatment.isEmpty()) {
        
        // 1. Move patients from AllPatient list to Early/Late
        Patient* p;
		AllPatient.peek(p);
		if (!AllPatient.isEmpty())
		{
			fromAllPatientsList(p);
		}

	

        // 2. Move early/late patients to the appropriate waitlists
        if (!Early.isEmpty()) {

			if (!Early.randReschedule(Presc))
			{
				Patient* earlyP = getNextEarlyPatient();
				toWaitList(earlyP);
			}
        }

        if (!Late.isEmpty()) {
            Patient* lateP = getNextLatePatient();
            toWaitList(lateP);
        }

		//////2.5 cancel
	

        // 3. Assign patients from waitlists to available resources
        Assign_E();  
        Assign_U();  
        Assign_X();


        // 4. Move finished
		if (!InTreatment.isEmpty())
		{
			From_INtreatment();

		}
		

        // 5. Output :-
		UI::PrintTimes(TimeStep);
		UI::PrintAllList(AllPatient);
		UI::PrintEarlyList(Early);
		UI::PrintLateList(Late);
		UI::PrintWaitingLists(eWaitList, uWaitList, xWaitList);
		UI::PrintAvailableDevices(E_Devices, U_Devices);
		UI::PrintAvailableRooms(X_Rooms);
		UI::PrintDumbbellList(DumbbellsList);
		UI::PrintFoamRoollerList(FoamRollersList);
		UI::PrintTreadmailList(TreadmillsList);
		UI::PrintInTreatmentList(InTreatment);
		UI::PrintFinishedPatients(finishedPatients);

        // time++
        IncTime();
    }

    //std::cout << "Simulation Finished at TimeStep: " << TimeStep << "\n";
    //printFinishedPatient(); // Final output
}


void Center::toWaitList(Patient* patient)
{
	
	Treatment* nextTr = patient->peekNextTreatment();
	Resource*  nextTool = patient->peekNextTool();
	
	if (!nextTr) return;
	string type = nextTr->GetTreType();

	if (patient->getPatientType()=='N')
	{
		if (type == "E_therapy")
			AddToEWait(patient);
		else if (type == "U_therapy")
			AddToUWait(patient);

		else if (type == "X_therapy")
		{
		
			if ((dynamic_cast<Dumbbell*>(nextTool)))
			{
				AddToDumbbellWait(patient);
				DumbbellsList.randCancelAppointment(Pcancel, finishedPatients, TimeStep);
			}
			else if ((dynamic_cast<FoamRoller*>(nextTool)))
			{
				AddToFoamRollerWait(patient);
				FoamRollersList.randCancelAppointment(Pcancel, finishedPatients, TimeStep);
			}
			else if ((dynamic_cast<Treadmill*>(nextTool)))
			{
				AddToTreadmillWait(patient);
				TreadmillsList.randCancelAppointment(Pcancel, finishedPatients, TimeStep);
			}
		}
		
	
	}
	else
	{

		char validTypes[5] = { 0 };
		int latencies[5] = { 0 };
		int count = 0;
		
		// check lists:
		if (type == "E_therapy") { validTypes[count] = 'E'; latencies[count++] = eWaitList.CalcTreatmentLatency('E'); }
		if (type == "U_therapy") { validTypes[count] = 'U'; latencies[count++] = uWaitList.CalcTreatmentLatency('U'); }
		if (type == "X_therapy")
		{ 
			if ((dynamic_cast<Dumbbell*>(nextTool))) { validTypes[count] = 'D'; latencies[count++] = DumbbellsList.CalcTreatmentLatency('D'); }
			if ((dynamic_cast<FoamRoller*>(nextTool))) { validTypes[count] = 'F'; latencies[count++] = FoamRollersList.CalcTreatmentLatency('F'); }
			if ((dynamic_cast<Treadmill*>(nextTool))) { validTypes[count] = 'T'; latencies[count++] = TreadmillsList.CalcTreatmentLatency('T'); }
		}
		
		// calc min:
		int minIndex = 0;
		for (int i = 1; i < count; i++) {
			if (latencies[i] < latencies[minIndex])
				minIndex = i;
		}
		
		// execute:
		switch (validTypes[minIndex]) {

			case 'E': AddToEWait(patient); break;
			case 'U': AddToUWait(patient); break;
			case 'D': AddToDumbbellWait(patient);   DumbbellsList.randCancelAppointment(Pcancel, finishedPatients, TimeStep); break;
			case 'F': AddToFoamRollerWait(patient); FoamRollersList.randCancelAppointment(Pcancel, finishedPatients, TimeStep); break;
			case 'T': AddToTreadmillWait(patient);  TreadmillsList.randCancelAppointment(Pcancel, finishedPatients, TimeStep); break;
		}
	}
	
}
void Center::save(string Filename)
{
	string filename = Filename + ".txt";
	ofstream OutFile(filename, ios::out);

	ArrayStack<Patient*> fin;
	Patient* x;
	string pp;
	int numpat = finishedPatients.getSize();
	int numR=0;
	int numToTwR = 0;
	int numToTtR = 0;
	int numToTw = 0;
	int numToTt = 0;
	int numEp = 0;


	OutFile << "PID   PType   PT   VT   FT   WT   TT   Cancel   Resc" << "\n";


	for (int i = 1; i <= numpat; i++)
	{
		finishedPatients.pop(x);
		OutFile <<"\n" << x->getID() << "    " << x->getPatientType() << "       " << x->getappointmentTime() << "   " << x->getarrivalTime() << "   " << x->getfinishTime() << "   " << x->getwaitingTime() << "   " << x->gettreatmentTime() ;
		if (x->didCancel() )
			OutFile << "   " << "T";
		else OutFile << "   " << "F";
		if (x->didResc())
			OutFile << "   " << "T";
		else OutFile << "   " << "F";

		pp = x->getPatientType();
		if (pp == "R")
		{
			numR++;
			numToTwR = numToTwR + x->getwaitingTime();
			numToTtR = numToTtR + x->gettreatmentTime();

		}
		fin.push(x);
	}
	while (!fin.isEmpty())
	{
		fin.pop(x);
		numToTw = numToTw + x->getwaitingTime();
		numToTt = numToTt + x->gettreatmentTime();
		pp = x->getStatus();
		if (pp == "E")
			numEp++;

		finishedPatients.push(x);
	}

	int numN = numpat - numR;
	int numToTwN =numToTw- numToTwR;
	int numToTtN = numToTt- numToTtR;
	int numLp = numpat - numEp;
	///////////////////////////////////////////////
	int TotalNum = NumE_Patinets + NumL_Patinets;

	OutFile <<"\n"<< "Total number of timesteps = " << TimeStep-1 << "\n" ;
	OutFile << "Total number of all , N , and R patients = " << numpat << " , " << numN << " , " << numR << "\n";
	OutFile << "Average total waiting time for all , N , and R patients = " << static_cast<float>(numToTw) / numpat << " , " << static_cast<float>(numToTwN)/ numN << " , " << static_cast<float>(numToTwR) / numR << "\n";
	OutFile << "Average total treatment time for all , N , and R patients = " << static_cast<float>(numToTt) / numpat << " , " << static_cast<float> (numToTtN) / numN << " , " << static_cast<float>(numToTtR) / numR << "\n";
	//
	//
	OutFile << "Percentage of early patient (%) = " << (NumE_Patinets / TotalNum) * 100 << " %\n";
	OutFile << "Percentage of late patient (%) = " << (NumL_Patinets / TotalNum) * 100 << " %\n";


}
// dummy

