// FriendList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <deque>
using namespace std;

int main()
{
	/*string oInputFile = "tripin.txt";
	string oOutputFile = "tripout.txt";

	freopen(oInputFile.data(), "r", stdin);
	freopen(oOutputFile.data(), "w", stdout);*/

	int nFriendListCount = 0;
	cin >> nFriendListCount;
	deque<int> pqueue;
	pqueue.push_back(1);
	unordered_map<int, int> oPairCol;
	int oMaxFriendList = 0;
	for (int iCounter = 1; iCounter <= nFriendListCount; ++iCounter)
	{
		int a, b;
		cin >> a >> b;
		oPairCol[a]++;
		oPairCol[b]++;
		oMaxFriendList = max(oPairCol[a], oMaxFriendList);
		oMaxFriendList = max(oPairCol[b], oMaxFriendList);
	}

	for (auto& val : oPairCol)
	{
		if (oPairCol[val.first] == oMaxFriendList)
		   cout << val.first << " ";
	}

	cout << endl;

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
