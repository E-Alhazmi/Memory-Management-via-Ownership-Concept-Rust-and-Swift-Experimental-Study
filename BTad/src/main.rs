/**
 COPYRIGHT (c) 2018 Elaf Alhazmi . All Rights Reserved.
 Rust Code - Binary Tree 
*/
extern crate rand;
extern crate time; 
use rand::{thread_rng, Rng};
use std::fmt;
use time::PreciseTime;
use std::time::Instant;

fn shuffle_x(a: &mut[i32], count_num: usize)
{	
	let mut r :usize;
	let mut temp;
	let mut rng = thread_rng();
	for i in 1..count_num
	{
		r = rng.gen_range(0, i);
		 temp = a[i];
         a[i] = a[r];
         a[r] = temp;
	}
}

/**
Node Structure
*/
#[derive(Debug)]
pub struct Node<T>{
	key: T,
	left : Option<Box<Node<T>>>,
	right: Option<Box<Node<T>>>,
}

/**
Tree Structure 
*/
#[derive(Debug)]
pub struct Tree<T> {
	root : Option<Box<Node<T>>>,
	size : usize,
}

/**
Node Implementation 
*/
impl<T> Node<T> {
	fn new( key: T) -> Self {
	Node { key : key , left : None, right : None}
	}
}

macro_rules! fmt_node { 
    ($fmt:expr, $node:expr) => { 
       if let Some(ref node) = $node.as_ref() { 
            try!(node.fmt($fmt)); 
         } 
     }; 
}

impl<T: std::fmt::Display> fmt::Display for Tree<T>  { 
	 fn fmt(&self, fmt: &mut fmt::Formatter) -> Result<(), fmt::Error> { 
			try!(write!(fmt, "[")); 
			fmt_node!(fmt, self.root); 
			try!(write!(fmt, "]")); 
			 Ok(()) 
	}			 
 } 

impl<T: std::fmt::Display> fmt::Display for Node<T> { 
     fn fmt(&self, fmt: &mut fmt::Formatter) -> Result<(), fmt::Error> { 
         fmt_node!(fmt, self.left); 
         try!(write!(fmt, "{}, ", self.key)); 
         fmt_node!(fmt, self.right); 
         Ok(()) 
     } 
} 

/**
Tree Implementation 
*/
impl<T:Ord> Tree<T> {
	pub fn new () -> Self {
	Tree { root : None, size: 0}
	}
	/**
	Function insert() adds new node in tree
	*/
	pub fn insert ( &mut self , key: T) {
		match self.root.as_mut() {
		None => {
			self.root = Some (Box::new (Node :: new(key)));
			self.size +=1;
			}, //end None
		Some(_) => {
			let mut next = self.root.as_mut().unwrap();
			loop {
				let cur = next;
				let target = {
					let elem_ref = &key;
					if cur.key == *elem_ref {
						return;
					} // end if
					if cur.key < *elem_ref 
					  {&mut cur.right } 
					else 
					  {&mut cur.left}
				}; // end target
			if target.is_some() {
				next = target.as_mut().unwrap();
				continue;
				} // end if
			*target= Some(Box::new(Node::new(key)));
			self.size +=1;
			return;
				} // end loop
			} // end some
		}// end match
	}// end insert

	/**
	Function search checking if value is exist in Tree
	*/
	pub fn search( &mut self , key: T)-> bool {
		let mut flag = false;
		match self.root.as_mut() {
			None => {
				println! ("No Elements in Tree");
			}//end None
			Some(_) => {
		        let mut next = self.root.as_mut().unwrap();
				loop {
					let cur = next;
				    let target = {
						let elem_ref = &key;
						if cur.key == *elem_ref {
							flag = true;
							break;
						} // end if
						if cur.key < *elem_ref {
							&mut cur.right 
						} // end if
						else {
							&mut cur.left
						}//end else
					}; //end target	
					if target.is_some() {
						next = target.as_mut().unwrap();
						continue;
					} // end if	
					break;
				} // end loop
			}//end Some
		}// end mathch
	return flag;
	}// end search function 
	
	
	
	/**
	Function replace new node of existing one
	*/
	pub fn replace  ( &mut self ,key: T) {
		match self.root.as_mut() {
			None => {
				println! ("No Elements in Tree");
			}//end None
			Some(_) => {
				{
					let mut parent = self.root.as_ref();
					
					{
						// Root checking 
						if parent.unwrap().key == *(&key) {
						return
						} // end if
					}
				}

				{
					let mut next = self.root.as_mut().unwrap();
					loop {
						let mut cur = next;
						let mut target = {
							if cur.left.is_some() {
								if (cur.left).as_mut().unwrap().key == *(&key) {
									let mut new_node = Some(Box::new(Node::new(key)));
									{
										let mutate_new_node = new_node.as_mut().unwrap();
										{
											mutate_new_node.left = (cur.left.as_mut().unwrap()).left.take();
										}// end mini left moving

										{
												{
													mutate_new_node.right = (cur.left.as_mut().unwrap()).right.take();
												}// end mini right moving
										}
									}
									cur.left = new_node;
									break;
								} // end left replacement 
							}
							if cur.right.is_some() {
								if (cur.right).as_mut().unwrap().key == *(&key) {
									let mut new_node = Some(Box::new(Node::new(key)));
									{
										let mutate_new_node = new_node.as_mut().unwrap();
										{
											mutate_new_node.left = (cur.right.as_mut().unwrap()).left.take();
										}// end mini left moving

										{
											{
												mutate_new_node.right = (cur.right.as_mut().unwrap()).right.take();
											}// end mini right moving
									    }
								    }
								    cur.right = new_node;
									break;
								} // end if
							}

							if cur.key < *(&key) {
								&mut cur.right 
							} 
							else {
							if cur.key > *(&key) {
								&mut cur.left
							}
							else {
								break;
							}
							}
						}; // end target
						if target.is_some() {
							next = target.as_mut().unwrap();
							continue;
							} // end if	
							else {
								break;
							}
							return;
						} // end loop
					}
			}//end Some
		}// end match
	}// end search function 
} // end ord

/**
 Main Function performs five main tasks
 1.Generating Permutation numbers from [0-Num_of_Nodes)
 2.Using Fisher Yates algorithm to shuffle permutation numbers order
 3.Insert - Num_of_Nodes - in Binary Tree
 4.Search - Num_of_Nodes - in Binary Tree
 5.Replace - Num_of_Nodes - in Binary Tree
 */
fn main() {
	const Num_of_Nodes:usize = 200000000;	
	let mut array_of_Rand_Num = vec![0; Num_of_Nodes]; 	

	/**
     Generating permutation numbers 
     */
	println!("Loop : Generating Permutation Numbers from 0 - {} \n",Num_of_Nodes);
    println!("Elapsed Time (Instant) \t Elapsed Time (Precise) \n");
    println!("--------------------------------------------------------------------\n");
	let start_Precise_loop1 = PreciseTime::now();
	let start_instant_loop1 = Instant::now();
	for i in 0..Num_of_Nodes {
	array_of_Rand_Num[i] = i as i32;
	}
	let end_instant_loop1 = start_instant_loop1.elapsed();
	let end_Precise_loop1 = PreciseTime::now();
	let diff_instant_loop1 = (end_instant_loop1.as_secs() as f64)*1000.0 + (end_instant_loop1.subsec_nanos() as f64 / 1000000.0);
	println!(" {} ms \t\t {} s",diff_instant_loop1, start_Precise_loop1.to(end_Precise_loop1));

	/**
     Shuflle permutation numbers using Fisher Yates Algorithm
     */
	println!("Shuffle : Shuffle Permutation Numbers");
    println!("Elapsed Time (Instant) \t Elapsed Time (Precise) \n");
    println!("--------------------------------------------------------------------");
	let start_Precise_shuffle1 = PreciseTime::now();
	let start_instant_shuffle1 = Instant::now();
	shuffle_x (&mut array_of_Rand_Num , Num_of_Nodes );
	let end_instant_shuffle1 = start_instant_shuffle1.elapsed();
	let end_Precise_shuffle1 = PreciseTime::now();
	let diff_instant_shuffle1 = (end_instant_shuffle1.as_secs() as f64)*1000.0 + (end_instant_shuffle1.subsec_nanos() as f64 / 1000000.0);
	println!(" {} ms \t\t {} s",diff_instant_shuffle1, start_Precise_shuffle1.to(end_Precise_shuffle1));

	/**
     Insert 
     */
	let mut tree = Tree::new();
	println!("Insertion, Binary Tree");
    println!("Elapsed Time (Instant) \t Elapsed Time (Precise) \n");
    println!("--------------------------------------------------------------------");
	let start_Precise_insert1 = PreciseTime::now();
	let start_instant_insert1 = Instant::now();
	for i in 0..Num_of_Nodes  {
		tree.insert(array_of_Rand_Num[i]);
	}
	let end_instant_insert1 = start_instant_insert1.elapsed();
	let end_Precise_insert1 = PreciseTime::now();
	let diff_instant_insert1 = (end_instant_insert1.as_secs() as f64)*1000.0 + (end_instant_insert1.subsec_nanos() as f64 / 1000000.0);
	println!(" {} ms \t\t {} s",diff_instant_insert1, start_Precise_insert1.to(end_Precise_insert1));

	/**
     Binary Search Tree using random numbers from 0-1000000
     */
	/*println!("Binary Search - Tree");
    println!("Elapsed Time (Instant) \t Elapsed Time (Precise) \n");
    println!("--------------------------------------------------------------------");
	let mut rng = thread_rng();
	let mut found = 0 ;
	let mut not_found = 0;
	let mut t ;
	let mut n: i32 = rng.gen_range(0, Num_of_Nodes as i32);
	let start_Precise_binary1 = PreciseTime::now();
	let start_instant_binary1 = Instant::now();
	for _ in 0..Num_of_Nodes  {
		t = tree.search(n);
		if  t == true {
		found = found + 1 ;
		}
		else {
		not_found= not_found + 1 ;
		}
		n = rng.gen_range(0, Num_of_Nodes as i32) ;
	}
	let end_instant_binary1 = start_instant_binary1.elapsed();
	let end_Precise_binary1 = PreciseTime::now();
	let diff_instant_binary1 = (end_instant_binary1.as_secs() as f64)*1000.0 + (end_instant_binary1.subsec_nanos() as f64 / 1000000.0);
	println!(" {} ms \t\t {} s",diff_instant_binary1, start_Precise_binary1.to(end_Precise_binary1));
	println! ("Found is {} and Not Found is {}", found, not_found);
	*/
	
	/**
     Binary Tree - replacement -
     */
	println!("Binary Tree - replace");
    println!("Elapsed Time (Instant) \t Elapsed Time (Precise) \n");
    println!("--------------------------------------------------------------------");
	let mut rng_replace = thread_rng();
	let mut n: i32 = rng_replace.gen_range(0, Num_of_Nodes as i32);
	let start_Precise_replace1 = PreciseTime::now();
	let start_instant_replace1 = Instant::now();
	for _ in 0..Num_of_Nodes  {
		tree.replace(n);
		n = rng_replace.gen_range(0, Num_of_Nodes as i32) ;
	}
	let end_instant_replace1 = start_instant_replace1.elapsed();
	let end_Precise_replace1 = PreciseTime::now();
	let diff_instant_replace1 = (end_instant_replace1.as_secs() as f64)*1000.0 + (end_instant_replace1.subsec_nanos() as f64 / 1000000.0);
	println!(" {} ms \t\t {} s",diff_instant_replace1, start_Precise_replace1.to(end_Precise_replace1));
	println!(" Size {} ", tree.size); 
	//println! ("{:} " , tree);
}
