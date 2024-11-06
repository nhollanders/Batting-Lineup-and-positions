#include <iostream>

#include "display_helpers.h"
#include "playerDataStruct.h"

using namespace std;

void printChar(char charPar, int count)
{
    for ( int i = 0; i < count; i++)
    {
        cout << charPar;
    }
    cout << endl;
}

void sortPlayerData(PlyData *Data,  int plyCount) // bubble sort because I was to tired to figure out how to use a fancy method like quick sort
{
    for ( int i = 0; i < plyCount - 1; i++)
    {
        for ( int j = 0; j < plyCount - i - 1; j++)
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
const string Pitcher = "P";
const string Catcher = "C";
const string FirstBase = "1B";
const string SecondBase = "2B";
const string ThirdBase = "3B";
const string ShortStop = "SS";

// Outfield positions //
const string LeftField = "LF";
const string CenterField = "CF";
const string RightField = "RF";
const string LeftCenterField = "LCF";
const string RightCenterField = "RCF";

// Misc positions //
const string Out = "Out";

void determineFieldPosition(PlyData* Data, string displayArrayPar[][6],  int plyCount)
{
    string infieldPositions[] = {Pitcher, Catcher, FirstBase, SecondBase, ThirdBase, ShortStop};
    string outfieldPositions[] = {LeftField, CenterField, RightField, LeftCenterField, RightCenterField};
    bool infieldAssigned[12] = {false}; // keeps track of which infield positions are assigned
    bool outfieldAssigned[12] = {false}; // keeps track of which outfield positions are assigned
    int sitOutCount[12] = {0}; // keeps track of how many times a player has sat out

    for ( int inning = 0; inning <= 5; inning++)
    {
        for ( int player = 0; player < plyCount; player++)
        {
            if (inning == 0)
            {
                displayArrayPar[player][inning] = Data[player].name;
                continue; // first item in list is name so we skip it basically
            }

            
        }
    }
}

const int BUFFER_SPACE = 4; // spaces between columns (should be longer than longest position name)

void displayPlayerData(string displayArray[][6],  int plyCount)
{
    for ( int i = 0; i < plyCount; i++)
    {
        cout << "Game Lineup and field positions:" << endl;
        printChar('-', 33);

        int longestName = 0;
        for ( int j = 0; j < 12; j++)
        {
            if (displayArray[j][0].length() > longestName)
            {
                longestName = displayArray[j][0].length();
            }
        }

        cout << "Name";
        printChar(' ', longestName + BUFFER_SPACE - 4);
        for ( int j = 1; j <= 5; j++)
        {
            cout << "Inning " << j;
            printChar(' ', BUFFER_SPACE);
        }
        cout << endl;

        for (int j = 0; j < plyCount; j++)
        {
            cout << displayArray[j][0];
            printChar(' ', longestName + BUFFER_SPACE - displayArray[j][0].length());
            for (int k = 1; k <= 5; k++)
            {
                cout << displayArray[j][k];
                printChar(' ', BUFFER_SPACE);
            }
            cout << endl;
        }
        
    }
}