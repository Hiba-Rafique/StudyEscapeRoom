#include "functiondefinitions.h"
using namespace std;

int main() {

    const int NUMOFQUESTIONS = 25;

    SetRandomSeed(time(0));
    InitAudioDevice();

    int width = 800;
    int height = 700;
    int worldwidth = 900;
    int worldheight = 780;

    bool correctans = true;
    bool isselected = false;

    int framesCounter = 0;

    GameScreen currentScreen = TITLE;



    Question mathquestions[NUMOFQUESTIONS] = {
    Question("Integral of 1/x", "lnx"),
    Question("d/dx(sinx)", "cosx"),
    Question("Lim x->0 sinx/x", "1"),
    Question("d/dx(e)?", "0"),
    Question("Integral of 0", "c"),
    Question("Derivative of x^2", "2x"),
    Question("Value of pi?", "3.14"),
    Question("Root of x^2=4", "2"),
    Question("d/dx(lnx)?", "1/x"),
    Question("Lim x->? 1/x", "0"),
    Question("Integral of 1?", "x"),
    Question("Value of cos(0)?", "1"),
    Question("Value of sin(90)?", "1"),
    Question("Log base 10 of 100", "2"),
    Question("d/dx(tanx)?", "sec^2x"),
    Question("Value of e?", "2.71"),
    Question("Area of circle?", "pi*r^2"),
    Question("Root of x^2=9?", "3"),
    Question("Solve: 5+3*2?", "11"),
    Question("Factorial of 3?", "6"),
    Question("Derivative of x?", "1"),
    Question("Lim x->0 1/x?", "undefined"),
    Question("Integral of x?", "x^2/2"),
    Question("Value of sin(0)?", "0"),
    Question("Value of cos(pi)?","-1")
    };


    Question phyquestions[NUMOFQUESTIONS] = {
    Question("Value of acceleration of gravity", "9.8"),
    Question("Power is scalar or vector?", "scalar"),
    Question("Unit of magnetic field", "tesla"),
    Question("Energy due to motion", "kinetic"),
    Question("Force = mass x ?", "acceleration"),
    Question("Speed of light?", "3e8"),
    Question("Unit of current?", "ampere"),
    Question("Value of absolute zero?", "-273"),
    Question("Sound travels in?", "medium"),
    Question("Formula for work?", "force*distance"),
    Question("SI unit of energy?", "joule"),
    Question("Heat transfer by waves?", "radiation"),
    Question("Unit of force?", "newton"),
    Question("Electric charge carrier?", "electron"),
    Question("SI unit of power?", "watt"),
    Question("Formula for pressure?", "force/area"),
    Question("Unit of frequency?", "hertz"),
    Question("Energy of position?", "potential"),
    Question("Celsius freezing point?", "0"),
    Question("Momentum = mass x ?", "velocity"),
    Question("Type of lens for magnification?", "convex"),
    Question("State of matter: ice?", "solid"),
    Question("Acceleration unit?", "m/s^2"),
    Question("Instrument to measure time?", "clock"),
    Question("SI unit of voltage?", "volt")
    };


    Question chemquestions[NUMOFQUESTIONS] = {
    Question("Chemical formula: table salt", "nacl"),
    Question("Chemical symbol: Gold?", "au"),
    Question("Gas from acid + metal?", "hydrogen"),
    Question("Bond involves sharing electrons?", "covalent"),
    Question("Symbol for oxygen?", "o"),
    Question("Formula of water?", "h20"),
    Question("Atomic number of carbon?", "6"),
    Question("Gas in air: 78%?", "nitrogen"),
    Question("Acid in vinegar?", "acetic"),
    Question("Formula of methane?", "ch4"),
    Question("Atomic number of oxygen?", "8"),
    Question("Gas burns with pop?", "hydrogen"),
    Question("Bond involves transfer electrons?", "ionic"),
    Question("Element with symbol Na?", "sodium"),
    Question("Liquid metal element?", "mercury"),
    Question("Symbol for iron?", "fe"),
    Question("Formula for ammonia?", "nh3"),
    Question("Common acid in soda?", "carbonic"),
    Question("Symbol for calcium?", "ca"),
    Question("Element in diamonds?", "carbon"),
    Question("Formula for ethanol?", "c2h5oh"),
    Question("Rust formula?", "fe2O3"),
    Question("Acid in stomach?", "hc;"),
    Question("Base in soap?", "naoh"),
    Question("Symbol for silver?", "ag")
    };


    Question tutorialquestions[5] = {
    Question("Capital of France?", "paris"),
    Question("13 * 3 =", "39"),
    Question("What is the color of the sky?", "blue"),
    Question("How many continents are there?", "7"),
    Question("What is 5 + 7?", "12")
    };


    InitWindow(width, height, "Escape Room");

    SetTargetFPS(60);


    int posX = 50;
    int posY = 50;
    int playerspeed = 5;

    Rectangle Player = { posX,posY,55,70 };
    Rectangle startbound = { 335,320 ,120,50 };
    Rectangle mathbound = { 300.0f,340.0f,150,70 };
    Rectangle phybound = { 305.0f,417.0f,150,70 };
    Rectangle chembound = { 300.0f,495.0f,150,70 };
    Rectangle tutorialbound = { 310.0f,347.0f,160,50 };
    Rectangle playbound = { 240.0f,450.0f,250,50 };
    Rectangle exitbound = { 330.0f,500.0f,250,50 };


    Camera2D camera = { 0 };
    camera.target = { 400.0f,350.0f };
    camera.offset = { width / 2.0f, height / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Texture2D Player1 = LoadTexture("resource/Player.png");
    Texture2D background = LoadTexture("resource/Classroom.png");
    Texture2D cactus = LoadTexture("resource/cactus.png");
    Texture2D Title = LoadTexture("resource/GameTitlePage.jpg");
    Texture2D Button = LoadTexture("resource/startbutton.png");
    Texture2D Menu = LoadTexture("resource/Menu.jpg");
    Texture2D chem = LoadTexture("resource/ChemistryLab.png");
    Texture2D flask = LoadTexture("resource/flask.png");
    Texture2D phy = LoadTexture("resource/PhysicsLab.png");
    Texture2D phychair = LoadTexture("resource/phychair.png");
    Texture2D tutorial = LoadTexture("resource/tutorial.png");
    Texture2D plant = LoadTexture("resource/plant.png");
    Texture2D ending = LoadTexture("resource/Ending.png");

    Font textfont = LoadFont("resource/PIXELFONT.ttf");
    Sound wrongans = LoadSound("resource/Buzzer.wav");
    Sound correct = LoadSound("resource/correctans.wav");
    Music gamesound = LoadMusicStream("resource/backgroundsound.wav");


    PlayMusicStream(gamesound);

    int obstaclesleft = NUMOFQUESTIONS;

    while (!WindowShouldClose())
    {

        UpdateMusicStream(gamesound);
        SetMusicVolume(gamesound, 0.5);

        Rectangle backbound = { camera.target.x - camera.offset.x,camera.target.y - camera.offset.y,70,30 };

        Vector2 mousepos = GetMousePosition();
        mousepos.x += backbound.x;
        mousepos.y += backbound.y;


        if (currentScreen == MATH || currentScreen == PHYSICS || currentScreen == CHEMISTRY || currentScreen == TUTORIAL)
        {
            StopMusicStream(gamesound);
            playerandcameramovementupdate(Player, playerspeed, camera, width, height, worldwidth, worldheight);
        }


        else if (!IsMusicStreamPlaying(gamesound))
            PlayMusicStream(gamesound);

        switch (currentScreen)
        {
        case LOGO:
        {

            framesCounter++;

            if (framesCounter > 120)
                currentScreen = TITLE;


        } break;
        case TITLE:
        {

            if ((CheckCollisionPointRec(GetMousePosition(), startbound) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
                currentScreen = MENU;
            if ((CheckCollisionPointRec(GetMousePosition(), tutorialbound) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
                currentScreen = TUTORIAL;

        } break;

        case TUTORIAL:
        {
            if (CheckCollisionPointRec(mousepos, backbound) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                currentScreen = TITLE;

        }break;

        case MENU:
        {
            if (CheckCollisionPointRec(mousepos, backbound) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                currentScreen = TITLE;
            if (CheckCollisionPointRec(GetMousePosition(), mathbound) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                currentScreen = MATH;
            if (CheckCollisionPointRec(GetMousePosition(), phybound) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                currentScreen = PHYSICS;
            if (CheckCollisionPointRec(GetMousePosition(), chembound) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                currentScreen = CHEMISTRY;

        } break;

        case MATH:
        {

            if (CheckCollisionPointRec(mousepos, backbound) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                currentScreen = MENU;
            if (correctans)
                currentScreen = ENDING;


        } break;

        case PHYSICS:
        {

            if (CheckCollisionPointRec(mousepos, backbound) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                currentScreen = MENU;
            if (correctans)
                currentScreen = ENDING;
        } break;

        case CHEMISTRY:
        {

            if (CheckCollisionPointRec(mousepos, backbound) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                currentScreen = MENU;
            if (correctans)
                currentScreen = ENDING;
        } break;

        case ENDING:
        {
            if (CheckCollisionPointRec(GetMousePosition(), playbound) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                ResetGame(mathquestions, NUMOFQUESTIONS);
                ResetGame(chemquestions, NUMOFQUESTIONS);
                ResetGame(phyquestions, NUMOFQUESTIONS);
                ResetGame(tutorialquestions, 2);

                currentScreen = TITLE;
            }



            if (CheckCollisionPointRec(GetMousePosition(), exitbound) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                return 0;
        }
        };

        BeginDrawing();
        BeginMode2D(camera);


        switch (currentScreen)
        {
        case LOGO:
        {
            DrawTextEx(textfont, "LOADING...", { 250.0f,(float)height / 2 }, 55, 10, GOLD);

        } break;
        case TITLE:
        {
            camera.target = { 400.0f,350.0f };
            ClearBackground(DARKBROWN);
            DrawTextureEx(Title, { -60.0f,0.0f }, 0.0f, 0.85f, WHITE);
            DrawTextEx(textfont, "Study Escape\n     Room", { 239.0f,235.0f }, 37, 8, WHITE);

            ButtonSetupAndHover(GetMousePosition(), startbound, "Start", textfont, 33, 8, WHITE, BLACK);
            ButtonSetupAndHover(GetMousePosition(), tutorialbound, "Tutorial", textfont, 33, 8, WHITE, BLACK);
        } break;

        case TUTORIAL:
        {

            PageSetupAndGameLogic(tutorial, Player, Player1, 2, tutorialquestions, plant, correctans, wrongans, correct, textfont);
            ButtonSetupAndHover(mousepos, backbound, "BACK", textfont, 30, 3, BLACK, WHITE);
            DrawRectangleRounded({ 515,35,(correctans ? 385.0f : 220.0f) ,40 }, 1.0f, 8, LIGHTGRAY);

            if (correctans)
                DrawTextEx(textfont, "Now you've learned how to play\n go check if you studied!", { 525,32 }, 18, 4, RED);




            else if (tutorialquestions[0].CheckCollisonwithplayer(Player) || tutorialquestions[1].CheckCollisonwithplayer(Player))
                DrawTextEx(textfont, "Answer to leave \nthe rooms!", { 525,35 }, 20, 4, RED);


            else
                DrawTextEx(textfont, "Move and find\nobstacles!", { 525,35 }, 20, 4, RED);


        }break;

        case MENU:
        {
            camera.target = { 400.0f,350.0f };

            DrawTextureEx(Menu, { -60.0f,0.0f }, 0.0f, 0.85f, WHITE);

            ButtonSetupAndHover(mousepos, backbound, "BACK", textfont, 30, 3, BLACK, WHITE);
            ButtonSetupAndHover(GetMousePosition(), mathbound, "   Math", textfont, 30, 3, DARKBROWN, BROWN);
            ButtonSetupAndHover(GetMousePosition(), phybound, " Physics", textfont, 30, 3, DARKBROWN, BROWN);
            ButtonSetupAndHover(GetMousePosition(), chembound, "Chemistry", textfont, 30, 3, DARKBROWN, BROWN);


        } break;

        case MATH:
        {

            PageSetupAndGameLogic(background, Player, Player1, NUMOFQUESTIONS, mathquestions, cactus, correctans, wrongans, correct, textfont);
            ButtonSetupAndHover(mousepos, backbound, "BACK", textfont, 30, 3, BLACK, WHITE);

        } break;

        case PHYSICS:
        {
            PageSetupAndGameLogic(phy, Player, Player1, NUMOFQUESTIONS, phyquestions, phychair, correctans, wrongans, correct, textfont);
            ButtonSetupAndHover(mousepos, backbound, "BACK", textfont, 30, 3, BLACK, WHITE);

        }break;

        case CHEMISTRY:
        {
            PageSetupAndGameLogic(chem, Player, Player1, NUMOFQUESTIONS, chemquestions, flask, correctans, wrongans, correct, textfont);
            ButtonSetupAndHover(mousepos, backbound, "BACK", textfont, 30, 3, WHITE, BLACK);


        }break;


        case ENDING:
        {
            camera.target = { 400.0f,350.0f };

            DrawTextureEx(ending, { -60.0f,0.0f }, 0.0f, 0.85f, WHITE);
            DrawTextEx(textfont, "Well Done!", { 250.0f,250.0f }, 25, 10, DARKBROWN);
            DrawTextEx(textfont, "\nLooks like\nyou studied!", { 250.0f,280.0f }, 25, 10, DARKBROWN);
            ButtonSetupAndHover(GetMousePosition(), playbound, "Play Again", textfont, 40, 10, WHITE, BLACK);
            ButtonSetupAndHover(GetMousePosition(), exitbound, "Exit", textfont, 40, 10, WHITE, BLACK);
        }
        };


        EndMode2D();
        EndDrawing();
    }

    UnloadTexture(Player1);
    UnloadTexture(background);
    UnloadTexture(cactus);
    UnloadTexture(Title);
    UnloadTexture(Button);
    UnloadTexture(Menu);
    UnloadTexture(chem);
    UnloadTexture(flask);
    UnloadTexture(phy);
    UnloadTexture(phychair);
    UnloadTexture(tutorial);
    UnloadTexture(plant);
    UnloadTexture(ending);
    UnloadFont(textfont);
    UnloadSound(wrongans);
    UnloadSound(correct);
    UnloadMusicStream(gamesound);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
