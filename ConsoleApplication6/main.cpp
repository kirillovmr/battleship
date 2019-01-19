/* * * * * * * * * * * * * * * * * *

	Program: Battleship game (course project)
	Date: date
	Author: Viktor Kirillov

* * * * * * * * * * * * * * * * * */

#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <cstring>
#include <string>

using namespace std;

#include "Prototypes.h"

#include "playerMove.h"
#include "OpponentMove.h"
#include "PlaceShips.h"
#include "Checking.h"
#include "Drawings.h"
#include "SettingsScreen.h"

void main() {
	system("mode con cols=80 lines=25");
	cursorVisible(false);
	srand(time(NULL));
	
	screenCover(15, 0);
	system("color F0");
	gameTitle();
	setColor(0, 15);
	settingsScreen();

	// Initializing fields as empty
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			playerBoard[i][j] = 0;
			opponentBoard[i][j] = 0;
			playerBoardForMovements[i][j] = 0;
			playerShoots[i][j] = 0;
			opponentShoots[i][j] = 0;
		}
	}

	PlaceOpponentShips();
	PlacePlayerShips();
	GameProcess();
}

void GameProcess() {
	warStarted = true;
	bool gameEnd = false;
	short int shootY, shootX;
	shootY = rand() % 10;
	shootX = rand() % 10;

	while (!gameEnd) {
		ShowField(true, showOpponentShips);
		SelectFieldForShooting(shootY, shootX);
		OpponentMove();
		checkWin();
	}
}