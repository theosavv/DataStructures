#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

#include "minHeap.h"
#include "maxHeap.h"
#include "AVLTree.h"
#include "Graph.h"
#include "Hashtable.h"

using namespace std;

int main()
{
    minHeap myMinHeap;
    maxHeap myMaxHeap;
    AVL myAVLTree;
    Graph myGraph;
    Hashtable myHashTable;

    ifstream file("commands.txt");
    ofstream outputFile("output.txt");
    if (file.is_open())
    {
        string line;

        while(getline(file,line))
        {


            istringstream iss(line);
            string firstWord,secondWord;
            iss>>firstWord>>secondWord;
            if (firstWord== "BUILD")
            {
                string filename;
                iss>>filename;
                if(secondWord == "MINHEAP")
                {
                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Kατασκευή σωρού ελαχίστων διαβάζοντας τα στοιχεία από το αρχείο filename.
                    myMinHeap.readData( filename );
                    myMinHeap.buildMinHeap();

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;

                    outputFile<<"MinHeap successfully build!\t" <<"Execution time: "<<duration.count()<<" seconds."<<endl;
                }
                else if (secondWord == "MAXHEAP")
                {
                     std::chrono::steady_clock::time_point start, end;
                     start = std::chrono::steady_clock::now();

                     //Kατασκευή σωρού μεγίστων διαβάζοντας τα στοιχεία από το αρχείο filename.
                     myMaxHeap.readData(filename);
                     myMaxHeap.buildMaxHeap();

                     end = std::chrono::steady_clock::now();
                     chrono::duration<double> duration = end - start;

                     outputFile<<"MaxHeap successfully build!\t" <<"Execution time: "<<duration.count()<<" seconds."<<endl;
                }
                else if (secondWord == "AVLTREE")
                {
                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Kατασκευή δυαδικού δένδρου αναζήτησης AVL διαβάζοντας τα στοιχεία από το αρχείο filename.
                    myAVLTree.BuildAVLTree(filename);

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;

                    outputFile<<"AVL Tree successfully build!\t" <<"Execution time: "<<duration.count()<<" seconds."<<endl;
                }
                else if (secondWord == "GRAPH")
                {
                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Kατασκευή γραφήματος διαβάζοντας τα στοιχεία από το αρχείο filename.
                    myGraph.BuildGraph(filename);

                    end = std::chrono::steady_clock::now();
                    std::chrono::duration<double> duration = end - start;

                    outputFile<<"Graph  successfully build!\t" <<"Execution time: "<<duration.count()<<" seconds."<<endl;
                }
                else if (secondWord == "HASHTABLE")
                {
                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Kατασκευή πίνακα κατακερματισμού διαβάζοντας τα στοιχεία από το αρχείο filename.
                    myHashTable.buildHashtable(filename);

                    end = std::chrono::steady_clock::now();
                    std::chrono::duration<double> duration = end - start;

                    outputFile<<"Hashtable successfully build!\t" <<"Execution time: "<<duration.count()<<" seconds."<<endl;
                }
            }
            else if (firstWord == "GETSIZE")
            {
                if(secondWord== "MINHEAP")
                {
                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Επιστρέφει το πλήθος των στοιχείων της σωρού ελαχίστων.
                    int minHeapSize = myMinHeap.getSize();
                    end = std::chrono::steady_clock::now();

                    chrono::duration<double> duration = end - start;
                    outputFile<<"Size of MinHeap: "<<minHeapSize <<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
                }
                else if ( secondWord == "MAXHEAP")
                {
                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Επιστρέφει το πλήθος των στοιχείων της σωρού μεγίστων.
                    int maxHeapSize = myMaxHeap.getSize();

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;
                    outputFile<<"Size of MaxHeap: "<<maxHeapSize <<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
                }
                else if (secondWord =="AVLTREE")
                {
                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Επιστρέφει το πλήθος των στοιχείων του δυαδικού δένδρου αναζήτησης AVL.
                    int avlTreeSize = myAVLTree.getSize();

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;

                    outputFile<<"Size of AVL Tree: "<<avlTreeSize <<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
                }
                else if (secondWord =="GRAPH")
                {
                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Επιστρέφει δύο τιμές: το πλήθος των κορυφών(getSizeOfVerteces) και το πλήθος των ακμών(getSizeOfEdges).
                    int vertecesSize = myGraph.getSizeOfVerteces();
                    int edgesSize = myGraph.getSizeOfEdges();

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;

                    outputFile<<"Size of Graph Verteces: "<<vertecesSize<<"\tSize of Graph Edges: "<<edgesSize<<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
                }
                else if (secondWord =="HASHTABLE")
                {
                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Επιστρέφει το πλήθος των στοιχείων του πίνακα κατακερματισμού.
                    int hashTableSize = myHashTable.getSize();

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;

                    outputFile<<"Size of hashTable Tree: "<<hashTableSize <<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
                }
            }
            else if (firstWord == "FINDMIN")
            {
                if(secondWord == "MINHEAP")
                {
                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Eύρεση του ελάχιστου στοιχείου από τη σωρό ελαχίστων.
                    int minMinHeap = myMinHeap.findMin();

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;

                    outputFile<<"Min of MinHeap: "<<minMinHeap <<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
                }
                else if (secondWord == "AVLTREE")
                {
                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Eύρεση του ελάχιστου στοιχείου από το δυαδικό δένδρο αναζήτησης AVL.
                    int minAVLTree = myAVLTree.findMin(myAVLTree.getRoot());

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;

                    outputFile<<"Min of AVL Tree: "<<minAVLTree <<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
                }
            }
            else if (firstWord == "FINDMAX" && secondWord == "MAXHEAP")
            {
                std::chrono::steady_clock::time_point start, end;
                start = std::chrono::steady_clock::now();

                //Eύρεση του μέγιστου στοιχείου από τη σωρό μεγίστων.
                int maxMaxHeap = myMaxHeap.findMax();

                end = std::chrono::steady_clock::now();
                chrono::duration<double> duration = end - start;

                outputFile<<"Max of MaxHeap: "<<maxMaxHeap <<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
            }
            else if (firstWord == "SEARCH")
            {
                int number;
                iss>>number;
                if(secondWord == "AVLTREE")
                {
                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Aναζήτηση του στοιχείου number στο δυαδικό δένδρο αναζήτησης AVL. Αν το στοιχείο υπάρχει, επιστρέφεται η συμβολοσειρά SUCCESS αλλιώς FAILURE.
                    string searchResult = myAVLTree.searchNumber(number,myAVLTree.getRoot());

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;

                    outputFile<<"Result of searching number "<<number<<" in AVL Tree: "<<searchResult <<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
                }
                else if (secondWord == "HASHTABLE")
                {
                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Aναζήτηση του στοιχείου number στον πίνακα.
                    string searchResult = myHashTable.search(number);

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;

                    outputFile<<"Result of searching number "<<number<<" in Hashtable: "<<searchResult <<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
                }
            }
            else if (firstWord == "COMPUTESHORTESTPATH" && secondWord == "GRAPH")
            {
                int number1,number2;
                iss>>number1>>number2;

                std::chrono::steady_clock::time_point start, end;
                start = std::chrono::steady_clock::now();

                //Υπολογίζει το κόστος της ελάχιστης διαδρομής από τον κόμβο number1 στον κόμβο number2.
                int shortestGraphPathCost = myGraph.getShortestPathCost(myGraph.findVertex(number1),myGraph.findVertex(number2));

                end = std::chrono::steady_clock::now();
                chrono::duration<double> duration = end - start;

                outputFile<<"Shortest path cost from vertex "<<number1<<" to vertex "<<number2<<" : "<<shortestGraphPathCost <<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
            }
            else if (firstWord == "COMPUTESPANNINGTREE" && secondWord == "GRAPH")
            {
                std::chrono::steady_clock::time_point start, end;
                start = std::chrono::steady_clock::now();

                //Υπολογίζει το κόστος των ελάχιστου εκτεινόμενου δένδρου του γραφήματος και το επιστρέφει.
                int minSpanningTreeCost = myGraph.getMinimumSpanningTreeCost();

                end = std::chrono::steady_clock::now();
                chrono::duration<double> duration = end - start;

                outputFile<<"Shortest spanning tree cost: "<<minSpanningTreeCost <<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
            }
            else if (firstWord == "FINDCONNECTEDCOMPONENTS" && secondWord == "GRAPH")
            {
                std::chrono::steady_clock::time_point start, end;
                start = std::chrono::steady_clock::now();

                //Υπολογίζει το πλήθος των συνεκτικών συνιστωσών του γραφήματος και επιστρέφει τον αριθμό αυτό.
                int connectedComponents = myGraph.findConnectedComponents();

                end = std::chrono::steady_clock::now();
                chrono::duration<double> duration = end - start;

                outputFile<<"Fount "<<connectedComponents<<" connected components in Graph.\tExecution time: "<<duration.count()<<" seconds."<<endl;
            }
            else if (firstWord == "INSERT")
            {
                if(secondWord == "MINHEAP")
                {
                    int number;
                    iss>>number;

                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Εισάγει τον αριθμό number στη σωρό ελαχίστων.
                    myMinHeap.insertNode(number);

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;

                    outputFile<<"Inserted number "<<number<<" to MinHeap."<<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
                }
                else if (secondWord == "MAXHEAP")
                {
                    int number;
                    iss>>number;

                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Εισάγει τον αριθμό number στη σωρό μεγίστων.
                    myMaxHeap.insertNode(number);

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;

                    outputFile<<"Inserted number "<<number<<" to MaxHeap."<<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
                }
                 else if (secondWord == "AVLTREE")
                {
                    int number;
                    iss>>number;

                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Εισάγει τον αριθμό number στο δυαδικό δένδρο αναζήτησης AVL.
                    myAVLTree.Insert(myAVLTree.getRoot(),number);

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;

                    outputFile<<"Inserted number "<<number<<" to AVL Tree."<<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
                }
                else if (secondWord == "HASHTABLE")
                {
                    int number;
                    iss>>number;

                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Εισάγει τον αριθμό number στο πίνακα κατακερματισμού.
                    myHashTable.insert(number);

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;

                    outputFile<<"Inserted number "<<number<<" to Hashtable."<<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
                }
                else if (secondWord == "GRAPH")
                {
                    int number1,number2,weight;
                    iss>>number1>>number2>>weight;

                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Εισάγει την ακμή <number1, number2> στο γράφημα αν η ακμή δεν υπάρχει.
                    myGraph.Insert(number1,number2,weight);

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;

                    outputFile<<"Inserted edge "<<number1<<"-"<<number2<<" to Graph if it did not exist."<<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
                }

            }
            else if (firstWord == "DELETEMIN" && secondWord=="MINHEAP")
            {
                std::chrono::steady_clock::time_point start, end;
                start = std::chrono::steady_clock::now();

                //Διαγραφή ελαχίστου από τη σωρό ελαχίστων.
                myMinHeap.deleteMin();
                end = std::chrono::steady_clock::now();
                chrono::duration<double> duration = end - start;

                outputFile<<"Deleted min from MinHeap."<<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
            }
            else if (firstWord =="DELETEMAX" && secondWord=="MAXHEAP")
            {
                std::chrono::steady_clock::time_point start, end;
                start = std::chrono::steady_clock::now();

                //Διαγραφή μεγίστου από τη σωρό μεγίστων.
                myMaxHeap.deleteMax();

                end = std::chrono::steady_clock::now();
                chrono::duration<double> duration = end - start;

                outputFile<<"Deleted max from MaxHeap."<<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
            }
            else if (firstWord == "DELETE")
            {
                if(secondWord == "AVLTREE")
                {
                    int number;
                    iss>>number;

                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Διαγραφή στοιχείου number από δυαδικό δένδρο αναζήτησης AVL.
                    myAVLTree.deleteNode(myAVLTree.getRoot(),number);
                    myAVLTree.rebalanceAfterDelete(myAVLTree.getRoot());

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;

                    outputFile<<"Deleted number "<<number<<" from AVL Tree."<<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
                }
                else if (secondWord == "GRAPH")
                {
                    int number1,number2;
                    iss>>number1>>number2;

                    std::chrono::steady_clock::time_point start, end;
                    start = std::chrono::steady_clock::now();

                    //Διαγραφή της ακμής <number1, number2> από το γράφημα εάν υπάρχει.
                    myGraph.deleteEdge(number1,number2);

                    end = std::chrono::steady_clock::now();
                    chrono::duration<double> duration = end - start;

                    outputFile<<"Deleted edge "<<number1<<"-"<<number2<<" from Graph if it existed."<<"\tExecution time: "<<duration.count()<<" seconds."<<endl;
                }
            }
        }
        file.close();

        //τυπώνει στο output.txt ότι η διαδικασία τελείωσε
        outputFile<<"Program Successfully finished. "<<endl;
        outputFile.close();
    }
    else
    {
        outputFile<<"Could not open commands.txt ."<<endl;
    }
    cout<<"Program Successfully terminated. "<<endl;
    return 0;

}
