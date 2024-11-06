#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>

#include "display_helpers.h"
#include "playerDataStruct.h"

using namespace std;

void printChar(char charPar, int count)
{
    for ( int i = 0; i < count; i++)
    {
        cout << charPar;
    }
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

// positions //
const string InfieldPositions[] = {"P", "C", "1B", "2B", "3B", "SS"};
const string OutfieldPositions[] = {"LF", "CF", "RF", "LCF", "RCF"};

const string Out = "Out";

// 1. The line-up should include batting order and player’s defensive positions for each of the five innings.

// 2. Each team shall play all players in the field in defensive positions. Additional players, (short fielders), shall be
// positioned in the outfield no closer than 20 feet to the baseline when the ball is hit and will be considered
// outfielders.
// 3. Each player must be scheduled to play an infield position at least one (1) inning. Catcher will be considered an
// infield position. A player may only be scheduled to play catcher a maximum of one (1) inning per game. No
// player may play a second inning of infield until every other player has played one inning of infield.
// 4. A player cannot play the same defensive position for more than one (1) inning per game.
// 5. A player can only sit out one (1) inning per game.

void determineFieldPosition(PlyData* Data, string displayArrayPar[][6],  int plyCount)
{
    bool infieldAssigned[11] = {false}; // keeps track of which infield positions are assigned
    bool outfieldAssigned[11] = {false}; // keeps track of which outfield positions are assigned
    bool hasSatOut[11] = {false}; // keeps track of how many times a player has sat out

    for ( int inning = 0; inning <= 5; inning++)
    {
        int sitOut = 0;
        for ( int player = 0; player < plyCount; player++)
        {
            if (inning == 0)
            {
                displayArrayPar[player][inning] = Data[player].name;
                continue; // first item in list is name so we skip it basically
            }
            
            // determine if player is sitting out
            if (sitOut < 2 && !hasSatOut[player])
            {
                if (rand() % 2 == 0)
                {
                    displayArrayPar[player][inning] = Out;
                    hasSatOut[player] = true;
                    sitOut++;
                    continue;
                }
            }

            // determine if player is playing infield
            if (rand() % 2 == 0)
            {
                for ( int i = 0; i < 6; i++)
                {
                    if (!infieldAssigned[i])
                    {
                        displayArrayPar[player][inning] = InfieldPositions[i];
                        infieldAssigned[i] = true;
                        break;
                    }
                }
            }
            else
            {
                for ( int i = 0; i < 5; i++)
                {
                    if (!outfieldAssigned[i])
                    {
                        displayArrayPar[player][inning] = OutfieldPositions[i];
                        outfieldAssigned[i] = true;
                        break;
                    }
                }
            }

            // determine if player is playing outfield
    
        }
    }
}

const int BUFFER_SPACE = 2; // spaces between columns

void displayPlayerData(string displayArray[][6],  int plyCount)
{
    cout << "Game Lineup and field positions:" << endl;
    printChar('-', 33);
    cout << endl;

    int longestName = 0; // find the longest name to format the output
    for ( int j = 0; j < 12; j++)
    {
        if (displayArray[j][0].length() > longestName)
        {
            longestName = displayArray[j][0].length();
        }
    }

    cout << "Name"; // print the header
    printChar(' ', max(4 - (longestName + BUFFER_SPACE), BUFFER_SPACE));

    for ( int j = 1; j <= 5; j++)
    {
        cout << "Inning" << j;
        printChar(' ', BUFFER_SPACE);
    }
    cout << endl;

    for (int j = 0; j < plyCount; j++) // print the data
    {
        cout << displayArray[j][0];
        printChar(' ', max(BUFFER_SPACE + abs(4 - static_cast<int>(displayArray[j][0].length())), longestName + BUFFER_SPACE));
        for (int k = 1; k <= 5; k++)
        {
            cout << displayArray[j][k];
            printChar(' ', (7 - displayArray[j][k].length()) + BUFFER_SPACE);
        }
        cout << endl;
    }
}