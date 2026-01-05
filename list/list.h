#pragma once
#include"dnode.h"

template<typename T>
class list {
private:
	dnode<T>* H;  // for dummy dnode
	int n; //for size
	friend class iterator;
public:
	template <typename U>
	friend bool operator==(const list<U>& lhs, const list<U>& rhs);
	
	//constuctor 
	list() {
		H = new dnode<T>;
		this->H->next = this->H->prev = this->H;
		this->n = 0;
	}
	/////////////////////////////////
	~list() {
		clear();
		delete H;  // dummy dnode<T>
	}
	////////////////////////////////////
	//	OPERATOR=
	
	list& operator=(const list& other) {
		
		this->clear();
		while (n <= other.n) {
			// allocate memory for nodes 
			dnode<T>* nn, *temp;
			nn = new dnode<T>;
			temp = other.H->next;
			nn->val = temp->val;
			nn->prev = H;
			nn->next = H->next;
			if (H->prev == H) { // check it we have no dnode, then 
				H->prev = nn;
				H->next = nn;
			}
			else {
				// link 2nds nodes prev ptr to nn
				nn->next->prev = nn;
			}
			++n;
			temp = temp->next;

		}
		return *this;

	}
	////////////////////////////////
	void push_front(const T& value) {
		dnode<T>* nn;
		nn = new dnode<T>;

		nn->val = value;

		nn->prev = H;
		nn->next = H->next;

		H->next = nn;
		if (H->prev == H) { // check it we have no dnode, then 
			H->prev = nn;
		}
		else {
			// link 2nds nodes prev ptr to nn
			nn->next->prev = nn;
		}
		++n;
	}
	///////////////////////////////////
	void push_back(const T& value) {
		dnode<T>* nn;
		nn = new dnode<T>;

		nn->val = value;
		nn->next = H;
		nn->prev = H->prev;

		if (H->next == H) {
			H->next = nn;
		}
		else {
			H->prev->next = nn;
		}
		H->prev = nn;
		++n;
	}
	/////////////////////////////////////
	T& front()const {
		return this->H->next->val;
	}
	/////////////////////////////
	T& back()const {
		return this->H->prev->val;
	}
	/////////////////////////////////
	bool empty()const {
		return n == 0;
	}
	//////////////////////////////////
	int size()const {
		return n;
	}
	///////////////////////////////////
	void pop_front() {
		dnode<T>* temp, *ptr;
		temp = H->next;
		ptr = temp->next;
		H->next = temp->next;
		ptr->prev = H;
		--n;
		delete temp;
	}
	///////////////////////////
	void pop_back() {
		dnode<T>* temp;
		temp = H->prev;
		H->prev = temp->prev;
		temp->prev->next = H;
		delete temp;
		--n;
	}
	/////////////////////////////
	class iterator {
	private:
		dnode<T>* ptr;
		friend class list<T>;
	public:
		//nothing yet
		iterator() {
			ptr = nullptr;
		}
		//OVERLOADING OPERATOR
		iterator& operator++() {
			this->ptr = this->ptr->next;
			return *this;
		}

		iterator& operator--() {
			this->ptr = this->ptr->prev;
			return *this;
		}


		T& operator* ()const {
			return ptr->val;
		}
		bool operator!= (iterator it)const {
			return this->ptr != it.ptr;

		}
		bool operator==(const iterator pos)const {
			return ptr == pos.ptr;
		}

	
	};
	////////////////////////////
	iterator begin()const {
		iterator it;
		it.ptr = H->next;
		return it;
	}
	///////////////////////////
	iterator end()const {
		iterator it;
		it.ptr = H;
		return it;
	}
	////////////////////////////

	/////////////////////////////
	class reverse_iterator {
	private:
		dnode<T>* ptr;
		friend class list<T>;
	public:
		
		reverse_iterator() {
			ptr = nullptr;
		}
		//OVERLOADING OPERATOR
		reverse_iterator& operator++() {
			this->ptr = this->ptr->prev;
			return *this;
		}

		reverse_iterator& operator--() {
			this->ptr = this->ptr->next;
			return *this;
		}
		T& operator* () {
			return ptr->val;
		}
	};
	//////////////////////
		//implementing rbegin and rend//
	reverse_iterator rend() {
		reverse_iterator rit;
		rit.ptr = H;  // dummy dnode
		return rit;
	}
	///////////////////////////////
	reverse_iterator rbegin() {
		reverse_iterator rit;
		rit.ptr = H->prev;
		return rit;
	}
	///////////////////////////////////

	void clear() {
		while (H->prev != H) {
			dnode<T>* temp;
			temp = H->prev;
			H->prev = temp->prev;
			temp->prev->next = H;
			delete temp;
			--n;
		}

	}
	////////////////////////////////////
	//input: iterator before which value will be inserted
	//process: add value before pos
	//output: iterator to inserted dnode

	iterator insert(iterator pos, const T& value) {
		// crate new node
		dnode<T>* nn;
		nn = new dnode<T>;
		nn->val = value;

		// setting pointers of nn
		nn->next = pos.ptr;
		nn->prev = pos.ptr->prev;

		pos.ptr->next->prev = nn;
		pos.ptr->next = nn;
		++n;
		// take an itetaor to nn and return that
		
		iterator it;
		it.ptr = nn  // new dnode 
		return it;
	}// end of insert function

	// erase function
	// input: iterator to a dnode
	// output: iterator to dnode after erased node
	// process:: link pointers--- check if it was last node--- return iterator
	iterator erase(iterator pos) {
		if (pos == begin()){
			return end();
		}
		dnode<T>* temp;
		temp = pos.ptr;
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		
		/// element removed
		iterator it;
		it.ptr = temp->next;
		delete temp;
		return it;
	}
	////////////////////////////////////////////////////////////////////////
	// Resizes the container to contain count elements:

	//	If the current size is less than count, then:
	//1) Additional copies of T()(until C++11)default - inserted elements(since C++11) are appended.
	
	// RESIZE FUNCTION//////////

	void resize(int count) {
		//If count is equal to the current size, does nothing.
		if (count == n) {

		}
		//	If the current size is greater than count, the container is reduced to its first count elements.

		else if (count < n) {
			for (int i = n ; i >  count ; --i){
				pop_back();
			}
		}
		else { // in this case: we have to add nodes:
			for(int i = n; i < count; ++i){
				push_back(T());
			}
		}
	}// end of resize 
	//////////////////////////////////////////////////////////
	void swap(list& other) {
		dnode<T>* temp1 = H; // points to dummy head of this

		H = other.H;
		other.H = temp1;

		int N;
		N = n;
		n = other.n;
		other.n = N;

	}// end of swap
	/////////////////////////////////////////////////////////////////////
	//OPERATIONS
	void merge(list& other) {
		//MERGES Two sorted list into one sorted list
		if (this == &other) { // overload == operator in list
			// nothing will be done
		}
		else {
			H->prev->next = other.H->next;
			other.H->next->prev = H->prev;
			H->prev = other.H->prev;
			other.H->prev->next = H;
			n = (n + other.n);
			other.n = 0;
			other.H->next = other.H->prev = other.H;
		}
	}// end of merge
	////////////////////////////////////////
	// splice///
	void splice(iterator pos, list& other) {
		other.H->prev->next = pos.ptr->next;
		pos.ptr->next->prev = other.H->prev->next;
		pos.ptr->next = other.H->next;
		other.H->next->prev = pos.ptr;
	}
	////////////////////////////////////
	//remove
	void remove(const T& value) {
		//1) Removes all elements that are equal to value(using operator==).
		// take a temp, compare its val with value , if same , set ptrs and then remove that node containing val == value
		dnode<T>* temp;
		temp = H->next;
		
		
		while (temp != H){
			// compare 
			if (temp->val == value) {
				// remove by taking a pointer to it 
				dnode<T>* to_del;
				to_del = temp;
				temp = temp->next;
				to_del->prev->next = to_del->next;
				to_del->next->prev = to_del->prev;
				delete to_del;	
				--n;	
			}
			else {
				temp = temp->next;
			}
			
			
		}


	}




	// has bugs : TODO === Remove them , 
	void reverse() {
		// reverses order such thAT NO ptr or iterator is violated
		dnode<T>* e, * s;  // s= starting,  e =  ending  node od non reversed list 
		s = H->next;
		e = H->prev;
		H->next = e;
		while (s->next != H) {
			// change their order
			e->prev->next = H;
			H->prev = e->prev;

			e->prev = s->prev;
			e->next = s;

			s->prev = e;
		}
	}//end of reverse 
};

//////////////////////////////////////////
//operator overloading 
template <typename T>
bool operator==(const list<T>& lhs, const list<T>& rhs) {
	// compare their values
	if (lhs.size() != rhs.size()) {
		return false;
	}
	else {
		typename list<T>::iterator li = lhs.begin();
		typename list<T>::iterator ri = rhs.begin();

		while (li != lhs.end()) {
			if (*li != *ri) {
				return false;
			}
			++li;
			++ri;
		}
		return true;
	}

}// end of operator=

///////////////////////////////////////////



