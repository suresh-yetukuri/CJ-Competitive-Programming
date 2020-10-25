// BalikaVadhu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using dp_type = vector<vector<vector<int>>>;

/*
TC: Exponential
SC: max(m,n)
*/
namespace BruteForce
{
	int MaxBlessing(string& oInput_F, string& oInput_S, int f_Idx, int s_Idx, int kCount)
	{
		if ((oInput_F.length() == f_Idx || oInput_S.length() == s_Idx) && kCount != 0)
			return INT_MIN;

		if (0 == kCount)
			return 0;
			
		if (oInput_F[f_Idx] == oInput_S[s_Idx])
		{
			int Option_F = static_cast<int>(oInput_F[f_Idx]) + MaxBlessing(oInput_F, oInput_S, f_Idx + 1, s_Idx + 1, kCount - 1);
			int Option_S = MaxBlessing(oInput_F, oInput_S, f_Idx + 1, s_Idx, kCount);
			int Option_T = MaxBlessing(oInput_F, oInput_S, f_Idx, s_Idx + 1, kCount);
			return max(Option_F, max(Option_S, Option_T));
		}
		else
		{
			int Option_F = MaxBlessing(oInput_F, oInput_S, f_Idx + 1, s_Idx, kCount);
			int Option_S = MaxBlessing(oInput_F, oInput_S, f_Idx, s_Idx + 1, kCount);
			return max(Option_F, Option_S);
		}
	}
}

/*
TC: m*n*k
SC: m*n*k + stack space
*/
namespace RecursiveDP
{
	int MaxBlessing(string& oInput_F, string& oInput_S, int f_Idx, int s_Idx, int kCount, dp_type& pAux)
	{
		if ((oInput_F.length() == f_Idx || oInput_S.length() == s_Idx) && kCount != 0)
			return INT_MIN;

		if (0 == kCount)
			return 0;

		if (-1 == pAux[f_Idx][s_Idx][kCount])
		{
			if (oInput_F[f_Idx] == oInput_S[s_Idx])
			{
				int Option_F = static_cast<int>(oInput_F[f_Idx]) 
					         + MaxBlessing(oInput_F, oInput_S, f_Idx + 1, s_Idx + 1, kCount - 1, pAux);
				int Option_S = MaxBlessing(oInput_F, oInput_S, f_Idx + 1, s_Idx, kCount, pAux);
				int Option_T = MaxBlessing(oInput_F, oInput_S, f_Idx, s_Idx + 1, kCount, pAux);
				pAux[f_Idx][s_Idx][kCount] = max(Option_F, max(Option_S, Option_T));
			}
			else
			{
				int Option_F = MaxBlessing(oInput_F, oInput_S, f_Idx + 1, s_Idx, kCount, pAux);
				int Option_S = MaxBlessing(oInput_F, oInput_S, f_Idx, s_Idx + 1, kCount, pAux);
				pAux[f_Idx][s_Idx][kCount] = max(Option_F, Option_S);
			}
		}

		return pAux[f_Idx][s_Idx][kCount];
	}
}


/*
TC: k*(m+n) + m*n*k
SC: m*n*k
*/
namespace IterativeDP
{
	int MaxBlessing(string& oInput_F, string& oInput_S, int kCount)
	{
		if ((oInput_F.empty() || oInput_S.empty()) && kCount != 0)
			return INT_MIN;

		if (0 == kCount)
			return 0;


		dp_type pAux(oInput_F.length() + 1, vector<vector<int>>(oInput_S.length() + 1, vector<int>(kCount + 1, 0)));
		for (int k_Idx = 1; k_Idx <= kCount; ++k_Idx)
		{
			for (int f_Idx = oInput_F.length(); f_Idx >= 0; --f_Idx)
				pAux[f_Idx][oInput_S.length()][k_Idx] = INT_MIN;

			for (int s_Idx = oInput_S.length(); s_Idx >= 0; --s_Idx)
				pAux[oInput_F.length()][s_Idx][k_Idx] = INT_MIN;
		}


		for (int k_Idx = 1; k_Idx <= kCount; ++k_Idx)
			for (int f_Idx = oInput_F.length() - 1; f_Idx >= 0; --f_Idx)
				for (int s_Idx = oInput_S.length() - 1; s_Idx >= 0; --s_Idx)
				{
					if (oInput_F[f_Idx] == oInput_S[s_Idx])
					{
						int Option_F = static_cast<int>(oInput_F[f_Idx]) + pAux[f_Idx + 1][s_Idx + 1][k_Idx - 1]; 
						int Option_S = pAux[f_Idx + 1][s_Idx][k_Idx];
						int Option_T = pAux[f_Idx][s_Idx + 1][k_Idx];
						pAux[f_Idx][s_Idx][k_Idx] = max(Option_F, max(Option_S, Option_T));
					}
					else
					{
						int Option_F = pAux[f_Idx + 1][s_Idx][k_Idx];
						int Option_S = pAux[f_Idx][s_Idx + 1][k_Idx];
						pAux[f_Idx][s_Idx][k_Idx] = max(Option_F, Option_S);
					}
				}



		return pAux[0][0][kCount];
	}
}

int main()
{
	int nTestCase = 0;
	cin >> nTestCase;
	while (nTestCase--)
	{
		int kCount = 0;
		string oInput_F;
		string oInput_S;
		cin >> oInput_F >> oInput_S >> kCount;
	    
		//dp_type pAux(oInput_F.length(), vector<vector<int>>(oInput_S.length(), vector<int>(kCount + 1, -1)));
		auto max_blessing = IterativeDP::MaxBlessing(oInput_F, oInput_S, kCount);
		cout << max(max_blessing, 0) << endl;
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
