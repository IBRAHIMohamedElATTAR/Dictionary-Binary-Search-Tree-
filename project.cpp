#include <iostream>
#include <fstream>

using namespace std;
template<class T>
struct TreeNode;

enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};
template<class T>
class TreeType
{
public:
    TreeType();
    ~TreeType();
    TreeType(const TreeType<T>&);
    void operator=(const TreeType<T>&);
    void MakeEmpty();
    bool IsEmpty() const;
    bool IsFull() const;
    int NumberOfNodes() const;
    void RetrieveItem(T&, bool& found);
    void RetrieveItemV2(T&, bool& found,T & prev,T&next);
    void InsertItem(T,bool &alreadyExist);
    void DeleteItem(T,bool & found);
    void ResetTree(OrderType);
    void GetNextItem(T&, OrderType, bool&);
    void PrintTree() const;

private:
    TreeNode<T>* root;
};

class Dictionary
{
public:

    Dictionary(string filepath);
    ~Dictionary();
    int size();
    int insert(string word);
    int lookup(string word);
    int remove(string word);
private:

    TreeType <string>* tree;

};

template <class T>
struct TreeNode
{
    T value;
    TreeNode<T> *left, *right;
};

template <class T>
TreeType<T>::TreeType()
{
    root = NULL;
}
template <class T>
TreeType<T>::~TreeType()
{
}
template <class T>
void TreeType<T>::InsertItem(T value, bool &alreadyExist)
{
    insertItem(root, value, alreadyExist);
}
template <class T>
void insertItem(TreeNode<T> *&node, T value, bool &alreadyExist)
{
    if (node == NULL)
    {
        node = new TreeNode<T>;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        alreadyExist = false;
    }
    else if (node->value > value)
    {
        insertItem(node->left, value, alreadyExist);
    }
    else if (node->value < value)
    {
        insertItem(node->right, value, alreadyExist);
    }
    else
    {
        alreadyExist = true;
    }
}

template <class T>
void TreeType<T>::RetrieveItem(T &value, bool &found)
{
    retriveItem(root, value, found);
}

template <class T>
void TreeType<T>::RetrieveItemV2(T &value, bool &found,T&prev,T&next)
{
    retriveItemV2(root, value, found);
    if(found) return;
    inorder_search(root,value,prev,next);
}
template <class T>
void inorder_search(TreeNode<T>*node,T value,T & prev,T& next)
{
    T temp;

    if(node != NULL)
    {
        temp=node->value;
        inorder_search(node->left,value, prev,next);
        if (next.length()>0)
        {
            return;
        }
        if(value > node->value)
        {
            prev=node->value;
        }
        else if(value < node->value)
        {
            next=node->value;
            return;
        }

        inorder_search(node->right,value, prev,next);
    }
}
template <class T>
void retriveItem(TreeNode<T> *&node, T &value, bool &found)
{
    if (node == NULL)
    {
        found = false;
        return;
    }
    else if (node->value == value)
    {
        found = true;
        return;
    }

    else if (node->value < value)
    {
        if (node->right == NULL)
        {
            found = false;
            value = node->value;
            return;
        }
        else
        {
            retriveItem(node->right, value, found);
        }
    }
    else if (node->value > value)
    {
        if (node->left == NULL)
        {
            found = false;
            value = node->value;
            return;
        }
        else
        {
            retriveItem(node->left, value, found);
        }
    }
}
template <class T>
void retriveItemV2(TreeNode<T> *&node, T &value, bool &found)
{
    if (node == NULL)
    {
        found = false;
        return;
    }
    else if (node->value == value)
    {
        found = true;
        return;
    }

    else if (node->value < value)
    {
        if (node->right == NULL)
        {
            found = false;

            return;
        }
        else
        {
            retriveItemV2(node->right, value, found);
        }
    }
    else if (node->value > value)
    {
        if (node->left == NULL)
        {
            found = false;

            return;
        }
        else
        {
            retriveItemV2(node->left, value, found);
        }
    }
}



template <class T>
void TreeType<T>::DeleteItem(T value, bool &found)
{
    deleteItem(root, value, found);
}
template <class T>
void deleteItem(TreeNode<T> *&node, T value, bool &found)
{
    if (node == NULL)
    {
        found = false;
        return;
    }
    else if (node->value > value)
    {
        deleteItem(node->left, value, found);
    }
    else if (node->value < value)
    {
        deleteItem(node->right, value, found);
    }
    else if (node->value == value)
    {
        if (node->left == NULL && node->right == NULL)
        {
            delete node;
            node = NULL;
            found = true;
            return;
        }
        else if (node->left == NULL)
        {
            TreeNode<T> *temp = node;
            node = node->right;
            found = true;
            delete temp;
            return;
        }
        else if (node->right == NULL)
        {
            TreeNode<T> *temp = node;
            node = node->left;
            found = true;
            delete temp;
            return;
        }
        else
        {
            T x;
            getPredecessor(node->left, x);

            node->value = x;
            deleteItem(node->left, x, found);
        }
    }
}

template <class T>
void getPredecessor(TreeNode<T> *node, T &value)
{
    while (node->right != NULL)
    {
        node = node->right;
    }
    value = node->value;
}

template <class T>
void TreeType<T>::PrintTree() const
{
    printTree(root);
}

template <class T>
void printTree(TreeNode<T> *node)
{
    if (node == NULL)
    {
        return;
    }
    printTree(node->left);

    printTree(node->right);
}
template <class T>
int TreeType<T>::NumberOfNodes() const
{
    return CountNodes(root);
}
template <class T>
int CountNodes(TreeNode<T> *node)
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        return CountNodes(node->left) + CountNodes(node->right) + 1;
    }
}

Dictionary::Dictionary(string filename)
{
    tree = new TreeType<string>();
    fstream *myfile = new fstream(filename);
    string data;
    while (getline(*myfile, data))
    {

        insert(data);
    }
    tree->PrintTree();
    myfile->close();
}

Dictionary::~Dictionary()
{
    delete tree;
}

int Dictionary::insert(string word)
{
    bool flag = false;

    tree->InsertItem(word, flag);
    if (flag)
    {
        cout << "Word already in the dictionary!" << endl;
        return 0;
    }
    else
    {
        return 1;
    }
}
int Dictionary::lookup(string word)
{
    bool found = false;
    string temp = word;
    string prev,next;
    tree->RetrieveItemV2(word, found,prev,next);
    if (found)
    {
        return 1;
    }
    else
    {
        if(next.length()>0)
            cout << temp << " is not found. Do you mean " << prev << " or "<<next <<"?" << endl;
        else
            cout << temp << " is not found. Do you mean " << prev <<"?" << endl;

        return 0;
    }
}
int Dictionary::remove(string word)
{
    bool found = false;

    tree->DeleteItem(word, found);
    if (found)
    {
        return 1;
    }
    else
    {
        cout << word << " is not found. It can't be removed" << endl;
        return 0;
    }
}
int Dictionary::size()
{
    return tree->NumberOfNodes();
}

bool isNumber(string word)
{
    for (int i = 0; i<word.length(); i++)
    {
        if(!isdigit(word[i]))
        {
            return false;
        }
    }
    return true;
}
int main()
{

    Dictionary *dictionary = new Dictionary("dictionary.txt");

    int choice;
    string temp;
    bool flag = true;
    while (flag)
    {
        cout << "Enter number to choose from:\n1. insert word into dictionary\n2. lookup word in dictionary\n3. remove word from dictionary \n4. print size of dictionary\n5. Exit dictionary" << endl;
        cin >> temp;
        if(isNumber(temp))
        {
            choice = stoi(temp);
        }
        else
        {
            cout<<"Enter integer value"<<endl;
            continue;
        }

        string word;
        switch (choice)
        {
        case 1:
            cout << "Enter word to insert it in your dictionary:" << endl;
            cin >> word;
            if(dictionary->insert(word)==1)
            {
                cout<<word<<" is successfully inserted into dictionary";
            }
            break;
        case 2:
            cout << "Enter word to lookup:" << endl;
            cin >> word;
            if(dictionary->lookup(word)==1)
            {
                cout <<word<< " is found"<<endl;
            }
            break;
        case 3:
            cout << "Enter word to remove it:" << endl;
            cin >> word;
            if(dictionary->remove(word)==1)
            {
                cout<<word<<" is successfully removed from dictionary";
            }
            break;
        case 4:
            cout << "Size = " << dictionary->size() << endl;
            break;
        case 5:
            flag = false;
            break;
        default:
            cout << "You have entered a wrong choice" << endl;
        }
    }
}
