// TakTakTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	string oInputFile = "taktakin.txt";
	string oOutputFile = "taktakout.txt";

	freopen(oInputFile.data(), "r", stdin);
	freopen(oOutputFile.data(), "w", stdout);
	 
	int nFullMoonPassed = 0;
	int nCurrentFruitCount = 0;
	cin >> nCurrentFruitCount;

	auto IsDistributable = [&nCurrentFruitCount]()->bool {
		if ((nCurrentFruitCount % 11) == 1)
			return true;

		return false;
	};

	while (!IsDistributable()) {
		nCurrentFruitCount *= 2;
		++nFullMoonPassed;
	}

	cout << nFullMoonPassed << " " << nCurrentFruitCount << endl;

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
