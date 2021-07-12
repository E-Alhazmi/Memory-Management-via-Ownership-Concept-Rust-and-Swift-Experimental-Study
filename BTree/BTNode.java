
/**
 COPYRIGHT (c) 2018 Elaf Alhazmi . All Rights Reserved.
 SUPERVISED BY Dr.Emil Sekerinski and Dr.Frantisek Franek 
 Class to declare Binary Tree Abstract Data Type - Node
 @author Elaf Alhazmi
 */

public class BTNode {
    BTNode left, right ;
    int key ;
    
    /**
     * Default constructor for BTNode
     */
    public BTNode()
    {
        left = null ;
        right = null;
        key = 0 ;
    }
    
    /**
     * Construct a Node with a value
     * @param n is integer value that is associated with a Node
     */
    public BTNode (int n)
    {
        left = null ;
        right = null;
        key = n ;
    }
    
    /**
     * Set left Node reference of the current Node
     * @param l is BTNode, linked to the left of current BTNode
     */
     public void setLeft (BTNode l)
     {
      left = l;   
     }
     
     /**
      * Set right Node reference of the current Node
      * @param r is BTNode, linked to the right of current BTNode
      */
     public void setRight (BTNode r)
     {
         right = r;
     }
     
     /**
      * Get left Node reference of the current Node
      * @return the left BTNode of the current BTNode
      */
     public BTNode getLeft ()
     {
         return left ;
     }
     
     /**
      * Get right Node reference  
      * @return the right BTNode of the current BTNode
      */
     public BTNode getRight ()
     {
         return right ;
     }
     
     /**
      * Edit the integer value of a Node
      * @param n is integer value, editing the key value of BTNode
      */
     public void setKey (int n)
     {
         key = n;
     }
     
     /**
      * Return the integer value of a Node
      * @return key value of current BTNode
      */
     public int getKey ()
     {
         return key ;
     }
}
