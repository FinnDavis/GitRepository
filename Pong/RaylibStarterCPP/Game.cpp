#include "Game.h"
#include "raymath.h"
#include <string>

using namespace Game;

void::GameWindow::Init()
{
	InitWindow(screenWidth, screenHeight, title);
	SetTargetFPS(targetFps);
	rng.seed(time(nullptr));
	range = std::uniform_real_distribution<float>(-PI / 4, PI / 4);
}

void::GameWindow::Update()
{
	if (gameStart && !gameOver)
	{
		if (IsKeyDown(KEY_W) && player1Pos.y > 0 && !IsKeyDown(KEY_DOWN))
		{
			player1Pos = Vector2Add(player1Pos, Vector2Scale(Vector2{ 0, -225 }, GetFrameTime()));
		}
		else if (IsKeyDown(KEY_S) && player1Pos.y < screenHeight - playerHight && !IsKeyDown(KEY_UP))
		{
			player1Pos = Vector2Add(player1Pos, Vector2Scale(Vector2{ 0, 225 }, GetFrameTime()));
		}

		if (IsKeyDown(KEY_UP) && player2Pos.y > 0 && !IsKeyDown(KEY_DOWN))
		{
			player2Pos = Vector2Add(player2Pos, Vector2Scale(Vector2{ 0, -225 }, GetFrameTime()));
		}
		else if (IsKeyDown(KEY_DOWN) && player2Pos.y < screenHeight - playerHight && !IsKeyDown(KEY_UP))
		{
			player2Pos = Vector2Add(player2Pos, Vector2Scale(Vector2{ 0, 225 }, GetFrameTime()));
		}
		if (IsKeyReleased(KEY_Z))
		{
			if (debug)
			{
				debug = false;
			}
			else
			{
				debug = true;
			}
		}

		ballPos = Vector2Add(ballPos, Vector2Scale(ballVelocity, GetFrameTime()));

		player1CurvePoint = Vector2{ player1Pos.x - 80, player1Pos.y + playerHight / 2 };
		player2CurvePoint = Vector2{ player2Pos.x + 100, player2Pos.y + playerHight / 2 };

		player1AABB.min = Vector3{ player1Pos.x, player1Pos.y, 1 };
		player1AABB.max = Vector3{ player1Pos.x + playerWidth, player1Pos.y + playerHight, 1 };

		player2AABB.min = Vector3{ player2Pos.x, player2Pos.y, 1 };
		player2AABB.max = Vector3{ player2Pos.x + playerWidth, player2Pos.y + playerHight, 1 };

		ballAABB.min = Vector3{ ballPos.x - ballRadius, ballPos.y - ballRadius, 1 };
		ballAABB.max = Vector3{ ballPos.x + ballRadius, ballPos.y + ballRadius, 1 };

		// Test Top and Bottom border collision
		if (edgeTop.TestSide(Vector3{ ballPos.x, ballPos.y, 0 }, ballRadius) == Plane::ePlaneResult::INTERSECTS && ballVelocity.y < 0)
			ballVelocity = Vector2{ ballVelocity.x, -ballVelocity.y };
		if (edgeBottom.TestSide(Vector3{ ballPos.x, ballPos.y, 0 }, ballRadius) == Plane::ePlaneResult::INTERSECTS && ballVelocity.y > 0)
			ballVelocity = Vector2{ ballVelocity.x, -ballVelocity.y };

		// Test Left and Right border collision
		if (edgeLeft.TestSide(Vector3{ ballPos.x, ballPos.y, 0 }, ballRadius) == Plane::ePlaneResult::INTERSECTS
		 || edgeRight.TestSide(Vector3{ ballPos.x, ballPos.y, 0 }, ballRadius) == Plane::ePlaneResult::INTERSECTS)
			gameOver = true;

		// Test paddle collision
		//
		// V = Velocity vector
		// N = Surface normal	
		// V-2N(V.N)
		if (ballAABB.Overlaps(player1AABB) && ballVelocity.x < 0)
		{
			Vector2 normal = Vector2Normalize(Vector2Subtract(ballPos, player1CurvePoint));
			ballVelocity = Vector2Subtract(ballVelocity, Vector2Scale(Vector2Scale(normal, 2), Vector2DotProduct(ballVelocity, normal)));
			ballVelocity = Vector2Scale(ballVelocity, 1.05);
			ballPos = Vector2Add(ballPos, Vector2Scale(ballVelocity, GetFrameTime()));
		}
		if (ballAABB.Overlaps(player2AABB) && ballVelocity.x > 0)
		{
			Vector2 normal = Vector2Normalize(Vector2Subtract(ballPos, player2CurvePoint));
			ballVelocity = Vector2Subtract(ballVelocity, Vector2Scale(Vector2Scale(normal, 2), Vector2DotProduct(ballVelocity, normal)));
			ballVelocity = Vector2Scale(ballVelocity, 1.05);
			ballPos = Vector2Add(ballPos, Vector2Scale(ballVelocity, GetFrameTime()));
		}
	}
	else
	{
		// Wait for user input to start/restart the game
		if (IsKeyReleased(KEY_SPACE))
		{
			gameOver = false;
			gameStart = true;
			float startingAngle = range(rng);
			player1Pos = Vector2{ 20, (float)screenHeight / 2 - (float)playerHight / 2};
			player2Pos = Vector2{ (float)screenWidth - playerWidth - 20, (float)screenHeight / 2 - (float)playerHight / 2 };
			ballPos = Vector2{ (float)(screenWidth - 5) / 2, (float)(screenHeight - 5) / 2 };
			ballVelocity = Vector2Scale(Vector2{ cos(startingAngle), sin(startingAngle) }, ballSpeed);
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
 		DrawCircle((int)ballPos.x, (int)ballPos.y, ballRadius, WHITE);

		if (debug)
			DrawDebug();
			
		if (!gameStart)
			DrawText(startText, (screenWidth - MeasureText(startText, fontSize)) / 2, (screenHeight - 40) / 2, fontSize, LIGHTGRAY);

		if (gameOver)
			DrawText(gameOverText, (screenWidth - MeasureText(startText, fontSize)) / 2, (screenHeight - 40) / 2, fontSize, LIGHTGRAY);
	}
	EndDrawing();
}

void::GameWindow::DrawDebug()
{
	// FPS counter
	std::string fps = std::to_string(GetFPS());
	std::string text = "FPS: ";
	text.append(fps);
	DrawText(text.c_str(), 60, 20, fontSize, LIGHTGRAY);

	// Circlular vector reflection
	DrawCircleLines(player1CurvePoint.x, player1CurvePoint.y, playerHight + 30, RED);
	DrawCircleLines(player2CurvePoint.x, player2CurvePoint.y, playerHight + 30, RED);

	// Middle of screen
	DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);

	// AABB's (Axis Aligned Bounding Box's)
	player1AABB.Draw(RED);
	player2AABB.Draw(RED);
	ballAABB.Draw(RED);
}
//merge test


// other merge test