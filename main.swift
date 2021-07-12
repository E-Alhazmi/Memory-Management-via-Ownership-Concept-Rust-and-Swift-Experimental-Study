/**
 COPYRIGHT (c) 2018 Elaf Alhazmi . All Rights Reserved.
 SUPERVISED BY Emil Sekerinski and Frantisek Franek
 Swift Code - Binary Tree
 */
#if os(Linux)
    import SwiftGlibc
    import Glibc
#endif
import Foundation

func shuffle (a: inout [Int], count_num: Int) {
    var r:Int
    var temp:Int
    srandom(UInt32(time(nil)))
    for i in 0..<a.count {
        #if os(Linux)
            r =  Int(random() % (count_num))
        #else
            r = Int(arc4random_uniform(UInt32(count_num)))
        #endif
        temp = a[i]
        a[i] = a[r]
        a[r] = temp
    }
}

/**
 Node Structure
 */
class Node {
    var key : Int
    var left : Node?
    var right : Node?
    
    init ()
    {
        self.key = 0
        self.left = nil
        self.right = nil
    }
    init (value : Int)
    {
        self.key = value
        self.left = nil
        self.right = nil
    }
    
    /*deinit
     {
     print("Node is deleted!\n");
     }*/
}

/**
 Swift class to create Binary Tree Abstract Data Type
 and its operations
 */
class BT {
    var root : Node?
    var created : Int = 0 ;
    var not_created : Int = 0 ;
    //var replacement: Int = 0;
    
    init ()
    {
        root = nil
    }
    
    /**
     Function insert adds new node in tree
     Note: "value" is the key value for new node
     */
    func insert (node: Node? , value : Int)
    {
        let temp =  Node()
        temp.key = value
        temp.left = nil
        temp.right = nil
        if (root == nil)
        {
            root = Node()
            root?.key = value
            root?.left = nil
            root?.right = nil
            created = created + 1
            return
        }
        else
        {
            if (value < (node!.key))
            {
                if(node?.left != nil)
                {
                    insert(node:node!.left, value: value)
                }
                else
                {
                    node!.left = temp
                    created = created + 1
                    return
                }
            }
            if (value > node!.key)
            {
                if (node?.right != nil)
                {
                    insert(node:node!.right, value: value)
                }
                else
                {
                    node!.right = temp
                    created = created + 1
                    return
                }
            }
            if ( value == node!.key)
            {
                not_created = not_created + 1
                return
            }
        }
    }//end insert function
    
    /**
     Function search checks if "value" is exist in Tree
     */
    func search (node: Node? , value: Int) -> Bool
    {
        if( root == nil )
        {
            print(" Root is nil")
            return false
        }
        if (node == nil)
        {
            return false
        }
        else
        {
            if ( node!.key == value)
            {
                return true
            }
            if (value < node!.key)
            {
                return search(node:node?.left, value: value)
            }
            else
            {
                return  search (node:node?.right, value: value)
            }
        }
    }// end search function
    
    
    /**
     Function replace node by creating new node (deallocation purposes)
     */
    func replace (node: Node? , item: Int)
    {
        var current:Node? ; var parent:Node?; var temp:Node?
        current = root
        parent = root
        temp = Node();
        
        while(current != nil)
        {
            parent = current;
            if(item < current!.key) {
                current = current!.left;
                
                if (item == current?.key)
                {
                    self.swap_node(parent: parent, current: current, temp: temp);
                    break;
                }
            }
            else if (item > current!.key)
            {
                current = current!.right;
                if (item == current?.key)
                {
                    self.swap_node(parent: parent, current: current, temp: temp);
                    break;
                }
            }
            else
            {
                // in case if the Node is root
                // no replacement will be occured
                break;
            }
            
        }// end while
        current = nil
        parent = nil
        
    }// end replace function
    
    /**
     Function swap_node by replacing old node by new node
     */
    func swap_node(parent: Node? , current: Node? , temp:Node?)
    {
        if (current === root){
            return;
        }
        if (parent!.key > current!.key) {
            parent!.left = temp;
            temp!.left = current!.left;
            temp!.right = current!.right;
            current!.left = nil;
        }
        else if (parent!.key < current!.key)
        {
            parent!.right = temp;
            temp!.right = current!.right;
            temp!.left = current!.left;
            current!.left = nil;
            current!.right = nil;
        }
    }
    
    func inorder(item: Node?)
    {
        if ( item != nil  )
        {
            inorder(item:item!.left)
            print (" value \(item!.key)")
            inorder(item:item!.right)
        }
    }//end function inorder
}// End class BT

/**
 on OSX, mach_absolute_time() is used for measuring elpased time
 it is monotonic
 */
func MAT() -> Double
{
    var timeBaseInfo = mach_timebase_info_data_t()
    mach_timebase_info(&timeBaseInfo)
    return Double(mach_absolute_time() * UInt64(timeBaseInfo.numer)/(UInt64(timeBaseInfo.denom)))/1000000.0
}

/**
 Main Function performs five main tasks
 1.Generating Permutation numbers from [0-Num_of_Nodes)
 2.Using Fisher Yates algorithm to shuffle permutation numbers order
 3.Insert - Num_of_Nodes - in Binary Tree
 4.Search - Num_of_Nodes - in Binary Tree
 5.Replace - Num_of_Nodes - in Binary Tree
 */

let Num_of_Nodes = 10000000
var array_of_Rand_Num = Array(repeating:0, count: Num_of_Nodes)

/**
 Generating permutation numbers
 */
print("Loop : Generating Permutation random numbers \n")
print("Elapsed (MAT)")
print("--------------------------------\n")
var start_MAT_loop1 = MAT()
for index in 0..<array_of_Rand_Num.count {
    array_of_Rand_Num[index] = index
}
var end_MAT_loop1 = MAT()
let diff_MAT_loop1 = end_MAT_loop1 - start_MAT_loop1;
print("\(diff_MAT_loop1)\t\t \n")

/**
 Shuflle permutation numbers using Fisher Yates Algorithm
 */
print("Shuffle : Shuffle Permutation random numbers \n")
print("Elapsed (MAT)")
print("----------------------\n")
var start_MAT_shuffle1 = MAT()
shuffle(a:&array_of_Rand_Num,count_num:Num_of_Nodes)
var end_MAT_shuffle1 = MAT()
let diff_MAT_shuffle1 = end_MAT_shuffle1 - start_MAT_shuffle1;
print("\(diff_MAT_shuffle1)\t\t \n")
var bt = BT()

/**
 Insert
 */
print("Insert\n")
print("Elapsed (MAT) \t\t")
print("----------------------\n")
var start_MAT_insert1 = MAT()
for  i in 0...(Num_of_Nodes-1)
{
    bt.insert(node:bt.root, value: array_of_Rand_Num[i])
}
var end_MAT_insert1 = MAT()
let diff_MAT_insert1 = end_MAT_insert1 - start_MAT_insert1;
print("\(diff_MAT_insert1)\t\t \n")


/**
 Search
*/
print("Binary Search Tree\n")
print("Elapsed (MAT) \t\t ")
print("-------------------------\n")
var r:Int ;
var found = 0;
var not_found = 0;
srandom(UInt32(time(nil)))
var start_MAT_binary1 = MAT()
for _ in 0...(Num_of_Nodes-1)
{
    #if os(Linux)
        r =  Int(random() % (Num_of_Nodes))
    #else
        r = Int(arc4random_uniform(UInt32(Num_of_Nodes)))
    #endif
    let b = bt.search(node:bt.root, value:r)
    if (b == true){
        found = found + 1;
    }else {
        not_found = not_found + 1;
    }
}
var end_MAT_binary1 = MAT()
let diff_MAT_binary1 = end_MAT_binary1 - start_MAT_binary1;
print("\(diff_MAT_binary1)\t\t \n")

/**
 Replace
 */
print("Binary Tree - Replacement\n")
print("Elapsed (MAT) \t\t ")
print("-------------------------\n")
var z:Int ;
srandom(UInt32(time(nil)))
var start_MAT_replace1 = MAT()
for _ in 0...(Num_of_Nodes-1)
{
    #if os(Linux)
        z =  Int(random() % (Num_of_Nodes))
    #else
        z = Int(arc4random_uniform(UInt32(Num_of_Nodes)))
    #endif
    bt.replace(node:bt.root, item:z)
}

var end_MAT_replace1 = MAT()
let diff_MAT_replace1 = end_MAT_replace1 - start_MAT_replace1;
print("\(diff_MAT_replace1)\t\t \n")
print ("Nodes created \(bt.created)")
print ("Nodes not created \(bt.not_created)")





