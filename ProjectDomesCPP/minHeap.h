
#pragma once
#include <string>

using namespace std;

class minHeap
{
protected:
    //δυναμικός πίνακας
    int *heap;

    //πλήθος στοιχείων που περιέχει η σωρός ελαχίστων
    int Size;

    //μέγιστος αριθμός στοιχείων που μπορεί να έχει η σωρός ελαχίστων
    int maxSize;

public:
    //Κατασκευστής
    minHeap();

    //Συναρτήσεις χρήσιμες για την Built
    void readData(const string& filename);
    void buildMinHeap();

    void minHeapify(int i);

    //Συναρτήσεις για
    int findMin();                //εύρεση ελαχίστου στοιχείου
    void insertNode(int data);    //εισαγωγή νέου στοιχείου στην σωρό ελαχίστων
    void deleteMin();             //διαγραφή ελαχίστου στοιχείου απο την σωρό ελαχίστων (το πρώτο στοιχείο)

    //Getter για την μεταβλητή Size
    int getSize();
};

