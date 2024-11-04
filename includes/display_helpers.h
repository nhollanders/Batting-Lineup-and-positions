#ifndef _display_helpers
#define _display_helpers

#include <string>
#include "playerDataStruct.h"

void printChar(char charPar, unsigned short int count); // prints multiple characters
void sortPlayerData(PlyData *Data, unsigned short int plyCount); // sorts player data from highest to lowest score
void determineFieldPosition(PlyData* Data, std::string displayArrayPar[][6], unsigned short int plyCount); // determines the field position of each player changing the input 2d list
void displayPlayerData(std::string displayArray[][6], unsigned short int plyCount); // displays the player data from the 2d list

#endif