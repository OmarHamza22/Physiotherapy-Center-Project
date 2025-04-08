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
		AddXRoom(i, capacityX);
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

void Center::AddXRoom(int id, int capacity) {
	X_Rooms.enqueue(new X_room(id, capacity));
}

E_device* Center::GetAvailableEDevice() {
	LinkedQueue<E_device*> tempQueue;
	E_device* device = nullptr;
	while (!E_Devices.isEmpty()) {
		E_Devices.dequeue(device);
		tempQueue.enqueue(device);
		if (device->IsAvailable()) {
			while (!tempQueue.isEmpty()) {
				E_device* tempDevice;
				tempQueue.dequeue(tempDevice);
				E_Devices.enqueue(tempDevice);
			}
			return device;
		}
	}
	while (!tempQueue.isEmpty()) {
		E_device* tempDevice;
		tempQueue.dequeue(tempDevice);
		E_Devices.enqueue(tempDevice);
	}
	return nullptr;
}

U_device* Center::GetAvailableUDevice() {
	LinkedQueue<U_device*> tempQueue;
	U_device* device = nullptr;
	while (!U_Devices.isEmpty()) {
		U_Devices.dequeue(device);
		tempQueue.enqueue(device);
		if (device->IsAvailable()) {
			while (!tempQueue.isEmpty()) {
				U_device* tempDevice;
				tempQueue.dequeue(tempDevice);
				U_Devices.enqueue(tempDevice);
			}
			return device;
		}
	}
	while (!tempQueue.isEmpty()) {
		U_device* tempDevice;
		tempQueue.dequeue(tempDevice);
		U_Devices.enqueue(tempDevice);
	}
	return nullptr;
}

X_room* Center::GetAvailableXRoom() {
	LinkedQueue<X_room*> tempQueue;
	X_room* room = nullptr;
	while (!X_Rooms.isEmpty()) {
		X_Rooms.dequeue(room);
		tempQueue.enqueue(room);
		if (room->IsAvailable()) {
			while (!tempQueue.isEmpty()) {
				X_room* tempRoom;
				tempQueue.dequeue(tempRoom);
				X_Rooms.enqueue(tempRoom);
			}
			return room;
		}
	}
	while (!tempQueue.isEmpty()) {
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
	xWaitList.enqueue(newPatient);
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
		else if (10<= X && X < 20)
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
		else if (20<=X && X < 40)
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
		else if (40<=X&&X < 50)
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
		else if (50<=X && X < 60)
		{
			if (!(InTreatment.isEmpty()))
			{
				InTreatment.dequeue(P, pri);
				finishedPatients.push(P);
			}
		}
		else if (60<=X && X < 70)
		{
			if (!(xWaitList.isEmpty()))
			{
				xWaitList.randCancelAppointment(Pcancel, finishedPatients);
			}

		}
		else if (70<=X && X < 80)
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

// dummy

