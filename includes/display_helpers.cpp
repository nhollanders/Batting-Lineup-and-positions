#include <iostream>

#include "display_helpers.h"

using namespace std;

void printChar(char charPar, unsigned short int count)
{
    for (unsigned short int i = 0; i < count; i++)
    {
        cout << charPar;
    }
    cout << endl;
}

void sortPlayerData(PlyData *Data, unsigned short int plyCount) // bubble sort because I was to tired to figure out how to use a fancy method like quick sort
{
    for (unsigned short int i = 0; i < plyCount - 1; i++)
    {
        for (unsigned short int j = 0; j < plyCount - i - 1; j++)
        {
            if (Data[j].battingPerc < Data[j + 1].battingPerc)
            {
                swap(Data[j], Data[j + 1]);
            }
        }
    }
}

// Position abbreviations //

// Infield positions //
string Pitcher = "P";
string Catcher = "C";
string FirstBase = "1B";
string SecondBase = "2B";
string ThirdBase = "3B";
string ShortStop = "SS";

// Outfield positions //
string LeftField = "LF";
string CenterField = "CF";
string RightField = "RF";
string LeftCenterField = "LCF";
string RightCenterField = "RCF";

// Misc positions //
string Out = "Out";

void determineFieldPosition(PlyData* Data, string* displayArrayPar, unsigned short int plyCount)
{
    string infieldPositions[] = {Pitcher, Catcher, FirstBase, SecondBase, ThirdBase, ShortStop};
    string outfieldPositions[] = {LeftField, CenterField, RightField, LeftCenterField, RightCenterField};
    bool infieldAssigned[12] = {false}; // keeps track of which infield positions are assigned
    bool outfieldAssigned[12] = {false}; // keeps track of which outfield positions are assigned
    int sitOutCount[12] = {0}; // keeps track of how many times a player has sat out

    for (unsigned short int inning = 0; inning <= 5; inning++)
    {
        for (unsigned short int player = 0; player < plyCount; player++)
        {
            
        }
    }
}