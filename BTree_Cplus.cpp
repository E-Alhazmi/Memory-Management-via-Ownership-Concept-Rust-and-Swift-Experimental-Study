/**
 COPYRIGHT (c) 2018 Elaf Alhazmi . All Rights Reserved.
 C++ Code - Binary Tree 
 */

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mach/mach_time.h>

using namespace std;

struct node
{
    long key;
    struct node *left;
    struct node *right ;
}*root ;

//Global Variables
long Nodes_created = 0;
long Nodes_not_created = 0;

class BT
{
    public :
    
    void insert_node (node*, node*);
    void search_node (long, node* );
    void replace(long, node* );
    void swap_node (node* ,node* ,node* );
    void inorder (node*);
    BT ()
    {
        root = NULL ;
    }
};

/**
 Function insert_node() inserts new node in tree
 Param:  Node *root, Node *newnode
 */
void BT::insert_node(node *tree, node *newnode)
{
    node *parent, *current ;
    if (root == NULL)
    {
        root = new node ;
        root->key = newnode->key ;
        root->left = NULL ;
        root->right =NULL ;
        Nodes_created++;
    }
    else
    {
        current = tree ;
        while( tree != NULL)
        {
            parent = current;
            if (newnode->key == current->key)
            {
                Nodes_not_created= Nodes_not_created + 1;
                break;
            }
            if (newnode->key < current->key)
            {
                current = current->left;
                if(current == NULL)
                {
                    parent->left= newnode;
                    newnode->left= NULL ;
                    newnode->right = NULL;
                    ++Nodes_created;
                    break;
                }
            }
            else
            {
                current=current->right;
                if(current == NULL)
                {
                    parent->right = newnode ;
                    newnode->left= NULL ;
                    newnode->right = NULL;
                    ++Nodes_created;
                    break;
                }
            }
        }
    }
}

/**
 Function search_node checking if item is exist in Tree
 Param :  long item, Node *par,
 */
void BT::search_node(long item, node *par)
{
    if (root == NULL)
    {
        cout<<"Root is NULL "<< endl;
        return;
    }
    else
    {
        if ( par != NULL)
        {
            if (item == par->key)
            {
                return;
            }
            if (item < par->key)
            {
                search_node(item, par->left);
            }
            else
            {
                search_node(item, par->right);
            }
        }
        else
        {
            return;
        }
    }
}



/**
 Function replace 
 Param :  long item, Node *par,
 */
void BT::replace(long item, node *par)
{
    node *parent, *current, *temp;
    current = root ;
    parent = root ;
    temp = new node ;
    temp->key = item;
    temp->left = NULL ;
    temp->right =NULL ;
    
    while (current != NULL)
    {
        parent = current;
        if (item < current->key) {
            current = current->left;
            if(item == current->key) {
                swap_node(parent, current, temp);
                break;
            }
            
        }
        else if (item > current->key) {
            current = current->right;
            if (item == current->key) {
                swap_node(parent, current, temp);
                break;
            }
            
        }
        else {
            break;
        }
    }
    
    
    
}

void BT::swap_node (node *parent ,node *current,node *temp)
{
    if (current == root) {
        return;
    }
    if (parent->key > current->key) {
        parent->left = temp;
        temp->left = current->left;
        temp->right = current->right;
        delete current;
    }
    else if (parent->key < current->key)
    {
        parent->right = temp;
        temp->right = current->right;
        temp->left = current->left;
        delete current;
    }
    
}

void BT::inorder(node *temp)
{
    if ( temp != NULL  )
    {
        inorder(temp->left);
        cout<<" value" << temp->key<<"\n";
        inorder(temp->right);
    }
}

void Shuffle(long *a, long count_num )
{
    int r;
    for (int i = count_num -1; i > 0; --i)
    {
        srandom(time(NULL));
        r = random() % (i+1) ;
        swap (a[i],a[r]);
    }
}

/**
 on OSX, mach_absolute_time() is used for measuring elpased time
 it is monotonic
 */
double MAT ()
{
    mach_timebase_info_data_t start_timeBase_loop1;
    mach_timebase_info(&start_timeBase_loop1);
    return (((mach_absolute_time() * (double)start_timeBase_loop1.numer )/ (double) start_timeBase_loop1.denom ));
}

/**
 Main Function performs five main tasks
 1.Generating Permutation numbers from [0-Num_of_Nodes)
 2.Using Fisher Yates algorithm to shuffle permutation numbers order
 3.Insert - Num_of_Nodes - in Binary Tree
 4.Search - Num_of_Nodes - in Binary Tree
 5.Replace - Num_of_Nodes - in Binary Tree
 */

int main()
{
    long Num_of_Nodes = 10000000;
    long *array_of_Rand_Num ;
    array_of_Rand_Num = new  long [Num_of_Nodes];
    
    
    /**
     Generating permutation numbers 
     */
    cout<<"\nLoop : Generating Permutation Numbers from 0 - "<<Num_of_Nodes<<" \n";
    cout<<"Elapsed (MAT) \n";
    cout<<"------------------\n";
    double elapsedTime_MAT_loop1 ;
    double start_timeBase_loop1 , end_timeBase_loop1;
    start_timeBase_loop1 = MAT() ;
    for (int i=0 ; i< Num_of_Nodes ; i++)
    {
        array_of_Rand_Num [i] = i;
    }
    end_timeBase_loop1 = MAT ();
    elapsedTime_MAT_loop1 = (end_timeBase_loop1 - start_timeBase_loop1)/ 1000000.0;
    cout<<elapsedTime_MAT_loop1<<" ms"<<endl ;
    
    
    /**
     Shuflle permutation numbers using Fisher Yates Algorithm
     */
    cout <<"\n\nShuffle : Shuffle Permutation number \n";
    cout<<"Elapsed (MAT) \n";
    cout<<"-----------------\n";
    double elapsedTime_MAT_shuffle1 ;
    double start_timeBase_shuffle1 , end_timeBase_shuffle1;
    start_timeBase_shuffle1 = MAT() ;
    Shuffle(array_of_Rand_Num, Num_of_Nodes);
    end_timeBase_shuffle1 = MAT ();
    elapsedTime_MAT_shuffle1 = (end_timeBase_shuffle1 - start_timeBase_shuffle1)/ 1000000.0;
    cout<< elapsedTime_MAT_shuffle1<<" ms"<<endl ;
    
    /**
     Insert 
     */
    BT bst;
    node *temp;
    cout<<"\n\n Insert \n";
    cout<<"Elapsed (MAT) \n";
    cout<<"--------------------\n";
    double elapsedTime_MAT_insert1 ;
    double start_timeBase_insert1 , end_timeBase_insert1;
    start_timeBase_insert1 = MAT() ;
    for (long i=0; i<Num_of_Nodes ; i++)
     {
        temp = new node;
        temp->key= array_of_Rand_Num[i];
        bst.insert_node(root,temp);
     }
     end_timeBase_insert1 = MAT ();
     elapsedTime_MAT_insert1 = (end_timeBase_insert1 - start_timeBase_insert1)/ 1000000.0;
     cout<<elapsedTime_MAT_insert1<<" ms"<<endl ;
    
    /**
      Search
     */
     cout<< "\n\nBinary Search Tree \n";
     cout<<"Elapsed (MAT) \n";
     cout<<"--------------------\n";
     double elapsedTime_MAT_binary1 ;
     double start_timeBase_binary1 , end_timeBase_binary1;
     start_timeBase_binary1 = MAT() ;
     srandom(time(NULL));
     int r;
     for (long j=0 ; j<Num_of_Nodes; j++)
     {
     r = random() % Num_of_Nodes ;
     bst.search_node( r,root);
     }
     end_timeBase_binary1 = MAT ();
     elapsedTime_MAT_binary1 = (end_timeBase_binary1 - start_timeBase_binary1)/ 1000000.0;
     cout<<elapsedTime_MAT_binary1<<" ms"<<endl ;

    /**
     Replace
     */
     cout<< "\n\nBinary Tree - replacement \n";
     cout<<"Elapsed (MAT) \n";
     cout<<"--------------------\n";
     double elapsedTime_MAT_replace1 ;
     double start_timeBase_replace1 , end_timeBase_replace1;
     start_timeBase_replace1 = MAT() ;
     srandom(time(NULL));
     int r2;
     for (long j=0 ; j<Num_of_Nodes; j++)
     {
     r2 = random() % Num_of_Nodes ;
     bst.replace( r2,root);
     }
     end_timeBase_replace1 = MAT ();
     elapsedTime_MAT_replace1 = (end_timeBase_replace1 - start_timeBase_replace1)/ 1000000.0;
     cout<<elapsedTime_MAT_replace1<<" ms"<<endl ;
     delete [] array_of_Rand_Num ;
     return 0;
}
