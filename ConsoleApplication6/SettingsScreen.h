#pragma once

void settingsScreen() {
	char input;
	bool showSettings = true;
	while (showSettings)
	{
		system("cls");
		cout << "\n\n\n\t\t\t\t    SETTINGS";
		cout << "\n\n\n\n\t1) Difficulty: ";
		if (smartShootsByComputer) {
			setColor(12, 15); cout << "hard"; setColor(0, 15);
		}
		else {
			setColor(9, 15); cout << "easy"; setColor(0, 15);
		}
		cout << "\n\n\t2) Automatically place ships: ";
		if (placePlayerShipsAutomatically) {
			setColor(2, 15); cout << "true"; setColor(0, 15);
		}
		else {
			setColor(12, 15); cout << "false"; setColor(0, 15);
		}
		cout << "\n\n\t3) Show computer ships: ";
		if (showOpponentShips) {
			setColor(2, 15); cout << "true"; setColor(0, 15);
		}
		else {
			setColor(12, 15); cout << "false"; setColor(0, 15);
		}
		cout << "\n\n\n\n\n\tUse "; setColor(6, 15); cout << "numpad"; setColor(0, 15); cout << " to change variables.";
		cout << "\n\n\tUse "; setColor(6, 15); cout << "ENTER"; setColor(0, 15); cout << " to start.";


		switch (input = _getch()) {
		case '1':
			smartShootsByComputer = !smartShootsByComputer;
			break;
		case '2':
			placePlayerShipsAutomatically = !placePlayerShipsAutomatically;
			break;
		case '3':
			showOpponentShips = !showOpponentShips;
			break;
		case 13:
			showSettings = false;
			break;
		default:
			break;
		}
	}
	screenCover(0, 0);
	screenCover(15, 15);
}