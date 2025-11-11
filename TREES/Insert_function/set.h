#pragma once
#include"tnode.h"

template <typename key_type>
class set {
private:
	tnode<key_type> *H;
	int n;
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
					temp->left == nn;
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


	//end of class
};