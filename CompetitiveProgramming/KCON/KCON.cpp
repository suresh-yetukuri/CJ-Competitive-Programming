// KCON.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
TC: O(N);
SC: O(1)
*/


#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

ll KadaneSubarraySum(int pArray[], int nSize)
{
	ll max_subarray_sum = INT_MIN;
	ll curr_subarray_sum = 0;

	for (int iCounter = 0; iCounter < nSize; ++iCounter)
	{
		curr_subarray_sum += pArray[iCounter];
		max_subarray_sum = max(curr_subarray_sum, max_subarray_sum);
		if (curr_subarray_sum < 0)
			curr_subarray_sum = 0;
	}

	return max_subarray_sum;
}

ll MaxSubarraySum(int pArray[], int nSize, int kCount)
{
	ll kadane_subarray_sum = KadaneSubarraySum(pArray, nSize);
	if (kCount == 1)
		return kadane_subarray_sum;

	ll curr_prefix_sum = 0;
	ll curr_suffix_sum = 0;
	ll max_prefix_sum = INT_MIN;
	ll max_suffix_sum = INT_MIN;
	ll& total_sum = curr_prefix_sum;

	/*
	// Computing Best Prefix Sum
	for (int iCounter = 0; iCounter < nSize; ++iCounter)
	{
		curr_prefix_sum += pArray[iCounter];
		max_prefix_sum = max(curr_prefix_sum, max_prefix_sum);
	}

	// Computing Best Suffix Sum
	for (int iCounter = nSize - 1; iCounter >= 0; --iCounter)
	{
		curr_suffix_sum += pArray[iCounter];
		max_suffix_sum = max(curr_suffix_sum, max_suffix_sum);
	}
	*/

	// Computing Best Prefix & Suffix Sum
	for (int iCounter = 0; iCounter < nSize; ++iCounter)
	{
		curr_prefix_sum += pArray[iCounter];
		curr_suffix_sum += pArray[nSize - iCounter - 1];
		max_prefix_sum = max(curr_prefix_sum, max_prefix_sum);
		max_suffix_sum = max(curr_suffix_sum, max_suffix_sum);
	}

	ll max_subarray_sum = INT_MIN;
	if (total_sum >= 0)
	{
		max_subarray_sum = max(max_prefix_sum 
							 + max_suffix_sum 
							 + (total_sum * (static_cast<ll>(kCount) - 2)), kadane_subarray_sum);
	}
	else {
		max_subarray_sum = max(max_prefix_sum + max_suffix_sum, kadane_subarray_sum);
	}

	return max_subarray_sum;
}

int main()
{
    int nTestCase = 0;
    cin >> nTestCase;

	while (nTestCase--)
	{
		int nSize = 0;
		int kCount = 0;
		cin >> nSize >> kCount;

		int* pArray = new int[nSize];
		for (int iCounter = 0; iCounter < nSize; ++iCounter)
			cin >> pArray[iCounter];

		cout << MaxSubarraySum(pArray, nSize, kCount) << endl;

		delete[]pArray;
		pArray = nullptr;
	}
	 
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
