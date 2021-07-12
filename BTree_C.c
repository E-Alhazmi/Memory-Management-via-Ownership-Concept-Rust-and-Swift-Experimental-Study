/**
 COPYRIGHT (c) 2018 Elaf Alhazmi . All Rights Reserved.
 SUPERVISED BY Dr.Emil Sekerinski and Dr.Frantisek Franek
 C Code - Binary Tree 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <mach/mach_time.h>

void shuffle(long *a, long count_num );
double MAT ();

typedef struct BTNode Node;
struct BTNode
{
    long key;
    Node *left;
    Node *right;
};
void swap_node ( Node *root, Node *parent, Node *current , Node *temp);


void shuffle(long *a, long count_num )
{
    int r;
    int temp;
    for (int i = count_num -1; i > 0; --i)
    {
        srandom(time(NULL));
        r = random() % (i+1) ;
        temp = a[i];
        a[i] = a[r];
        a[r] = temp ;
    }
}

//Global Variables
long Nodes_created = 0 ;
long Nodes_not_created =0;

/**
 Function insert() returns inserted Node pointer
 Note:   if the value n is already exist in Binary Tree,
 new node will not be dublicated.
 Param:  Node *root, long n
 */
Node* insert (Node *root, long n )
{
    if (root == NULL)
    {
        root= malloc(sizeof(Node));
        root->key = n ;
        root->left = NULL ;
        root->right = NULL ;
        Nodes_created= Nodes_created + 1 ;
    }
    else
    {
        if (n == root->key)
        {
            Nodes_not_created = Nodes_not_created + 1;
            return root;
        }
        else if (n < root->key)
        {
            root->left = insert (root->left, n);
        }
        else
        {
            root->right = insert (root->right, n);
        }
    }
    return root ;
}

/**
 Function search returns int, either 0 or 1
 Note:   search function returns 1
 if  item is found or 0 if not
 Param :  long item, Node *par,
 */
int search (long item, Node *par)
{
    int flag = 0;
    if (par != NULL)
    {
        if (par->key == item)
        {
            return 1;
        }
        else
        {
            if(item  < par->key)
            {
                flag = search (item, par->left);
            }
            else
            {
                flag = search (item, par->right);
            }
        }
    }
    return flag;
}

/**
 Function replace
 Param :  long item, Node *root,
 */
void replace (long item, Node *root)
{
    Node *parent, *current, *temp;
    current = root ;
    parent = root ;
    
    temp= (Node *)malloc(sizeof(Node));
    temp->key = item ;
    temp->left = NULL ;
    temp->right = NULL ;
    
    while(current != NULL)
    {
        parent = current;
        if (item < current->key) {
            current = current->left;
            if(item == current->key) {
              swap_node( root, parent, current, temp);
                break;
            }
        }
        else if (item > current->key) {
            current = current->right;
            if(item == current->key) {
                
               swap_node(root, parent, current, temp);
                break;
            }
            
        }
        else {
            break;
        }
    } 
}

/**
 Function swap_node
 Param :  Node *root,Node *parent, Node *current, Node *temp
 */
void swap_node ( Node *root, Node *parent, Node *current , Node *temp)
{
    if (current == root) {
        return;
    }
    
    if (parent->key > current->key) {
        
        parent->left = temp;
        temp->left = current->left;
        temp->right = current->right;
        free(current);
        
    }
    else{
        if ( parent->key < current->key){
        parent->right = temp;
        temp->right = current->right;
        temp->left = current->left;
        free(current);
        }
    }
    
}

/**
 Function inorder
 Param :  Node *temp, Node *current, Node *temp
 */
void inorde_node ( Node *temp)
{
    if (temp!= NULL) {
        inorde_node(temp->left);
        printf("value %ld \n",temp->key);
        inorde_node(temp->right);
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
    array_of_Rand_Num = (long *)malloc(Num_of_Nodes*sizeof(long));
    
    /**
     Generating permutation numbers 
     */
    printf("Loop : Generating Permutation Numbers from 0 - %ld \n",Num_of_Nodes);
    printf("Elapsed (MAT) \n");
    printf("--------------------\n");
    double elapsedTime_MAT_loop1 ;
    double start_timeBase_loop1 , end_timeBase_loop1;
    start_timeBase_loop1 = MAT() ;
    int i=0;
    while (i< Num_of_Nodes)
    {
        *(&array_of_Rand_Num[i]) = i;
        i++;
    }
    end_timeBase_loop1 = MAT ();
    elapsedTime_MAT_loop1 = (end_timeBase_loop1 - start_timeBase_loop1)/ 1000000.0;
    printf("%f ms  \n",elapsedTime_MAT_loop1);
    
    /**
     Shuflle permutation numbers using Fisher Yates Algorithm
     */
    printf("\n\n Shuffle \n");
    printf("Elapsed (MAT) \n");
    printf("-------------------------\n");
    double  elapsedTime_MAT_shuffle1 ;
    double start_timeBase_shuffle1 , end_timeBase_shuffle1;
    start_timeBase_shuffle1 = MAT() ;
    shuffle (array_of_Rand_Num , Num_of_Nodes) ;
    end_timeBase_shuffle1 = MAT ();
    elapsedTime_MAT_shuffle1 = (end_timeBase_shuffle1 - start_timeBase_shuffle1)/ 1000000.0;
    printf("%f ms \n", elapsedTime_MAT_shuffle1);
    
    /**
     Insert 
     */
    Node *root = NULL ;
    printf("\n\nInsertion \n");
    printf("Elapsed (MAT) \n");
    printf("-------------------------\n");
    double elapsedTime_MAT_insert1;
    double start_timeBase_insert1 , end_timeBase_insert1;
    int j =0;
    start_timeBase_insert1 = MAT() ;
    while (j< Num_of_Nodes)
     {
        root = insert (root,array_of_Rand_Num[j]);
        j++;
     }
     end_timeBase_insert1 = MAT ();
     elapsedTime_MAT_insert1 = (end_timeBase_insert1 - start_timeBase_insert1)/ 1000000.0;
     printf("%f ms \n", elapsedTime_MAT_insert1);

     /**
     Search 
     */
     printf("\n\n Binary Search Tree \n");
     printf("Elapsed (MAT) \n");
     printf("------------------\n");
     double elapsedTime_MAT_binary1;
     double start_timeBase_binary1 , end_timeBase_binary1;
     int  k=0;
     int c;
     start_timeBase_binary1 = MAT() ;
     int c_found = 0;
     int c_not_found = 0 ;
     srandom(time(NULL));
     long r;
     while (k< Num_of_Nodes)
     {
     r=(random() % Num_of_Nodes);
         replace(r, root);
     c = search (r, root );
     if ( c == 1 ) {
     c_found++ ;
     }
     else {
     c_not_found++ ;
     }
     k++;
     }
     end_timeBase_binary1 = MAT ();
     elapsedTime_MAT_binary1 = (end_timeBase_binary1 - start_timeBase_binary1)/ 1000000.0;
     printf("%f ms \n",elapsedTime_MAT_binary1);
     printf("Found is %i \n",c_found);
     printf("Not Found is %i \n",c_not_found);

     /**
     Replace
     */
     printf("\n\n Binary Tree Replacement \n");
     printf("Elapsed (MAT) \n");
     printf("------------------\n");
     double elapsedTime_MAT_replace1;
     double start_timeBase_replace1 , end_timeBase_replace1;
     int  z=0;
     start_timeBase_replace1 = MAT() ;
     srandom(time(NULL));
     long r2;
     while (z< Num_of_Nodes)
     {
     r2=(random() % Num_of_Nodes);
     replace(r2, root);
     z++;
     }
     end_timeBase_replace1 = MAT ();
     elapsedTime_MAT_replace1 = (end_timeBase_replace1 - start_timeBase_replace1)/ 1000000.0;
     printf("%f ms \n",elapsedTime_MAT_replace1);
     free(array_of_Rand_Num);
     return 0;
}
