#pragma once
#include"mnode.h"
#include<algorithm>


template <typename key_type, typename T>
class map {
private:
	mnode<key_type, T>* H;
	int n;

	//std::pair<key_type, T>

	// creating successor function tobe used in erase function
	// returns a ptr to successor node 
	mnode<key_type, T>* successor(mnode<key_type, T>* ptr) {          // to_Del ka right side par sab sa chooti value, that is: left most value there
		mnode<key_type, T>* temp;

		//case1:  right child exists
		if (!ptr->right->is_nill) {
			ptr = ptr->right;
			// if left child exists
			while (!ptr->left->is_nill) {
				ptr = ptr->left;
			}
			return ptr;
		}// end of case 1
		else {
			while (ptr->parent->right == ptr  && !ptr->parent->is_nill)
			{
				ptr = ptr->parent;
			}
			ptr = ptr->parent;
			return ptr;

		}
	}//end of successor function


	//recursive clear function
	void clear_r(mnode<key_type, T>* ptr) {
		if (ptr == H) {
			return;
		}
		else {
			clear_r(ptr->left);
			clear_r(ptr->right);
			delete ptr;
		}
	}
	// aik map ki value par insert call karo aur isse dusre map ka andar insert kar do 
	/////////COPY FUNCTION FOR OPERATOR=
	mnode<key_type, T>* copy(mnode<key_type, T>* ptr)
	{
		if (ptr == H) {
			return this->H;
		}
		mnode<key_type, T>* nn;
		nn = new mnode<key_type, T>;
		nn->data.first = ptr->data.first;
		nn->data.second = ptr->data.second;

		nn->height = ptr->height;
		nn->left = copy(ptr->left);
		nn->right = copy(ptr->right);
		nn->parent = H;

		//set parent pointers
		if (nn->left != H) {
			nn->left->parent = nn;
		}
		if (nn->right != H) {
			nn->right->parent = nn;
		}
		return nn;
	}//END OF COPY

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	void update_height(mnode<key_type, T>* ptr) {
		// leaf node sa root node tak sab nodes ki height update kare ga
		ptr->height = 1 + std::max(ptr->left->height, ptr->right->height);
	}
	int balance_factor(mnode<key_type, T>* ptr) {
		// this function will calculate balance factor
		//if balance factor == 2 or -2  we will perform rotations based on x, y, z
		return ptr->left->height - ptr->right->height;
	}

	mnode<key_type, T>* left_rotate(mnode<key_type, T>* ptr) {
		mnode<key_type, T>* x, * y, * left_y, * Parent_x;
		x = ptr;
		Parent_x = x->parent;
		//y = taller child of x : z = taller child of y
		y = x->right;   // agar +ve ha tou left side taller ha agar -ve ha tou right side taller hoge according to our implementation of balance factor
		left_y = y->left;

		///////now change pointers//////////
		//pointer 1: make x left child of y
		y->left = x;
		//pointer 2: change parent of x
		x->parent = y;
		//pointer 3: make left child of y , right child of x
		x->right = left_y;
		//pointer 4: if x->right exists: set its parent tobe x
		if (left_y != H) {
			left_y->parent = x;
		}
		//pointer 5: now assign x ka parent to y
		y->parent = Parent_x;
		//pointer 6: now point x ka parent to y
		if (Parent_x == H) {
			H->parent = y;
		}
		else if (Parent_x->left == x) {  /*agar x apne parent ka left par ha tou y b left pa aye ga*/
			Parent_x->left = y;
		}
		else {
			Parent_x->right = y;
		}
		/////update height of x and y
		update_height(x);
		update_height(y);
		return y;
	}

	mnode<key_type, T>* right_rotate(mnode<key_type, T>* ptr) {
		mnode<key_type, T>* x, * y, * right_y, * Parent_x;
		x = ptr;
		Parent_x = x->parent;
		y = x->left;
		right_y = y->right;

		//changing pointers:
		//1: x ko y ki right par
		y->right = x;
		x->parent = y;
		x->left = right_y;
		if (right_y != H) {
			right_y->parent = x;
		}

		// parent change
		y->parent = Parent_x;
		if (Parent_x == H) {   // checks if x is root node?
			H->parent = y;
		}
		else if (Parent_x->right == x) {
			Parent_x->right = y;
		}
		else {
			Parent_x->left = y;
		}

		// now updating height of x and y
		update_height(x);
		update_height(y);
		return y;

	}

	void rebalance(mnode<key_type, T>* ptr) {
		// in rebalance function
		while (ptr != H) {

			// tree is unbalanced at node ptr
		// now we will balance it, for that we need y and z , these are nodes that have max height along the nn or to_del
		//perfom rotations		
			update_height(ptr);
			if (balance_factor(ptr) >= 2) {  // imbalance is on left side
				if (balance_factor(ptr->left) >= 0) {
					//Left of left  TODO: make a function for it and pass ptr to it 
					ptr = right_rotate(ptr);
				}
				else if (balance_factor(ptr->left) < 0) {
					//Left of right TODO: make a function for it and pass ptr to it 
					left_rotate(ptr->left);
					ptr = right_rotate(ptr);
				}

			}/// >1
			else if (balance_factor(ptr) <= -2) {  // imbalance is on right side
				if (balance_factor(ptr->right) > 0) {
					//RL rotation	TODO: make a function for it and pass ptr to it 
					right_rotate(ptr->right);
					ptr = left_rotate(ptr);
				}
				else if (balance_factor(ptr->right) <= 0) {
					//RR rotation	TODO: make a function for it and pass ptr to it 
					ptr = left_rotate(ptr);
				}
			}// <1

			ptr = ptr->parent;
		}//end of while

	}//end of rebalance 

public:
	// constructor
	map(){
		H = new mnode<key_type, T>;
		H->left = H->right = H->parent = H;
		H->is_nill = true;
		n = 0;
		
	}

	int size()const {
		return this->n;
	}
	bool empty()const {
		return H->left == H->parent == H->right;
	}
	~map() {
		clear();
		delete H;
	}
	////////////////////OPERATOR=//////////////
	map<key_type, T>& operator= (const map<key_type, T>& other) {
		//if (this == &other)
		//	return *this;

		clear();

		//2: set H->left 
		//3: set H->right
		// 
		//1: set parent of H
		if (other.H->parent != other.H) { // will  not copy if other set is empty
			H->parent = copy(other.H->parent);
			H->parent->parent = H; // parent of root node


			//
			mnode<key_type, T>* temp = H->parent;
			while (temp->left != H) {
				temp = temp->left;
			}
			H->left = temp;
			while (temp->right != H) {
				temp = temp->right;
			}
			H->right = temp;
		}
		else { /*will work in case other is empty*/
			H->parent = H;
			H->left = H;
			H->right = H;
		}

		this->n = other.n;
		return *this;
	}// end of operator == 

	//clear function//////////
	void clear() {
		// only dummy node remains all other are deleted 
		clear_r(H->parent);
		H->left = H->parent = H->right = H;
		n = 0;
	}
	/////////////////////////////////////////////////////

	//iterator class 
	class iterator {
	private:
		mnode<key_type, T>* ptr;
	public:
		friend class map<key_type, T>;

		iterator() {
			ptr = nullptr;
		}
		iterator(mnode<key_type, T>* p) : ptr(p) {}

		std::pair<key_type, T>& operator*() const {
			return ptr->data;
		}
		// todo:implement iterator != 
		bool operator!=(const iterator& other) const {
			return this->ptr != other.ptr;
		}
		bool operator==(const iterator& other)const {
			return this->ptr == other.ptr;
		}

		iterator& operator++() {
			//case1:  right child exists
			if (!ptr->right->is_nill) {
				ptr = ptr->right;
				// if left child exists
				while (!ptr->left->is_nill) {
					ptr = ptr->left;
				}
				return *this;
			}// end of case 1

			//case 2: see if tnode is on left side of its parent
			else if (ptr->parent->left == ptr) {
				ptr = ptr->parent;
				return *this;
			}

			//case 3: find node which is NOT on left side of its parent
			else {
				while (ptr->parent->left != ptr && ptr->parent != H) {
					ptr = ptr->parent;
				}
				ptr = ptr->parent;
				return *this;
			}


		}//end of ++

	};// end of iterator class

	T& at(const key_type& key) {
		iterator it = find(key);
		if (it == end()) {
			//value not found
			throw("out of range");
		}
		else {
			return it.ptr->data.second;
		}


	}// end of at{} function

	T& operator[](const key_type& key) {
		iterator it;
		it = find(key);
		if (it == end()) {
			// value not found : insert it
			std::pair<iterator, bool> result;
			result = insert({ key, T() });
			iterator it = result.first;
			
		}
		return it.ptr->data.second;
	}

	//end function
	iterator end() {
		//iterator past the last element
		iterator it;
		it.ptr = H;
		return it;
	}
	//begin function
	iterator begin() {
		//iterator past the last element
		iterator it;
		it.ptr = H->left;
		return it;
	}

	// implement count function
	// it tells if key exists: 1 or does not exists 0
	int  count(const key_type& key)  {
		iterator it = find(key);
		if (it == end()) {
			// value not found 
			return 0;

		}
		else return 1;
	}
	/////////////////////////////////////////////////
	bool contains(const key_type& key) {
		// ya btata ha ka key jese koi key mojuud ha map me ya nahe ?
		iterator it = find(key);
		if (it == end()) {
			// value not found 
			return false;

		}
		else return true;
	}

	///////////////////////////////////////////////
	//find function
	iterator find(const key_type value) {
		mnode<key_type, T>* temp = H->parent; 

		if (temp->data.first == value) {
			iterator it(temp);
			return it;
		}
		while (temp != H)
		{
			if (value < temp->data.first) {  // for smaller 
				temp = temp->left;
				
			}
			else if (value > temp->data.first) {
				temp = temp->right;
				
			}
			else{
				
				return iterator(temp);
			}
			// value not found, reached leaf node's right or left ------ returns iterator pass the last element
		}//end of while
		return end();
	}//end of find 

	////////////////////////////////////////////////////
	//insert function          // iterator to inserted element // bool = true if element inserted successfully
	std::pair<iterator, bool> insert(const std::pair<key_type, T>& p) {
		iterator it = find(p.first);
		//todo: check if value exixts by creating find function 
		if (it != end()) {
			//iterator to that value which is already present
			return std::pair<iterator, bool>(it, false);
		}


		// creating new tnode
		mnode<key_type, T>* nn, * temp;
		nn = new mnode<key_type, T>;
		// assigning values to members of new node
		nn->left = H;
		nn->right = H;
		nn->parent = H;
		nn->data  = p;  // pair is assighned to pair
		nn->is_nill = false;
		nn->height = 1;

		//root node insertion
		if (H->parent == H) {  // only true when tree is empty
			H->parent = H->left = H->right = nn;
			++n;

			H->is_nill = true;
			H->height = 0;
			// now we take iterator to newly inserted tnode and return that
			iterator it(nn);
			return std::pair<iterator, bool>(it, true);

		}
		////////////////////// for all other cases/////////////////////////// 
		temp = H->parent;  // root tnode
		while (true)
		{
			if (p.first < temp->data.first) {  // goto left side 
				if (temp->left != H) {
					temp = temp->left;
				}
				else {
					// no further node availabe, we at leaf node,
					temp->left = nn;
					nn->parent = temp;


					if (p.first < H->left->data.first) {
						H->left = nn;
					}
					if (p.first > H->right->data.first) {
						H->right = nn;
					}
					++n;
					rebalance(nn);
					iterator it(nn);

					// checks for left and right of dummy node 
					if (p.first < H->left->data.first) {
						H->left = nn;
					}
					if (p.first > H->right->data.first) {
						H->right = nn;
					}

					return std::pair<iterator, bool>(it, true);
				}
			}
			////////////////check for right side//////////////////////////////////// 
			else if (p.first > temp->data.first) {
				if (temp->right != H) {
					temp = temp->right;
				}
				else {
					temp->right = nn;
					nn->parent = temp;
					++n;
					rebalance(nn);
					iterator it(nn);

					// checks for left and right of dummy node
					if (p.first < H->left->data.first) {
						H->left = nn;
					}
					if (p.first > H->right->data.first) {
						H->right = nn;
					}

					return std::pair<iterator, bool>(it, true);
				}
		
			}

		}// end of while 
		/////////////////////////////////////AVL		BASED	IMPLEMENTATION		//////////////////////////////////
		// private member function rebalance that will balance the tree after each insertion
		// all other functions needed to balance will be called from this function

		/////////////////////////////////////AVL		BASED	IMPLEMENTATION		//////////////////////////////////


	}//end of insert


	iterator erase(iterator pos)
	{
		mnode<key_type, T>* to_del;  // node we have to delete
		mnode<key_type, T>* left; // left child of to_del
		mnode<key_type, T>* right; // right child of to_del
		to_del = pos.ptr;
		mnode<key_type, T>* succ; // successor tnode
		mnode<key_type, T>* BASHEER; // this node will be give as a  and argument to implemement AVL;
		succ = successor(to_del);

		// todo: deleting root node case 

		//case 1: deleting leaf tnode////////////////////////////////////
		if (to_del->left == H && to_del->right == H)
		{   // leaf node
			//left child
			BASHEER = to_del->parent;
			if (to_del->parent->left == to_del) {
				to_del->parent->left = H;
			}
			else {
				to_del->parent->right = H;
			}

			/////////////////////////////////////// check  H->left an H->right 
			if (to_del == H->left) {
				H->left = succ;
			}
			if (to_del == H->right) {
				H->right = to_del->parent;
			}
			////////////////////////////////////////
			
			delete to_del;
			--n;
	/*		iterator it;
			it.ptr = succ;*/



			rebalance(BASHEER);
			return iterator(succ);
		}//end of if

		//case 2: node has only 1 child : either left or right
		//case 2.1: has only left child
		else if (to_del->left != H && to_del->right == H)
		{
			left = to_del->left;
			if (to_del->parent->left == to_del) {
				to_del->parent->left = left;
			}
			else {
				to_del->parent->right = left;
			}
			left->parent = to_del->parent;

			BASHEER = to_del->parent;
			if (to_del == H->right) {
				H->right = to_del->parent;
			}

			delete to_del;
			--n;
			rebalance(BASHEER);
		
			return iterator(succ);
		}// end of case when node has only 1 child and its only left child 

		//case 2.2
		else if (to_del->right != H && to_del->left == H)
		{
			right = to_del->right;
			BASHEER = to_del->parent;
			if (to_del->parent->left == to_del) {  //check if to_Del is right child or left child
				to_del->parent->left = right;

			}
			else {
				to_del->parent->right = right;
			}
			right->parent = to_del->parent;
			
			BASHEER = to_del->parent;

			// Update H pointers
			if (to_del == H->left) {
				H->left = succ;
			}

			delete to_del;
			rebalance(BASHEER);
			--n;
			
			return iterator(succ);

		}// end of case when node has only 1 child and its only right child 


		//case 3: to_del has 2 childs
		// we need successor private function
		else
		{
			to_del->data = succ->data;
			BASHEER = succ->parent;
			// succ is immediate right child
			if (to_del->right == succ)
			{
				succ->left = to_del->left;
				to_del->left->parent = succ;
				succ->parent = to_del->parent;

				if (to_del->parent->right == to_del) {
					to_del->parent->right = succ;
				}
				else {
					to_del->parent->left = succ;
				}
			}

			///////////////////////////////////////
			//case 1: succ is in left subtree of to_del->right
			else
			{
				// part 1: remove succ from its current position, relocate its ptrs
				//succ's right exists then move its right 
				if (!succ->right->is_nill)
				{
					succ->right->parent = succ->parent;
				}
				succ->parent->left = succ->right;

				// part 2: move succ to replace to_del
				succ->left = to_del->left;
				succ->right = to_del->right;
				succ->left->parent = succ;
				succ->right->parent = succ;
				succ->parent = to_del->parent;

				if (to_del->parent->left == to_del) {
					to_del->parent->left = succ;
				}
				else {
					to_del->parent->right = succ;
				}
			}// end of else

			//if succ is intermediate node then 
			if (to_del->right == succ) {
				BASHEER = succ;
			}
			else {
				BASHEER = succ->parent;
			}
			delete succ;

			rebalance(BASHEER);

			--n;
			return iterator(succ);
			
		}//end of else 	
	}//end of erase 
};
