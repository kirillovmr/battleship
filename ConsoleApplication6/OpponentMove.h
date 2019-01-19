#pragma once

void OpponentMove() {

	checkWin();

	Sleep(1000);
	short int shootX, shootY;
	short int direction;
	short int tries = 0;

	bool emptyFieldForShoot = false;

	if (smartShootsByComputer) {
		if (!lastShipDestroyedByComp) {
			if (!knownDirection) {
				shootY = originSuccessY;
				shootX = originSuccessX;
				direction = rand() % 4;

			randDirection:
				direction++;
				if (direction > 3)
					direction = 0;

				if (direction == 0) { // top
					if (shootY > 0 && opponentShoots[shootY - 1][shootX] == 0) {
						shootY = originSuccessY - 1;
						shootX = originSuccessX;
					}
					else {
						goto randDirection;
					}
				}
				else if (direction == 1 && opponentShoots[shootY][shootX + 1] == 0) { // right
					if (shootX < 9) {
						shootY = originSuccessY;
						shootX = originSuccessX + 1;
					}
					else {
						goto randDirection;
					}
				}
				else if (direction == 2 && opponentShoots[shootY + 1][shootX] == 0) { // bottom
					if (shootY < 9) {
						shootY = originSuccessY + 1;
						shootX = originSuccessX;
					}
					else {
						goto randDirection;
					}
				}
				else if (direction == 3 && opponentShoots[shootY][shootX - 1] == 0) { // left
					if (shootX > 0) {
						shootY = originSuccessY;
						shootX = originSuccessX - 1;
					}
					else {
						goto randDirection;
					}
				}
				else {
					direction++;
					goto randDirection;
				}
			}
			else { // if direction is known
				if (hitsPerShip >= 2) {
					if (lastShootSuccess) {
						switch (smartDirection) {
						case 1:
							if (lastSuccessY - 1 >= 0 && opponentShoots[lastSuccessY - 1][lastSuccessX] == 0) {
								shootY = lastSuccessY - 1;
								shootX = lastSuccessX;
							}
							else {
								shootY = originSuccessY + 1;
								shootX = lastSuccessX;
								smartDirection = 3;
							}
							break;
						case 2:
							if (lastSuccessX + 1 <= 9 && opponentShoots[lastSuccessY][lastSuccessX + 1] == 0) {
								shootY = lastSuccessY;
								shootX = lastSuccessX + 1;
							}
							else {
								shootY = lastSuccessY;
								shootX = originSuccessX - 1;
								smartDirection = 4;
							}
							break;
						case 3:
							if (lastSuccessY + 1 <= 9 && opponentShoots[lastSuccessY + 1][lastSuccessX] == 0) {
								shootY = lastSuccessY + 1;
								shootX = lastSuccessX;
							}
							else {
								shootY = originSuccessY - 1;
								shootX = lastSuccessX;
								smartDirection = 1;
							}
							break;
						case 4:
							if (lastSuccessX - 1 >= 0 && opponentShoots[lastSuccessY][lastSuccessX - 1] == 0) {
								shootY = lastSuccessY;
								shootX = lastSuccessX - 1;
							}
							else {
								shootY = lastSuccessY;
								shootX = originSuccessX + 1;
								smartDirection = 2;
							}
							break;
						default:
							cout << " ERROR_678 "; getch();
							break;
						}
					}
					else {
						if (lastSuccessX > originSuccessX) {
							shootY = lastSuccessY;
							shootX = originSuccessX - 1;
							smartDirection = 4;
						}
						else if (lastSuccessX < originSuccessX) {
							shootY = lastSuccessY;
							shootX = originSuccessX + 1;
							smartDirection = 2;
						}
						else if (lastSuccessY > originSuccessY) {
							shootY = originSuccessY - 1;
							shootX = lastSuccessX;
							smartDirection = 1;
						}
						else if (lastSuccessY < originSuccessY) {
							shootY = originSuccessY + 1;
							shootX = lastSuccessX;
							smartDirection = 3;
						}
					}
				}
			}
		}
	}

	while (!emptyFieldForShoot) {

		if (lastShipDestroyedByComp) {
			shootY = rand() % 10;
			shootX = rand() % 10;
		}

		if (opponentShoots[shootY][shootX] == 0) { // shooting
			emptyFieldForShoot = true;

			opponentShoots[shootY][shootX] = 9; // indicating point of shoot
			ShowField(true, showOpponentShips);
			TextDuringGame();
			Sleep(500);

			if (playerBoard[shootY][shootX] == 1) {
				opponentShoots[shootY][shootX] = 1; // hit

				score -= 5; // if hit

				if (smartShootsByComputer) {
					if (lastShipDestroyedByComp) { // if it is first hit
						lastShipDestroyedByComp = false;
						originSuccessY = shootY;
						originSuccessX = shootX;
						hitsPerShip++;
					}
					else { // if 2+ hit
						hitsPerShip++;
						if (!knownDirection) {
							knownDirection = true;
							if (shootX > originSuccessX) {
								smartDirection = 2; // right
							}
							else if (shootX < originSuccessX) {
								smartDirection = 4; // left
							}
							else if (shootY > originSuccessY) {
								smartDirection = 3; // bottom
							}
							else if (shootY < originSuccessY) {
								smartDirection = 1; // top
							}
						}

						lastSuccessY = shootY;
						lastSuccessX = shootX;
						lastShootSuccess = true;
					}
				}

				bool destroyed = checkWholeShipDestroyedOrNot(true, shootY, shootX);

				if (destroyed) {
					if (smartShootsByComputer) {
						lastShipDestroyedByComp = true;
						knownDirection = false;
						checkedLeft = false, checkedRight = false, checkedTop = false, checkedBottom = false;
					}
				}
				ShowField(true, showOpponentShips);
				OpponentMove();
			}
			else {
				opponentShoots[shootY][shootX] = 2; // miss

				if (smartShootsByComputer) {
					if (knownDirection) {
						lastShootSuccess = false;
					}
				}
			}
		}
	}
}