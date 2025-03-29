#include <algorithm>
#include <fstream>
#include <iostream>
#include "AVLTree.h"

using namespace std;

/////////////////////////////////////////////////////////////////

//Κατασκευαστής
AVL::AVL()
{
    root = nullptr;
    Size=0;
}

/////////////////////////////////////////////////////////////////

TreeNode * AVL :: getRoot()
{
    return root;
}

/////////////////////////////////////////////////////////////////

//Βοηθητική συνάρτηση για την εισαγωγή ενός κόμβου στο δέντρο αναδρομικά
TreeNode* AVL::Insert(TreeNode* node, int value)
{
    if (node == nullptr)
    {
        Size++;
        return new TreeNode(value);
    }

    if (value < node->data)
    {
        node->left = Insert(node->left, value);
    }
    else
    {
        node->right = Insert(node->right, value);
    }

    //Ένημέρωση του ύψους του τρέχον κόμβου
    node->height = 1 + max(height(node->left), height(node->right));

    //Ελέγχουμε αν το δένδρο είναι ισορροπημένο και υλοποιούμε περιατροφές αν είναι αναγκαίο
    int balanceFactor = getBalanceFactor(node);

    //Απλή δεξιά περιστροφή
    if (balanceFactor > 1 && value < node->left->data)
        return rotateRight(node);

    //Απλή αριστερή περιστροφή
    if (balanceFactor < -1 && value > node->right->data)
        return rotateLeft(node);

    //Διπλή δεξιά περιστροφή
    if (balanceFactor < -1 && value < node->right->data)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    //Διπλή αριστερή περιστροφή
    if (balanceFactor > 1 && value > node->left->data)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

    return node;
}

/////////////////////////////////////////////////////////////////

//Βοηθητική συνάρτηση για τον υπολογισμό του ύψους του AVL
int AVL::height(TreeNode* node)
{
    if (node == nullptr)
    {
        return -1;
    }
    else
    {
        return node->height;
    }
}

/////////////////////////////////////////////////////////////////

//Βοηθητική συνάρτηση που επιστρέφει τον παράγοντα ισορροπίας ενός κόμβου
int AVL::getBalanceFactor(TreeNode* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return height(node->left) - height(node->right);
}

/////////////////////////////////////////////////////////////////

//Βοηθητική συνάρτηση για την πραγματοποίηση  αριστερής περιστροφής
TreeNode* AVL::rotateLeft(TreeNode* y)
{
    TreeNode* x = y->right;
    TreeNode* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

/////////////////////////////////////////////////////////////////

//Βοηθητική συνάρτηση για την πραγματοποίηση δεξιάς περιστροφής
TreeNode* AVL::rotateRight(TreeNode* x)
{
    TreeNode* y = x->left;
    TreeNode* T2 = y->right;

    y->right = x;
    x->left = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

/////////////////////////////////////////////////////////////////

int AVL::getSize()
{
    return Size;
}

/////////////////////////////////////////////////////////////////

//Αναζήτηση ενός αριθμού number
string AVL::searchNumber(int number,TreeNode * node)
{
    if(number==node->data)
        return "SUCCESS";

    //Αν ο κόμβος δεν έχει αριστερό παιδί και το number είναι μικρότερο του data, το number δεν υπάρχει
    if(number<node->data && node->left==nullptr)
    {
        return "FAILURE";
    }

    //Αν ο κόμβος δεν έχει δεξί παιδί και το number είναι μεγαλύτερο του data, το number δεν υπάρχει
    if(number>node->data && node->right==nullptr)
    {
        return "FAILURE";
    }

    if (number < node->data)
    {
        return searchNumber(number,node->left);
    }
    else
    {
        return searchNumber(number,node->right);
    }
}

/////////////////////////////////////////////////////////////////

//Επιστρέφει το ελάχιστο στοιχείο του δέντρου
int AVL::findMin(TreeNode * node)
{
    if(node->left==nullptr)
        return node->data;
    return findMin(node->left);
}

/////////////////////////////////////////////////////////////////

//Επιστρέφει τη διεύθυνση του ελάχιστου στοιχείου του AVL
TreeNode * AVL:: minValueNode(TreeNode * node)
{
    while(node && node->left!=nullptr)
    {
        node = node->left;
    }
    return node;
}

/////////////////////////////////////////////////////////////////

//Συνάρτηση διαγραφής κόμβου από το δέντρο
TreeNode * AVL::deleteNode(TreeNode * node,int number)
{

    if (node == nullptr)
    {
        return node;
    }
    else if (number<node->data)
        node->left = deleteNode(node->left, number);
    else if (number>node->data)
        node-> right = deleteNode(node->right, number);
    else
    {
                //Για ένα ή κανένα παιδί, απλή διαγραφή του κόμβου
                if(node->left==nullptr && node->right == nullptr)
                {
                    delete node;
                    Size--;
                    node=nullptr;
                }
                else if(node->left==nullptr)
                {
                    TreeNode * temp=node;
                    node=node->right;
                    delete temp;
                    Size--;
                }
                else if(node->right==nullptr)
                {
                    TreeNode * temp=node;
                    node=node->left;
                    delete temp;
                    Size--;
                }
                else
                {
                    //Αν το κόμβο έχει δύο παιδιά, αναδιατάσουμε το δένδρο
                    TreeNode * temp= minValueNode(node->right);
                    node->data = temp->data;
                    node->right = deleteNode(node->right,temp->data);

                }
    }
    return node;
}

/////////////////////////////////////////////////////////////////

TreeNode * AVL:: rebalanceAfterDelete(TreeNode * node)
{
                node->height = 1 + max(height(node->left), height(node->right));

                // Έλεγχος του παράγοντα ισορροπίας και πραγματοποίηση περιστροφών αν είναι απαραίτητο
                int balanceFactor = getBalanceFactor(node);

                // Απλή δεξιά περιστροφή
                if (balanceFactor > 1 && node->data < node->left->data)
                    return rotateRight(node);

                // Απλή αριστερή περιστροφή
                if (balanceFactor < -1 && node->data > node->right->data)
                    return rotateLeft(node);

                // Διπλή δεξιά περιστροφή
                if (balanceFactor > 1 && node->data > node->left->data)
                {
                    node->left = rotateLeft(node->left);
                    return rotateRight(node);
                }

                // Διπλή αριστερή περιστροφή
                if (balanceFactor < -1 && node->data < node->right->data)
                {
                    node->right = rotateRight(node->right);
                    return rotateLeft(node);
                }

    return node;
}

/////////////////////////////////////////////////////////////////

//Συνάρτηση κατασκευής δέντρου διαβάζοντας στοιχεία από το αρχείο filename
TreeNode* AVL::BuildAVLTree(const string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file " << filename << endl;
        return nullptr;
    }
    int fileData;
    while (file >> fileData)
    {
        root = Insert(root, fileData);
    }
    file.close();

    return root;

}

/////////////////////////////////////////////////////////////////
