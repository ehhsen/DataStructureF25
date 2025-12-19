#pragma once
#include"tnode.h"

template <typename key_type>
class set {
private:
	tnode<key_type> *H, *temp, *to_del, *succ;
	int n;
	
	// we give ptr to to_Del and get succ:
	// what is successor: it is larger than to_del and found on right side of to_del (smallest key on right side of to_DEl)
	tnode<key_type>* successor(tnode<key_type>* ptr) {
		tnode<key_type>* temp;
		temp = ptr->right;

		while (temp->left != H) {
			temp = temp->left;

		}
		return temp;
	}
	///////////////////////////////////////

public:
	// constructor
	set() {
		H = new tnode<key_type>;
		H->left = H->right = H->parent = H;
		H->is_nill = true;
		n = 0;
	}
	/// insert function
	void insert(key_type &key) {
		
    // creating new tnode
		tnode<key_type> *nn, *temp;
		nn = new tnode<key_type>;

		// assigning values to members of new node
		nn->left = H;
		nn->right = H;
		nn->parent = H;
		nn->key = key;
		nn->is_nill = false;

	//for root node
		if (H->parent == H) { /// will be true for first node only
			H->parent = nn;
			H->left = H->right = nn;
			++n;
			return;
		}

		// take a temp ptr that points to root tnode(first tnode)
		temp = H->parent;
		
		while (true) {
			
			//case1: key / new value is less than root node ---- goto left side 
			if (key <= temp->key) {
				// on left side

				// check if this side is empty or not, 
				// if empty nn tnode should be placed here else
				// we should go further left

				if (temp->left != H) {
					temp = temp->left;
				}
				else {
					// this will run when the left side of tnode is empty
					temp->left = nn;
					nn->parent = temp;
					break;
				}

			}//end of left side 

			//case2: key is greater than temp val 
			else if(key > temp->key){

				if (temp->right != H) {
					temp = temp->right;
				}
				else {
					temp->right = nn;
					nn->parent = temp;
					break;
				}

			}// end of right side 
		}// end of while loop

		// pointing left and right of H to min and max values respectively
		if (H->left->key > key) {
			H->left = nn;
		}
		else if ( H->right->key < key){
			H->right = nn;
		}
	}// end of insert function
	////////////////////////////////////////////////////////////////////////////////

	bool empty() {
		return H->parent == H;
	}
	
	// make iterator subclass	
	class iterator {
	private:
		tnode<key_type>* ptr;
	public:
		friend class set<key_type>;
		key_type operator*()const {
			return this->ptr->key;
		}

		iterator& operator++() {
			
			//check if R child exists
			if (!ptr->right->is_nill) {
				ptr = ptr->right;
				// ptr left child exists
				while (!ptr->left->is_nill) {
					ptr = ptr->left;
				}
			}//end of iff

			else if (ptr->parent->left == ptr)// check that tnode  left child of parent
			{
				ptr = ptr->parent;
			}
			else {
				while (ptr->parent->left != ptr) {
					ptr = ptr->parent;
				}
				ptr = ptr->parent;
			}
			
			return *this;
		}// end of ++

	};//end of iteator class

	/////////////////////////
	iterator begin() {
		iterator it;
		it.ptr = H->left;
		return it;
	}
	//////////////////
	iterator end() { // returns iteator pass the last element
		iterator it;
		it.ptr = H;
		return it;
	}

	class reverse_iterator {
	private:
		tnode<key_type>* ptr;
	public:
		friend class set<key_type>;
		key_type operator*()const {
			return this->ptr->key;
		}
		///////////////////////

		reverse_iterator& operator++() {

			//check if L child exists
			if (!ptr->left->is_nill) {
				ptr = ptr->left;
				// ptr right child exists
				while (!ptr->right->is_nill) {
					ptr = ptr->right;
				}
			}//end of iff

			else if (ptr->parent->right == ptr)// check that tnode  righht child of parent
			{
				ptr = ptr->parent;
			}
			else {
				while (ptr->parent->right != ptr) {
					ptr = ptr->parent;
				}
				ptr = ptr->parent;
			}

			return *this;
		}// end of ++
		////////////////////
	/*	key_type operator*()const {
			return this->ptr->key;
		}*/


	};

	////////////////////////////////////////////////////
	template <typename key_type>
	//erase function//
	void erase(iterator pos) {
		tnode<key_type>* to_del;
		pos.ptr = H->parent;
		to_del = pos.ptr;


		//case5: to_del is root tnode 
		if (to_del->parent == H) {
			/// we are dealing with dummy tnode


			// no child root tnode 
			if (to_del->left == to_del->right == H) {
				H->parent = H->left = H->right = H;
				delete to_del; --n;
			}

			// only  left child 
			else if (to_del->left != H && to_del->right == H) {
				to_del->left->parent = H;
				H->parent = to_del->left;
				delete to_del; --n;

			}
			// only  right child 
			else if (to_del->right != H && to_del->left == H) {
				to_del->right->parent = H;
				H->parent = to_del->right;
				delete to_del; --n;
			}


			}//end of dummy tnode case

		//case1: deleteing leaf tnode
		else if (to_del->left == H && to_del->right == H) {

			//which side of parent is this child on

			// if on left side
			if (to_del->parent->left == to_del) {
				to_del->parent->left = H;  ///  khali jo geya abb . dummy node daal deya

			}
			//  leaf tnode is on right side
			else {
				to_del->parent->right = H;
			}

		}///end of case 1

		// case2: to_del has only 1 tnode : it can be left or right

		
		//has only left tnode
		else if (to_del->right == H && to_del->left != H) {

			//tnode<key_type>* leftChild = to_del->left;
			if (to_del->parent->left == to_del) {
				to_del->parent->left = to_del->left;
			}
			else {
				to_del->parent->right = to_del->left;
			}

		}

		//case3: to_del hjas only 1 child and its right 
		else if (to_del->right != H && to_del->left == H) {
			if (to_del->parent->left == to_del) {
				to_del->parent->left = to_del->right;
			}
			else {
				to_del->parent->right = to_del->right;
			}
		}
		//////////////////////////////////////////////////

		
		//case4:  to_Del had 2 childs
		// we need a successor , we will extract both to_del and succ : and replace them
		// for that we make a successor function 
		else {
			succ = successor(to_del);

			// changing pointers

			// to del is left child of its parent
			if (to_del->parent->left == to_del) {
				to_del->parent->left = succ;
			}
			//to del is rigjht child of its parent
			else {
				
				to_del->parent->right = succ;
			}
			to_del->left->parent = succ;

			succ->parent = to_del->parent;
			succ->left = to_del->left;

			if (succ->parent != to_del) {
				to_del->right->parent = succ;
				succ->parent->left = succ->right;
				if (succ->right != H) {
					succ->right->parent = succ->parent;
				}
				succ->right = to_del->right;
			}
		}
		///////////////////////////////////////

	}

	/////////////////////
	reverse_iterator rbegin() {
		reverse_iterator rit;
		rit.ptr = H->right;
		return rit;

	}
	/////////////////////////////////////////////
	reverse_iterator rend() {
		reverse_iterator rit;
		rit.ptr = H;
		return rit;
	}

	//end of class
	void r_insert(tnode<key_type>* ,  key_type& key) {
		if (empty() {

			// general case 
			// creating new tnode
			tnode<key_type>* nn, * temp;
			nn = new tnode<key_type>;

			// assigning values to members of new node
			nn->left = H;
			nn->right = H;
			nn->parent = H;
			nn->key = key;
			nn->is_nill = false;

			/// will be true for first node only- 
				H->parent = nn;
				H->left = H->right = nn;
				++n;
				return;

			

		}// end of base case 

		// general case 1: key / new value is less than root node ---- goto left side 
		else{
			temp = H->parent;
			tnode<key_type>* ptr;
			ptr = r_insert(H->parent);
			if (key < H->temp->key) {
				// go on left side

			}
			

			// case1

			
		}

	}/// end of r_insert
};