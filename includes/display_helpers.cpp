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

void determineFieldPosition(PlyData* Data, string displayArrayPar[][6],  int plyCount)
{
    vector<string> Infield_Positions(INFIELD_POSITIONS, INFIELD_POSITIONS + 6);
    vector<string> Outfield_Positions(OUTFIELD_POSITIONS, OUTFIELD_POSITIONS + 5);
    bool hasSatOut[plyCount] = {false};

    random_device rd;
    mt19937 gen(rd());

    for (int inning = 0; inning < 6; inning++)
    {
        shuffle(Infield_Positions.begin(), Infield_Positions.end(), gen);
        shuffle(Outfield_Positions.begin(), Outfield_Positions.end(), gen);
        int satOutPlayers = 0;

        for (int player = 0; player < plyCount; player++)
        {
            if (inning == 0)
            {
                displayArrayPar[player][inning] = Data[player].name;
                continue;
            }

            // if player has sat out, put them on the bench
            if (rand() % 2 == 0 && !hasSatOut[player] && satOutPlayers < abs(plyCount - 11)) // we only have 11 positions to assign so extra players get sat out
            {
                displayArrayPar[player][inning] = BENCH;
                hasSatOut[player] = true;
                satOutPlayers++;
                continue;
            }

            // if it is inning 1 and not 0:
            if (rand() % 2 == 0) // infield
            {
                for (int inPos = 0; inPos < 6; inPos++) // for each infield position
                {
                    string position = Infield_Positions[inPos];
                    if (!hasPlayedPos(player, position, displayArrayPar) && !isPositionUsed(position, displayArrayPar, inning)) // if hasnt played and position isnt being used
                    {
                        displayArrayPar[player][inning] = position;
                        break;
                    }
                }
            }
            else // outfield
            {
                for (int outPos = 0; outPos < 5; outPos++)
                {
                    string position = Outfield_Positions[outPos];
                    if (!hasPlayedPos(player, position, displayArrayPar) && !isPositionUsed(position, displayArrayPar, inning))
                    {
                        displayArrayPar[player][inning] = position;
                        break;
                    }
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