#pragma once

#include "AABB.h"
#include "Plane.h"
#include "raylib.h"
#include "raygui.h"
#include <iostream>
#include <random>

namespace Game
{
	class GameWindow
	{
	private:
		bool gameStart = false;
		bool gameOver = false;
		bool debug = false;
		
		int score = 0;

		int playerWidth = 20;
		int playerHight = 80;
		float ballRadius = 10;

		int ballSpeed = 300;

		int screenWidth = 800;
		int screenHeight = 450;
		int targetFps = 60;

		std::mt19937 rng;
		std::uniform_real_distribution<float> range;

		Plane edgeTop = { 0, 1, 0 };
		Plane edgeBottom = { 0, -1, (float)screenHeight };
		Plane edgeLeft = { 1, 0, 0 };
		Plane edgeRight = { -1, 0, (float)screenWidth };

		Vector2 player1CurvePoint;
		Vector2 player2CurvePoint;

		Vector2 player1Pos = Vector2{ 20, 10 }; 
		Vector2 player2Pos = Vector2{ (float)screenWidth - 40, 10 };
		Vector2 ballPos = Vector2{ (float)(screenWidth - 5) / 2, (float)(screenHeight - 5) / 2 };
		Vector2 ballVelocity = Vector2{ 0, 0 };

		AABB player1AABB;
		AABB player2AABB;
		AABB ballAABB;

		const char* title = "Pong";
		const char* startText = "Press space to start!";
		const char* gameOverText = "        Game Over!\nPress space to restart.";
		int fontSize = 20;


	public:
		void Init();
		void Update();
		void Draw();
		void DrawDebug();
	};
}