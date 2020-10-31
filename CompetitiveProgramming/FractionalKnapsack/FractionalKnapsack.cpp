// FractionalKnapsack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct worker
{
	long long time;
	long long cost;
	long long speed;
};

int main()
{
	long long nWorkers = 0;
	long long nUnitsPaintWork = 0;
	cin >> nWorkers >> nUnitsPaintWork;
	vector<worker> pInput(nWorkers);
	for (int iCounter = 0; iCounter < nWorkers; ++iCounter)
		cin >> pInput[iCounter].time >> pInput[iCounter].cost >> pInput[iCounter].speed;

	// First we will give priority to time, speed, and then cost
	sort(pInput.begin(), pInput.end(), [](worker& oFirst, worker& oSecond)->bool {
		if (oFirst.time < oSecond.time)
			return true;
		else if (oFirst.time == oSecond.time)
		{
			if (oFirst.speed > oSecond.speed)
				return true;
			else if (oFirst.speed == oSecond.speed)
			{
				if (oFirst.cost < oSecond.cost)
					return true;
			}
		}

		return false;
		});

	long long min_cost = 0;
	auto selected_worker = pInput[0];
	min_cost += selected_worker.cost;
	nUnitsPaintWork = max(0ll, nUnitsPaintWork - selected_worker.speed);

	// we will change the worker only if find another worker with higher speed
	// then current worker
	for (int iCounter = 1; iCounter < nWorkers; ++iCounter)
	{
		if (nUnitsPaintWork > 0)
		{
			auto curr_worker = pInput[iCounter];
			if (curr_worker.speed > selected_worker.speed)
			{
				selected_worker = curr_worker;
				min_cost += selected_worker.cost;
				nUnitsPaintWork = max(0ll, nUnitsPaintWork - selected_worker.speed);
			}
			else
				nUnitsPaintWork = max(0ll, nUnitsPaintWork - selected_worker.speed);
		}
		else
			break;
	}

	cout << min_cost << endl;

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
