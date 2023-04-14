#include <iostream>
#include "ForestAnalyzer.h"


using namespace std;

int main(int argc, char **argv)
{
    const char* fileName = "day8.in";

    ForestAnalyzer a(fileName);

    cout << " Number of visible trees: " << a.GetNumberOfVisibleTrees() << endl;
    cout << " Maximum scenic score: " << a.GetMaximumScenicScore() << endl;

    return 0;
}