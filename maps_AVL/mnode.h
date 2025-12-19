#pragma once
template<typename key_type, typename T>
struct mnode {
	std::pair<key_type, T> data;
	mnode<key_type, T>* parent, * left, *right;
	int height;
	bool is_nill;
	mnode() {
		is_nill = false;
		height = 1;
		left = right = parent = nullptr;
		data.first = key_type();
		data.second = T();
	}
};

