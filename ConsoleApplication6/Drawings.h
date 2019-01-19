#pragma once

void ShowField(bool ShowOpponent, bool OpponentShipsVisible) {
	system("cls");
	cout << "\n";
	cout << "   0 1 2 3 4 5 6 7 8 9";
	if (ShowOpponent)
	{
		cout << "\t     0 1 2 3 4 5 6 7 8 9";
	}
	cout << "\n  " << (char)218; for (int i = 0; i < 9; i++) { cout << (char)196 << (char)194; } cout << (char)196 << (char)191; // top border of player
	if (ShowOpponent)
	{
		cout << "\t    " << (char)218; for (int i = 0; i < 9; i++) { cout << (char)196 << (char)194; } cout << (char)196 << (char)191;
	} // top border of enemy
	cout << "\n";

	for (int i = 0; i < 10; i++) { // rows
		cout << " " << i;
		cout << (char)179;
		for (int j = 0; j < 10; j++) { // cols

			if (!warStarted) {
				if ((playerBoard[i][j] == 0 && playerBoardForMovements[i][j] == 0) || (playerBoard[i][j] == 0 && playerBoardForMovements[i][j] == 3))
					cout << " ";
				else if (playerBoard[i][j] == 1 && playerBoardForMovements[i][j] == 0)
					cout << (char)219;
				else if (playerBoard[i][j] == 0 && playerBoardForMovements[i][j] == 2)
					cout << (char)176;
				else if (playerBoard[i][j] != 0 && playerBoardForMovements[i][j] == 2) {
					setColor(4, 15);
					cout << (char)178;
					setColor(0, 15);
				}
				else if (playerBoard[i][j] != 0 && playerBoardForMovements[i][j] == 3) {
					cout << (char)219;
				}
			}
			else {
				if (opponentShoots[i][j] == 9) { // Indicating shoot point
					setColor(13, 15); cout << "o"; setColor(0, 15);
				}
				else {
					if (playerBoard[i][j] == 1) {
						if (opponentShoots[i][j] == 1) { // if opponent hit the ship
							cout << (char)178;
						}
						else if (opponentShoots[i][j] == 4) { // if opponent destroyed the ship
							setColor(4, 15); cout << (char)219; setColor(0, 15);
						}
						else {
							cout << (char)219;
						}
					}
					else {
						if (opponentShoots[i][j] == 2) { // if opponent missed
							cout << (char)176;
						}
						else if (opponentShoots[i][j] == 3) { // if dots 
							cout << ".";
						}
						else {
							cout << " ";
						}
					}
				}
			}

			cout << (char)179;
		}

		if (ShowOpponent) {
			cout << "\t   " << i;
			cout << (char)179;
			for (int j = 0; j < 10; j++) { // cols

				if (playerBoardForMovements[i][j] == 3) {
					setColor(12, 15); cout << "o"; setColor(0, 15);
				}
				else if (playerShoots[i][j] == 1) {
					if (OpponentShipsVisible)
						cout << (char)178;
					else
						cout << (char)219;
				}
				else if (playerShoots[i][j] == 2) {
					cout << (char)176;
				}
				else if (playerShoots[i][j] == 3) {
					cout << ".";
				}
				else if (playerShoots[i][j] == 4) {
					setColor(4, 15); cout << (char)219; setColor(0, 15);
				}
				else if (OpponentShipsVisible && opponentBoard[i][j] == 1) {
					cout << (char)219;
				}
				else
					cout << " ";

				cout << (char)179;
			}
		}

		cout << "\n";

		i != 9 ? cout << "  " << (char)195 : cout << "  " << (char)192;
		for (int a = 0; a < 9; a++)
			i != 9 ? cout << (char)196 << (char)197 : cout << (char)196 << (char)193;
		i != 9 ? cout << (char)196 << (char)180 : cout << (char)196 << (char)217;

		if (ShowOpponent) {
			i != 9 ? cout << "\t    " << (char)195 : cout << "\t    " << (char)192;
			for (int a = 0; a < 9; a++)
				i != 9 ? cout << (char)196 << (char)197 : cout << (char)196 << (char)193;
			i != 9 ? cout << (char)196 << (char)180 : cout << (char)196 << (char)217;
		}

		cout << "\n";
	}
	cout << "\t   You"; if (ShowOpponent) { cout << "\t\t\t   Opponent"; }

}

void TextDuringPlayerPlacing() {
	gotoxy(40, 1);
	setColor(0, 15); cout << "_" << (char)214 << (char)215;
	setColor(4, 15); cout << "  BATTLE SHIPS  ";
	setColor(0, 15); cout << (char)215 << (char)183 << "_";

	gotoxy(30, 3);
	cout << "Now its your turn to place ships on the field";
	gotoxy(40, 6);
	cout << (char)218 << (char)196 << (char)194 << (char)196 << (char)194 << (char)196 << (char)194 << (char)196 << (char)191 << "  1x";
	gotoxy(40, 7);
	cout << (char)192 << (char)196 << (char)193 << (char)196 << (char)193 << (char)196 << (char)193 << (char)196 << (char)217;

	gotoxy(40, 9);
	cout << (char)218 << (char)196 << (char)194 << (char)196 << (char)194 << (char)196 << (char)191 << "  2x";
	gotoxy(40, 10);
	cout << (char)192 << (char)196 << (char)193 << (char)196 << (char)193 << (char)196 << (char)217;

	gotoxy(40, 12);
	cout << (char)218 << (char)196 << (char)194 << (char)196 << (char)191 << "  3x";
	gotoxy(40, 13);
	cout << (char)192 << (char)196 << (char)193 << (char)196 << (char)217;

	gotoxy(40, 15);
	cout << (char)218 << (char)196 << (char)191 << "  4x";
	gotoxy(40, 16);
	cout << (char)192 << (char)196 << (char)217;

	gotoxy(30, 18);
	cout << "Use ";
	setColor(2, 15); cout << "W A S D";
	setColor(0, 15); cout << " to relocate ship, ";
	setColor(2, 15); cout << "R";
	setColor(0, 15); cout << " to rorate";
	gotoxy(30, 20);
	cout << "and ";
	setColor(2, 15); cout << "Enter ";
	setColor(0, 15); cout << "to place a ship";
	gotoxy(30, 22);
	cout << "Or type "; setColor(12, 15); cout << "reset"; setColor(0, 15); cout << " to reset the field";
}

void TextDuringGame() {
	gotoxy(54, 1);
	setColor(0, 15); cout << "_" << (char)214 << (char)215;
	setColor(4, 15); cout << "  BATTLE SHIPS  ";
	setColor(0, 15); cout << (char)215 << (char)183 << "_";

	gotoxy(54, 4);
	cout << "Your ships left: " << playerShipsLeft;
	gotoxy(54, 6);
	cout << "Opponent ships left: " << opponentShipsLeft;
	gotoxy(54, 8); cout << "-";
	gotoxy(54, 10); setColor(2, 15); cout << "W A S D "; setColor(0, 15); cout << "for moves";
	gotoxy(54, 12); setColor(2, 15); cout << "Enter "; setColor(0, 15); cout << "for shoots";
}

void gameTitle() {
	system("cls");
	cout << "\n\n\n\n\n\n\n\n";
	cout << "\t\t      " << (char)219 << "        " << (char)219 << "   " << (char)219 << "  " << (char)219 << "     " << "" << "     " << (char)219 << "        " << "\n";
	cout << "\t\t      " << (char)219 << "        " << (char)219 << "   " << (char)219 << "  " << (char)219 << "     " << "" << "     " << (char)219 << "   " << (char)220 << "    " << "\n";
	cout << "\t\t      " << (char)219 << (char)219 << (char)219 << " " << (char)219 << (char)219 << (char)219 << " " << (char)219 << (char)219 << (char)219 << " " << (char)219 << (char)219 << (char)219 << " " << (char)219 << "  " << (char)219 << (char)219 << (char)219 << "" << " " << (char)219 << (char)223 << (char)223 << " " << (char)219 << (char)219 << (char)219 << " " << (char)220 << " " << (char)219 << (char)219 << (char)219 << "\n";
	cout << "\t\t      " << (char)219 << " " << (char)219 << " " << (char)219 << " " << (char)219 << "  " << (char)219 << "   " << (char)219 << "  " << (char)219 << "  " << (char)219 << (char)220 << (char)219 << "" << " " << (char)223 << (char)223 << (char)219 << " " << (char)219 << " " << (char)219 << " " << (char)219 << " " << (char)219 << " " << (char)219 << "\n";
	cout << "\t\t      " << (char)219 << (char)219 << (char)219 << " " << (char)219 << (char)219 << (char)219 << (char)219 << " " << (char)219 << (char)219 << "  " << (char)219 << (char)219 << " " << (char)219 << (char)219 << " " << (char)219 << (char)220 << (char)220 << "" << " " << (char)220 << (char)220 << (char)219 << " " << (char)219 << " " << (char)219 << " " << (char)219 << " " << (char)219 << (char)219 << (char)219 << "\n";
	cout << "\t\t      " << "                                 " << (char)219 << "  " << "\n";
	cout << "\t\t      " << "                                 " << (char)219 << "  " << "\n";
	cout << "\n\n\n\t\t\t\t   by kirillov";

	Sleep(2000);
	screenCover(0, 0);
	screenCover(15, 15);
}

void winScreen(bool win) {
	// Stats
	FILE *file;
	file = fopen("stats.txt", "r");
	int rows = 0;
	string names[5];
	int scores[5];
	if (file != NULL) {
		char buffs[40];
		int buffi = 0;

		for (int i = 0; i < 8; i++) 
			if (fscanf(file, "%s", buffs) != -1) 
				if (fscanf(file, "%d", &buffi) != -1) {
					names[i] = buffs;
					scores[i] = buffi;
					rows++;
				}

		fcloseall();
	}
	//Stats

	Sleep(1000);
	screenCover(0, 0);
	screenCover(15, 15);
	system("cls");
	cout << "\n\n\n\n\n";
	if (win) {
		setColor(2, 15);
		cout << "\t\t\t   " << (char)219 << " " << (char)219 << " " << (char)219 << (char)219 << (char)219 << " " << (char)219 << " " << (char)219 << "" << "   " << (char)219 << " " << (char)219 << " " << (char)219 << " " << (char)223 << " " << (char)219 << (char)219 << (char)219 << "\n";
		cout << "\t\t\t   " << (char)219 << (char)220 << (char)219 << " " << (char)219 << " " << (char)219 << " " << (char)219 << " " << (char)219 << "" << "   " << (char)219 << " " << (char)219 << " " << (char)219 << " " << (char)219 << " " << (char)219 << " " << (char)219 << "\n";
		cout << "\t\t\t   " << (char)220 << (char)220 << (char)219 << " " << (char)219 << (char)219 << (char)219 << " " << (char)219 << (char)219 << (char)219 << "" << "   " << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << " " << (char)219 << " " << (char)219 << " " << (char)219 << "\n";
	}
	else {
		setColor(12, 15);
		cout << "\t\t\t " << (char)219 << " " << (char)219 << " " << (char)219 << (char)219 << (char)219 << " " << (char)219 << " " << (char)219 << "" << "   " << (char)219 << "   " << (char)219 << (char)219 << (char)219 << " " << (char)219 << (char)223 << (char)223 << " " << (char)219 << (char)219 << (char)219 << "\n";
		cout << "\t\t\t " << (char)219 << (char)220 << (char)219 << " " << (char)219 << " " << (char)219 << " " << (char)219 << " " << (char)219 << "" << "   " << (char)219 << "   " << (char)219 << " " << (char)219 << " " << (char)223 << (char)223 << (char)219 << " " << (char)219 << (char)220 << (char)219 << "\n";
		cout << "\t\t\t " << (char)220 << (char)220 << (char)219 << " " << (char)219 << (char)219 << (char)219 << " " << (char)219 << (char)219 << (char)219 << "" << "   " << (char)219 << (char)219 << (char)219 << " " << (char)219 << (char)219 << (char)219 << " " << (char)220 << (char)220 << (char)219 << " " << (char)219 << (char)220 << (char)220 << "\n";
	}
	setColor(0, 15);
	cout << "\n\n\n\t\t\t\t " << "Your score: " << score;

	//stats
		//vyvod
	setColor(9, 15);
	cout << "\n\n\n" << "\t\t\t\t  TOP PLAYERS:" << "\n\n";
	setColor(8, 15);
	if (rows == 0) 
		cout << "\t\t\t       still no players :(";
	else 
		for (int i = 0; i < rows; i++) {
			cout << "\t\t\t\t  " << names[i];
			cout << " - " << scores[i] << "\n";
		}
	setColor(0, 15);

	// Adding new player
	if (rows < 5 || score > scores[4]) {
		cursorVisible(true);
		gotoxy(0, 22);
		cout << "\t\t      Enter your name to save score: ";
		string player;
		int playerScore;
		cin >> player;
		gotoxy(0, 22); cout << "\t\t\t\t\t\t\t\t\t"; gotoxy(0, 22);
		setColor(2, 15); cout << "\t\t\t\t     Saved!"; setColor(0, 15);
		playerScore = score;
		cursorVisible(false);

		//copying
		int *newScores = new int[rows + 1];
		string *newNames = new string[rows + 1];

		for (int i = 0; i < rows; i++) {
			newNames[i] = names[i];
			newScores[i] = scores[i];
		}
		newNames[rows] = player;
		newScores[rows] = playerScore;
		rows++;

		//sortirovka
		for (int j = 0; j < rows; j++) {
			bool changes = false;
			for (int i = 0; i < rows - 1; i++) {
				if (newScores[i] <= newScores[i + 1]) {
					changes = true;
					string buffs = newNames[i + 1];
					int buffi = newScores[i + 1];
					newNames[i + 1] = newNames[i];
					newScores[i + 1] = newScores[i];
					newNames[i] = buffs;
					newScores[i] = buffi;
				}
			}
			if (!changes)
				break;
		}

		//Print in file
		file = fopen("stats.txt", "w");

		if (file != NULL) {
			int till;
			rows > 5 ? till = 5 : till = rows;

			for (int i = 0; i < till; i++) {
				const char *newName = newNames[i].c_str();
				fprintf(file, "%s", newName);
				fprintf(file, "\n");
				fprintf(file, "%d", newScores[i]);
				fprintf(file, "\n");
			}
			fcloseall();
		}
	}
	//stats

	getch();
	screenCover(0, 0);
	exit(0);
}

void screenCover(short int textColor, short int backgroundColor) {
	setColor(textColor, backgroundColor);
	for (int i = 0; i < 80; i++) {
		Sleep(5);
		for (int j = 0; j < 25; j++) {
			gotoxy(i, j);
			cout << (char)219;
		}
	}
}