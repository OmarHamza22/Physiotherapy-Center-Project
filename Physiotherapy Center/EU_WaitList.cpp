#include "EU_WaitList.h"
void EU_WaitList::insertSort(Patient* newpatient)
{
    if (isEmpty())
    {
        enqueue(newpatient);
        return;
    }

    LinkedQueue<Patient*>tempQueue;
    Patient* frontpat;

    while (!isEmpty())
    {
        peek(frontpat);
        if (newpatient->getsortValue() < frontpat->getsortValue())
        {
            break;
        }
        dequeue(frontpat);
        tempQueue.enqueue(frontpat);
    }

    tempQueue.enqueue(newpatient);

    while (!tempQueue.isEmpty())
    {
        tempQueue.dequeue(frontpat);
        enqueue(frontpat);
    }

    while (!tempQueue.isEmpty())
    {
        tempQueue.dequeue(frontpat);
        enqueue(frontpat);
    }
}


int EU_WaitList::CalcTreatmentLatency(char M)
{
    
    if (isEmpty())
    {
        return 0;
    }

    LinkedQueue<Patient*>tempQueue;
    Patient* tempPAT;
    int TlE = 0;
    int TlU = 0;
    //int TlX = 0;
    int TlD = 0;
    int TlF = 0;
    int TlT = 0;
    while (!isEmpty())
    {
        dequeue(tempPAT);
        TlE += tempPAT->getEtt();
        TlU += tempPAT->getUtt();
        //TlX += tempPAT->getXtt();
        TlD += tempPAT->getDummbellTime();
        TlF += tempPAT->getFoamRollerTime();
        TlT += tempPAT->getTreadmillTime();
        tempQueue.enqueue(tempPAT);
    }
    while (!tempQueue.isEmpty())
    {
        tempQueue.dequeue(tempPAT);
        enqueue(tempPAT);
    }
    if (M == 'U')
    {
        return TlU;
    }
    else if (M == 'E')
    {
        return TlE;
    }
    else if (M =='D')
    {
        return TlD;
    }
    else if (M =='F')
    {
        return TlF;
    }
    else if (M = 'T')
    {
        return TlT;
    }
    
    else
    {
        return 0;
    }
}
