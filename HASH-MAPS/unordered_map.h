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

	// insert function
	std::pair  <typename std::list<std::pair<const K, T>>::iterator  , bool   > insert(const std::pair<const K, T>& p) {
		iterator it; // it to um
		typename std::list<std::pair<const K, T>>::iterator it_list;  // iterator to list
		int h = hash(p.first);  // pass key to hashing function
		it_list = find(table[h], p.first);
		if ( it_list == table[h].end()) { // list.end()
			table[h].push_back(p);
			++n;
			return { it_list, true };
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
		unordered_map<const K, T>* um;
	public:
		friend class unordered_map;


	};

};