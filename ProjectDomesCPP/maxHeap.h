#pragma once

#include <string>
using namespace std;

class maxHeap
{
protected:
    //δυναμικός πίνακας
    int *heap;

    //πλήθος στοιχείων που περιέχει η σωρός μεγίστων
    int Size;

    //μέγιστος αριθμός στοιχείων που μπορεί να έχει η σωρός μεγίστων
    int maxSize;

public:
    //Κατασκευστής
    maxHeap();

    //Συναρτήσεις χρήσιμες για την Build
    void readData(const string& filename);
    void buildMaxHeap();

    void maxHeapify(int i);

    //Συναρτήσεις για
    int findMax();                //εύρεση μεγίστου στοιχείου
    void insertNode(int data);    //εισαγωγή νέου στοιχείου στην σωρό μεγίστων
    void deleteMax();             //διαγραφή μέγιστου στοιχείου απο την σωρό μεγίστων (το πρώτο στοιχείο)

    //Getter για την μεταβλητή Size
    int getSize();
};
