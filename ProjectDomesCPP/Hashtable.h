#pragma once

#include <iostream>
#include <string>

using namespace std;

//Κλάση λίστα
class node {
private:
  int data;   //δεδομένο
  node *next; //δείκτης για το επόμενο κόμβο

public:
  //Κατασκευαστής
  node(int data);

  //Setters και Getters
  void setNext(node *next);
  node *getNext();
  int getData();
};

//Κλάση πίνακα κατακερματισμού υλοποιημένη από λίστες (κάθε θέση του πίνακα αναπαριστά μια λίστα)
class Hashtable {
private:
  node **hashTable;
  int size;
  int maxSize;

public:
  //Κατασκευαστής
  Hashtable();

  //Συνάρτηση για την κατασκευή του πίνακα Κατακερματισμού διαβάζοντας στοιχεία απο το αρχείο filename
  void buildHashtable(const string &filename);
  void insert(int data);

  //Βοηθητική συνάρτηση για την δεσμευση περισσότερης μνήμης όταν ο πίνακας κατακερματισμού φτάσει στο 70% της χωρητικότητας του
  void resize();

  //Συνάρτηση που επιστρέφει το πλήθος των στοιχείων του πίνακα κατακερματισμού
  int getSize();

  // Η συνάρτηση κατακερματισμού
  int hashFunction(int key);

  //Επιστρέφει τη συμβολοσειρά "SUCCESS" αν το key υπάρχει στον πίνακα κατακερματισμού, αλλιώς επιστρέφει τη συμβολοσειρά "FAILURE"
  string search(int key);
};
