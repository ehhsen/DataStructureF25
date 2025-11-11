#pragma once
template <typename key_type>
struct tnode {
	key_type key;  // similar to T val;
	tnode<key_type> * parent, * left, * right;
	bool is_nill;
	tnode() {
		key = key_type();  // val = T();
		left = right = parent = nullptr;
		is_nill = false;
	}
};

