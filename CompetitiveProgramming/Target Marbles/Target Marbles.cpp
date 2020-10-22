#include <iostream>
#include <deque>
#include <queue>
using namespace std;
int main() {
    int nMarbleCount = 0;
    int nTarget = 0;
    cin >> nMarbleCount >> nTarget;

    int* pMarbles = new int[nMarbleCount];
    for (int iCounter = 0; iCounter < nMarbleCount; ++iCounter)
        cin >> pMarbles[iCounter];


    int pCounter = 0;
    int qCounter = pCounter + 1;
    int oSum = pMarbles[pCounter];
    deque<int> pDeque;
    pDeque.push_back(pMarbles[pCounter]);

    while (qCounter < nTarget)
    {
        if (oSum < nTarget)
        {
            oSum += pMarbles[qCounter];
            pDeque.push_back(pMarbles[qCounter]);
            qCounter++;
        }
        else if (oSum > nTarget)
        {
            oSum -= pMarbles[pCounter];
            pDeque.pop_front();
            ++pCounter;
        }
        else
        {
            cout << "true" << endl;
            for (auto& oNum : pDeque)
                cout << oNum << " ";

            return 0;
        }
    }

    cout << "false" << endl;
    return 0;
}