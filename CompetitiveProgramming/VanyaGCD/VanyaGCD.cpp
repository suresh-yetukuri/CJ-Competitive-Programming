// VanyaGCD.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const long long M = 1e9 + 7;

long long getGCD(long long a, long long b)
{
	if (0 == b)
		return a;

	return getGCD(b, a % b);
}

int main()
{
	const long long max_gcd = 100;
	long long nSize = 0;
	cin >> nSize;
	vector<long long> pInput(nSize);
	for (int iCounter = 0; iCounter < nSize; ++iCounter)
		cin >> pInput[iCounter];

	vector<vector<long long>> pAux(nSize, vector<long long>(max_gcd + 1, 0));
	for (int iCounter = 0; iCounter < nSize; ++iCounter)
	{
		pAux[iCounter][pInput[iCounter]] = 1;
		for (int jCounter = iCounter - 1; jCounter >= 0; --jCounter)
		{
			if (pInput[jCounter] < pInput[iCounter])
			{
				for (int kCounter = 0; kCounter <= max_gcd; ++kCounter)
				{
					auto curr_gcd = getGCD(kCounter, pInput[iCounter]);
					pAux[iCounter][curr_gcd] = (pAux[iCounter][curr_gcd] + pAux[jCounter][kCounter]) % M;
				}
			}
		}
	}

	long long result = 0;
	for (int iCounter = 0; iCounter < nSize; ++iCounter)
		result = (result + pAux[iCounter][1]) % M;

	cout << result << endl;
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
