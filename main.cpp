#include <iostream>
#include <string>
#include <math.h>
#include <ctime>

#include "includes/display_helpers.h"
#include "includes/playerDataStruct.h"

using namespace std;

unsigned short int const PLAYER_COUNT = 12;

int main()
{
    PlyData PlayerData[PLAYER_COUNT];

    cout << "Enter " << PLAYER_COUNT << " player names: " << endl;
    printChar('-', 25);

    for (unsigned short int i = 0; i < PLAYER_COUNT; i++)
    {
        cout << "What is player " << (i + 1) << "'s name: ";
        getline(cin, PlayerData[i].name);
    }

    cout << endl << "Enter the batting average for each player (0-1000):" << endl;
    printChar('-', 52);

    for (unsigned short int i = 0; i < PLAYER_COUNT; i++)
    {
        string value;

        cout << "What is " << PlayerData[i].name << "'s average: ";
        getline(cin, value);

        try
        {
            int tempNum = min(stoi(value), 1000);
            PlayerData[i].battingPerc = max(tempNum, 0);
        }
        catch(...)
        {
            PlayerData[i].battingPerc = 0;
        }
    }

    sortPlayerData(PlayerData, PLAYER_COUNT); // sorts from highest to lowest score

    cout << "Game lineup and field positions: " << endl;
    printChar('-', 34);

    string displayArray[PLAYER_COUNT][6]; // 0 is name, the rest is position by inning

    determineFieldPosition(PlayerData, displayArray, PLAYER_COUNT);

    return 0;
}