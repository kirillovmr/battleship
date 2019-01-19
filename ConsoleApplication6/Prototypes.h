#pragma once

// ---------- Custom Functions ------------------------------------ //
void gotoxy(int x, int y) {
	HANDLE hConsole;
	COORD cursorLoc;
	std::cout.flush();
	cursorLoc.X = x;
	cursorLoc.Y = y;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, cursorLoc);
}
void setColor(int text, int background) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
void cursorVisible(bool visible) {
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = visible;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}
// ---------- Custom Functions ------------------------------------ //

// ---------- Prototypes ------------------------------------------ //
void PlaceOpponentShips();
void PlacePlayerShips();
void SelectFieldForShooting(short int &shootY, short int &shootX);
void moveAim(char direction, short int &shootY, short int &shootX);
void GameProcess();
bool CheckOnBoard(bool player, int size, int randY, int randX, bool horizontal); // the part of PlaceOpponentShips() and PlacePlayerShips();
bool checkWholeShipDestroyedOrNot(bool player, short int lastY, short int lastX);
void moveShip(char direction, bool &horizontal, short int &randY, short int &randX, int size);
void ShowField(bool ShowOpponent, bool OpponentVisible);
void TextDuringPlayerPlacing();
void TextDuringGame();
void OpponentMove();
void checkWin();
void screenCover(short int textColor, short int backgroundColor);
void gameTitle();
void winScreen(bool win);
void settingsScreen();
// ---------- Prototypes ------------------------------------------ //

// ---------- Variables ( DONT CHANGE ) --------------------------- //
short int playerBoard[10][10];				 // [rows][cols]
short int opponentBoard[10][10];			 // [rows][cols]
short int playerBoardForMovements[10][10];   // [rows][cols] // 3 - aim 
short int playerShoots[10][10];				 // [rows][cols] // 1 - hit, 2 - miss, 3 - around sunken ship
short int opponentShoots[10][10];		     // [rows][cols
short int playerShipInfo[10][4];
short int opponentShipInfo[10][4];
short int playerShipsLeft = 10;
short int opponentShipsLeft = 10;
bool warStarted = false;
short int score = 300;
bool lastShipDestroyedByComp = true;
short int lastSuccessY;
short int lastSuccessX;
short int originSuccessY;
short int originSuccessX;
short int hitsPerShip = 0;
bool checkedLeft = false, checkedRight = false, checkedTop = false, checkedBottom = false, knownDirection = false, lastShootSuccess = false;
short int smartDirection = 0; // 1 - top, 2 - right, 3 bottom, 4 left
// ---------- Variables ( DONT CHANGE ) --------------------------- //

// ---------- Variables ------------------------------------------- //
bool showOpponentShips = false;
bool placePlayerShipsAutomatically = false;
bool pauseAfterPlayerShoot = true;
int allShipsDirection = 0; // 0 - random, 1 - vertical, 2 - horizontal
bool smartShootsByComputer = true;
// ---------- Variables ------------------------------------------- //