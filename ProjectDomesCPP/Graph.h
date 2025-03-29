
#pragma once

#include <iostream>
#include <string>

using namespace std;

class Vertex {
public:
    Vertex(int value);
int data;  // Η τιμή του κόμβου (ή κορυφής) του γράφου
    Vertex** edges;  // Οι κόμβοι (ή κορυφές) που συνδέονται με αυτόν τον κόμβο
    int* weights;  // Τα βάρη των ακμών που συνδέουν τον τρέχοντα κόμβο με τους άλλους κόμβους
    size_t sizeOfEdges;  // Τρέχον αριθμός ακμών
    size_t sizeOfWeights;  // Τρέχον αριθμός βαρών
    size_t maxSizeOfEdges;  // Μέγιστος αριθμός ακμών πριν από ανακατασκευή του πίνακα
    size_t maxSizeOfWeights;  // Μέγιστος αριθμός βαρών πριν από ανακατασκευή του πίνακα
};

class HashMap {
private:
    struct HashNode {
        int key;  // Το κλειδί για την αποθήκευση του κόμβου στον χάρτη
        Vertex* value;  // Ο κόμβος που αποθηκεύεται
        HashNode* next;  // Δείκτης στον επόμενο κόμβο (για την αντιμετώπιση συγκρούσεων)
        HashNode(int k, Vertex* v) : key(k), value(v), next(nullptr) {}
    };

     HashNode** table;  // Ο πίνακας με τις αλυσίδες για αποθήκευση των κόμβων
    size_t capacity;  // Χωρητικότητα του πίνακα
    size_t size;  // Τρέχον αριθμός στοιχείων στον χάρτη

    size_t hashFunction(int key);  // Συνάρτηση κατακερματισμού για υπολογισμό του δείκτη
    void resizeTable();  // Συνάρτηση αναδιάταξης του πίνακα σε περίπτωση που γεμίσει

public:
    HashMap(size_t initialCapacity = 256);  // Κατασκευαστής με προαιρετική αρχική χωρητικότητα
    ~HashMap();  // Καταστροφέας
    Vertex* get(int key);  // Λήψη του κόμβου από τον χάρτη με βάση το κλειδί
    void put(int key, Vertex* value);  // Αποθήκευση ενός κόμβου στον χάρτη
    void remove(int key);  // Διαγραφή ενός κόμβου από τον χάρτη
    size_t getSize();  // Λήψη του τρέχοντος αριθμού στοιχείων στον χάρτη
};


class Graph {
private:


    HashMap vertexIndexMap;  // Χάρτης για να αποθηκεύονται οι κόμβοι και οι δείκτες τους

    size_t SizeOfVerteces;  // Μέγεθος των κορυφών του γράφου
    size_t SizeOfEdges;  // Μέγεθος των ακμών του γράφου
    size_t maxSizeOfVerteces;  // Μέγιστος αριθμός κορυφών πριν από ανακατασκευή του πίνακα
    Vertex** graph;  // Ο πίνακας των κορυφών του γράφου
    HashMap vertexMap;  // Επιπλέον χάρτης για αποθήκευση των κορυφών με βάση τις τιμές τους

    void resizeGraph();  // Συνάρτηση αναδιάταξης του πίνακα των κορυφών
    void resizeVertexEdges(Vertex* vertex);  // Αλλαγή μεγέθους του πίνακα ακμών ενός κόμβου
    void resizeVertexWeights(Vertex* vertex);  // Αλλαγή μεγέθους του πίνακα βαρών ενός κόμβου

public:
Graph();  // Κατασκευαστής για τη δημιουργία ενός κενού γράφου
int getSizeOfVerteces();  // Επιστρέφει τον αριθμό των κορυφών του γράφου
int getSizeOfEdges();  // Επιστρέφει τον αριθμό των ακμών του γράφου
void BuildGraph(const string& filename);  // Κατασκευή γράφου από ένα αρχείο
void Insert(int value1, int value2, int weight);  // Εισαγωγή νέας ακμής με βάρος μεταξύ δύο κορυφών
Vertex* findVertex(int value);  // Αναζήτηση και επιστροφή κόμβου με δεδομένη τιμή
int getShortestPathCost(Vertex* Start, Vertex* End);  // Επιστρέφει το κόστος του συντομότερου μονοπατιού μεταξύ δύο κορυφών
int getMinimumSpanningTreeCost();  // Επιστρέφει το κόστος του ελάχιστου συνδετικού δέντρου του γράφου
void unite(int*& parent, int*& rank, int x, int y);  // Συνάρτηση για την ενοποίηση (union) δύο συνόλων στην υλοποίηση του αλγορίθμου Union-Find
int find(int*& parent, int i);  // Συνάρτηση για την εύρεση (find) του αντιπροσώπου ενός στοιχείου στην υλοποίηση του αλγορίθμου Union-Find
size_t getIndex(Vertex* vertex);  // Επιστρέφει τον δείκτη της κορυφής στον πίνακα γράφου για δοθέντα κόμβο
int getIndexByData(int data);  // Επιστρέφει τον δείκτη της κορυφής με δεδομένη τιμή δεδομένων
void deleteEdge(int value1, int value2);  // Διαγράφει την ακμή μεταξύ δύο κορυφών
int DFS(int v, bool visited[], HashMap& visitedVertices);  // Υπολογίζει τον αριθμό των κόμβων σε μια συνδεδεμένη συνιστώσα γράφου από τον κόμβο v
int findConnectedComponents();  // Υπολογίζει τον αριθμό των συνδεδεμένων συνιστωσών στο γράφο
void DFS(int vertexIndex, bool visited[]);  // Υλοποιεί την αναζήτηση κατά βάθος (DFS) από δεδομένο δείκτη κορυφής
void DFS(int startVertexData);  // Εκτελεί αναζήτηση κατά βάθος (DFS) από δεδομένη τιμή δεδομένων κορυφής




 void DFS(Vertex* startVertex);
};





