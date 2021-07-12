/**
 COPYRIGHT (c) 2018 Elaf Alhazmi . All Rights Reserved.
 SUPERVISED BY Dr.Emil Sekerinski and Dr.Frantisek Franek
 Class to implement Binary Tree Abstract Data Type
 */
public class BT {
    public BTNode root ;
    public long Nodes_created = 0;      // Total of created Nodes
    public long Nodes_not_created = 0;  // Total of Nodes not created 
    public long s = 0;  // Total of Nodes not created 

    /**
     * Default constructor for Binary Tree (BT)
     * Note: creating empty BT with null pointer
     */
    public BT ()
    {
        root = null ;
    }
    
    /**
     * Check if BT is empty
     * @return root with null pointer
     */
    public boolean isEmpty ()
    {
        return root == null ;
    }
    
    /**
     * Insert New BTNode to the current BT
     * @param n is integer value, key value of the new Node
     */
     public void insert (int n)
     {
         BTNode parent, current , temp;
         if ( root == null)
         {
             root = new BTNode (n);
             ++Nodes_created;
         }
         else
         {
             temp = new BTNode ( n);
             current = root;
             while (root != null)
             {
                 parent = current ;
                 if (n == current.getKey())
                 { 
                     ++Nodes_not_created;
                     break ;
                 }
                 else
                 {
                    if (n < current.getKey())
                    {
                        current = current.getLeft();
                        if(current == null)
                        {
                            parent.setLeft(temp);
                            ++Nodes_created;
                            break;
                        }
                    }
                    else
                    {
                        current = current.getRight();
                        if (current == null)
                        {
                            parent.setRight(temp);
                            Nodes_created++;
                            break;
                        }
                    }
                 }
             }
         }
     }
     
     /**
      * Binary search Tree
      * @param item is  integer value,used for searching
      * @param par is  BTNode
      * @return true if it is found, otherwise return false
      */
     public boolean search (int item , BTNode par)
     {
         boolean flag = false;
         if (root == null )
         {
             
            flag = false;
         }
         else
         {
             if(par != null)
             {
                 if(par.getKey() == item)
                 {
                     flag =true;
                     
                     return flag; 
                 }
                 if(item < par.getKey() )
                 {
                     this.search(item, par.left);
                 }
                 else
                 {
                     this.search(item, par.right);
                 }
             }
             else
             {
                 return flag;
             }
         }
         return flag;
     }

     /**
      * Replace
      * @param item is  integer value,used for searching
      * @param par is  BTNode
      */    
      public void replase (int item , BTNode par)
      {
         BTNode current , parent , temp;
         current = root;
         parent = root;
         temp = new BTNode(item);
         
         while(current != null)
         {
             parent = current;
             if(item < current.key) {
                 current = current.left;
                 
                 if (item == current.key)
             {
                 this.swap_node(parent, current, temp);
                 break;
              }
             }
             else if (item > current.key)
              {
                     current = current.right;
                     if (item == current.key)
             { 
                 this.swap_node(parent, current, temp);
                 break;
              }
               }
             else
             {
                 break;
             }
         }// end while
       }
        
      public void swap_node (BTNode parent , BTNode current , BTNode temp)
      {
           if (current == root){
               return;
           }
           else {
            if (parent.key > current.key)
             {
                 parent.left = temp;
                 temp.left = current.left;
                 temp.right = current.right;
                 current = null;

             }

            else if (parent.key < current.key)
             {               
               parent.right = temp;
               temp.right = current.right;
               temp.left = current.left;
               current = null;
             }              
        }
      }
     
     /**
      * Printing BT Nodes by using in-order traverser 
      * @param r is BTNode
      */
     public void inorder(BTNode r)
     {
         if ( r != null )
         {
             inorder (r.getLeft());
             System.out.println(r.getKey());
             s += 1;
             inorder (r.getRight());
         }
     }
}
