#pragma once
#include<list>
#include<utility>
template<typename K, typename T>
class unordered_map {
private:
	std::list<std::pair<const K, T>>* table;
	int m;  // table size;
	int n;  // number of values in unordered map
	
	int hash(const K& key) const {
		return key % m; // may have to convert into float before taking modulus
	}
	// we take hash table of size =  prime number, then to increase that we take size of next big prime number
	 
	// find function
	std::list<std::pair<const K, T> >:: iterator
		find(std::list<std::pair<const K, T>>& L, const K& key) {
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
	////////////////////
	~unordered_map() {
		delete[] table;
	}

	// insert function
	std::pair  <typename std::list<std::pair<const K, T>>::iterator  , bool   > insert(const std::pair<const K, T>& p) {
		iterator it; // it to um
		typename std::list<std::pair<const K, T>>::iterator it_list;  // iterator to list
		int h = hash(p.first);  // pass key to hashing function
		it_list = find(table[h], p.first);
		if ( it_list == table[h].end()) { // list.end()
			table[h].push_back(p);
			++n;

			typename std::list<std::pair<const K, T>>::iterator nn;
			nn = table[h].end();
			--nn;
			// taking an iterator to new element and returning

			return { nn, true };
		}
		else {
			return { it_list, false };// key already exists
		}
	}

	// class iterator to the unordered map

	class iterator {
	private:
		int idx;  // index of table------------
		// iterator to list        [.][--/\--][.]
		typename std::list<std::pair<const K, T>>::iterator it_list;  
		const unordered_map< K, T>* um;
	public:
		friend class unordered_map< K, T>;

		//////////
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
				if (idx == um->m) {
					idx = um->m - 1;
				}
				it_list = um->table[idx].begin();

			}
			return *this;
		}// end of operator++

		bool operator!=(const iterator& other) const {
			if (um != other.um ||	idx != other.idx || it_list != other.it_list) {
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
		if (it.idx == m) {
			it.idx = m - 1;
		}
		it.it_list = table[it.idx].begin();
		return it;
	}
	iterator end()const {
		iterator it;
		it.um = this;
		it.idx = m - 1;
		it.it_list = table[it.idx].end();
		return it;
	}

	/////////////////////////CAPACITY////////////
	bool empty() {
		return n > 0;
	}
	int size() {
		return n;
	}


	iterator erase(iterator pos) {
		iterator it2 = pos;
		++it2;
		pos.um->table[pos.idx].erase(pos.it_list);
		return it2;
	}
};
