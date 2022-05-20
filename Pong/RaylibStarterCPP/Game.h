#pragma once

#include "AABB.h"
#include "Plane.h"
#include "raylib.h"
#include "raygui.h"
#include <iostream>


namespace Game
{
	class GameWindow
	{
	private:
		bool gameStart = false;

		int playerWidth = 20;
		int playerHight = 80;
		int ballRadius = 10;

		int screenWidth = 800;
		int screenHeight = 450;

		Plane edgeTop = { 0, 1, 0 };
		Plane edgeBottom = { 0, -1, screenHeight };
		Plane edgeLeft = { 1, 0, 0 };
		Plane edgeRight = { -1, 0, screenWidth };

		Vector2 player1Pos = Vector2{ 20, 10 }; 
		Vector2 player2Pos = Vector2{ (float)screenWidth - 40, 10 };
		Vector2 ballPos = Vector2{ (float)(screenWidth - 5) / 2, (float)(screenHeight - 5) / 2 };
		Vector2 ballVelocity = Vector2{ 0, 0 };

		AABB player1AABB;
		AABB player2AABB;
		AABB ballAABB;

		const char* startText = "Press space to start!";
		int fontSize = 20;


	public:
		void Init();
		void Update();
		void Draw();

		/*
		void DrawCoordinateSystem()
		{
			float lineLength = 64;

			Vector3 worldPosition = Vector3{ ballPos.x, ballPos.y, 0.0f };
			Vector3 forwardDirection = GlobalTransform * Vector3{ 1, 0, 0 };
			Vector3 rightDirection = GlobalTransform * Vector3{ 0, 1, 0 };
			Vector3 forwardPosition = worldPosition + forwardDirection * lineLength;
			Vector3 rightPosition = worldPosition + rightDirection * lineLength;

			DrawCircleLines((int)worldPosition.x, (int)worldPosition.y, 16, PURPLE);

			DrawLine((int)worldPosition.x, (int)worldPosition.y, (int)forwardPosition.x, (int)forwardPosition.y, RED);
			DrawLine((int)worldPosition.x, (int)worldPosition.y, (int)rightPosition.x, (int)rightPosition.y, GREEN);
		}
		*/
	};
}