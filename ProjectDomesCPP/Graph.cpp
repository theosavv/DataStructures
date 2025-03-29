#include "Graph.h"
#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>

using namespace std;

/////////////////////////////////////////////////////////////////

HashMap::HashMap(size_t initialCapacity) : capacity(initialCapacity), size(0) {
  table = new HashNode *[capacity]();  // Δέσμευση μνήμης για τον πίνακα με pointers σε HashNode, αρχικοποίηση σε nullptr
}

/////////////////////////////////////////////////////////////////

HashMap::~HashMap() {
  for (size_t i = 0; i < capacity; ++i) {
    HashNode *entry = table[i];
    while (entry != nullptr) {
      HashNode *prev = entry;
      entry = entry->next;
      delete prev;  // Απελευθέρωση μνήμης για κάθε HashNode στη λίστα αλυσίδων
    }
  }
  delete[] table;  // Απελευθέρωση του πίνακα
}

/////////////////////////////////////////////////////////////////

size_t HashMap::hashFunction(int key) {
  return key % capacity;  // Συνάρτηση κατακερματισμού για να υπολογίσει τον δείκτη στον πίνακα
}

/////////////////////////////////////////////////////////////////

void HashMap::resizeTable() {
  size_t newCapacity = capacity * 2;
  HashNode **newTable = new HashNode *[newCapacity]();  // Δημιουργία νέου διπλάσιου πίνακα
  for (size_t i = 0; i < capacity; ++i) {
    HashNode *entry = table[i];
    while (entry != nullptr) {
      HashNode *next = entry->next;
      size_t newIndex = entry->key % newCapacity;  // Υπολογισμός νέου δείκτη για κάθε κόμβο
      entry->next = newTable[newIndex];  // Εισαγωγή του κόμβου στο νέο πίνακα
      newTable[newIndex] = entry;
      entry = next;
    }
  }
  delete[] table;  // Απελευθέρωση του παλιού πίνακα
  table = newTable;  // Αντικατάσταση με το νέο πίνακα
  capacity = newCapacity;  // Ενημέρωση της χωρητικότητας
}

/////////////////////////////////////////////////////////////////

Vertex* HashMap::get(int key) {
  size_t hashIndex = hashFunction(key);
  HashNode *entry = table[hashIndex];
  while (entry != nullptr) {
    if (entry->key == key)
      return entry->value;  // Επιστροφή της τιμής που αντιστοιχεί στο κλειδί
    entry = entry->next;
  }
  return nullptr;  // Επιστροφή nullptr αν δεν βρεθεί το κλειδί
}

/////////////////////////////////////////////////////////////////

void HashMap::put(int key, Vertex* value) {
  size_t hashIndex = hashFunction(key);
  HashNode *entry = table[hashIndex];
  while (entry != nullptr) {
    if (entry->key == key) {
      entry->value = value;  // Ενημέρωση της τιμής αν το κλειδί υπάρχει ήδη
      return;
    }
    entry = entry->next;
  }
  entry = new HashNode(key, value);  // Δημιουργία νέου κόμβου αν το κλειδί δεν υπάρχει
  entry->next = table[hashIndex];
  table[hashIndex] = entry;
  size++;

  if (size >= capacity * 0.75) {  // Αν υπερβεί η γεμισμένη χωρητικότητα, αλλαγή μεγέθους
    resizeTable();
  }
}

/////////////////////////////////////////////////////////////////

void HashMap::remove(int key) {
  size_t hashIndex = hashFunction(key);
  HashNode *entry = table[hashIndex];
  HashNode *prev = nullptr;
  while (entry != nullptr) {
    if (entry->key == key) {
      if (prev == nullptr) {
        table[hashIndex] = entry->next;  // Αφαίρεση του κόμβου από τη λίστα αλυσίδων
      } else {
        prev->next = entry->next;
      }
      delete entry;  // Απελευθέρωση μνήμης του κόμβου
      size--;
      return;
    }
    prev = entry;
    entry = entry->next;
  }
}

/////////////////////////////////////////////////////////////////

size_t HashMap::getSize() {
  return size;  // Επιστροφή του μεγέθους του χάρτη
}

/////////////////////////////////////////////////////////////////
Graph::Graph() : SizeOfVerteces(0), SizeOfEdges(0), maxSizeOfVerteces(25000), vertexMap(25000) {
  graph = new Vertex *[maxSizeOfVerteces]();  // Δέσμευση μνήμης για τον πίνακα κορυφών του γράφου, αρχικοποίηση σε nullptr
}

/////////////////////////////////////////////////////////////////

Vertex::Vertex(int value)
    : data(value), sizeOfEdges(0), sizeOfWeights(0), maxSizeOfEdges(1000),
      maxSizeOfWeights(1000) {
  edges = new Vertex *[maxSizeOfEdges]();  // Δέσμευση μνήμης για τον πίνακα ακμών της κορυφής, αρχικοποίηση σε nullptr
  weights = new int[maxSizeOfWeights]();  // Δέσμευση μνήμης για τον πίνακα βαρών των ακμών της κορυφής, αρχικοποίηση σε 0
}

/////////////////////////////////////////////////////////////////

int Graph::getSizeOfVerteces() { return SizeOfVerteces; }  // Επιστρέφει τον αριθμό των κορυφών

/////////////////////////////////////////////////////////////////

int Graph::getSizeOfEdges() { return SizeOfEdges; }  // Επιστρέφει τον αριθμό των ακμών

/////////////////////////////////////////////////////////////////

Vertex* Graph::findVertex(int value) {
  return vertexMap.get(value);  // Αναζήτηση κορυφής με βάση την τιμή της
}

/////////////////////////////////////////////////////////////////

void Graph::resizeGraph() {
  maxSizeOfVerteces *= 2;  // Αύξηση του μέγιστου αριθμού κορυφών
  Vertex **tempArray = new Vertex *[maxSizeOfVerteces]();  // Δημιουργία νέου διπλάσιου πίνακα για τις κορυφές
  for (size_t i = 0; i < SizeOfVerteces; ++i) {
    tempArray[i] = graph[i];  // Αντιγραφή των κορυφών στον νέο πίνακα
  }
  delete[] graph;  // Απελευθέρωση του παλιού πίνακα
  graph = tempArray;  // Αντικατάσταση με το νέο πίνακα
}

/////////////////////////////////////////////////////////////////

void Graph::resizeVertexEdges(Vertex *vertex) {
  vertex->maxSizeOfEdges *= 2;  // Αύξηση του μέγιστου αριθμού ακμών της κορυφής
  Vertex **tempArray = new Vertex *[vertex->maxSizeOfEdges]();  // Δημιουργία νέου διπλάσιου πίνακα για τις ακμές
  for (size_t i = 0; i < vertex->sizeOfEdges; ++i) {
    tempArray[i] = vertex->edges[i];  // Αντιγραφή των ακμών στον νέο πίνακα
  }
  delete[] vertex->edges;  // Απελευθέρωση του παλιού πίνακα ακμών
  vertex->edges = tempArray;  // Αντικατάσταση με το νέο πίνακα ακμών
}

/////////////////////////////////////////////////////////////////

void Graph::resizeVertexWeights(Vertex *vertex) {
  vertex->maxSizeOfWeights *= 2;  // Αύξηση του μέγιστου αριθμού βαρών των ακμών της κορυφής
  int *tempArray = new int[vertex->maxSizeOfWeights]();  // Δημιουργία νέου διπλάσιου πίνακα για τα βάρη
  for (size_t i = 0; i < vertex->sizeOfWeights; ++i) {
    tempArray[i] = vertex->weights[i];  // Αντιγραφή των βαρών στον νέο πίνακα
  }
  delete[] vertex->weights;  // Απελευθέρωση του παλιού πίνακα βαρών
  vertex->weights = tempArray;  // Αντικατάσταση με το νέο πίνακα βαρών
}

/////////////////////////////////////////////////////////////////

void Graph::BuildGraph(const string &filename) {
  ifstream inputFile(filename);
  if (!inputFile.is_open()) {
    return;  // Αν το αρχείο δεν ανοίξει, τερματίζει τη συνάρτηση
  }
  int value1, value2, weight;
  while (inputFile >> value1 >> value2 >> weight) {
    Insert(value1, value2, weight);  // Εισαγωγή κόμβων και ακμών από το αρχείο
  }
  inputFile.close();  // Κλείσιμο του αρχείου εισόδου
}

/////////////////////////////////////////////////////////////////

void Graph::Insert(int value1, int value2, int weight) {
  Vertex *v1 = findVertex(value1);  // Αναζήτηση ή δημιουργία κόμβου με την τιμή value1
  Vertex *v2 = findVertex(value2);  // Αναζήτηση ή δημιουργία κόμβου με την τιμή value2

  if (!v1) {  // Αν ο κόμβος v1 δεν υπάρχει
    if (SizeOfVerteces == maxSizeOfVerteces) {  // Έλεγχος για αύξηση του μέγεθους του γράφου
      resizeGraph();
    }
    v1 = new Vertex(value1);  // Δημιουργία νέου κόμβου v1
    graph[SizeOfVerteces++] = v1;  // Προσθήκη του v1 στον πίνακα γράφου και αύξηση του μεγέθους των κορυφών
    vertexMap.put(value1, v1);  // Αποθήκευση του v1 στον χάρτη κορυφών
  }

  if (!v2) {  // Αν ο κόμβος v2 δεν υπάρχει
    if (SizeOfVerteces == maxSizeOfVerteces) {  // Έλεγχος για αύξηση του μέγεθους του γράφου
      resizeGraph();
    }
    v2 = new Vertex(value2);  // Δημιουργία νέου κόμβου v2
    graph[SizeOfVerteces++] = v2;  // Προσθήκη του v2 στον πίνακα γράφου και αύξηση του μεγέθους των κορυφών
    vertexMap.put(value2, v2);  // Αποθήκευση του v2 στον χάρτη κορυφών
  }

  for (size_t i = 0; i < v1->sizeOfEdges; ++i) {  // Έλεγχος για υπάρχουσες ακμές ανάμεσα στις κορυφές v1 και v2
    if (v1->edges[i] == v2) {
      return;  // Αν υπάρχει ήδη ακμή μεταξύ των κορυφών, τερματίζει τη συνάρτηση
    }
  }

  if (v1->sizeOfEdges == v1->maxSizeOfEdges) {  // Έλεγχος για αύξηση του μέγεθους των ακμών της κορυφής v1
    resizeVertexEdges(v1);
  }
  if (v1->sizeOfWeights == v1->maxSizeOfWeights) {  // Έλεγχος για αύξηση του μέγεθους των βαρών των ακμών της κορυφής v1
    resizeVertexWeights(v1);
  }
  v1->edges[v1->sizeOfEdges] = v2;  // Προσθήκη της ακμής v2 στη λίστα ακμών της κορυφής v1
  v1->weights[v1->sizeOfWeights] = weight;  // Προσθήκη του βάρους της ακμής στη λίστα βαρών της κορυφής v1
  v1->sizeOfEdges++;  // Αύξηση του μεγέθους των ακμών της κορυφής v1
  v1->sizeOfWeights++;  // Αύξηση του μεγέθους των βαρών των ακμών της κορυφής v1

  if (v2->sizeOfEdges == v2->maxSizeOfEdges) {  // Έλεγχος για αύξηση του μέγεθους των ακμών της κορυφής v2
    resizeVertexEdges(v2);
  }
  if (v2->sizeOfWeights == v2->maxSizeOfWeights) {  // Έλεγχος για αύξηση του μέγεθους των βαρών των ακμών της κορυφής v2
    resizeVertexWeights(v2);
  }
  v2->edges[v2->sizeOfEdges] = v1;  // Προσθήκη της ακμής v1 στη λίστα ακμών της κορυφής v2
  v2->weights[v2->sizeOfWeights] = weight;  // Προσθήκη του βάρους της ακμής στη λίστα βαρών της κορυφής v2
  v2->sizeOfEdges++;  // Αύξηση του μεγέθους των ακμών της κορυφής v2
  v2->sizeOfWeights++;  // Αύξηση του μεγέθους των βαρών των ακμών της κορυφής v2

  SizeOfEdges++;  // Αύξηση του μεγέθους των ακμών του γράφου
}

/////////////////////////////////////////////////////////////////

size_t Graph::getIndex(Vertex *vertex) {
  for (size_t i = 0; i < SizeOfVerteces; ++i) {
    if (graph[i] == vertex) {
      return i;  // Επιστροφή του δείκτη της κορυφής στον πίνακα γράφου
    }
  }
  return SizeOfVerteces;  // Επιστροφή μίας τιμής εκτός ορίων αν η κορυφή δεν βρεθεί
}

/////////////////////////////////////////////////////////////////


int Graph::getIndexByData(int data) {
  // Εύρεση κόμβου με βάση τα δεδομένα
  for (int i = 0; i < SizeOfVerteces; ++i) {
    if (graph[i]->data == data) {
      return i; // Επιστροφή δείκτη του κόμβου
    }
  }
  return -1; // Ο κόμβος δεν βρέθηκε
}

/////////////////////////////////////////////////////////////////

#include <queue> // Έτοιμες βιβλιοθήκες χρησιμοποιήθηκαν μόνο σε αυτό το σημείο για την getShortestPathCost
#include <unordered_map>
struct CompareDist {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
};

int Graph::getShortestPathCost(Vertex* Start, Vertex* End) {
  queue<Vertex*> q;
  unordered_map<Vertex*, int> distance;

  // Αρχικοποίηση των αποστάσεων
  for (int i = 0; i < SizeOfVerteces; ++i) {
    distance[graph[i]] = INT_MAX;
  }

  q.push(Start);
  distance[Start] = 0;

  while (!q.empty()) {
    Vertex* current = q.front();
    q.pop();

    // Εξερεύνηση των γειτόνων του τρέχοντος κόμβου
    for (int i = 0; i < current->sizeOfEdges; ++i) {
      Vertex* neighbor = current->edges[i];
      int weight = current->weights[i];

      // Ανανέωση της απόστασης αν είναι βελτιωτική
      if (distance[current] != INT_MAX && distance[current] + weight < distance[neighbor]) {
        distance[neighbor] = distance[current] + weight;
        q.push(neighbor);
      }
    }
  }

  // Επιστροφή της απόστασης ή -1 αν το τέλος δεν είναι προσβάσιμο
  return distance[End] != INT_MAX ? distance[End] : -1;
}

/////////////////////////////////////////////////////////////////


struct Edge {
  int srcIndex;
  int destIndex;
  int weight;
};

/////////////////////////////////////////////////////////////////

void swap(Edge *a, Edge *b) {
  Edge t = *a;
  *a = *b;
  *b = t;
}

/////////////////////////////////////////////////////////////////
int partition(Edge *edges, int low, int high) {
  int pivot = edges[high].weight;
  int i = low - 1;

  for (int j = low; j <= high - 1; j++) {

    if (edges[j].weight < pivot) {
      i++;
      swap(&edges[i], &edges[j]);
    }
  }
  swap(&edges[i + 1], &edges[high]);
  return (i + 1);
}

/////////////////////////////////////////////////////////////////


int Graph::find(int*& parent, int i) {
  if (parent[i] != i) {
    parent[i] = find(parent, parent[i]);
  }
  return parent[i];
}

/////////////////////////////////////////////////////////////////

void Graph::unite(int*& parent, int*& rank, int x, int y) {
  int rootX = find(parent, x);
  int rootY = find(parent, y);

  if (rootX != rootY) {
    if (rank[rootX] > rank[rootY]) {
      parent[rootY] = rootX;
    } else if (rank[rootX] < rank[rootY]) {
      parent[rootX] = rootY;
    } else {
      parent[rootY] = rootX;
      rank[rootX]++;
    }
  }
}

/////////////////////////////////////////////////////////////////

// Συνάρτηση για εύρεση του ελάχιστου κόστους ενός ελάχιστου συνδετικού δέντρου
int Graph::getMinimumSpanningTreeCost() {
  Edge *edges = new Edge[SizeOfEdges];
  int edgeCount = 0;

  // Συλλογή όλων των ακμών σε έναν πίνακα
  for (size_t i = 0; i < SizeOfVerteces; ++i) {
    Vertex *vertex = graph[i];
    for (size_t j = 0; j < vertex->sizeOfEdges; ++j) {
      Vertex *destVertex = vertex->edges[j];
      if (vertex->data < destVertex->data) {
        int destIndex = vertexMap.get(destVertex->data)->data;
        edges[edgeCount++] = {static_cast<int>(i), destIndex, vertex->weights[j]};
      }
    }
  }

  // Ταξινόμηση των ακμών βάσει του βάρους τους
  std::sort(edges, edges + edgeCount, [](const Edge& a, const Edge& b) {
      return a.weight < b.weight;
  });

  int *parent = new int[SizeOfVerteces];
  int *rank = new int[SizeOfVerteces];
  for (int i = 0; i < SizeOfVerteces; ++i) {
    parent[i] = i;
    rank[i] = 0;
  }

  int mstCost = 0;
  for (int i = 0; i < edgeCount; ++i) {
    int srcIndex = edges[i].srcIndex;
    int destIndex = edges[i].destIndex;
    int weight = edges[i].weight;

    int x = find(parent, srcIndex);
    int y = find(parent, destIndex);

    // Ένωση των συνόλων αν δεν ανήκουν στο ίδιο
    if (x != y) {
      mstCost += weight;
      unite(parent, rank, x, y);
    }
  }

  delete[] edges;
  delete[] parent;
  delete[] rank;

  // Επιστροφή του συνολικού κόστους του MST
  return mstCost;
}

/////////////////////////////////////////////////////////////////

// Συνάρτηση για διαγραφή ακμής μεταξύ δύο κόμβων
void Graph::deleteEdge(int value1, int value2) {
  Vertex *vertex1 = findVertex(value1);
  Vertex *vertex2 = findVertex(value2);

  if (!vertex1 || !vertex2)
    return; // Έξοδος αν ένας από τους κόμβους δεν υπάρχει

  bool edgeDeleted = false;

  // Αναζήτηση και διαγραφή της ακμής στον πρώτο κόμβο
  for (int i = 0; i < vertex1->sizeOfEdges; ++i) {
    if (vertex1->edges[i]->data == value2) {
      vertex1->edges[i] = nullptr;
      vertex1->weights[i] = 0;
      vertex1->sizeOfEdges--;
      vertex1->sizeOfWeights--;
      edgeDeleted = true;
      break;
    }
  }

  if (!edgeDeleted)
    return; // Έξοδος αν η ακμή δεν βρέθηκε στον πρώτο κόμβο

  // Αναζήτηση και διαγραφή της ακμής στον δεύτερο κόμβο
  for (int i = 0; i < vertex2->sizeOfEdges; ++i) {
    if (vertex2->edges[i]->data == value1) {
      vertex2->edges[i] = nullptr;
      vertex2->weights[i] = 0;
      vertex2->sizeOfEdges--;
      vertex2->sizeOfWeights--;
      break;
    }
  }

  SizeOfEdges--;
}

/////////////////////////////////////////////////////////////////

/*
#include <stack>
#include <vector>
void Graph::DFS(Vertex* startVertex) {
    // Initialize a stack for DFS
    std::stack<Vertex*> stack;
    stack.push(startVertex);

    // Initialize a hashmap to keep track of visited vertices
    HashMap visitedVertices(SizeOfVerteces); // Assuming HashMap has a constructor with initial capacity

    while (!stack.empty()) {
        Vertex* currentVertex = stack.top();
        stack.pop();

        // Check if the vertex has already been visited
        if (!visitedVertices.get(currentVertex->data)) {
            // Process the current vertex (e.g., mark as visited, perform operations)
            visitedVertices.put(currentVertex->data, currentVertex);

            // Traverse all adjacent vertices
            for (size_t i = 0; i < currentVertex->sizeOfEdges; ++i) {
                Vertex* adjacentVertex = currentVertex->edges[i];

                // If adjacent vertex is not visited, push it to the stack
                if (!visitedVertices.get(adjacentVertex->data)) {
                    stack.push(adjacentVertex);
                }
            }
        }
    }
}*/

/////////////////////////////////////////////////////////////////

int Graph::findConnectedComponents() {
   /* // Initialize an array to keep track of visited vertices
    bool* visited = new bool[SizeOfVerteces];
    for (size_t i = 0; i < SizeOfVerteces; ++i) {
        visited[i] = false;
    }

    int connectedComponentsCount = 0;

    // Traverse all vertices
    for (size_t i = 0; i < SizeOfVerteces; ++i) {
        if (!visited[i]) {
            // Start a new DFS traversal from this vertex
            DFS(graph[i]); // Here, graph[i] is a Vertex*, assuming graph is Vertex**
            connectedComponentsCount++;
        }
    }

    delete[] visited;
    return connectedComponentsCount; */
    return -1;
}

/////////////////////////////////////////////////////////////////

/*
void Graph::DFS(int vertexIndex, bool visited[]) {
    // Stack-based iterative DFS implementation
    std::stack<int> stack;
    stack.push(vertexIndex);
    visited[vertexIndex] = true;

    while (!stack.empty()) {
        int currentVertexIndex = stack.top();
        stack.pop();

        // Process the current vertex
        Vertex* vertex = graph[currentVertexIndex];
        // Optionally, perform operations on 'vertex' here

        // Traverse all adjacent vertices
        for (size_t i = 0; i < vertex->sizeOfEdges; ++i) {
            Vertex* adjacentVertex = vertex->edges[i];
            size_t adjacentVertexIndex = getIndex(adjacentVertex);

            // If adjacent vertex is not visited, visit it and push to stack
            if (!visited[adjacentVertexIndex]) {
                visited[adjacentVertexIndex] = true;
                stack.push(adjacentVertexIndex);
            }
        }
    }
}*/

/////////////////////////////////////////////////////////////////
