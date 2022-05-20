#include "Game.h"
#include "raymath.h"
using namespace Game;

void::GameWindow::Init()
{
	InitWindow(screenWidth, screenHeight, "Pong");

	SetTargetFPS(60);
}

void::GameWindow::Update()
{
	if (gameStart)
	{
		if (IsKeyDown(KEY_UP) && player1Pos.y > 0 && !IsKeyDown(KEY_DOWN))
		{
			//player1Pos.y -= 5;
			player1Pos = Vector2Add(player1Pos, Vector2{ 0, -5 });
		}
		else if (IsKeyDown(KEY_DOWN) && player1Pos.y < screenHeight - playerHight && !IsKeyDown(KEY_UP))
		{
			//player1Pos.y += 5;
			player1Pos = Vector2Add(player1Pos, Vector2{ 0, 5 });
		}
	}
	else
	{
		if (IsKeyReleased(KEY_SPACE)) gameStart = true;
	}
}

void::GameWindow::Draw()
{
	BeginDrawing();
	{
		ClearBackground(BLACK);

		DrawRectangle(player1Pos.x, player1Pos.y, playerWidth, playerHight, WHITE);

		DrawRectangle(player2Pos.x, player2Pos.y, playerWidth, playerHight, WHITE);

		if (gameStart)
			DrawCircle(ballPos.x, ballPos.y, 10, WHITE);

		if (!gameStart)
			DrawText(startText, (screenWidth - MeasureText(startText, fontSize)) / 2, (screenHeight - 40) / 2, fontSize, LIGHTGRAY);
	}
	EndDrawing();
}
