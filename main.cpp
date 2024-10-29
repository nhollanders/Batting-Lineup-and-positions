#include <iostream>
#include <string>

#include "includes/display_helpers.h"

using namespace std;

unsigned short int const PLAYER_COUNT = 12;

int main()
{
    string unsortedPlayerData[PLAYER_COUNT];

    cout << "Enter " << PLAYER_COUNT << " player names: " << endl;
    printDiv(30);

    for (unsigned short int i = 0; i < PLAYER_COUNT; i++)
    {
        cout << "What is player " << (i + 1) << "'s name: ";
        getline(cin, unsortedPlayerData[i]);
    }
    
    
    return 0;
}