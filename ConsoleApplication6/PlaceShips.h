#pragma once

void PlacePlayerShips() {
	if (!placePlayerShipsAutomatically) {
		system("cls");
		ShowField(false, showOpponentShips);
		TextDuringPlayerPlacing();
	}

	short int randX, randY;
	short int shipCount = 0; // used to place ship info into array
	bool horizontal, placeShip;
	char input = ' ';

reset:
	for (int i = 0; i < 10; i++) { for (int j = 0; j < 10; j++) { playerBoard[i][j] = 0; playerBoardForMovements[i][j] = 0; } } // Initializing fields as empty

	for (int size = 4; size > 0; size--) { // size of ships
		for (int amount = 5 - size; amount > 0; amount--) { // number of ships required on field
			placeShip = false;
			bool place = false;

			// Randomly and automatically founding a place for ship
			while (!place) {
				horizontal = rand() % 2;

				if (allShipsDirection == 1)
					horizontal = false;
				else if (allShipsDirection == 2)
					horizontal = true;

				if (horizontal) {
					randX = (rand() % (11 - size));
					randY = (rand() % 10);
				}
				else {
					randX = (rand() % 11);
					randY = (rand() % (10 - size));
				}

				//checking 
				place = CheckOnBoard(true, size, randY, randX, horizontal);

				// Placing ship prototype
				if (place) {
					if (horizontal) {
						for (int offset = 0; offset < size; offset++)
							playerBoardForMovements[randY][randX + offset] = 2;
					}
					else {
						for (int offset = 0; offset < size; offset++)
							playerBoardForMovements[randY + offset][randX] = 2;
					}
				}
			}

			while (!placeShip) {

				if (!placePlayerShipsAutomatically) {
					system("cls");
					ShowField(false, showOpponentShips);
					TextDuringPlayerPlacing();
				}

				if (placePlayerShipsAutomatically)
					input = (char)13;
				else
					input = _getch();

			checking:
				if (input == 'W' || input == 'w' || input == 'ö' || input == 'Ö') {
					moveShip('W', horizontal, randY, randX, size);
				}
				else if (input == 'S' || input == 's' || input == 'û' || input == 'Û') {
					moveShip('S', horizontal, randY, randX, size);
				}
				else if (input == 'A' || input == 'a' || input == 'ô' || input == 'Ô') {
					moveShip('A', horizontal, randY, randX, size);
				}
				else if (input == 'D' || input == 'd' || input == 'â' || input == 'Â') {
					moveShip('D', horizontal, randY, randX, size);
				}
				else if (input == 'R' || input == 'r' || input == 'ê' || input == 'Ê') {
					moveShip('R', horizontal, randY, randX, size);
					system("cls");
					ShowField(false, showOpponentShips);
					TextDuringPlayerPlacing();

					// cheatcode "reset" to reset the field
					input = _getch();
					if (input == 'E' || input == 'e') {
						input = _getch();
						system("cls");
						ShowField(false, showOpponentShips);
						TextDuringPlayerPlacing();
						if (input == 'S' || input == 's') {
							moveShip('S', horizontal, randY, randX, size);
							system("cls");
							ShowField(false, showOpponentShips);
							TextDuringPlayerPlacing();
							input = _getch();
							if (input == 'E' || input == 'e') {
								system("cls");
								ShowField(false, showOpponentShips);
								TextDuringPlayerPlacing();
								input = _getch();
								if (input == 'T' || input == 't') {
									goto reset;
								}
								else { goto checking; }
							}
							else { goto checking; }
						}
						else { goto checking; }
					}
					else { goto checking; }
					// !cheatcode

				}
				else if ((int)input == 13) { // Enter pressed
					if (CheckOnBoard(true, size, randY, randX, horizontal))
						placeShip = true;
				}

				if (placeShip) { // Applying ship on board
					if (horizontal) {
						for (int offset = 0; offset < size; offset++)
							playerBoard[randY][randX + offset] = 1;
					}
					else {
						for (int offset = 0; offset < size; offset++)
							playerBoard[randY + offset][randX] = 1;
					}

					playerShipInfo[shipCount][0] = randY;
					playerShipInfo[shipCount][1] = randX;
					playerShipInfo[shipCount][2] = size;
					horizontal ? playerShipInfo[shipCount++][3] = 1 : playerShipInfo[shipCount++][3] = 0;

					for (int i = 0; i < 10; i++) { for (int j = 0; j < 10; j++) { playerBoardForMovements[i][j] = 0; } } // Initializing fields as empty
				}
			}

			if (!placePlayerShipsAutomatically) {
				system("cls");
				ShowField(false, showOpponentShips);
				TextDuringPlayerPlacing();
			}
		}
	}
	system("cls");
	ShowField(false, showOpponentShips);
	TextDuringPlayerPlacing();
}

void PlaceOpponentShips() {
	short int randX, randY;
	short int shipCount = 0; // used to place ship info into array
	bool horizontal;
	bool place;

start:
	for (int i = 0; i < 10; i++) { for (int j = 0; j < 10; j++) { opponentBoard[i][j] = 0; } } // Initializing fields as empty

	for (int size = 4; size > 0; size--) { // size of ships
		for (int amount = 5 - size; amount > 0; amount--) { // number of ships required on field

			place = false;
			int tries = 0;

			while (!place)
			{
				if (tries++ > 1000)
					goto start;

				// getting random position to place ship
				horizontal = rand() % 2;

				if (allShipsDirection == 1)
					horizontal = false;
				else if (allShipsDirection == 2)
					horizontal = true;

				if (horizontal) {
					randX = (rand() % (11 - size));
					randY = (rand() % 10);
				}
				else {
					randX = (rand() % 10);
					randY = (rand() % (11 - size));
				}

				//checking 
				place = CheckOnBoard(false, size, randY, randX, horizontal);

				// Placing ship
				if (place) {
					if (horizontal) {
						for (int offset = 0; offset < size; offset++)
							opponentBoard[randY][randX + offset] = 1;
					}
					else {
						for (int offset = 0; offset < size; offset++)
							opponentBoard[randY + offset][randX] = 1;
					}

					opponentShipInfo[shipCount][0] = randY;
					opponentShipInfo[shipCount][1] = randX;
					opponentShipInfo[shipCount][2] = size;
					horizontal ? opponentShipInfo[shipCount++][3] = 1 : opponentShipInfo[shipCount++][3] = 0;
				}
			}
		}
	}
}