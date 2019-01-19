#pragma once

void SelectFieldForShooting(short int &shootY, short int &shootX) {

	checkWin();

	char input;
	bool shoot = false;
	bool hit = false;
	playerBoardForMovements[shootY][shootX] = 3;
	ShowField(true, showOpponentShips);
	TextDuringGame();

	while (!shoot) {
		input = _getch();
		if (input == 'W' || input == 'w' || input == 'ö' || input == 'Ö') {
			moveAim('W', shootY, shootX);
		}
		else if (input == 'S' || input == 's' || input == 'û' || input == 'Û') {
			moveAim('S', shootY, shootX);
		}
		else if (input == 'A' || input == 'a' || input == 'ô' || input == 'Ô') {
			moveAim('A', shootY, shootX);
		}
		else if (input == 'D' || input == 'd' || input == 'â' || input == 'Â') {
			moveAim('D', shootY, shootX);
		}
		else if ((int)input == 13) { // Enter pressed
			shoot = true;
		}

		if (shoot) { // Making shoot;
			if (opponentBoard[shootY][shootX] == 1 && playerShoots[shootY][shootX] == 0) {
				if (playerShoots[shootY][shootX] == 0) {
					score += 5; // if hit
				}
				playerShoots[shootY][shootX] = 1;
				checkWholeShipDestroyedOrNot(false, shootY, shootX);
				hit = true;
			}
			else if (opponentBoard[shootY][shootX] == 0)
				playerShoots[shootY][shootX] = 2;
		}

		if (shoot && pauseAfterPlayerShoot) {
			playerBoardForMovements[shootY][shootX] = 0;
			ShowField(true, showOpponentShips);
			TextDuringGame();
			Sleep(200);
			if (hit) {
				SelectFieldForShooting(shootY, shootX);
			}
		}

		ShowField(true, showOpponentShips);
		TextDuringGame();
	}

}

void moveAim(char direction, short int &shootY, short int &shootX) {
	if (direction == 'W') {
		if (shootY != 0) {
			playerBoardForMovements[shootY][shootX] = 0;
			playerBoardForMovements[shootY - 1][shootX] = 3;
			shootY--;
		}
	}
	else if (direction == 'S') {
		if (shootY != 9) {
			playerBoardForMovements[shootY][shootX] = 0;
			playerBoardForMovements[shootY + 1][shootX] = 3;
			shootY++;
		}
	}
	else if (direction == 'A') {
		if (shootX != 0) {
			playerBoardForMovements[shootY][shootX] = 0;
			playerBoardForMovements[shootY][shootX - 1] = 3;
			shootX--;
		}
	}
	else if (direction == 'D') {
		if (shootX != 9) {
			playerBoardForMovements[shootY][shootX] = 0;
			playerBoardForMovements[shootY][shootX + 1] = 3;
			shootX++;
		}
	}
}

void moveShip(char direction, bool &horizontal, short int &randY, short int &randX, int size) {
	if (direction == 'W') {
		if (randY != 0) {
			if (horizontal) {
				for (int offset = 0; offset < size; offset++) {
					playerBoardForMovements[randY][randX + offset] = 0;
					playerBoardForMovements[randY - 1][randX + offset] = 2;
				}
			}
			else {
				for (int offset = 0; offset < size; offset++) {
					playerBoardForMovements[randY + offset][randX] = 0;
					playerBoardForMovements[randY - 1 + offset][randX] = 2;
				}
			}
			randY--;
		}
	}
	else if (direction == 'S') {
		if (horizontal) {
			if (randY != 9) {
				for (int offset = 0; offset < size; offset++) {
					playerBoardForMovements[randY][randX + offset] = 0;
					playerBoardForMovements[randY + 1][randX + offset] = 2;
				}
				randY++;
			}
		}
		else {
			if (randY != 10 - size) {
				playerBoardForMovements[randY][randX] = 0;
				playerBoardForMovements[randY + size][randX] = 2;
				randY++;
			}
		}
	}
	else if (direction == 'A') {
		if (randX != 0) {
			if (horizontal) {
				playerBoardForMovements[randY][randX + size - 1] = 0;
				playerBoardForMovements[randY][randX - 1] = 2;
			}
			else {
				for (int offset = 0; offset < size; offset++) {
					playerBoardForMovements[randY + offset][randX] = 0;
					playerBoardForMovements[randY + offset][randX - 1] = 2;
				}
			}
			randX--;
		}

	}
	else if (direction == 'D') {
		if (horizontal) {
			if (randX != 10 - size) {
				playerBoardForMovements[randY][randX] = 0;
				playerBoardForMovements[randY][randX + size] = 2;
				randX++;
			}
		}
		else {
			if (randX != 9) {
				for (int offset = 0; offset < size; offset++) {
					playerBoardForMovements[randY + offset][randX] = 0;
					playerBoardForMovements[randY + offset][randX + 1] = 2;
				}
				randX++;
			}
		}
	}
	else if (direction == 'R') {
		if (horizontal) {
			if (randY > 10 - size) { // Moving ship upper for possibility to rotate
				int move = (size - (10 - randY));
				for (int i = 0; i < move; i++) {
					moveShip('W', horizontal, randY, randX, size);
				}
			}
			for (int offset = 1; offset < size; offset++) {
				playerBoardForMovements[randY][randX + offset] = 0;
				playerBoardForMovements[randY + offset][randX] = 2;
			}
			horizontal = !horizontal;
		}
		else {
			if (randX > 10 - size) { // Moving ship upper for possibility to rotate
				int move = (size - (10 - randX));
				for (int i = 0; i < move; i++) {
					moveShip('A', horizontal, randY, randX, size);
				}
			}
			for (int offset = 1; offset < size; offset++) {
				playerBoardForMovements[randY + offset][randX] = 0;
				playerBoardForMovements[randY][randX + offset] = 2;
			}
			horizontal = !horizontal;
		}
	}
}