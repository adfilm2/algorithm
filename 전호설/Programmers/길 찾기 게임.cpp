#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
struct node
{
	int a;
	int b;
	int idx;
	int fromTo[2][2]; //0이 왼쪽 1이 오른쪽
	int child[2] = { -1,-1 };
};
bool cmp(node a, node b)
{
	return a.b > b.b;
};
int len;
vector<node> Graph;
vector<vector<int>> ANS(2, vector<int>());

void GraphIn(int idx, int f1, int t1, int f2, int t2)
{
	Graph[idx].fromTo[0][0] = f1;
	Graph[idx].fromTo[0][1] = t1;
	Graph[idx].fromTo[1][0] = f2;
	Graph[idx].fromTo[1][1] = t2;
}

void FindChild(int parent)
{

	for (int i = parent + 1; i < len; i++)
	{

		if (Graph[i].b == Graph[parent].b) { continue; }
		if (!(Graph[i].a >= Graph[parent].fromTo[0][0] && Graph[i].a <= Graph[parent].fromTo[0][1]))
		{
			continue;
		}
		Graph[parent].child[0] = i;
		GraphIn(i, Graph[parent].fromTo[0][0], Graph[i].a - 1, Graph[i].a + 1, Graph[parent].fromTo[0][1]);
		break;
	}
	for (int i = parent + 1; i < len; i++) //오른쪽 노드
	{
		if (Graph[i].b == Graph[parent].b) { continue; }
		if (!(Graph[i].a >= Graph[parent].fromTo[1][0] && Graph[i].a <= Graph[parent].fromTo[1][1]))
		{
			continue;
		}
		Graph[parent].child[1] = i;
		GraphIn(i, Graph[parent].fromTo[1][0], Graph[i].a - 1, Graph[i].a + 1, Graph[parent].fromTo[1][1]);
		break;
	}
}
int visited[10000];
void DFS(int i)
{
	ANS[0].push_back(Graph[i].idx);
	if (Graph[i].child[0] != -1) { DFS(Graph[i].child[0]); }
	if (Graph[i].child[1] != -1) { DFS(Graph[i].child[1]); }
}

void DFS_I(int i)
{
	if (Graph[i].child[0] != -1) { DFS_I(Graph[i].child[0]); }
	if (Graph[i].child[1] != -1) { DFS_I(Graph[i].child[1]); }
	ANS[1].push_back(Graph[i].idx);
}


vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	len = nodeinfo.size();

	for (int i = 0; i < len; i++)
	{
		node temp;
		temp.a = nodeinfo[i][0];
		temp.b = nodeinfo[i][1];
		temp.idx = i + 1;
		Graph.push_back(temp);
	}
	sort(Graph.begin(), Graph.end(), cmp);
	GraphIn(0, 0, Graph[0].a - 1, Graph[0].a + 1, 100000);
	for (int i = 0; i < len; i++)
	{
		FindChild(i);
	}
	DFS(0); cout << endl;
	DFS_I(0);
	return ANS;
}