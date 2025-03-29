#include <fstream>
#include <iostream>

#include "maxHeap.h"

using namespace std;

/////////////////////////////////////////////////////////////////

maxHeap :: maxHeap ()
{
    //Αρχικοποίηση μεταβλητών.
    heap = new int[10000];
    Size=0;
    maxSize = 10000;
}

/////////////////////////////////////////////////////////////////

void maxHeap :: readData( const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        //Αν το αρχείο δεν μπορεί να ανοίξει, εκτυπώνεται ένα μήνυμα λάθους.
        cerr << "Could not open file.";
        return;
    }
    int data;
    while (file >> data)
    {
        //Αν ο διαθέσιμος χώρος εξαντληθεί, γίνεται resize.
        if(Size==maxSize)
        {
            int *newHeap = new int[Size+10000];
            for(int i=0; i<Size; i++)
            {
                newHeap[i]=heap[i];
            }
            delete [] heap;
            heap = newHeap;
            maxSize+=10000;
        }
        heap[Size] = data;
        Size++;
    }

    file.close();

}

/////////////////////////////////////////////////////////////////

void maxHeap:: buildMaxHeap()
{
    for(int i=(Size/2)-1; i>=0; i--)
    {
        maxHeapify(i);
    }
}

/////////////////////////////////////////////////////////////////

//Αναδρομική εκτέληση της mαχHeapify για την σωστή διάταξη της σωρού.
void maxHeap:: maxHeapify(int i)
{
    int left = 2*i+1;
    int right = 2*i+2;
    int largest;

    if (left < Size && heap[left] > heap[i])
        largest= left;
    else
        largest=i;

    if (right < Size && heap[right] > heap[largest])
        largest = right;

    if (largest!=i)
    {
        swap(heap[i], heap[largest]);

        maxHeapify(largest);
    }

}

/////////////////////////////////////////////////////////////////

int maxHeap::getSize()
{
    return Size;
}

//Το πρώτο στοιχείο είναι και το max.
int maxHeap::findMax()
{
    return heap[0];
}

/////////////////////////////////////////////////////////////////

void maxHeap::insertNode(int data)
{
    //Αν ο διαθέσιμος χώρος εξαντληθεί, γίνεται resize.
    if(Size==maxSize)
    {
        int *newHeap = new int[Size+10000];
        for(int i=0; i<Size; i++)
        {
            newHeap[i]=heap[i];
        }
        delete [] heap;
        heap = newHeap;
        maxSize+=10000;
    }
    heap[Size] = data;
    Size++;
    int parent = (Size-1)/2;
    for( int kid = Size-1; kid>=0 && heap[parent] < heap[kid];)
    {
        swap(heap[parent], heap[kid]);
        kid = parent;
        parent = (parent-1)/2;
    }

}

/////////////////////////////////////////////////////////////////

void maxHeap:: deleteMax()
{
    //Διαγραφή στοιχείου και αναδιάταξη.
    heap[0] = heap[Size-1];
    int *newHeap = new int[Size-1];
    for(int i=0; i<Size-1; i++)
    {
        newHeap[i]=heap[i];
    }
    delete [] heap;
    heap = newHeap;
    maxSize-=1;

    Size--;

    maxHeapify(0);
}

/////////////////////////////////////////////////////////////////
