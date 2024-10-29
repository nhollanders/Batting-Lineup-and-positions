#include <iostream>
#include <string>

using namespace std;

unsigned short int const PLAYER_COUNT = 12;

void printDiv(int count)
{
    for (unsigned short int i = 0; i < count; i++)
    {
        cout << ' ';
    }
    cout << endl;
}

int main()
{
    cout << "Enter " << PLAYER_COUNT << "player names: " << endl;
    printDiv(16);

    for (unsigned short int i = 1; i <= PLAYER_COUNT; i++)
    {
        cout << "What is player " << i << "'s name: ";
    }
    

    return 0;
}