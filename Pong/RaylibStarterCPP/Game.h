#pragma once

#define RAYGUI_SUPPORT_ICONS
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

		int screenWidth = 800;
		int screenHeight = 450;

		Vector2 player1Pos = Vector2{ 20, 10 }; 
		Vector2 player2Pos = Vector2{ (float)screenWidth - 40, 10 };
		Vector2 ballPos = Vector2{ (float)(screenWidth - 5) / 2, (float)(screenHeight - 5) / 2 };

		const char* startText = "Press space to start!";
		int fontSize = 20;


	public:
		void Init();
		void Update();
		void Draw();
	};
}