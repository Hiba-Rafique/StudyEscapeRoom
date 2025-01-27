#pragma once

#include<raylib.h>
#include"classdefinitions.h"




void playerandcameramovementupdate(Rectangle& Player, int playerspeed, Camera2D& camera, int width, int height, int worldwidth, int worldheight)
{
    if (IsKeyDown(KEY_UP))
        Player.y -= playerspeed;

    if (IsKeyDown(KEY_DOWN))
        Player.y += playerspeed;

    if (IsKeyDown(KEY_RIGHT))
        Player.x += playerspeed;

    if (IsKeyDown(KEY_LEFT))
        Player.x -= playerspeed;

    if (Player.x < 0) Player.x = 0;
    if (Player.x > worldwidth - Player.width) Player.x = (float)(worldwidth - Player.width);
    if (Player.y < 0) Player.y = 0;
    if (Player.y > worldheight - Player.height) Player.y = (float)(worldheight - Player.height);




    camera.target = { Player.x + Player.width / 2, Player.y + Player.height / 2 };

    if (camera.target.x < width / 2) camera.target.x = width / 2;
    if (camera.target.x > worldwidth - width / 2) camera.target.x = worldwidth - width / 2; //camera follows player 
    if (camera.target.y < height / 2) camera.target.y = height / 2;
    if (camera.target.y > worldheight - height / 2) camera.target.y = worldheight - height / 2;
}


void ButtonSetupAndHover(Vector2 mouse, Rectangle bounds, string buttontext, Font text, int fontsize, int spacing, Color c1, Color c2)
{
    if (CheckCollisionPointRec(mouse, bounds))
        DrawTextEx(text, buttontext.c_str(), { bounds.x,bounds.y }, fontsize, spacing, c1);
    else
        DrawTextEx(text, buttontext.c_str(), { bounds.x,bounds.y }, fontsize, spacing, c2);
}

void ShuffleQuestions(Question questions[], int numQuestions) {
    for (int i = numQuestions - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        swap(questions[i], questions[j]);
    }
}

void ResetGame(Question questions[], const int NUMOFQUESTIONS) {
    ShuffleQuestions(questions, NUMOFQUESTIONS);

    for (int i = 0; i < NUMOFQUESTIONS; i++) {
        questions[i].solved = false;
        questions[i].playeranswer = "";
        questions[i].obj = { (float)GetRandomValue(50, 800), (float)GetRandomValue(150, 550), 90.0f, 70.0f };
    }


}

