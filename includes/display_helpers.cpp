#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <iomanip>

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

// displayArrayPar //
const string INFIELD_POSITIONS[] = {"P", "C", "1B", "2B", "3B", "SS"};
const string OUTFIELD_POSITIONS[] = {"LF", "CF", "RF", "LCF", "RCF"};
const string BENCH = "Out";

// 2. Each team shall play all players in the field in defensive positions. Additional players, (short fielders), shall be will be considered
// outfielders.

// 3. Each player must be scheduled to play an infield position at least one (1) inning. Catcher will be considered an
// infield position. A player may only be scheduled to play catcher a maximum of one (1) inning per game. No
// player may play a second inning of infield until every other player has played one inning of infield.

// 4. A player cannot play the same defensive position for more than one (1) inning per game.

// 5. A player can only sit out one (1) inning per game.

bool hasPlayedPos(int player, string position, string playerPositions[][6])
{
    for (int inning = 0; inning < 6; inning++)
    {
        if (playerPositions[player][inning] == position)
        {
            return true;
        }
    }
    return false;
}

bool isPositionUsed(string position, string displayArrayPar[][6], int inning)
{
    for (int player = 0; player < 12; player++)
    {
        if (displayArrayPar[player][inning] == position)
        {
            return true;
        }
    }
    return false;
}

void determineFieldPosition(PlyData* Data, string displayArrayPar[][6], int plyCount)
{
    vector<string> Infield_Positions(INFIELD_POSITIONS, INFIELD_POSITIONS + 6);
    vector<string> Outfield_Positions(OUTFIELD_POSITIONS, OUTFIELD_POSITIONS + 5);
    bool hasSatOut[plyCount] = {false};  // Track who has sat out
    bool availiblePlayers[plyCount] = {false}; // Track who is available to play
    bool playerAssigned[plyCount] = {false};  // Track if a player has been assigned a position in an inning

    random_device rd;
    mt19937 gen(rd());

    for (int inning = 0; inning < 6; inning++)
    {
        shuffle(Infield_Positions.begin(), Infield_Positions.end(), gen);
        shuffle(Outfield_Positions.begin(), Outfield_Positions.end(), gen);
        
        int satOutPlayers = 0;

        // Randomly sit people who haven't sat before
        for (int player = 0; player < plyCount; player++)
        {
            if (!hasSatOut[player])
            {
                availiblePlayers[player] = true;
            }
            else
            {
                availiblePlayers[player] = false;
            }
        }

        shuffle(availiblePlayers, availiblePlayers + plyCount, gen);

        // Sit out extra players who need to be benched
        for (int player = 0; player < plyCount; player++)
        {
            if (availiblePlayers[player] && satOutPlayers < abs(plyCount - 11) + 1) // Bench players if there are more than 11
            {
                displayArrayPar[player][inning] = BENCH;
                hasSatOut[player] = true;
                satOutPlayers++;
            }
        }

        // Assign positions
        vector<bool> positionUsedInInning(11, false); // Track used positions for this inning

        // Assign positions to players
        for (int player = 0; player < plyCount; player++)
        {
            if (inning == 0) // First inning special case, just assign player names
            {
                displayArrayPar[player][inning] = Data[player].name;
                continue;
            }

            bool positionAssigned = false;

            // Try to assign an infield or outfield position
            if (rand() % 2 == 0) // Assign infield
            {
                for (int inPos = 0; inPos < 6; inPos++) // Iterate through infield positions
                {
                    string position = Infield_Positions[inPos];
                    if (!hasPlayedPos(player, position, displayArrayPar) && !isPositionUsed(position, displayArrayPar, inning) && !positionUsedInInning[inPos])
                    {
                        displayArrayPar[player][inning] = position;
                        positionUsedInInning[inPos] = true;
                        positionAssigned = true;
                        break;
                    }
                }
            }
            else // Assign outfield
            {
                for (int outPos = 0; outPos < 5; outPos++) // Iterate through outfield positions
                {
                    string position = Outfield_Positions[outPos];
                    if (!hasPlayedPos(player, position, displayArrayPar) && !isPositionUsed(position, displayArrayPar, inning) && !positionUsedInInning[outPos])
                    {
                        displayArrayPar[player][inning] = position;
                        positionUsedInInning[outPos] = true;
                        positionAssigned = true;
                        break;
                    }
                }
            }

            // If no position was assigned (i.e., the player is unassigned), attempt to assign or swap
            if (!positionAssigned)
            {
                // Find a player who is already on the bench and swap them
                bool swapped = false;
                for (int playerToSwap = 0; playerToSwap < plyCount; playerToSwap++)
                {
                    if (displayArrayPar[playerToSwap][inning] == BENCH && !hasSatOut[playerToSwap]) // Ensure the player is not already out
                    {
                        // Swap the unassigned player with the bench player
                        swap(displayArrayPar[playerToSwap][inning], displayArrayPar[player][inning]);

                        // Mark both players as assigned
                        hasSatOut[player] = true;
                        hasSatOut[playerToSwap] = true;
                        swapped = true;
                        break;
                    }
                }

                // If no swap was made, assign them a fallback position (avoid overlap)
                if (!swapped)
                {
                    // Try to assign a unique infield position
                    for (int i = 0; i < plyCount; i++)
                    {
                        string position = Infield_Positions[i % 6]; // Use modulus to cycle through positions
                        if (!hasPlayedPos(player, position, displayArrayPar) && !isPositionUsed(position, displayArrayPar, inning))
                        {
                            displayArrayPar[player][inning] = position;
                            break;
                        }
                    }
                }
            }

            // Ensure that no player is left without a position
            if (!positionAssigned && displayArrayPar[player][inning] == "")
            {
                // Assign a fallback position if needed
                for (int inPos = 0; inPos < 6; inPos++)
                {
                    if (!hasPlayedPos(player, Infield_Positions[inPos], displayArrayPar) && !isPositionUsed(Infield_Positions[inPos], displayArrayPar, inning))
                    {
                        displayArrayPar[player][inning] = Infield_Positions[inPos];
                        break;
                    }
                }

                // Ensure no player stays without a position
                if (displayArrayPar[player][inning] == "")
                {
                    displayArrayPar[player][inning] = "UNKNOWN"; // Fallback if no valid position found
                }
            }
        }
    }
}

// slightly modified to fix a issue where the code didnt align correctly
void displayPlayerData(string displayArray[][6], int plyCount) {
    cout << "Game lineup and field positions:" << endl;
    cout << "--------------------------------" << endl;
    cout << left << setw(15) << "Name" 
         << setw(15) << "Inning 1" 
         << setw(15) << "Inning 2" 
         << setw(15) << "Inning 3" 
         << setw(15) << "Inning 4" 
         << setw(15) << "Inning 5" << endl;

    for (int i = 0; i < plyCount; i++) {
        for (int j = 0; j < 6; j++) {
            cout << left << setw(15) << displayArray[i][j];
        }
        cout << endl;
    }
}