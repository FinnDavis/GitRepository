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

		// Image
		Image icon = Image{};

		// Bool
		bool gameStart = false;
		bool gameOver = false;
		bool debug = false;
		
		// Int
		int screenHeight = 450;
		int screenWidth = 800;

		int playerWidth = 20;
		int playerHight = 80;
		int ballSpeed = 300;
		int targetFps = 60;
		int fontSize = 20;

		// Float
		float ballRadius = 10;

		// Rng
		std::uniform_real_distribution<float> range;
		std::mt19937 rng;

		// Plane
		Plane edgeTop = { 0, 1, 0 };
		Plane edgeBottom = { 0, -1, (float)screenHeight };
		Plane edgeLeft = { 1, 0, 0 };
		Plane edgeRight = { -1, 0, (float)screenWidth };

		// Vector 2
		Vector2 player1Pos = Vector2{ 20, 10 }; 
		Vector2 player2Pos = Vector2{ (float)screenWidth - 40, 10 };
		Vector2 ballPos = Vector2{ (float)(screenWidth - 5) / 2, (float)(screenHeight - 5) / 2 };
		Vector2 ballVelocity = Vector2{ 0, 0 };
		Vector2 player1CurvePoint;
		Vector2 player2CurvePoint;

		// AABB (Axis Aligned Bounding Box)
		AABB player1AABB;
		AABB player2AABB;
		AABB ballAABB;

		// const char (strings)
		const char* gameOverText = "        Game Over!\nPress space to restart.";
		const char* startText = "Press space to start!";
		const char* title = "Pong";

	public:

		// Functions
		void Init();
		void Update();
		void Draw();
		void DrawDebug();
	};
}