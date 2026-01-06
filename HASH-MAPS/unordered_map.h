#pragma once
#include<list>
#include<utility>
template<typename K, typename T>
class unordered_map {
private:
	std::list<std::pair<const K, T>>* table;
	int m;  // table size;
	int n;  // number of values in unordered map
	
	size_t hash(const K& key) const {
		return std::hash<K>{}(key); // may have to convert into float before taking modulus
	}
	// we take hash table of size =  prime number, then to increase that we take size of next big prime number
	 
	// find function
	std::list<std::pair<const K, T> >:: iterator
		find_key(std::list<std::pair<const K, T>>& L, const K& key) {
		typename std::list<std::pair<const K, T>>::iterator it_list;
		it_list = L.begin();
		while (it_list != L.end()) {
			// traverse whole list 
			if (key == it_list->first) {
				return it_list;
			}
			++it_list;
		}
		return it_list;
	}
public:
	class iterator;

	// constructor
	unordered_map(int s = 17) {
		m = s;
		n = 0;
		table = new std::list<std::pair< const K, T>>[s];
	}
	~unordered_map() {
		delete[] table;
	}

	// insert function
	std::pair  <typename std::list<std::pair<const K, T>>::iterator  , bool> 
		insert(const std::pair<const K, T>& p) {
		iterator it; // it to um
		typename std::list<std::pair<const K, T>>::iterator it_list;  // iterator to list
		int idx = hash(p.first) % m;  // pass key to hashing function
		it_list = find_key(table[idx], p.first);
		if ( it_list == table[idx].end()) { // list.end()
			table[idx].push_back(p);
			++n;

			typename std::list<std::pair<const K, T>>::iterator nn;
			nn = table[idx].end();
			--nn;
			// taking an iterator to new element and returning

			return { nn, true };
		}
		else {
			return { it_list, false };// key already exists
		}
	}

	class iterator {
	private:
		int idx;  // index of table
		// iterator to list   
		typename std::list<std::pair<const K, T>>::iterator it_list;  
		const unordered_map< K, T>* um;
	public:
		friend class unordered_map< K, T>;
		iterator() {
			

		}

		iterator(const unordered_map<K, T>* map, int index,
			typename std::list<std::pair<const K, T>>::iterator list)
			: um(map), idx(index), it_list(list) {}   // list initializer method

		std::pair<const K, T>& operator*() const {
			return *it_list;
		}
		
		iterator& operator++() {
			++it_list; // plus plus list iterator
			if (it_list == um->table[idx].end()) {
				++idx;
				while (idx < um -> m && um->table[idx].empty()) {
					++idx;
				}
				if (idx < um->m) {
					it_list = um->table[idx].begin();
					
				}
				else {
					idx = um->m - 1;
					it_list = um->table[idx].end();
				}

			}
			return *this;
		}// end of operator++

		// ++pos
		iterator operator++(int)
		{
			iterator temp = *this;
			++(*this);
			return temp;
		}

		bool operator!=(const iterator& other) const {
			if (um != other.um ||	idx != other.idx || it_list != other.it_list) {
				return true;
			}
			else {
				return false;
			}
		}

		bool operator==(const iterator& other) const {
			if (um == other.um && idx == other.idx && it_list == other.it_list) {
				return true;
			}
			else {
				return false;
			}
		}

		std::pair<const K, T>* operator->() const {
			return &(*it_list);
		}	
	};

	/////// BEGIN ////
	iterator begin()const {
		iterator it;
		it.um = this;
		it.idx = 0;
		while (it.idx < m && table[it.idx].empty()) {
			++it.idx;
		}
		if (it.idx < m) {

			it.it_list = table[it.idx].begin();
		}
		else{
			it.idx = m - 1;
			it.it_list = table[it.idx].end();
		}
		return it;
	}
	iterator end()const {
		iterator it;
		it.um = this;
		it.idx = m - 1;
		it.it_list = table[it.idx].end();
		return it;
	}

	bool empty() {
		return n == 0;
	}
	int size() {
		return n;
	}
	iterator erase(iterator pos) {
		iterator it2 = pos;
		++it2;
		table[pos.idx].erase(pos.it_list);
		--n;
		return it2;
	}

	void clear()
	{
		delete[] table;
		table = new std::list<std::pair<const K, T>>[m];  
		n = 0;
	}

	void swap(unordered_map& other) {
		std::swap(this->m , other.m);
		std::swap(this->n , other.n);
		std::swap(this->table ,  other.table);
	}

	iterator find(const K & key)const {
			int h = hash(key);
			int idx = h % m;

			typename std::list<std::pair<const K, T>>::iterator it_list;
			it_list = table[idx].begin();
			while (it_list != table[idx].end()) {
				if (key == it_list->first) {
					// key found

					return iterator(this, idx, it_list);
				}
				++it_list;
			}

			return end();
		}

		//LOOKUP  first implement find(key)
		T& at(const K& key)const {
			iterator it = find(key);
			if (it == end()) {
				// key not found
				throw("out of range");

			}
			else {
				// key found
				return it->second;
			}
		}

		T& operator[](const K& key) {
			// return value or insert new and then return 
			iterator it = find(key);
			if (it == end) {
				// key does not exists:  INSERT

				std::pair  <typename std::list<std::pair<const K, T>>::iterator, bool> res insert(key, T());
				return res->second;
			}
			return it.um->table[it.idx].
		}
};

