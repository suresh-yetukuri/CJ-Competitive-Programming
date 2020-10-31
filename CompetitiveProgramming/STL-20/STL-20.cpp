// STL-20.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <utility>
using namespace std;

namespace Comparator
{
    void Test()
    {
        short val = -3;
        unsigned int ival = 1729;
        // cout << (val < ival) << endl; 
        // returns false, because short gets converted to unsigned int (2^32-1)
        // which is for sure greater than ival 
        cout << cmp_less(val, ival) << endl;
        cout << cmp_equal(val, val) << endl; 
        cout << cmp_less_equal(val, 1729) << endl;
        val = 1729;
        cout << cmp_less_equal(val, 1729) << endl;
        cout << cmp_less_equal(val, 1729) << endl;
        
        // cmp_less           <
        // cmp_greater        >
        // cmp_equal          ==
        // cmp_not_equal      !=
        // cmp_less_equal     <=
        // cmp_greater_equal  >=
    }
}

namespace FileSystem
{
    void Test()
    {
        string oPath =  R"(C:\TARGET-2020\boost_1_74_0\boost_1_74_0\boost)";
        filesystem::path fPath = R"(C:\TARGET-2020\boost_1_74_0\boost_1_74_0\boost)";
        string sFile = R"(C:\TARGET-2022\System\Explanations\Something)";
        error_code e;
        cout << filesystem::relative(fPath, sFile).string() << endl;
        cout << fPath << endl;
        cout << fPath.string() << endl;
        cout << fPath.root_name() << endl;
        cout << fPath.root_directory() << endl;
        cout << fPath.root_path() << endl;
        filesystem::create_directories(sFile);
        for (const auto& ent : filesystem::recursive_directory_iterator{ fPath })
            cout << ent.path().string() << endl;

        auto ent = filesystem::current_path();
        cout << ent.string() << endl;
    }
}


int main()
{
    vector<int> pInput{ 1, 2, 3, 4 };
    sort(pInput.begin(), pInput.end(), greater<int>());
    sort(pInput.begin(), pInput.end(), less<int>());
    long long x = 0;
    for (int iCounter = 0; iCounter < 10; ++iCounter)
        x |= (1ll << iCounter);

    FileSystem::Test();
    return 0;
}
