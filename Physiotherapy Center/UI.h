#pragma once
#include "Center.h"
#include <iostream>
#include <iomanip>
using namespace std;

class UI {
public: 
    static void PrintTimes(int timestep);

    static void PrintAllList(const LinkedQueue<Patient*>& allPatients);

    static void Print10(const LinkedQueue<Patient*>& allPatients);

    static void PrintWaitingLists(const EU_WaitList& eWaitList, const EU_WaitList& uWaitList, const X_WaitList& xWaitList);

    static void PrintEarlyList(const EarlyPList& earlyList);

    static void PrintLateList(const priQueue<Patient*>& lateList);

    static void PrintAvailableDevices(const LinkedQueue<E_device*>& eDevices, const LinkedQueue<U_device*>& uDevices);

    static void PrintAvailableRooms(const LinkedQueue<X_room*>& xRooms);

    static void PrintInTreatmentList(const priQueue<Patient*>& inTreatmentList);

    static void PrintFinishedPatients(const ArrayStack<Patient*>& finishedStack);

    static void PrintDumbbellList(const LinkedQueue<Patient*>& DumbbellList);
    
    static void PrintFoamRoollerList(const LinkedQueue<Patient*>& FoamList);

    static void PrintTreadmailList(const LinkedQueue<Patient*>& TreadMailList);

    static void TimeStepEndMessage();


};
