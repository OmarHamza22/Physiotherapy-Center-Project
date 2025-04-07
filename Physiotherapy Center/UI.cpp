#include "UI.h"
#include <iostream>
using namespace std;

void UI::PrintTimes(int timestep) {
    cout << "Current Timesteps: " << timestep << endl;
}

void UI::PrintAllList(const LinkedQueue<Patient*>& allPatients) {
    cout << " ===================== [All Patients] =====================" <<endl;
    cout << allPatients.getSize() <<"patients remaining: ";
    allPatients.printQueue();
    cout << endl;
}

void UI::PrintWaitingLists(const EU_WaitList& eWaitList, const EU_WaitList& uWaitList, const X_WaitList& xWaitList) {
    
    cout << " ===================== Waiting Lists =====================" <<endl;

    cout << eWaitList.getSize() << "E-therapy patients: ";
    eWaitList.printQueue();
    cout << endl;

    cout << uWaitList.getSize() << "U-therapy patients: ";
    uWaitList.printQueue();
    cout << endl;

    cout << uWaitList.getSize() << "x-therapy patients: ";
    xWaitList.printQueue();
    cout << endl;
}

void UI::PrintEarlyList(const EarlyPList& earlyList) {
    cout << " ===================== Early List =====================" <<endl;
    cout << earlyList.getSize() << "patients: ";
    earlyList.printQueue();
    cout << endl;
}

void UI::PrintLateList(const priQueue<Patient*>& lateList) {
    cout << " ===================== Late List =====================" <<endl;
    cout << lateList.getSize() << "patients: ";
    lateList.printQueue();
    cout << endl;
}

void UI::PrintAvailableDevices(const LinkedQueue<E_device*>& eDevices, const LinkedQueue<U_device*>& uDevices) {
    cout << " ===================== Available E-Devices =====================" <<endl;
    cout << eDevices.getSize() << "Electro Devices: ";
    eDevices.printQueue();
    cout << endl;

    cout << " ===================== Available U-Devices =====================" <<endl;
    cout << uDevices.getSize() << "Ultra Devices: ";
    uDevices.printQueue();
    cout << endl;
}

void UI::PrintAvailableRooms(const LinkedQueue<X_room*>& xRooms) {
    cout << " ===================== Available X-Rooms =====================" <<endl;
    cout << xRooms.getSize() << "Rooms: ";
    xRooms.printQueue();
    cout << endl;
}

void UI::PrintInTreatmentList(const priQueue<Patient*>& inTreatmentList) {
    cout << " ===================== In-treatement List =====================" <<endl;
    cout << inTreatmentList.getSize() << "Rooms: ";
    inTreatmentList.printQueue();
    cout << endl;
}

void UI::PrintFinishedPatients(const ArrayStack<Patient*>& finishedStack) {
    cout << " ----------------------------------------" <<endl;
    cout << finishedStack.getSize() << "patients: ";
    finishedStack.print();
    cout << endl;
}


void UI::Print10(const LinkedQueue<Patient*>& allPatients) {
    cout << " ===================== [All Patients] =====================" << endl;
    allPatients.print10QueueElements();  // Calls the new print method to print the first 10 patients
    cout << endl;
}

void UI::TimeStepEndMessage(){
    cout << "Press any key to display next timestep";
}
