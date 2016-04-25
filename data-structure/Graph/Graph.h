#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <vector>
using namespace std;

enum VertexName { A, B, C, D, E, F, G, H, J };

class Stack
{
public:
	void push(int data) {
		m_list.push_back(data);
	}
	int pop() {
		int ret = m_list.back();
		m_list.pop_back();
		return ret;
	}
	int top() {
		return m_list.back();
	}
	bool is_empty() {
		return static_cast<int>(m_list.size()) <= 0 ? true : false;
	}
	void clear() {
		m_list.clear();
	}
	int size() {
		return static_cast<int>(m_list.size());
	}

private:
	list<int> m_list;
};

class Graph
{
public:
	Graph();
	virtual ~Graph();

	void GraphInit(int nVertices);
	void AddVertex(int data);
	void AddEdge(int fromV, int toV);
	void ShowGraphEdgeInfo();

	void DFSShowGraphVertex(int startV);
	bool VisitVertex(int visitV);

	int m_nVertex;
	int m_nEdge;

private:
	vector< list<int>* > m_nAdjList;
	vector<int> m_VisitInfo;
	Stack m_Stack;
};

#endif // GRAPH_H_
