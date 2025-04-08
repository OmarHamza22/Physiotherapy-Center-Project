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

bool Center::LoadALL(string filename)
{
    int Pt, Vt, XT, ET, UT, NumU, NumX, NumE, NumP, Numteratments;
    char pType, tType;
    int Presc, Pcancel;
    //E_device* Edev;
    //U_device* Udev;
    //X_room* Xroom;
    
    Patient* newP;
    U_therapy* Uther;
    E_therapy* Ether;
    X_therapy* Xther;
    std::ifstream INfile("D:/Studying/Uni/Data Structure/DS project/Physiotherapy-Center-Project/data.txt");
    if (!INfile) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }


    INfile >> NumE >> NumU >> NumX;
    for (int i = 1; i <= NumE; i++)
    {
        AddEDevice(i);
    }

    for (int i = 1; i <= NumU; i++)
    {
        AddUDevice(i);
    }

    for (int i = 1; i <= NumE; i++)
    {
        int capacityX;
        INfile >> capacityX;
        AddXRoom(i, capacityX);
    }

    INfile >> Pcancel >> Presc;
    
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
                 int e = 1;
                 INfile >> ET;
                 newP->setEtt(ET);
                 Ether = new E_therapy(e, ET, -1);
                 newP->addTreatment(Ether);
                 e++;
            }
            else if (tType == 'U')
            {
                 int u = 1;
                 INfile >> UT;
                 newP->setUtt(UT);
                 Uther = new U_therapy(u, UT, -1);
                 newP->addTreatment(Uther);
                 u++;
            }
            else if (tType == 'X')
            {
                int x = 1;
                INfile >> XT;
                newP->setXtt(XT);
                Xther = new X_therapy(x, XT, -1);
                newP->addTreatment(Xther);
                x++;
            }

        }

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
    Early.enqueue(newpatient, -( newpatient->getappointmentTime()));
}

void Center::ComeLate(Patient* newpatient)
{
    int pri,vt,pt;

    vt = newpatient->getarrivalTime();
    pt = newpatient->getappointmentTime();
    
    if (vt > pt)
    {
        pri = -(vt + 0.5 * (vt - pt));
        Late.enqueue(newpatient, pri);
        newpatient->setappointmentTime( - pri);
    }

    if (vt < pt)
    {
        pri = -(vt + 0.5 * (vt+24 - pt));
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




void Center::Simulate() {
    TimeStep = 5;
    // Initial state print before any simulation starts
    UI::PrintTimes(TimeStep);
    UI::PrintAllList(AllPatient);
    UI::PrintEarlyList(Early);
    UI::PrintLateList(Late);
    UI::PrintWaitingLists(eWaitList, uWaitList, xWaitList);
    UI::PrintInTreatmentList(InTreatment);
    UI::PrintFinishedPatients(finishedPatients);
    // Initial state print before any simulation starts
    UI::PrintTimes(TimeStep);
    UI::PrintAllList(AllPatient);
    UI::PrintEarlyList(Early);
    UI::PrintLateList(Late);
    UI::PrintWaitingLists(eWaitList, uWaitList, xWaitList);
    UI::PrintInTreatmentList(InTreatment);
    UI::PrintFinishedPatients(finishedPatients);

    // Step 1: Load all patient data and setup therapy units
    LoadALL("data");

    // Step 2: Main simulation loop
    while (!PatientListIsEmpty() || !EarlyListIsEmpty() || !LateListIsEmpty() || !InTreatment.isEmpty()) {
        TimeStep++; // Increment simulation time

        // Step 3: Handle patient arrivals at this time step
        Patient* patient;
        while (AllPatient.peek(patient)) {
            if (patient->getarrivalTime() == TimeStep) {
                // Step 3.1: Classify patients based on arrival time
                if (patient->getarrivalTime() < patient->getappointmentTime()) {
                    ComeEarly(patient); // Arrived early
                } else if (patient->getarrivalTime() > patient->getappointmentTime()) {
                    ComeLate(patient); // Arrived late
                } else {
                    RandomWaiting(patient); // Arrived on time → sent to random waitlist
                }
                AllPatient.dequeue(patient); // Remove from general list
            } else {
                break; // No more arrivals at this time
            }
        }

        // Step 4: Random event simulation (introduces variability in behavior)
        int X = rand() % 100;

        // Step 4.1: 10% chance → move an early patient to a waitlist
        if (X < 10 && !EarlyListIsEmpty()) {
            Patient* earlyPatient;
            int priority;
            Early.dequeue(earlyPatient, priority);
            RandomWaiting(earlyPatient);
        }

        // Step 4.2: 10% chance → move late patient to waitlist and delay appointment
        else if (X >= 10 && X < 20 && !LateListIsEmpty()) {
            Patient* latePatient;
            int priority;
            Late.dequeue(latePatient, priority);
            latePatient->setappointmentTime(latePatient->getappointmentTime() + 5); // Delay
            RandomWaiting(latePatient);
        }

        // Step 4.3: 20% chance → move up to 2 patients from waitlists to treatment
        else if (X >= 20 && X < 40) {
            for (int i = 0; i < 2; i++) {
                Patient* patient;
                if (!eWaitList.isEmpty()) {
                    eWaitList.dequeue(patient);
                    AddToTreatmentList(patient);
                } else if (!uWaitList.isEmpty()) {
                    uWaitList.dequeue(patient);
                    AddToTreatmentList(patient);
                } else if (!xWaitList.isEmpty()) {
                    xWaitList.dequeue(patient);
                    AddToTreatmentList(patient);
                }
            }
        }

        // Step 4.4: 10% chance → move a patient from treatment back to a waitlist
        else if (X >= 40 && X < 50 && !InTreatment.isEmpty()) {
            Patient* patient;
            int priority;
            InTreatment.dequeue(patient, priority);
            RandomWaiting(patient);
        }

        // Step 4.5: 10% chance → finish treatment for a patient
        else if (X >= 50 && X < 60 && !InTreatment.isEmpty()) {
            Patient* patient;
            int priority;
            InTreatment.dequeue(patient, priority);
            addToFinishedPatientslist(patient);
        }

        // Step 4.6: 10% chance → discharge patient directly from X waitlist
        else if (X >= 60 && X < 70 && !xWaitList.isEmpty()) {
            Patient* patient;
            xWaitList.dequeue(patient);
            addToFinishedPatientslist(patient);
        }

        // Step 4.7: 10% chance → attempt to reschedule an early patient
        else if (X >= 70 && X < 80 && !EarlyListIsEmpty()) {
            Patient* patient;
            int priority;
            Early.dequeue(patient, priority);
            bool rescheduled = Early.randReschedule(50); // 50% chance
            if (rescheduled) {
                // Optional: Logging or message
            }
        }

        // Step 5: Print current simulation state
        UI::PrintTimes(TimeStep);
        UI::PrintAllList(AllPatient);
        UI::PrintEarlyList(Early);
        UI::PrintLateList(Late);
        UI::PrintWaitingLists(eWaitList, uWaitList, xWaitList);
        UI::PrintInTreatmentList(InTreatment);
        UI::PrintFinishedPatients(finishedPatients);

        // Step 6: Check if simulation is done (all patients treated)
        if (finishedPatients.getSize() == AllPatient.getSize()) {
            break;
        }

        // Step 7: End of timestep message or pause
        UI::TimeStepEndMessage();
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
        eTherapy.MovetoWait(patient);
    } 
    else if (randomNum < 66) {
        // Send to U-Waiting (33-65)
        uTherapy.MovetoWait(patient);
    } 
    else {
        // Send to X-Waiting (66-100)
        xTherapy.MovetoWait(patient);
    }
}







// dummy

