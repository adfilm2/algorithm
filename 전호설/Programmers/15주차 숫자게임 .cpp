#include <string>
#include <vector>
#include <algorithm>
using namespace std;




int solution(vector<int> A, vector<int> B) {
	int answer = 0;
	sort(B.begin(), B.end());
	sort(A.begin(), A.end());
	int ptrA = 0; int ptrB = 0;
	int len = A.size();
	for (int i = 0; i < len; i++)
	{
		if (ptrB == len) { break; }
		if (A[ptrA] < B[ptrB])
		{
			ptrA++; ptrB++; answer++;
			continue;
		}
		ptrB++;

	}
	return answer;
}