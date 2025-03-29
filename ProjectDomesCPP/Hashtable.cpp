#include "Hashtable.h"
#include <cmath>
#include <fstream>

using namespace std;

/////////////////////////////////////////////////////////////////

node::node(int data) {
  this->data = data;
  this->next = nullptr;
}

/////////////////////////////////////////////////////////////////

int node::getData() { return data; }

/////////////////////////////////////////////////////////////////

node *node::getNext() { return next; }

/////////////////////////////////////////////////////////////////

void node::setNext(node *next) { this->next = next; }

/////////////////////////////////////////////////////////////////

Hashtable::Hashtable() {
  size = 0;
  maxSize = 50000;
  hashTable = new node *[50000]();
}

/////////////////////////////////////////////////////////////////

void Hashtable ::buildHashtable(const string &filename) {
  ifstream inputFile(filename);
  if (!inputFile.is_open())
  {
    cerr << "Error: Unable to open file " << filename << endl;
    return;
  }
  int fileData;
  while (inputFile >> fileData) {
    insert(fileData);
  }
  inputFile.close();
}

/////////////////////////////////////////////////////////////////

//Στη resize επειδή αλλάζει το μέγεθος του πίνακα αλλάζουν και τα indexes οπότε αλλάζει ανάλογα
//και ο πίνακας κατακερματισμού
void Hashtable::resize() {
  maxSize += 50000;
  node **tempArray = new node *[maxSize]();
  for (int i = 0; i < size; ++i) {
    if (hashTable[i] != nullptr) {
      node *current = hashTable[i];
      while (current != nullptr) {
        int newIndex = hashFunction(current->getData());
        if (tempArray[newIndex] == nullptr) {
          tempArray[newIndex] = new node(current->getData());
        } else {
          node *temp = tempArray[newIndex];
          while (temp->getNext() != nullptr) {
            temp = temp->getNext();
          }
          temp->setNext(new node(current->getData()));
        }
        current = current->getNext();
      }
    }
  }
  delete[] hashTable;
  hashTable = tempArray;
}

/////////////////////////////////////////////////////////////////

void Hashtable ::insert(int key) {
  //Αν ο πίνακας κατακερματισμού φτάσει σε πληρότητα 70% τότε χρησιμοποιούμε την resize για εύρεση περισσότερου χώρου
  if (size >= maxSize * 0.7) {
    resize();
  }

  int index = hashFunction(key); //Ανάθεση index για το στοιχείο key

  if (hashTable[index] == nullptr) {
    hashTable[index] = new node(key);
  } else {
    node *current = hashTable[index];
    while (current->getNext() != nullptr) {
      current = current->getNext();
    }
    current->setNext(new node(key));
  }
  size++;
}

/////////////////////////////////////////////////////////////////

int Hashtable ::getSize() { return size; }

/////////////////////////////////////////////////////////////////

int Hashtable::hashFunction(int key) { return key % maxSize; }

/////////////////////////////////////////////////////////////////

string Hashtable::search(int key) {
  int index = hashFunction(key);

  //Αν η θέση του πίνακα είναι κενή, επιστρέφει η συμβολοσειρα "FAILURE" εφόσον το key δεν βρέθηκε
  if (hashTable[index] == nullptr) {
    return "FAILURE";
  } else {
    node *current = hashTable[index];

    //Ελέγχουμε αν το key βρισκεται στη λίστα
    while (current != nullptr) {
      if (current->getData() == key) {
        return "SUCCESS";
      }
      current = current->getNext();
    }
  }

  //Αν το key δεν βρέθηκε στη λίστα επιστρέφει η συμβολοσειρα "FAILURE" εφόσον το key δεν βρέθηκε
  return "FAILURE";
}

/////////////////////////////////////////////////////////////////
