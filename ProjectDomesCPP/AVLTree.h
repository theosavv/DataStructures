#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Κλάση για κάθε κόμβο του δέντρου
class TreeNode
{
public:
    int data;        //στοιχείο κόμβου
    TreeNode* left;  //Αριστερό παιδί
    TreeNode* right; //Δεξί παιδί
    int height;      //Υψος του AVL

    // Κατασκευαστής
    TreeNode(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
        height = 0;
    }
};

//Κλάση του  δένδρου AVL
class AVL
{
protected:

    //Δείκτης για την ρίζα του δέντρου AVL
    TreeNode* root;
    int Size;

public:

    // Κατασκευαστής
    AVL();

    // Βοηθητική συνάρτηση για την εισαγωγή ενός νέου κόμβου αναδρομικά
    TreeNode * Insert(TreeNode* root, int value);

    //Συνάρτηση κατασκευής του δέντρου AVL από το αρχείο filename
    TreeNode * BuildAVLTree(const string& filename);

    //Συναρτήσεις περιστροφών
    TreeNode * rotateLeft(TreeNode *node);
    TreeNode * rotateRight(TreeNode *node);

    //Getter για το υψος κάθε κόμβου (Αν είναι nullptr το υψος είναι -1)
    int height(TreeNode* node);

    //Επιστρέφει τη διαφορά του ύψους των δύο παιδιών του κόμβου
    int getBalanceFactor(TreeNode* node);

    //Getter για το size
    int getSize();

    //Επιστρέφεται "SUCCESS" αν υπάρχει το number ή "FAILURE" αν δεν υπάρχει το σοιχείο number στο δέντρο
    string searchNumber(int number,TreeNode * node);

    //Εύρεση ελαχίστου στοιχείου του δέντρου AVL
    int findMin(TreeNode * node);
    TreeNode *  deleteNode(TreeNode * node,int number);

    //Συνάρτηση που επιστρέφει την διεύθυνση του κόμβου που περιέχει το στοιχείο number
    TreeNode * findNode(int number,TreeNode * node);
    TreeNode * minValueNode(TreeNode * node);
    TreeNode * rebalanceAfterDelete(TreeNode * node);

    //Getter που επιστρέφει την διεύθυνση της ρίζας του δέντρου
    TreeNode * getRoot();
};
