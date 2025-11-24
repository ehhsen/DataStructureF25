#pragma once
template<typename T>
struct dnode {
	T val;
	dnode<T>* next;  // points to next dnode in list
	dnode<T>* prev;		// points to previous dnode in list
};
