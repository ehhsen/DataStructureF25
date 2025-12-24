#pragma once
#pragma once
#include <forward_list>
#include<stack>
#include<queue>
#include<map>
//Directed graph
//Weighted graph
template<typename V, typename E>
class graph {
private:
	std::forward_list<std::pair<int, E>>* edges;
	V* vertices;
	int g_size;
	int n;
	void grow_graph(int new_size) {

	}

	int get_index(const V& v) const {
		for (int i = 0; i < n; ++i) {
			if (vertices[i] == v)
				return i;
		}
		return -1;
	}
public:
	graph(int S = 100) {
		g_size = S;
		n = 0;
		edges = new std::forward_list<std::pair<int, E>>[S];
		vertices = new V[S];
	}

	~graph() {
		delete[] vertices;
		delete[] edges;
	}

	void add_vertex(const V& v) {
		vertices[n] = v;
		++n;
	}

	void add_edge(const V& s, const V& d, const E& w) {
		int s_i, d_i;
		s_i = get_index(s);
		d_i = get_index(d);
		if (s_i == -1 || d_i == -1)
			throw("Invalid vertex");
		edges[s_i].push_front({ d_i, w });
	}

	void clear() {
		/*
		delete[]vertices;
		delete[]edges;
		edges = new forward_list<std::pair<int, E>>[g_size];
		vertices = new V[g_size];
		*/

		for (int i = 0; i < n; ++i)
			edges[i].clear();
		n = 0;

	}

	bool is_empty() const {
		return n == 0;
	}

	bool is_full() const {
		return g_size == n;
	}

	E weight(const V& s, const V& d) const {
		int s_i, d_i;
		s_i = get_index(s);
		d_i = get_index(d);
		auto it = edges[s_i].begin();
		while (it != edges[s_i].end()) {
			if (it->first == d_i)
				return it->second;
			++it;
		}
		throw("Edge does not exist");
	}

	std::forward_list<V> neighbors(const V& v) const {
		int v_i;
		v_i = get_index(v);
		std::forward_list<V> f;
		auto it = edges[v_i].begin();
		while (it != edges[v_i].end()) {
			f.push_front(vertices[it->first]);
			++it;
		}
		return f;
	}

	//Depth First Search
	bool  search_dfs(const V& s, const V& d)const
	{
		// mark starting vertex
		// take a  map ;  store s  , with value = 1;
		std::map<const V, int> m;
		int value = 1;
		m.insert({ s, value });

		// push start vertex on stack
		std::stack<V> stk;
		stk.push(s);
		V check_start = s;

		//while stack is  not empty
		while (!stk.empty()) {
			//pop  s from stack
			V source_vtx = stk.top();
			stk.pop();
			if (source_vtx == d)
			{
				return true;
			}
			// find neighbours of s,  
			// those will be stored in forwards list
			std::forward_list<V> neighbours_of_s;
			neighbours_of_s = neighbors(source_vtx);


			// find unmarked neighbours of v
			while (!neighbours_of_s.empty())
			{
				m.insert({ neighbours_of_s.front(), value });
				stk.push(neighbours_of_s.front());
				neighbours_of_s.pop_front();
			}
		}// end of while
		return false;
		
	}//end of  search dfs

	bool search_bfs(const V& s, const V& d)const {
		// mark starting vertex
		// take a  map ;  store s  , with value = 1;
		std::map<const V, int> m;
		int value = 1;
		m.insert({ s, value });

		// push start vertex on queue
		std::queue<V> que;
		que.push(s);
		V check_start = s;

		//while queue is  not empty
		while (!que.empty()) {
			//pop  s from stack
			V source_vtx = que.front();
			que.pop();
			if (source_vtx == d)
			{
				return true;
			}
			// find neighbours of s,  
			// those will be stored in forwards list
			std::forward_list<V> neighbours_of_s;
			neighbours_of_s = neighbors(source_vtx);


			// find unmarked neighbours of v
			while (!neighbours_of_s.empty())
			{
				m.insert({ neighbours_of_s.front(), value });
				que.push(neighbours_of_s.front());
				neighbours_of_s.pop_front();
			}
		}// end of while
		return false;

	}//end of bfs

};