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
		if (edgeTop.TestSide(Vector3{ ballPos.x, ballPos.y, 0 }, (float)ballRadius) == Plane::ePlaneResult::INTERSECTS)
		{
			ballVelocity = Vector2MultiplyV(ballVelocity, edgeTop.GetPlaneDirection());
		}

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

		player1AABB.min = Vector3{ player1Pos.x, player1Pos.y, 1 };
		player1AABB.max = Vector3{ player1Pos.x + playerWidth, player1Pos.y + playerHight, 1 };

		player2AABB.min = Vector3{ player2Pos.x, player2Pos.y, 1 };
		player2AABB.max = Vector3{ player2Pos.x + playerWidth, player2Pos.y + playerHight, 1 };

		ballAABB.min = Vector3{ ballPos.x - ballRadius, ballPos.y - ballRadius, 1 };
		ballAABB.max = Vector3{ ballPos.x + ballRadius, ballPos.y + ballRadius, 1 };
		
		
		ballPos = Vector2Add(ballPos, ballVelocity);
	}
	else
	{
		if (IsKeyReleased(KEY_SPACE))
		{
			gameStart = true;

			ballVelocity = Vector2{ 0, -10 };
			//ballVelocity = Vector2{(float)(rand() % 10 + 1), (float)(rand() % 10 + 1)};
		}
	}
}

void::GameWindow::Draw()
{
	BeginDrawing();
	{
		ClearBackground(BLACK);

		DrawRectangle((int)player1Pos.x, (int)player1Pos.y, playerWidth, playerHight, WHITE);
		DrawRectangle((int)player2Pos.x, (int)player2Pos.y, playerWidth, playerHight, WHITE);

		if (gameStart)
		{
			DrawCircle((int)ballPos.x, (int)ballPos.y, ballRadius, WHITE);
			player1AABB.Draw(RED);
			player2AABB.Draw(RED);
			ballAABB.Draw(RED);
		}
			
		if (!gameStart)
			DrawText(startText, (screenWidth - MeasureText(startText, fontSize)) / 2, (screenHeight - 40) / 2, fontSize, LIGHTGRAY);
	}
	EndDrawing();
}

