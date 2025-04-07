#include "Center.h"

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
    //U_therapy* U;
    //E_therapy* E;
    //X_therapy* X;
    filename = filename + ".txt";

    std::ifstream INfile(filename);
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
                INfile >> ET;
                newP->setEtt(ET);
              //  newP->addrequiredTreatment(E);
            }
            else if (tType == 'U')
            {
                INfile >> UT;
                newP->setUtt(UT);
               // newP->addrequiredTreatment(U);

            }
            else if (tType == 'X')
            {
                INfile >> XT;
                newP->setXtt(XT);
               // newP->addrequiredTreatment(X);
            }

        }

    }
    return true;
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
    if (finishedPatients.empty())
        return nullptr;
    Patient* finished = finishedPatients.top();
    finishedPatients.pop();
    return finished;

}

bool Center::removeFinishedPatient(Patient* patient)
{
    stack<Patient*> tempStack;
    bool found = false;

    while (!finishedPatients.empty()) {
        Patient* topPatient = finishedPatients.top();
        finishedPatients.pop();

        if (topPatient == patient) {
            return true;
            break;
        }
        tempStack.push(topPatient);
    }
    while (!tempStack.empty()) {
        finishedPatients.push(tempStack.top());
        tempStack.pop();
    }
    return found;

}

void Center::printFinishedPatient() const
{
    if (finishedPatients.empty()) {
        cout << "No finished patients available." << endl;
        return;
    }

    stack<Patient*> tempStack = finishedPatients;
    cout << "Finished Patients List:\n";
    while (!tempStack.empty()) {
        Patient* p = tempStack.top();
        tempStack.pop();
        cout << "Patient ID: " << p->getID() << ", Finish Time: " << p->getfinishTime() << endl;
    }

}

void Center::clearFinishedPatients()
{
    while (!finishedPatients.empty()) {
        Patient* p = finishedPatients.top();
        finishedPatients.pop();
        delete p;
    }

}










// dummy

