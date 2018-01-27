#include <Windows.h>
#include <iostream>

#include "main.h"

#include "snake.h"

using namespace std;

Snake* Game = new Snake;

void drawBoard()
{
	//Clear the screen
	system("cls");
	//Draw the board
	for (unsigned y = 0; y < boardHeight; y++)
	{
		for (unsigned x = 0; x < boardWidth; x++)
		{
			switch (Game->CheckPosition(x, y))
			{
			case SNAKE_NONE:
				cout << "+";
				break;
			case SNAKE_HEAD:
				cout << "*";
				break;
			case SNAKE_BODY:
				cout << "#";
				break;
			case SNAKE_APPLE:
				cout << "@";
				break;
			}
		}
		cout << endl;
	}
}

void CheckControls()
{
	if (IsKeyDown(VK_UP))
		Game->SetVelocity(0, 1);
	else if (IsKeyDown(VK_RIGHT))
		Game->SetVelocity(1, 0);
	else if (IsKeyDown(VK_DOWN))
		Game->SetVelocity(0, -1);
	else if (IsKeyDown(VK_LEFT))
		Game->SetVelocity(-1, 0);

#ifdef _DEBUG
	if (IsKeyDown(VK_CONTROL))
		Game->AddPiece();
#endif //_DEBUG
}

void CheckAppleSpawn()
{
	if (rand() % 100 + 1 < appleChance) //1 to 100
	{
		Game->AddApple(boardWidth, boardHeight);
	}
}

void GameOver()
{
	system("cls");
	cout << R"(#####################################################
#                                                   #
#       .::::                                       #
#     .:    .::                                     #
#    .::           .::    .::: .:: .::    .::       #
#    .::         .::  .::  .::  .:  .:: .:   .::    #
#    .::   .::::.::   .::  .::  .:  .::.::::: .::   #
#     .::    .: .::   .::  .::  .:  .::.:           #
#      .:::::     .:: .:::.:::  .:  .::  .::::      #
#                                                   #
#        .::::                                      #
#      .::    .::                                   #
#    .::        .::.::     .:: .::   .: .:::        #
#    .::        .:: .::   .::.:   .:: .::           #
#    .::        .::  .:: .::.::::: .::.::           #
#      .::     .::    .:.:: .:        .::           #
#        .::::         .::    .::::  .:::           #
#                                                   #
#####################################################
        )";
}

int main()
{
	Game->Init(boardWidth / 2, boardHeight / 2);
	while (Game->IsRunning())
	{
		Game->UpdatePositions();
		drawBoard();
		Sleep(100);
		CheckControls();
		CheckAppleSpawn();
	}

	GameOver();

	system("PAUSE");
	return 0;
}