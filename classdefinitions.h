#pragma once
#include<raylib.h>
#include<string>
#include<ctime>

using namespace std;

class Question
{
public:

	Rectangle obj;
	string questiontext;
	string answer;
	Rectangle textbox;
	bool solved;
	string playeranswer;


	Question(string q, string a) :obj{ (float)(GetRandomValue(50,800)), (float)(GetRandomValue(150,500)),90.0f,70.0f }, questiontext(q), answer(a), textbox{ obj.x - 40,obj.y - 35,165,25 }, solved(false)
	{
	}



	void Draw(Rectangle player, Texture2D obstacle) {
		static float previousx = 0, previousy = 0;

		// Avoid overlapping questions by skipping if they are too close
		if (obj.x <= previousx + 40 && obj.x >= previousx - 40 &&
			obj.y <= previousy + 40 && obj.y >= previousy - 40)
			return;

		previousx = obj.x;
		previousy = obj.y;

		if (CheckCollisonwithplayer(player)) {
			Color rectlines = solved ? GREEN : YELLOW; //control colour of the box around the obstacle


			float scaleFactor = 0.5f;
			float scaledWidth = obstacle.width * scaleFactor;
			float scaledHeight = obstacle.height * scaleFactor;

			DrawRectangleLinesEx({ obj.x, obj.y, scaledWidth, scaledHeight }, 5, rectlines);
		}
	}





	bool CheckCollisonwithplayer(Rectangle Player)
	{

		return CheckCollisionRecs(obj, Player);
	}

	string AskQuestion(Font textfont) {
		float maxWidth = 200.0f;
		float fontSize = 23.0f;
		float spacing = 2.0f;
		float startY = obj.y - 60;
		float currentY = startY;

		// Draw question box (initial size estimate, later adjust)
		DrawRectangleRounded({ obj.x - 90, obj.y - 70, 270, 100 }, 1.0f, 8, DARKGREEN);


		string currentLine = "";
		for (int i = 0; i < questiontext.size(); ++i) {
			currentLine += questiontext[i];

			// Check if the current line width exceeds the max width 
			if (MeasureTextEx(textfont, currentLine.c_str(), fontSize, spacing).x > maxWidth || i == questiontext.size() - 1) {
				// Draw the current line
				DrawTextEx(textfont, currentLine.c_str(), { obj.x - 70, currentY }, fontSize, spacing, WHITE);
				currentLine = "";
				currentY += fontSize; // Move to the next line position
			}
		}


		DrawRectangleLines((int)obj.x - 50, (int)obj.y - 20, (int)textbox.width, (int)textbox.height, WHITE);

		// Handle player input
		if (IsKeyPressed(KEY_BACKSPACE) && !playeranswer.empty())
			playeranswer.pop_back();

		int key = GetCharPressed();
		while (key > 0) {
			if (key >= 32 && key <= 125 && playeranswer.size() < 50)
				playeranswer += (char)key;

			key = GetCharPressed();
		}

		DrawTextEx(textfont, playeranswer.c_str(), { obj.x - 20, obj.y - 20 }, 20, 4, BLACK);

		if (IsKeyPressed(KEY_ENTER) && answer != playeranswer)
			playeranswer.clear();

		if (IsKeyPressed(KEY_ENTER))
			return playeranswer;

		return "";
	}



	void CheckAnswer(string playeranswer, Sound wrongans, Sound correct, Texture2D obstacle)
	{


		float scaleFactor = 0.5f;
		float scaledWidth = obstacle.width * scaleFactor;
		float scaledHeight = obstacle.height * scaleFactor;



		if (answer == playeranswer)
			solved = true;

		else if (answer != playeranswer && IsKeyPressed(KEY_ENTER))
			PlaySound(wrongans);
		if (answer == playeranswer && IsKeyPressed(KEY_ENTER))
			PlaySound(correct);

		if (IsSoundPlaying(wrongans))
			DrawRectangleLinesEx({ obj.x, obj.y, scaledWidth, scaledHeight }, 5, RED);

	}




};

typedef enum GameScreen { LOGO = 0, TITLE, TUTORIAL, MENU, MATH, PHYSICS, CHEMISTRY, ENDING } GameScreen;


void PageSetupAndGameLogic(Texture2D background, Rectangle Player, Texture2D Player1, const int NUMOFQUESTIONS, Question questions[], Texture2D obstacle, bool& correctans, Sound wrongans, Sound correct, Font textfont)
{
	ClearBackground(DARKBROWN);
	DrawTextureEx(background, { 0.0f,0.0f }, 0.0f, 0.95f, WHITE);
	DrawRectangle(Player.x + 25, Player.y + 12, 20, 40, DARKBROWN); //Rectangle behind texture to check collisions 
	DrawTextureEx(Player1, { Player.x, Player.y }, 0.0f, 0.8f, WHITE); //Player draw
	int limit = 4;

	if (NUMOFQUESTIONS < 5)
		limit = NUMOFQUESTIONS;


	for (int i = 0; i < limit; i++)
	{

		questions[i].Draw(Player, obstacle);
		DrawTextureEx(obstacle, { questions[i].obj.x,questions[i].obj.y }, 0.0f, 0.5f, WHITE);


		if (questions[i].CheckCollisonwithplayer(Player))
			questions[i].CheckAnswer(questions[i].AskQuestion(textfont), wrongans, correct, obstacle);

	}

	for (int i = 0; i < limit; i++)
	{
		correctans = questions[i].solved;

		if (!correctans)
			break;

	}
}