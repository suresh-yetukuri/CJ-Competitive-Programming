// HasanTrip.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct city
{
    double xCoord;
    double yCoord;
    double happiness;

    double operator-(const city& oCity)
    {
        return sqrt(pow(abs(xCoord - oCity.xCoord), 2) + pow(abs(yCoord - oCity.yCoord), 2));
    }
};
 
namespace UsingDP
{
    double getMax(vector<city>& pInput, int nCity)
    {
        if (nCity == 1)
            return pInput[0].happiness;

        vector<double> pAux(nCity, 0.0);
        pAux[0] = pInput[0].happiness;

        for (int iCityCounter = 1; iCityCounter < nCity; ++iCityCounter)
        {
            // max happiness that can be achieved if i include this city 
            double distance = pInput[iCityCounter] - pInput[0];
            double curr_max_happiness = (pAux[0] + pInput[iCityCounter].happiness) - distance;

            int jCityCounter = iCityCounter - 1;
            while (jCityCounter > 0)
            {
                double curr_distance = pInput[iCityCounter] - pInput[jCityCounter];
                auto curr_happiness = (pAux[jCityCounter] + pInput[iCityCounter].happiness) - curr_distance;
                curr_max_happiness = max(curr_happiness, curr_max_happiness);
                --jCityCounter;
            }

            pAux[iCityCounter] = curr_max_happiness;
        }

        return pAux[nCity - 1];
    }
}

namespace UsingBruteForce
{

    /**
     * @brief Get Max Happiness For Hasan
     * @param pInput Cities
     * @param nCity  Total Cities
     * @param curr_city_Idx Current City
     * @param lastVisitedCity Last Visited City
     * @return Max Happiness
    */
    double Utility(vector<city>& pInput, int nCity, int curr_city_Idx, city& lastVisitedCity)
    {
        if (curr_city_Idx == nCity)
            return 0.0;

        if (curr_city_Idx == (nCity - 1)) 
            return pInput[curr_city_Idx].happiness - (lastVisitedCity - pInput[curr_city_Idx]);

        auto IfVisitedCurrCity = Utility(pInput, nCity, curr_city_Idx + 1, pInput[curr_city_Idx])
                               + (pInput[curr_city_Idx].happiness - (lastVisitedCity - pInput[curr_city_Idx]));

        auto IfNotVisitedCurrCity = Utility(pInput, nCity, curr_city_Idx + 1, lastVisitedCity);

        return max(IfVisitedCurrCity, IfNotVisitedCurrCity);
    }

    double getMax(vector<city>& pInput, int nCity)
    {
        return pInput[0].happiness + Utility(pInput, nCity, 1, pInput[0]);
    }
}

int main()
{  
    int nCity = 0;
    cin >> nCity;
    vector<city> pInput(nCity);
    for (int iCounter = 0; iCounter < nCity; ++iCounter)
    {
        city curr_city;
        cin >> curr_city.xCoord >> curr_city.yCoord >> curr_city.happiness;
        pInput[iCounter] = curr_city;
    }
     
    double oResult = UsingBruteForce::getMax(pInput, nCity);
    cout << fixed << setprecision(6) << oResult << endl;
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
