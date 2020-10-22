// Prereq-Basic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Rectangle
{
	int lbX;
	int lbY;
	int trX;
	int trY;
};


int main()
{
	string oInputFile = "bendin.txt";
	string oOutputFile = "bendout.txt";

	freopen(oInputFile.data(), "r", stdin);
	freopen(oOutputFile.data(), "w", stdout);

	Rectangle oFRec;
	Rectangle oSRec;

	// Reading First Rectangle Inputs
	cin >> oFRec.lbX >> oFRec.lbY;
	cin >> oFRec.trX >> oFRec.trY;

	// Reading Second Rectangle Inputs
	cin >> oSRec.lbX >> oSRec.lbY;
	cin >> oSRec.trX >> oSRec.trY;

	// Calculate Area of both rectangles
	int oFArea = abs(oFRec.trX - oFRec.lbX) * abs(oFRec.trY - oFRec.lbY);
	int oSArea = abs(oSRec.trX - oSRec.lbX) * abs(oSRec.trY - oSRec.lbY);

	// Calcualte Intersection
	int oLeftIntersection = max(oFRec.lbX, oSRec.lbX);
	int oRightIntersection = min(oFRec.trX, oSRec.trX);
	int oBottomIntersection = max(oFRec.lbY, oSRec.lbY);
	int oTopIntersection = min(oFRec.trY, oSRec.trY);

	int oIntersectionalArea = 0;
	// Condition for Rectangular Intersection
	if ((oLeftIntersection < oRightIntersection)
	 && (oBottomIntersection < oTopIntersection)) 
		oIntersectionalArea = abs(oLeftIntersection - oRightIntersection) * abs(oTopIntersection - oBottomIntersection); 

	int oTotalArea = (oFArea + oSArea) - oIntersectionalArea;
	cout << oTotalArea << endl;
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
