#include "Graph.h"
#include <cstdio>

Graph::Graph()
:m_nVertex(0)
,m_nEdge(0)
{

}

Graph::~Graph()
{
	for(int i=0; i<m_nVertex; i++) {
		delete m_nAdjList[i];
	}
}

void Graph::GraphInit(int nVertices)
{
	m_nVertex = nVertices;
	m_nEdge = 0;

	for( int i=0; i<m_nVertex; i++ ) {
		list<int>* pList = new list<int>;
		m_nAdjList.push_back(pList);
	}
}

void Graph::AddVertex(int data)
{
//	m_nAdjList
}

void Graph::AddEdge(int fromV, int toV)
{
	m_nAdjList[fromV]->push_back(toV);
	m_nAdjList[toV]->push_back(fromV);
	m_nEdge++;
}

void Graph::ShowGraphEdgeInfo()
{
	for(int i=0; i<m_nVertex; i++) {
		printf("%c와 연결된 정점: ", i + 65);

		list<int>::iterator it = m_nAdjList[i]->begin();
		for(; it != m_nAdjList[i]->end(); ++it) {
			printf("%c ", *it + 65);
		}
		printf("\n");
	}
}

bool Graph::VisitVertex(int visitV)
{
	// 처음 방문일 경우...
	if(m_VisitInfo[visitV] == 0) {
		m_VisitInfo[visitV] = 1;
		printf("%c ", visitV + 65);
		return true;
	}
	return false;
}

void Graph::DFSShowGraphVertex(int startV)
{
	int visitV = startV;
	int nextV;

	m_Stack.clear();		// 스택 초기화
	m_VisitInfo.clear();	// 배열 초기화
	for( int i=0; i<m_nVertex; i++ ) {
		m_VisitInfo.push_back(0);
	}

//	printf("Stack size: %d\n", static_cast<int>(m_Stack.size()));
//	printf("List size: %d\n", static_cast<int>(m_VisitInfo.size()));

	list<int>::iterator it = m_nAdjList[visitV]->begin();

	VisitVertex(visitV);	// 시작 정점을 방문
	m_Stack.push(visitV);	// 시작 정점 정보를 스택에 담는다


	while( it != m_nAdjList[visitV]->end()) {
		nextV = *it;
		//printf("nextv : %c(%d)\n",nextV + 65, nextV);
		bool visitFlag = false;

		if(VisitVertex(nextV) == true) {
			m_Stack.push(visitV);
			visitV = nextV;
			visitFlag = true;
		} else {
			it = next(it,1);

			while(it != m_nAdjList[visitV]->end()) {
				nextV = *it;

				if(VisitVertex(nextV) == true) {
					m_Stack.push(visitV);
					visitV = nextV;
					visitFlag = true;
					break;
				}

				it = next(it, 1);
			}
		}

		if(visitFlag == false) {
			if(m_Stack.is_empty() == true)
				break;
			else
				visitV = m_Stack.pop();
		}

		it = m_nAdjList[visitV]->begin();
	}
}
