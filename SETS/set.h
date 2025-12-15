#pragma once
#include"tnode.h"
#include<algorithm>
#include<queue>

template <typename key_type>
class set {
private:
	tnode<key_type>* H;
	int n;

	// creating successor function tobe used in erase function
	// returns a ptr to successor node 
	tnode<key_type>* successor(tnode<key_type>* ptr) {          // to_Del ka right side par sab sa chooti value, that is: left most value there
		tnode<key_type>* temp;

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
			while (ptr->parent->right == ptr) {
				ptr = ptr->parent;
			}
			ptr = ptr->parent;
			return ptr;

		}
	}//end of successor function


	//recursive clear function
	void clear_r(tnode<key_type>* ptr) {
		if (ptr == H) { 
			return;
		}
		else {
			clear_r(ptr->left);
			clear_r(ptr->right);
			delete ptr;
		}
	}
	/////////COPY FUNCTION FOR OPERATOR=
		tnode<key_type>* copy(tnode<key_type>* ptr)
		{
			if(ptr->is_nill) {
				return this->H;
			}
			tnode<key_type>* nn;
			nn = new tnode<key_type>;
			nn->key = ptr->key;

			nn->left = copy(ptr->left);
			nn->right = copy(ptr->right);
				
			//set parent pointers
			if (nn->left != H) {
				nn->left->parent = nn;
			}
			if (nn->right != H) {
				nn->right->parent = nn;
			}
			return nn;
		}//END OF COPY


	void update_height(tnode<key_type>* ptr) {
		// leaf node sa root node tak sab nodes ki height update kare ga
		ptr->height = 1 + std::max(ptr->left->height, ptr->right->height);
	}
	int balance_factor(tnode<key_type>* ptr) {
		// this function will calculate balance factor
		//if balance factor == 2 or -2  we will perform rotations based on x, y, z
		return ptr->left->height - ptr->right->height;
	}

	tnode<key_type>* left_rotate(tnode<key_type>* ptr) {
		tnode<key_type>* x, *y, *left_y, *Parent_x;
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

	tnode<key_type>* right_rotate(tnode<key_type>* ptr) {
		tnode<key_type>* x, * y, * right_y, *Parent_x;
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

	void rebalance(tnode<key_type>* ptr) {
		// in rebalance function
		while (ptr != H) {

			// tree is unbalanced at node ptr
		// now we will balance it, for that we need y and z , these are nodes that have max height along the nn or to_del
		//perfom rotations		
			update_height(ptr);
			if (balance_factor(ptr) >= 2 ){  // imbalance is on left side
				if (balance_factor(ptr->left) >= 0) {
					//Left of left  TODO: make a function for it and pass ptr to it 
					right_rotate(ptr);
				}
				else if (balance_factor(ptr->left) < 0) {
					//Left of right TODO: make a function for it and pass ptr to it 
					left_rotate(ptr->left);
					right_rotate(ptr);
				}
				
			}/// >1
			if (balance_factor(ptr) <= -2) {  // imbalance is on right side
				if (balance_factor(ptr->right) > 0) {
					//RL rotation	TODO: make a function for it and pass ptr to it 
					right_rotate(ptr->right);
					left_rotate(ptr);
				}
				else if (balance_factor(ptr->right) <= 0) {
					//RR rotation	TODO: make a function for it and pass ptr to it 
					left_rotate(ptr);
				}
			}// <1

			ptr = ptr->parent;
		}//end of while
		
	}//end of rebalance 

public:
	// constructor
	set() {
		H = new tnode<key_type>;
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
	~set() {
		clear();
		delete H;
	}
	////////////////////OPERATOR=//////////////
	set<key_type>& operator= (const set<key_type>& other) {
		
		clear();
		
		//2: set H->left 
		//3: set H->right
		// 
		//1: set parent of H
		if (other.H->parent != other.H) { // will  not copy if other set is empty
			H->parent = copy(other.H->parent);
			H->parent->parent = H; // parent of root node
			
		}
		//
		tnode<key_type>* temp = H->parent;
		while (temp->left != H) {
			temp = temp->left;
		}
		H->left = temp;
		while (temp->right != H) {
			temp = temp->right;
		}
		H->right = temp;
	
		this->n = other.n;
		return *this;
	}

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
		tnode<key_type>* ptr;
	public:
		friend class set<key_type>;

		iterator() {
			ptr = nullptr;
		}
		iterator(tnode<key_type>* p) : ptr(p) {}

		key_type& operator*() const {
			return ptr->key;
		}
		// todo:implement iterator != 
		bool operator!=(const iterator& other) const {
			return this->ptr != other.ptr;
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
				while (ptr->parent->left != ptr) {
					ptr = ptr->parent;
				}
				ptr = ptr->parent;
				return *this;
			}


		}//end of ++

	};

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

	///////////////////////////////////////////////
	//find function
	iterator find(const key_type value) {
		tnode<key_type>* temp = H->parent;

		if (temp->key == value) {
			iterator it(temp);
			return it;
		}
		while (true)
		{
			if (value < temp->key) {  // for smaller 
				temp = temp->left;
				if (temp->key == value) {
					iterator it(temp);
					return it;
				}

			}
			else if (value > temp->key) {
				temp = temp->right;
				if (temp->key == value) {
					iterator it(temp);
					return it;
				}

			}
			if (temp == H) {// value not found, reached leaf node's right or left ------ returns iterator pass the last element
				return end();
			}
		}//end of while
	}//end of find 

	////////////////////////////////////////////////////
	//insert function          // iterator to inserted element // bool = true if element inserted successfully
	std::pair<iterator, bool> insert(const key_type& value) {
		iterator it = find(value);
		//todo: check if value exixts by creating find function 
		if (it != end()) {
			//iterator to that value which is already present
			return std::pair<iterator, bool>(it, false);
		}


		// creating new tnode
		tnode<key_type>* nn, * temp;
		nn = new tnode<key_type>;
		// assigning values to members of new node
		nn->left = H;
		nn->right = H;
		nn->parent = H;
		nn->key = value;
		nn->is_nill = false;

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
		////////////////////// for all other cases 
		temp = H->parent;  // root tnode
		while (true)
		{
			if (value < temp->key) {  // goto left side 
				if (temp->left != H) {
					temp = temp->left;
				}
				else {
					// no further node availabe, we at leaf node,
					temp->left = nn;
					nn->parent = temp;


					if (value < H->left->key) {
						H->left = nn;
					}
					if (value > H->right->key) {
						H->right = nn;
					}
					++n;
					iterator it(nn);
					return std::pair<iterator, bool>(it, true);
				}
			}
			////////////////check for right side//////////////////////////////////// 
			else if (value > temp->key) {
				if (temp->right != H) {
					temp = temp->right;
				}
				else {
					temp->right = nn;
					nn->parent = temp;
					++n;
					iterator it(nn);
					return std::pair<iterator, bool>(it, true);
				}
				if (value < H->left->key) {
					H->left = nn;
				}
				if (value > H->right->key) {
					H->right = nn;
				}
			}

		}// end of while 
		/////////////////////////////////////AVL		BASED	IMPLEMENTATION		//////////////////////////////////
		// private member function rebalance that will balance the tree after each insertion
		// all other functions needed to balance will be called from this function
		 
		rebalance(nn);
		
		/////////////////////////////////////AVL		BASED	IMPLEMENTATION		//////////////////////////////////


		return { iterator(), false };

	}//end of insert


	iterator erase(iterator pos)
	{
		tnode<key_type>* to_del;  // node we have to delete
		tnode<key_type>* left; // left child of to_del
		tnode<key_type>* right; // right child of to_del
		to_del = pos.ptr;
		tnode<key_type>* succ; // successor tnode
		tnode<key_type>* BASHEER; // this node will be give as a  and argument to implemement AVL;
		succ = successor(to_del);

		//case 1: deleting leaf tnode////////////////////////////////////
		if (to_del->left == H && to_del->right == H)
		{   // leaf node
			//left child
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
			BASHEER = to_del->parent;
			delete to_del;
			--n;
			iterator it;
			it.ptr = succ;



			rebalance(BASHEER);
			return it;
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

			delete to_del;
			--n;
			rebalance(BASHEER);
			iterator it;
			it.ptr = succ;
			return it;
		}// end of case when node has only 1 child and its only left child 

		//case 2.2
		else if (to_del->right != H && to_del->left == H)
		{
			right = to_del->right;
			if (to_del->parent->left == to_del) {  //check if to_Del is right child or left child
				to_del->parent->left = right;

			}
			else {
				to_del->parent->right = right;
			}
			succ = successor(to_del);
			BASHEER = to_del->parent;

			delete to_del;
			rebalance(BASHEER);
			--n;
			iterator it;
			it.ptr = succ;
			return it;

		}// end of case when node has only 1 child and its only right child 


		//case 3: to_del has 2 childs
		// we need successor private function
		else
		{
			succ = successor(to_del);

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

			//if succ id intermediate node then 
			if (to_del->right == succ) {
				BASHEER = succ;
			}
			else {
				BASHEER = succ->parent;
			}
			delete to_del;
		
			rebalance(BASHEER);
			
			--n;
			return iterator(succ);
			// todo: deleting root node case }
		}//end of else 	
	}//end of erase 
	////////////////////////////////  test code generated by Gen Ai only for testing purposes
	void inorder_r(tnode<key_type>* node) {
		if (node == H) return;

		inorder_r(node->left);
		std::cout << node->key << " ";
		inorder_r(node->right);
	}
	void inorder() {
		inorder_r(H->parent);   // root lives here
		std::cout << "\n";
	}
	void level_order() {
		if (H->parent == H) return;

		std::queue< tnode<key_type>* > q;
		q.push(H->parent);

		while (!q.empty()) {
			auto* cur = q.front(); q.pop();
			std::cout << cur->key << "(h=" << cur->height << ") ";

			if (cur->left != H) q.push(cur->left);
			if (cur->right != H) q.push(cur->right);
		}
		std::cout << "\n";
	}

};
