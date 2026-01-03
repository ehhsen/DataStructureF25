#pragma once
template <typename T>
struct node {
	T val;
	node* link;
};
template <typename T>
class forward_list {
private:
	node<T>* H;
	int n;  // for obtaining size
public:

	template<typename T>
	friend bool operator==(const forward_list<T>& lhs, const forward_list<T>& rhs);

	forward_list() {
		H = new node<T>;
		//TODO: deallocate 
		H->link = nullptr;
		n = 0;
	}
	~forward_list() {
		// deallocate memory
		while (H != H->link) {
			node<T>* temp;
			temp = H->link;
			H->link = temp->link;
			delete temp;
		}
	}

	bool empty()const {
		return H->link == nullptr;
	}
	int size() {
		return n;
	}

	T front()const {
		if (H->link == H) {
			throw("Underflow");
		}
		else {
			return H->link->val;
		}
	}
	/// modifier/////////////////////
	void push_front(const T& val) {
		node<T>* temp;
		temp = new node<T>;
		temp->val = val;
		temp->link = H->link;
		H->link = temp;
		++n;
	}
	void pop_front() {
		if (empty()) {
			throw("Underflow");
		}
		else {
			node<T>* temp;
			temp = H->link;
			H->link = temp->link;
			delete temp;
			--n;
		}
	}

	void resize(int count){
		if (count < 0) {
			return;  // Invalid size
		}
		//case1: sizes are same neither block will run
		if (n == count) {
			//do nothing
		}
		else {
			//case2:  reduce container
			if (this->n > count) {
				if (count == 0) {
					// Delete all nodes
					node<T>* temp = H->link;
					while (temp != nullptr) {
						node<T>* to_delete = temp;
						temp = temp->link;
						delete to_delete;
					}
					H->link = nullptr;
				}
				else {
					// Traverse to the (count-1)th node
					node<T>* temp = H->link;
					for (int i = 1; i < count; ++i) {
						temp = temp->link;
					}
					// Delete all nodes after this point
					node<T>* next_to_last_node = temp->link;
					temp->link = nullptr;
					while (next_to_last_node != nullptr) {
						node<T>* to_be_deleted = next_to_last_node;
						next_to_last_node = next_to_last_node->link;
						delete to_be_deleted;
					}
				}
			}
			else {
				// increase the container
				node<T>* temp = H->link;
				// Traverse to the last node
				for (int i = 1; i < n; ++i) {
					if (temp == nullptr) break;
					temp = temp->link;
				}
				// If list is empty, start from H
				if (n == 0) {
					temp = H;
				}
				// Add new nodes
				for (int i = n; i < count; ++i) {
					node<T>* nn = new node<T>;
					nn->val = T();
					nn->link = nullptr;
					temp->link = nn;
					temp = nn;
				}
			}
		}//end of else
		
		n = count;  // Update size
	}//end of resize
	 


	class iterator {
	private:
		node<T>* ptr;
	public:
		iterator() {
			ptr = nullptr;
			friend class forward_list;

		}
		T& operator*() {
			return ptr->val;
		}
		iterator& operator++() {
			iterator it;
			//it.ptr = it.ptr->link;
			//return it;
			ptr = ptr->link;
			return *this;
		}
	};


	iterator begin()const {
		iterator it;
		it.ptr = H->link;
		return it;
	}

	iterator end()const {
		iterator it;
		it.ptr = nullptr;
		return it;
	}

	void remove(const T& value) {
		//1) Removes all elements that are equal to value(using operator==).
		// take a ptr to H->link;
		
		int counter = 0;
		node<T>* temp, *prev;
		temp = H->link;
		prev = H;
		while (temp != nullptr) {
			if (temp->val == value) {

				node<T>* to_del = temp;
				temp = temp->link;
				if (temp == nullptr) {
					prev->link = H;
				}
				else {

					prev->link = temp;
				}
			
				delete to_del;
				++counter;
			}
			else {
				temp = temp->link;
				prev = prev->link;
			}
		}

		n = n - counter;
	}
	
	//iterator& insert_after(iterator& it, T &val) {
	//	node<T>* temp;
	//	temp = new node<T>;
	//	temp->val = val;
	//	temp->link = it.ptr->link;
	//	it.ptr->link = temp;
	//	it.ptr = it.ptr->link;
	//	return it;
	//}
	////////////////////////////
	//iterator erase_after(const iterator& itr)
	//{

	//	node<T>* temp;
	//	temp= itr.ptr->link;
	//	itr.ptr->link = temp->link;
	//	iterator it;
	//	it.ptr = itr.ptr->link;
	//	delete temp;
	//	--n;
	//	return it;
	//}

	void merge(forward_list& other) {
		node<T> *ptr1, *ptr2;
		ptr1 = this->H;
		ptr2 = other.H->link;
		while (ptr1->link != nullptr && ptr2 != nullptr) {
			if (ptr1->link->val <= ptr2->link->val) {
				ptr1 = ptr1->link;
			}
			else {
				///////////////////
				node<T>* tempp = ptr2->link;
				ptr2->link = ptr1->link;
				ptr1->link = ptr2;
				ptr2 = tempp;
				ptr1 = ptr1->link;
			}////end of else

		}// end of while
		if (ptr2->link != nullptr) {
			ptr1->link = ptr2;
	
		}
		n = n + other.n;
		other.H->link = nullptr;
		other.n = 0;

	}


	void unique() {
		if (empty()) {
			
		}
		else {
			node<T>* prev, * temp;
			prev = H;
			temp = H->link;
			while (temp != nullptr) {
				if (temp->val == prev->val) {
					node<T>* del;
					del = temp;
					temp = temp->link;
					prev->link = temp;
					delete del;
				}
				else {
					prev = prev->link;
					temp = temp->link;
				}
			}
		}
	}//end of unique

};
//declare Non-member functions
template <typename T>
bool operator==(const forward_list<T>& lhs, const forward_list<T>& rhs) {
	if (lhs.n == rhs.n) {
		// take 2 pointers to both list and compare them
		node<T>* list1, *list2;
		list1 = lhs.H->link;
		list2 = rhs.H->link;
		if (rhs.n == 0) {
			return true;
		}

		while (list1 != nullptr) {
			if (list1->val == list2->val) {
				list1 = list1->link;
				list2 = list2->link;
			}
			else {
				return false;
			}
		}
		return true;

	}//end of iff
	return false;
}//end of ==
