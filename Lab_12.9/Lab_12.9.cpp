#include <iostream>

using namespace std;

struct Node
{
    Node* left,
        * right;
    int info;
};

Node* CreateTree(int nodeCount)
{
    if (nodeCount == 0)
        return NULL;
    else
    {
        Node* newNode = new Node;
        cout << " Enter node value: ";
        cin >> newNode->info;
        int leftCount = nodeCount / 2;
        int rightCount = nodeCount - leftCount - 1;
        newNode->left = CreateTree(leftCount);
        newNode->right = CreateTree(rightCount);
        return newNode;
    }
}

Node* BinarySearchInsert(Node*& root, int value, bool& found)
{
    Node* current = root, * parent = current;
    found = false;
    while (current != NULL && !found)
    {
        if (value == current->info)
        {
            found = true;
            return current;
        }
        else
        {
            parent = current;
            if (value < current->info)
                current = current->left;
            else
                current = current->right;
        }
    }
    current = new Node;
    current->info = value;
    current->left = NULL;
    current->right = NULL;
    found = false;
    if (parent != NULL)
    {
        if (value < parent->info)
            parent->left = current;
        else
            parent->right = current;
    }
    if (root == NULL)
        root = current;
    return current;
}

Node* FindMax(Node* root) {
    if (root->right != NULL)
        return FindMax(root->right);
    else
        return root;}

Node* BinarySearchDelete(Node* root, int value)
{
    if (NULL == root) return NULL;
    if (root->info == value)
    {
        if (NULL == root->left && NULL == root->right)
        {
            delete root;
            return NULL;
        }
        if (NULL == root->right && root->left != NULL)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        if (NULL == root->left && root->right != NULL)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        root->info = FindMax(root->left)->info;
        root->left = BinarySearchDelete(root->left, root->info);
        return root;
    }
    if (value < root->info)
    {
        root->left = BinarySearchDelete(root->left, value);
        return root;
    }
    if (value > root->info)
    {
        root->right = BinarySearchDelete(root->right, value);
        return root;
    }
    return root;
}

void PrintTree(Node* root, int level)
{
    if (root != NULL)
    {
        PrintTree(root->right, level + 1);
        for (int i = 1; i <= level; i++)
            cout << " ";
        cout << root->info << endl;
        PrintTree(root->left, level + 1);
    }
}

void RightRotation(Node*& root)
{
    Node* tmp1 = root->left;
    Node* tmp2 = tmp1->right;
    tmp1->right = root; 
    root->left = tmp2; 
    root = tmp1; 
}

void LeftRotation(Node*& root)
{
    Node* tmp1 = root->right;
    Node* tmp2 = tmp1->left;
    tmp1->left = root;
    root->right = tmp2;
    root = tmp1;
}


int Height(Node* root)
{
    if (root == NULL)
        return 0;
    int hL = Height(root->left);
    int hR = Height(root->right);
    return (hL > hR ? hL : hR) + 1;
}

int BFactor(Node* root)
{
    return Height(root->right) - Height(root->left);
}

void BalanceHeight(Node*& root)
{
    if (root != NULL)
    {
        while (BFactor(root) >= 2)
        {
            if (BFactor(root->right) < 0)
                RightRotation(root->right);
            LeftRotation(root);
        }
        while (BFactor(root) <= -2)
        {
            if (BFactor(root->left) > 0)
                LeftRotation(root->left);
            RightRotation(root);
        }
        BalanceHeight(root->left);
        BalanceHeight(root->right);
    }
}

int Count(Node* root)
{
    if (root == nullptr)
        return 0;

    int count = 1;

    count += Count(root->left); 
    count += Count(root->right); 

    return count;
}


void BalanceCount(Node*& root)
{
    if (root != NULL)
    {
        while (Count(root->left) > Count(root->right) + 1)
        {
            RightRotation(root);
        }
        while (Count(root->left) + 1 < Count(root->right))
        {
            LeftRotation(root);
        }
        BalanceCount(root->left);
        BalanceCount(root->right);
    }
}

//int CountParentsWithValueK(Node* node, int k)
//{
//    if (node == nullptr)
//        return 0;
//
//    int count = 0;
//
//    if (node->left != nullptr && node->left->info == k)
//        count++;
//
//    if (node->right != nullptr && node->right->info == k)
//        count++;
//
//    count += CountParentsWithValueK(node->left, k);
//    count += CountParentsWithValueK(node->right, k);
//
//    return count;
//}

int CountParentsWithValueK(Node* root, int k)
{
    if (root == nullptr)
        return 0;

    int count = 0;

    if (root->left != nullptr && root->left->info == k)
        count++;
    if (root->right != nullptr && root->right->info == k)
        count++;

    count += CountParentsWithValueK(root->left, k); 
    count += CountParentsWithValueK(root->right, k); 

    return count;
}

Node* Find(Node* root, int value)
{
    if (root == NULL || value == root->info)
        return root;
    if (value < root->info)
        return Find(root->left, value);
    else
        return Find(root->right, value);
}

void DeleteTree(Node*& root, Node* node)
{
    if (node != NULL)
    {
        DeleteTree(root, node->left);
        DeleteTree(root, node->right);
        root = BinarySearchDelete(root, node->info);
    }
}

int main()
{
    Node* root = NULL;
    int N;
    cout << "Enter nodes count: "; cin >> N;
    int menu;
    do
    {
        cout << "1. Binary tree create" << endl;
        cout << "2. Print tree" << endl;
        cout << "3. Create Binary Search Tree" << endl;
        cout << "4. Balance Tree" << endl;
        cout << "5. Binary Search Delete" << endl;
        cout << "6. Delete Tree" << endl;
        cout << "7. Count elements parents to which have the value" << endl;
        cout << "Choose action 1-6: "; cin >> menu;
        switch (menu)
        {
        case 1:
            root = CreateTree(N);
            break;
        case 2:
            PrintTree(root, 0);
            break;
        case 3:
            bool found;
            int value;
            for (int i = 0; i < N; i++)
            {
                cout << "value: "; cin >> value;
                BinarySearchInsert(root, value, found);
            }
            break;
        case 4:
            BalanceHeight(root);
            break;
        case 5:
            cout << "value: "; cin >> value;
            BinarySearchDelete(root, value);
            break;
        case 6:
            cout << "value: "; cin >> value;
            DeleteTree(root, Find(root, value));
            break;
        case 7:
            cout << "value: "; cin >> value;
            cout << CountParentsWithValueK(root, value) << endl;
            break;
        default:
            break;
        }
    } while (menu != 0);


    //Node* root = CreateTree(N);
    //PrintTree(root, 3);
    /*bool found;
    int value;
    for (int i = 0; i < N; i++)
    {
        cout << "value: "; cin >> value;
        BinarySearchInsert(root, value, found);
    }
    cout << endl;
    cout << endl;
    cout << endl;
    PrintTree(root, 3);
    BalanceHeight(root);
    cout << endl;
    cout << endl;
    cout << endl;
    PrintTree(root, 3);
    cout << CountElementsWithParentValueK(root, 3);*/
}
