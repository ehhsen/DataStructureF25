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
	//////////////////////////////////////////////
	forward_list() {
		H = new node<T>;
		//TODO: deallocate 
		H->link = nullptr;
		n = 0;
	}
	/////////////////////////////////////////////////////
	~forward_list() {
		// deallocate memory
		while (H != H->link) {
			node<T>* temp;
			temp = H->link;
			H->link = temp->link;
			delete temp;
		}

	}
	/////////////////////////////////////////////////////////
	bool empty()const {
		return H->link == nullptr;
	}
	/////////////////////////////////////////////////////
	// 
	/////////////////////////////////////////////////////////
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
	/////////////////////////////////////////////////////////
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
	/// resize////r///////////////////////////////
	//void resize(int &new_size){
	//	//case1: sizes are same neither block will run
	//	
	//	//case2: size n > new_size : reduce size
	//	if (n > new_size) {
	//		//////
	//		node<T>* temp;
	//		for(int i = 0; i < new_size ; i++) {
	//			temp = H->link;
	//			H->link = temp->link;
	//			temp->link = H->link;
	//		}
	//		
	//		// delete preceding one
	//		for (int i = 0; i < (n - new_size); i++) {
	//			node<T>* temp1;
	//			temp1 = H->link;
	//			H->link = temp1->link;
	//			delete temp1;
	//		}
	//	}
	//	//case1: size n <  new_size: increase 
	//	if (new_size > n) {
	//		// goto dummy ptr, 

	//		for (int i = 0; i < (new_size - n); i++) {
	//			push_front(0);
	//		}
	//	}
	//	
	//}
	// /////////////////////////////////////////////
	// begin function
	//iterator begin()const {
	//	iterator it;
	//	it.ptr = H->link;
	//	return it;
	//}
	///////////////////////////////
	//iterator end()const {
	//	iterator it;
	//	it.ptr = nullptr;
	//	return it;
	//}
	/////////////////////////////////////////////////////////
	//class iterator {
	//private:
	//	node<T>* ptr;
	//public:
	//	iterator() {
	//		ptr = nullptr;
	//		friend class Forward_list;

	//	}
	//	T& operator*() {
	//		return ptr->val;
	//	}
	//	iterator& operator++() {
	//		iterator it;
	//		//it.ptr = it.ptr->link;
	//		//return it;
	//		ptr = ptr->link;
	//		return *this;
	//	}
	//};
	///////////////////////////////////////end of iterator class
	
	/////////////////////// insert after//////////////////////////
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
};