#pragma once

bool checkWholeShipDestroyedOrNot(bool player, short int lastY, short int lastX) {

	bool destroyed;

	if (!player) { // now Checking opponent
		if (opponentBoard[lastY][lastX] == 1) {

			for (int i = 0; i < 10; i++) { // going through each ship except 1-size
				destroyed = true;

				short int startY = opponentShipInfo[i][0];
				short int startX = opponentShipInfo[i][1];
				short int size = opponentShipInfo[i][2];
				short int finishAt;

				if (opponentShipInfo[i][3] == 1) { // horizontal or no
					finishAt = startX + size; // + 1 tile for loop
					for (int j = startX; j < finishAt; j++) {
						if (opponentBoard[startY][j] == 1 && playerShoots[startY][j] != 1) {
							destroyed = false;
							break;
						}
					}

					if (destroyed) {
						for (int j = startX; j < finishAt; j++) { // Making it Red
							playerShoots[startY][j] = 4;
						}
						for (int a = startY - 1; a < startY + 2; a++) { // Making dots around
							for (int j = startX - 1; j < startX + size + 1; j++) {
								if (playerShoots[a][j] == 0 && a >= 0 && a < 10 && j >= 0 && j < 10)
									playerShoots[a][j] = 3;
							}
						}
						opponentShipsLeft--;
						score += 10 * size; // if kill
						return true;
					}
				}
				else {
					finishAt = startY + size - 1; // + 1 tile for loop
					for (int j = startY; j < startY + size + 1; j++) {
						if (opponentBoard[j][startX] == 1 && playerShoots[j][startX] != 1) {
							destroyed = false;
							break;
						}
					}

					if (destroyed) {
						for (int j = startY; j < startY + size; j++) { // Making it Red
							playerShoots[j][startX] = 4;
						}
						for (int a = startY - 1; a < startY + size + 1; a++) { // Making dots around
							for (int j = startX - 1; j < startX + 2; j++) {
								if (playerShoots[a][j] == 0 && a >= 0 && a < 10 && j >= 0 && j < 10)
									playerShoots[a][j] = 3;
							}
						}
						opponentShipsLeft--;
						score += 10 * size; // if kill
						return true;
					}
				}
			}
		}
	}
	else {
		if (playerBoard[lastY][lastX] == 1) {
			for (int i = 0; i < 10; i++) { // going through each ship except 1-size
				destroyed = true;

				short int startY = playerShipInfo[i][0];
				short int startX = playerShipInfo[i][1];
				short int size = playerShipInfo[i][2];
				short int finishAt;

				if (playerShipInfo[i][3] == 1) { // horizontal or no
					finishAt = startX + size; // + 1 tile for loop
					for (int j = startX; j < finishAt; j++) {
						if (playerBoard[startY][j] == 1 && opponentShoots[startY][j] != 1) {
							destroyed = false;
							break;
						}
					}
					if (destroyed) {
						for (int j = startX; j < finishAt; j++) { // Making it Red
							opponentShoots[startY][j] = 4;
						}
						for (int a = startY - 1; a < startY + 2; a++) { // Making dots around
							for (int j = startX - 1; j < startX + size + 1; j++) {
								if (opponentShoots[a][j] == 0 && a >= 0 && a < 10 && j >= 0 && j < 10)
									opponentShoots[a][j] = 3;
							}
						}
						playerShipsLeft--;
						score -= 10 * size; // if kill
						return true;
					}
				}
				else {
					finishAt = startY + size - 1; // + 1 tile for loop
					for (int j = startY; j < startY + size + 1; j++) {
						if (playerBoard[j][startX] == 1 && opponentShoots[j][startX] != 1) {
							destroyed = false;
							break;
						}
					}
					if (destroyed) {
						for (int j = startY; j < startY + size; j++) { // Making it Red
							opponentShoots[j][startX] = 4;
						}
						for (int a = startY - 1; a < startY + size + 1; a++) { // Making dots around
							for (int j = startX - 1; j < startX + 2; j++) {
								if (opponentShoots[a][j] == 0 && a >= 0 && a < 10 && j >= 0 && j < 10)
									opponentShoots[a][j] = 3;
							}
						}
						playerShipsLeft--;
						score -= 10 * size; // if kill
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool CheckOnBoard(bool player, int size, int randY, int randX, bool horizontal) {
	short int board[10][10];

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			player ? board[i][j] = playerBoard[i][j] : board[i][j] = opponentBoard[i][j];
		}
	}

	if (horizontal) {
		for (int offset = 0; offset < size; offset++) {

			if (board[randY][randX + offset] != 0) // Checking for ship at the same position
				return false;
			if (randY != 0) // Checking top cells
				if (board[randY - 1][randX + offset] != 0)
					return false;
			if (randY != 9) // Checking bottom cells
				if (board[randY + 1][randX + offset] != 0)
					return false;
		}

		if (randX != 0) {
			if (board[randY][randX - 1] != 0) // left tile
				return false;
			if (randY != 0)
				if (board[randY - 1][randX - 1] != 0) // left upper tile
					return false;
			if (randY != 9)
				if (board[randY + 1][randX - 1]) // left bottom tile
					return false;
		}

		if (randX != 10 - size) {
			if (board[randY][randX + size] != 0) // right tile
				return false;
			if (randY != 0)
				if (board[randY - 1][randX + size] != 0) // right upper tile
					return false;
			if (randY != 9)
				if (board[randY + 1][randX + size]) // right bottom tile
					return false;
		}
		return true;
	}
	else {
		bool ok = true;
		for (int offset = 0; offset < size; offset++) {

			if (board[randY + offset][randX] != 0) // Checking for ship at the same position
				ok = false;
			if (randX != 0)
				if (board[randY + offset][randX - 1] != 0) // Checking left cells
					ok = false;
			if (randX != 9)
				if (board[randY + offset][randX + 1] != 0) // Checking right cells
					ok = false;
		}

		if (randY != 0) {
			if (board[randY - 1][randX] != 0) // upper tile
				ok = false;
			if (randX != 0)
				if (board[randY - 1][randX - 1] != 0) // upper left tile
					ok = false;
			if (randX != 9)
				if (board[randY - 1][randX + 1] != 0) // upper right tile
					ok = false;
		}

		if (randY != 10 - size) {
			if (board[randY + size][randX] != 0) // bottom tile
				ok = false;
			if (randX != 0)
				if (board[randY + size][randX - 1] != 0) // bottom left tile
					ok = false;
			if (randX != 9)
				if (board[randY + size][randX + 1] != 0) // bottom right tile
					ok = false;
		}

		if (ok) {
			return true;
		}
		else {
			return false;
		}
	}
}

void checkWin() {
	if (playerShipsLeft == 0)
		winScreen(false);
	else if (opponentShipsLeft == 0)
		winScreen(true);
}