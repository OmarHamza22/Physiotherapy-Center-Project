#pragma once
#include "LinkedQueue.h"
#include"Patient.h"
class EU_WaitList :
    public LinkedQueue<Patient* >
{
    void insertSort(Patient* newpatient);
    int CalcTreatmentLatency(char M);
};

