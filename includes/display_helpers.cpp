#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include <map>

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

// Function to check if a player has already played a position
bool hasPlayedPosition(const vector<string>& positions, const string& position) {
    for (const auto& pos : positions) {
        if (pos == position) {
            return true;
        }
    }
    return false;
}

random_device rd;
mt19937 rng(rd());

void shuffleArray(vector<string>& array) {
    shuffle(array.begin(), array.end(), rng);
}

// displayArrayPar //
const string INFIELD_POSITIONS[] = {"P", "C", "1B", "2B", "3B", "SS"};
const string OUTFIELD_POSITIONS[] = {"LF", "CF", "RF", "LCF", "RCF"};
const string BENCH = "Out";

void determineFieldPosition(PlyData* Data, string displayArrayPar[][6], int plyCount)
{
    int numInfield = sizeof(INFIELD_POSITIONS) / sizeof(INFIELD_POSITIONS[0]);
    int numOutfield = sizeof(OUTFIELD_POSITIONS) / sizeof(OUTFIELD_POSITIONS[0]);

    // Track positions played by each player
    vector<vector<string>> playedPositions(plyCount);

    // Helper variables to ensure rules are followed
    vector<int> infieldCount(plyCount, 0);  // Tracks how many infield positions each player has played
    vector<int> catcherCount(plyCount, 0);  // Tracks how many times a player has played catcher
    vector<int> sitOutCount(plyCount, 0);   // Tracks how many times a player has sat out
    int innings = 5;  // Number of innings
    int maxPlayersOutPerInning = 2;  // Max players out per inning

    for (int inning = 1; inning <= innings; inning++) {
        // Randomly shuffle the player order and the positions for this inning
        vector<int> playerOrder(plyCount);
        iota(playerOrder.begin(), playerOrder.end(), 0);
        shuffle(playerOrder.begin(), playerOrder.end(), rng);

        vector<string> infieldPositions(INFIELD_POSITIONS, INFIELD_POSITIONS + numInfield);
        vector<string> outfieldPositions(OUTFIELD_POSITIONS, OUTFIELD_POSITIONS + numOutfield);
        shuffleArray(infieldPositions);
        shuffleArray(outfieldPositions);

        int currentInfield = 0;
        int currentOutfield = 0;
        int playersOutThisInning = 0;

        for (int j = 0; j < plyCount; j++) {
            int i = playerOrder[j];  // Random player order

            // Check if player should sit out (but only once and no more than maxPlayersOutPerInning per inning)
            if (sitOutCount[i] < 1 && playersOutThisInning < maxPlayersOutPerInning) {
                displayArrayPar[i][inning] = BENCH;
                sitOutCount[i]++;
                playersOutThisInning++;
                continue;
            }

            // Assign infield positions if player hasn't played one yet
            if (infieldCount[i] < 1 && currentInfield < numInfield) {
                string position = infieldPositions[currentInfield];

                // Assign catcher only once
                if (position == "C" && catcherCount[i] == 0) {
                    displayArrayPar[i][inning] = position;
                    catcherCount[i]++;
                } else if (position != "C" || catcherCount[i] == 0) {
                    displayArrayPar[i][inning] = position;
                }

                playedPositions[i].push_back(position);
                infieldCount[i]++;
                currentInfield++;
            } 
            // Assign outfield positions
            else if (currentOutfield < numOutfield) {
                string position = outfieldPositions[currentOutfield];
                displayArrayPar[i][inning] = position;
                playedPositions[i].push_back(position);
                currentOutfield++;
            } else if (currentInfield < numInfield) {
                // If outfield is full, assign remaining players to infield
                string position = infieldPositions[currentInfield];
                displayArrayPar[i][inning] = position;
                currentInfield++;
            } else if (currentOutfield < numOutfield) {
                // Ensure remaining players are given outfield positions if available
                string position = outfieldPositions[currentOutfield];
                displayArrayPar[i][inning] = position;
                currentOutfield++;
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