#include <iostream>
#include <string>
#include <ctime>
#include <random>

#include "includes/display_helpers.h"
#include "includes/playerDataStruct.h"

using namespace std;

int const PLAYER_COUNT = 12;

int main()
{
    static PlyData PlayerData[PLAYER_COUNT];

    cout << "Enter " << PLAYER_COUNT << " player names: " << endl;
    printChar('-', 25);
    cout << endl;

    for (int i = 0; i < PLAYER_COUNT; i++)
    {
        cout << "What is player " << (i + 1) << "'s name: ";
        getline(cin, PlayerData[i].name);
    }

    cout << endl << "Enter the batting average for each player (0-1000):" << endl;
    printChar('-', 52);
    cout << endl;

    for (int i = 0; i < PLAYER_COUNT; i++)
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
    cout << endl;

    sortPlayerData(PlayerData, PLAYER_COUNT); // sorts from highest to lowest score

    string displayArray[PLAYER_COUNT][6]; // 0 is name, the rest is position by inning

    determineFieldPosition(PlayerData, displayArray, PLAYER_COUNT);
    displayPlayerData(displayArray, PLAYER_COUNT);

    system("pause");
    return 0;
}