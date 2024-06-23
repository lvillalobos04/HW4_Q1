// Luis M. Villalobos (1224922959)
// CSE310 - Recitation 4

#include <iostream>
#include <cstdlib>
using namespace std;

class BinarySearchTree
{
    private:
        class node
        {
        public:
            node* left;
            node* right;
            node* parent;
            int key;
            string data;
        };

    public:
        node* root;
        BinarySearchTree()
        {
        root = NULL;
        }

        bool isEmpty() const { return root == NULL; }
        void INORDER_TREE_WALK(node*);
        void TREE_INSERT(int);
        void PREORDER_TRAVERSAL(node *);
        void POSTORDER_TRAVERSAL(node *);
        int FINDMAX(node *x);
        void REMOVEMAX(node* x);
        int TREESUCCESSOR(node* x, int key);
        int FINDMIN(node* x);
        void TRANSPLANT(node* u, node* v);
        node* FINDMINNODE(node* x);
        void DELETENODE(node* x, int key);
};

void BinarySearchTree::TREE_INSERT(int d)
{
    // This implements the algorithm in page 261 of the textbook
    node* z = new node();
    z->key = d;
    z->left = NULL;
    z->right = NULL;
    node* y = NULL;
    node* x = root;
    node* parent = NULL;

    while (x != NULL)
    {
    y = x;
    if (z->key < x->key)
    x = x->left;
    else
    x = x->right;
    }

    z->parent = y;
    if (y == NULL)
    root = z;
    else if (z->key < y->key)
    y->left = z;
    else
    y->right = z;
}

void BinarySearchTree::INORDER_TREE_WALK(node* x)
{
    if (x != NULL)
    {
    if (x->left) INORDER_TREE_WALK(x->left);
    cout << " " << x->key << " ";
    if (x->right) INORDER_TREE_WALK(x->right);
    }
}

void BinarySearchTree::PREORDER_TRAVERSAL(node* x) // Pre-Order Traversal function with bst.root as argument
{
    if (x != NULL) // if BST is not empty, we pre-order traverse
    {
    cout << " " << x->key << " "; // print the root
    if (x->left) PREORDER_TRAVERSAL(x->left); // after root, we print all left subtree elements
    if (x->right) PREORDER_TRAVERSAL(x->right); // and lastly, the right subtree nodes
    }
}

void BinarySearchTree::POSTORDER_TRAVERSAL(node* x) // Post-Order Traversal function with bst.root as argument
{
    if (x != NULL) // if BST is not empty, we perform Post-order Traversal
    {
        if (x->left) POSTORDER_TRAVERSAL(x->left); // first print out left subtree
        if (x->right) POSTORDER_TRAVERSAL(x->right); // secondly print out the right subtree
        cout << " " << x->key << " "; // and lastly, print out the root
    }
}

int BinarySearchTree::FINDMAX(node *x)
{
    while (x->right != NULL) // if BST has right subtree, go through it until we find NULL
    {
        x = x->right; // x is going through the greater keys to get to the max
    }
    return x->key; // simply return the max value found at the bottom of right subtree
}

int BinarySearchTree::FINDMIN(node* x) // helper function to complete my successor function
{
    while (x->left != NULL) // same as FINDMAX function except this one finds min
    {
        x = x->left;
    }
    return x->key;
}

int BinarySearchTree::TREESUCCESSOR(node* x, int key) // finding successor function with bst.root and the key as arguments
{
    // this code was inspired by the pseudocode of the successor function in the book

    // searching for the node that has the key the user inputted:
    while (x != NULL)
    {
        if (key < x->key)
        {
            x = x->left;
        }

        else if (key > x->key)
        {
            x = x->right;
        }

        else
        {
            break;
        }
    }

    // if none of the nodes in our BST contain the key, then just notify user
    if (x == NULL)
        {
            cout << "Key doesn't exist " << endl;
        }


    if (x->right != NULL) // else if node with the key has a right subtree,
    {
        return FINDMIN(x->right); // then return the leftmost ndoe of the right subtree
    }

    else // we need to find the lowest ancestor of x whose left child is an ancestor of x
    {
        // creating new nodes to be able to find the successor if we get to this else statement 
        node* y = new node(); 
        y = x->parent;
        

        while ((y != NULL) && (x == y->right)) // two conditions that indicates that we can move and get closer to find/s/ing the successor
        {
            x = y;
            y = y->parent;
        }
        return y->key;  
    }
}

BinarySearchTree::node* BinarySearchTree::FINDMINNODE(node* x) // FINDMIN function but returns the node as helper for DELETENODE
{
    while (x->left != NULL) // same as FINDMIN function except this one returns the node and not the key
    {
        x = x->left;
    }
    return x;
}

void BinarySearchTree::TRANSPLANT(node* u, node* v) // helper function that helps us successfully delete the node
{   // this code is inspired on the pseudocode of the Transplant function in the book
    // its function is to help us move the tree when deleting nodes
    if (u->parent == NULL)
    {
        root = v;
    }

    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }

    else 
    {
        u->parent->right = v;
    }

    if (v != NULL)
    {
        v->parent = u->parent;
    }
}

void BinarySearchTree::DELETENODE(node* x, int key)
{
    // searching for the node that has the key the user inputted:
    while (x != NULL)
    {
        if (key < x->key)
        {
            x = x->left;
        }

        else if (key > x->key)
        {
            x = x->right;
        }

        else
        {
            break;
        }
    }

    // if none of the nodes in our BST contain the key, then just notify user
    if (x == NULL)
        {
            cout << "Key doesn't exist " << endl;
        }

    if (x->left == NULL)
    {
        TRANSPLANT(x, x->right); // call Transplant
    }

    else if (x->right == NULL)
    {
        TRANSPLANT(x, x->left); // call Transplant
    }

    else
    {
        node* y = new node(); // helper node to delete
        y = FINDMINNODE(x->right);

        if (y != x->right)
        {
            TRANSPLANT(x, x->right);
            y->right = x->right;
            y->right->parent = y;
        }

        TRANSPLANT(x, y);
        y->left = x->left;
        y->left->parent = y;
    }

}

int main()
{
    BinarySearchTree bst;
    int choice, key, tempMax;

    while (true)
    {
    cout << endl << endl;
    cout << " Binary Search Tree Example " << endl;
    cout << " ----------------------------- " << endl;
    cout << " 1. Insert a Node " << endl;
    cout << " 2. Pre-Order Traversal " << endl;
    cout << " 3. Post-Oreder Traversal " << endl;
    cout << " 4. In-Order Traversal " << endl;
    cout << " 5. Find Max " << endl;
    cout << " 6. Remove Max " << endl;
    cout << " 7. Successor " << endl;
    cout << " 8. Delete a Node " << endl;
    cout << " 9. Exit " << endl;
    cout << " Enter your choice : ";
    cin >> choice;

    switch (choice)
    {
    case 1: cout << " Enter key (int value) to be inserted : ";
    cin >> key;
    bst.TREE_INSERT(key);
    break;

    case 2: cout << endl;
    cout << " Pre-Order Traversal " << endl;
    cout << " --------------------" << endl;
    bst.PREORDER_TRAVERSAL(bst.root); // calling the Pre-Order traversal function with our BST
    break;

    case 3: cout << endl;
    cout << " Post-Order Traversal " << endl;
    cout << " ---------------------" << endl;
    bst.POSTORDER_TRAVERSAL(bst.root);// call the Pre-order traversal on our BST
    break;

    case 4: cout << endl;
    cout << " In-Order Traversal " << endl;
    cout << " -------------------" << endl;
    bst.INORDER_TREE_WALK(bst.root); // In-order traversal was already implemented in file provided
    break;

    case 5: cout << endl;
    cout << " Finding Max... " << endl;
    cout << "----------------" << endl;
    cout << "The max is: " << bst.FINDMAX(bst.root) << endl;// calling FINDMAX function so we can return and print
    break;

    case 6: cout << endl;
    cout << " Removing Max... " << endl;
    cout << " ----------------" << endl;
    tempMax = bst.FINDMAX(bst.root); // simply set a temp to display it the results
    bst.DELETENODE(bst.root, bst.FINDMAX(bst.root)); // call the delete node function on the max that was implemented for case 8
    cout << " The max: " << tempMax << " has now been removed " << endl;
    break;

    case 7: cout << endl;
    cout << "Enter a node (int value existing in tree) to find its successor " << endl;
    cin >> key;
    // having the key, call the successor function with it to find it
    cout << "Successor of " << key << " is " << bst.TREESUCCESSOR(bst.root, key) << endl;
    break;

    case 8: cout << endl;
    cout << "Enter the node (int value existing in tree) that you would like to remove" << endl;
    cin >> key;
    bst.DELETENODE(bst.root, key); // call the removing node function here
    cout << "The node with the value " << key << " has now been removed " << endl; 
    break;

    case 9: cout << endl;
    cout << "Thank you! Now exiting... " << endl;
    system("pause");
    return 0;
    break;

    default:
    cout << "Invalid choice, select an option between 1 and 9!";
    }

    }

    // Document said to specifically test these operations:
    // Successor of 6 should display 7
    // Successor of 13 should display 15
    // Delete 13 and then run in-order traversal to check if the resulting BST is correct.
    // Delete 6 and then run in-order traversal to check if the resulting BST is correct.

    // Results -> 
    // Successor of 6 is 7
    // Successor of 13 is 15
    // In-Order Traversal (with 13 and 6 already deleted):
    // 2  3  4  7  9  15  17  18  20 

}