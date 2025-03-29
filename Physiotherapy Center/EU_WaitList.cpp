#include "EU_WaitList.h"
#include "LinkedQueue.h"
void EU_WaitList::insertSort(Patient* newpatient)
{
    if (isEmpty())
    {
        enqueue(newpatient);
 
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

    while (!isEmpty)
    {
        dequeue(frontpat);
        tempQueue.enqueue(frontpat);
    }

    while (!isEmpty())
    {
        tempQueue.dequeue(frontpat);
        enqueue(frontpat);

    }
}


int EU_WaitList::CalcTreatmentLatency()
{
    
    if (isEmpty)
    {
        return 0;
    }

    LinkedQueue<Patient*>tempQueue;
    Patient* tempPAT;
    int TlE = 0;
    int TlU = 0;
    while (!isEmpty)
    {
        dequeue(tempPAT);
        //to be cont.
    }
}
