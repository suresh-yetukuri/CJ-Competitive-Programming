// VOTERS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void Merge(vector<int>& voters_list, int v1_start, int v1_end, int v2_start, int v2_end)
{
    int pCounter = v1_start;
    int qCounter = v2_start;
    int rCounter = 0;
    int total_voter = (v1_end - v1_start) + (v2_end - v2_start) + 2;
    vector<int> pAux(total_voter, 0);

    while (pCounter <= v1_end && qCounter <= v2_end)
    {
        if (voters_list[pCounter] >= voters_list[qCounter]) 
            pAux[rCounter++] = voters_list[qCounter++];
        else
            pAux[rCounter++] = voters_list[pCounter++];
    }

    while(pCounter <= v1_end)
        pAux[rCounter++] = voters_list[pCounter++];

    while(qCounter <= v2_end)
        pAux[rCounter++] = voters_list[qCounter++];

    for (int iCounter = 0; iCounter < total_voter; ++iCounter)
        voters_list[iCounter + v1_start] = pAux[iCounter];
}

void MergeSTL(vector<int>& voters_list, int v1_start, int v1_end, int v2_start, int v2_end)
{
    int total_voter = (v1_end - v1_start) + (v2_end - v2_start) + 2;
    vector<int> pAux(total_voter, 0);

    auto Itr = voters_list.begin();
    merge(Itr, Itr + v2_start, Itr + v2_start, Itr + v2_end + 1, pAux.begin());

    for (int iCounter = 0; iCounter < total_voter; ++iCounter)
        voters_list[iCounter + v1_start] = pAux[iCounter];
}

vector<int> getVoters(vector<int>& voters_list)
{
    vector<int> final_voter_list;
    int pCounter = 0;
    int qCounter = 0;
    int total_voters = voters_list.size();
    while (qCounter < total_voters)
    {
        if (voters_list[pCounter] == voters_list[qCounter])
            ++qCounter;
        else
        {
            if ((qCounter - pCounter) > 1)
                final_voter_list.push_back(voters_list[pCounter]);

            pCounter = qCounter;
        }
    }

    if ((qCounter - pCounter) > 1)
        final_voter_list.push_back(voters_list[pCounter]);

    return move(final_voter_list);
}

int main()
{
    int n1, n2, n3;
    cin >> n1 >> n2 >> n3;
    int total_voters = n1 + n2 + n3;
    vector<int> voters_list(total_voters, 0);
    for (int iCounter = 0; iCounter < total_voters; ++iCounter)
        cin >> voters_list[iCounter];

    // sort the voters
    //sort(voters_list.begin(), voters_list.end());
    MergeSTL(voters_list, 0, n1 - 1, n1, (n1 + n2) - 1);
    MergeSTL(voters_list, 0, (n1 + n2) - 1, (n1 + n2), total_voters - 1);
    auto final_voter_list = getVoters(voters_list);
    
    cout << final_voter_list.size() << endl;
    for (auto& Id : final_voter_list)
        cout << Id << endl;

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
